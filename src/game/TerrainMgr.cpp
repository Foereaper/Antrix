/****************************************************************************
 *
 * General Object Type File
 *
 */

#include "StdAfx.h"
#include <fcntl.h>
#include "TerrainMgr.h"

TerrainMgr::TerrainMgr(string MapPath, uint32 MapId, bool Instanced) : mapPath(MapPath), mapId(MapId), Instance(Instanced)
{
    // Allocate both storage arrays.
    CellInformation = new CellTerrainInformation**[_sizeX];
    for(uint32 x = 0; x < _sizeX; ++x)
    {
        CellInformation[x] = new CellTerrainInformation*[_sizeY];
        for(uint32 y = 0; y < _sizeY; ++y)
        {
            // Clear the pointer.
            CellInformation[x][y] = 0;
            CellOffsets[x][y] = 0;
        }
    }

    // Load the file.
    LoadTerrainHeader();
}

TerrainMgr::~TerrainMgr()
{
#ifndef USE_MEMORY_MAPPING_FOR_MAPS
    if(FileDescriptor)
    {
        // Free up our file pointer.
        mutex.Acquire();
        fclose(FileDescriptor);
        mutex.Release();
    }

    // Big memory cleanup, whee.
    for(uint32 x = 0; x < _sizeX; ++x)
    {
        for(uint32 y = 0; y < _sizeY; ++y)
        {
            if(CellInformation[x][y] != 0)
                delete CellInformation[x][y];
        }
        delete [] CellInformation[x];
    }
    delete CellInformation;
#else

    mutex.Acquire();

    // Big memory cleanup, whee.
    for(uint32 x = 0; x < _sizeX; ++x)
    {
        for(uint32 y = 0; y < _sizeY; ++y)
        {
            if(CellInformation[x][y] != 0)
            {
#ifdef WIN32
                UnmapViewOfFile((LPCVOID)CellInformation[x][y]);
#else
#error moo
#endif
            }        
        }
        delete [] CellInformation[x];
    }
    delete CellInformation;

#ifdef WIN32
    UnmapViewOfFile((LPCVOID)CellOffsets);
    CloseHandle(hMap);
    CloseHandle(hMappedFile);
#else
#error moo
#endif
    mutex.Release();
#endif
}

bool TerrainMgr::LoadTerrainHeader()
{
    // Create the path
    char File[200];

    snprintf(File, 200, "%s/Map_%u.bin", mapPath.c_str(), (unsigned int)mapId);

#ifndef USE_MEMORY_MAPPING_FOR_MAPS

    FileDescriptor = fopen(File, "rb");

    if(FileDescriptor == 0)
    {
        sLog.outError("Could not load map file header for %s.", File);
        return false;
    }

    // Read in the header.
    if(fread(CellOffsets, TERRAIN_HEADER_SIZE, 1, FileDescriptor) < 1)
        return false;

    return true;

#else

#ifdef WIN32
    
    hMappedFile = CreateFile(File, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
    if(hMappedFile == INVALID_HANDLE_VALUE)
        return false;

    DWORD bytes;
    ASSERT(ReadFile(hMappedFile, CellOffsets, TERRAIN_HEADER_SIZE, &bytes, NULL));
    ASSERT(bytes == TERRAIN_HEADER_SIZE);
    SetFilePointer(hMappedFile, 0, 0, FILE_END);

    mFileSize = GetFileSize(hMappedFile, NULL);
    hMap = CreateFileMapping(hMappedFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if(hMap == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hMappedFile);
        hMappedFile = INVALID_HANDLE_VALUE;
        return false;
    }

    // Map the terrain header
    //CellOffsets = (uint32**)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, TERRAIN_HEADER_SIZE);
    //memcpy(temp, CellOffsets, TERRAIN_HEADER_SIZE);

#else
#error unimplemented in *nix
#endif
    return true;
#endif
}

bool TerrainMgr::LoadCellInformation(uint32 x, uint32 y)
{
#ifdef USE_MEMORY_MAPPING_FOR_MAPS
    if(!CellOffsets)
        return false;
#else
    if(!FileDescriptor)
        return false;
#endif

    // Make sure that we're not already loaded.
    assert(CellInformation[x][y] == 0);

    // Find our offset in our cached header.
    uint32 Offset = CellOffsets[x][y];

    // If our offset = 0, it means we don't have cell information for 
    // these coords.
    if(Offset == 0)
        return false;

    // Lock the mutex to prevent double reading.
    mutex.Acquire();

    // Check that we haven't been loaded by another thread.
    if(CellInformation[x][y] != 0)
    {
        mutex.Release();
        return true;
    }
    
#ifdef USE_MEMORY_MAPPING_FOR_MAPS
    #ifdef WIN32
        if(Offset >= mFileSize)
        {
            mutex.Release();
            return false;
        }

        CellInformation[x][y] = (CellTerrainInformation*)MapViewOfFile(hMap, FILE_MAP_READ, 0, Offset, sizeof(CellTerrainInformation));
    #else
        #error moo
    #endif
#else
    // Seek to our specified offset.
    if(fseek(FileDescriptor, Offset, SEEK_SET) == 0)
    {
        // Allocate the cell information.
        CellInformation[x][y] = new CellTerrainInformation;

        // Read from our file into this newly created struct.
        fread(CellInformation[x][y], sizeof(CellTerrainInformation), 1, FileDescriptor);
    }
#endif
    // Release the mutex.
    mutex.Release();

    // If we don't equal 0, it means the load was successful.
    if(CellInformation[x][y] != 0)
        return true;
    else
        return false;
}

bool TerrainMgr::UnloadCellInformation(uint32 x, uint32 y)
{
    uint32 Start = getMSTime();

    assert(!Instance);
    // Find our information pointer.
    CellTerrainInformation * ptr = CellInformation[x][y];
    assert(ptr != 0);

    // Set the spot to unloaded (null).
    CellInformation[x][y] = 0;
#ifdef USE_MEMORY_MAPPING_FOR_MAPS
    #ifdef WIN32
        if(!UnmapViewOfFile((LPCVOID)ptr))
            Log.Error("TerrainMgr", "Could not unmap view of file at memory address 0x%.8X", ptr);
    #else
        #error moo
    #endif
#else
    // Free the memory.
    delete ptr;
#endif

    sLog.outDetail("Unloaded cell information for cell [%u][%u] in %ums.", x, y, getMSTime() - Start);
    // Success
    return true;
}

uint8 TerrainMgr::GetWaterType(float x, float y)
{
    if(!AreCoordinatesValid(x, y))
        return 0;

    // Convert the co-ordinates to cells.
    uint32 CellX = ConvertGlobalXCoordinate(x);
    uint32 CellY = ConvertGlobalYCoordinate(y);

    if(!CellInformationLoaded(CellX, CellY))
        return 0;

    // Convert the co-ordinates to cell's internal
    // system.
    float IntX = ConvertInternalXCoordinate(x, CellX);
    float IntY = ConvertInternalYCoordinate(y, CellY);

    // Find the offset in the 2d array.
    return GetCellInformation(CellX, CellY)->LiquidType[ConvertTo2dArray(IntX)][ConvertTo2dArray(IntY)];
}

float TerrainMgr::GetWaterHeight(float x, float y)
{
    if(!AreCoordinatesValid(x, y))
        return 0.0f;

    // Convert the co-ordinates to cells.
    uint32 CellX = ConvertGlobalXCoordinate(x);
    uint32 CellY = ConvertGlobalYCoordinate(y);

    if(!CellInformationLoaded(CellX, CellY))
        return 0.0f;

    // Convert the co-ordinates to cell's internal
    // system.
    float IntX = ConvertInternalXCoordinate(x, CellX);
    float IntY = ConvertInternalYCoordinate(y, CellY);

    // Find the offset in the 2d array.
    return GetCellInformation(CellX, CellY)->LiquidLevel[ConvertTo2dArray(IntX)][ConvertTo2dArray(IntY)];
}

uint8 TerrainMgr::GetWalkableState(float x, float y)
{
    // This has to be implemented.
    return 1;
}

uint16 TerrainMgr::GetAreaID(float x, float y)
{
    if(!AreCoordinatesValid(x, y))
        return 0;

    // Convert the co-ordinates to cells.
    uint32 CellX = ConvertGlobalXCoordinate(x);
    uint32 CellY = ConvertGlobalYCoordinate(y);

    if(!CellInformationLoaded(CellX, CellY) && !LoadCellInformation(CellX, CellY))
        return 0;

    // Convert the co-ordinates to cell's internal
    // system.
    float IntX = ConvertInternalXCoordinate(x, CellX);
    float IntY = ConvertInternalYCoordinate(y, CellY);

    // Find the offset in the 2d array.
    return GetCellInformation(CellX, CellY)->AreaID[ConvertTo2dArray(IntX)][ConvertTo2dArray(IntY)];
}

float TerrainMgr::GetLandHeight(float x, float y)
{
    if(!AreCoordinatesValid(x, y))
        return 0.0f;

    // Convert the co-ordinates to cells.
    uint32 CellX = ConvertGlobalXCoordinate(x);
    uint32 CellY = ConvertGlobalYCoordinate(y);

    if(!CellInformationLoaded(CellX, CellY) && !LoadCellInformation(CellX, CellY))
        return 0.0f;

    // Convert the co-ordinates to cell's internal
    // system.
    float IntX = ConvertInternalXCoordinate(x, CellX);
    float IntY = ConvertInternalYCoordinate(y, CellY);

    // Calculate x index.
    float TempFloat = IntX * (MAP_RESOLUTION / CellsPerTile / _cellSize);
    uint32 XOffset = FL2UINT(TempFloat);
    if((TempFloat - (XOffset * _cellSize)) >= 0.5f)
        ++XOffset;

    // Calculate y index.
    TempFloat = IntY * (MAP_RESOLUTION / CellsPerTile / _cellSize);
    uint32 YOffset = FL2UINT(TempFloat);
    if((TempFloat - (YOffset * _cellSize)) >= 0.5f)
        ++YOffset;

    // Return our cached information.
    return GetCellInformation(CellX, CellY)->Z[XOffset][YOffset];
}

void TerrainMgr::CellGoneActive(uint32 x, uint32 y)
{
    // Load cell information if it's not already loaded.
    if(!CellInformationLoaded(x, y))
        LoadCellInformation(x, y);
}

void TerrainMgr::CellGoneIdle(uint32 x, uint32 y)
{
    // If we're not an instance, unload our cell info.
    if(!Instance && CellInformationLoaded(x, y) && sWorld.UnloadMapFiles)
        UnloadCellInformation(x, y);
}
