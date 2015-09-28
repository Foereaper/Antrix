/****************************************************************************
 *
 * General Object Type File
 *
 */

//
// MapMgr.h
//

#ifndef __MAPMGR_H
#define __MAPMGR_H

class MapCell;
class Map;
class Object;
class MapScriptInterface;
class WorldSession;
class GameObject;
class Creature;
class Player;
class Pet;
class Transporter;
class Corpse;


enum MapMgrTimers
{
	MMUPDATE_OBJECTS = 0,
	MMUPDATE_SESSIONS = 1,
	MMUPDATE_FIELDS = 2,
	MMUPDATE_IDLE_OBJECTS = 3,
	MMUPDATE_ACTIVE_OBJECTS = 4,
	MMUPDATE_COUNT = 5
};

enum ObjectActiveState
{
	OBJECT_STATE_NONE	 = 0,
	OBJECT_STATE_INACTIVE = 1,
	OBJECT_STATE_ACTIVE   = 2,
};

typedef std::set<Object*> ObjectSet;
typedef std::set<Object*> UpdateQueue;
typedef std::set<Player*> PUpdateQueue;
typedef std::set<Player*> PlayerSet;
typedef UNORDERED_MAP<uint32, Object*> StorageMap;
typedef UNORDERED_MAP<uint64, uint64> CombatProgressMap;
typedef set<Creature*> CreatureSet;
typedef set<GameObject*> GameObjectSet;

#define MAX_TRANSPORTERS_PER_MAP 25

class Transporter;
#define RESERVE_EXPAND_SIZE 1024

class SERVER_DECL MapMgr : public CellHandler <MapCell>, public EventableObject,public CThread
{
	friend class UpdateObjectThread;
	friend class ObjectUpdaterThread;
	friend class MapCell;
	friend class MapScriptInterface;
public:
		
	//This will be done in regular way soon

	Mutex m_objectinsertlock;
	ObjectSet m_objectinsertpool;
	void AddObject(Object *);

////////////////////////////////////////////////////////
// Local (mapmgr) storage/generation of GameObjects
/////////////////////////////////////////////
	uint32 m_GOArraySize;
	uint32 m_GOHighGuid;
	GameObject ** m_GOStorage;
	__inline GameObject * CreateGameObject()
	{
		if(++m_GOHighGuid  >= m_GOArraySize)
		{
			// Reallocate array with larger size.
			m_GOArraySize += RESERVE_EXPAND_SIZE;
			m_GOStorage = (GameObject**)realloc(m_GOStorage, sizeof(GameObject*) * m_GOArraySize);
			memset(&m_GOStorage[m_GOHighGuid],0,(m_GOArraySize-m_GOHighGuid)*sizeof(GameObject*));
		}
		return new GameObject(HIGHGUID_GAMEOBJECT, m_GOHighGuid);
	}

	__inline GameObject * GetGameObject(uint32 guid)
	{
		if(guid > m_GOHighGuid)
			return 0;
		return m_GOStorage[guid];
	}

/////////////////////////////////////////////////////////
// Local (mapmgr) storage/generation of Creatures
/////////////////////////////////////////////
	uint32 m_CreatureArraySize;
	uint32 m_CreatureHighGuid;
	Creature ** m_CreatureStorage;
	__inline Creature * CreateCreature()
	{
		if(++m_CreatureHighGuid  >= m_CreatureArraySize)
		{
			// Reallocate array with larger size.
			m_CreatureArraySize += RESERVE_EXPAND_SIZE;
			m_CreatureStorage = (Creature**)realloc(m_CreatureStorage, sizeof(Creature*) * m_CreatureArraySize);
			memset(&m_CreatureStorage[m_CreatureHighGuid],0,(m_CreatureArraySize-m_CreatureHighGuid)*sizeof(Creature*));
		}
		
		return new Creature(HIGHGUID_UNIT, m_CreatureHighGuid);
	}

	__inline Creature * GetCreature(uint32 guid)
	{
		if(guid > m_CreatureHighGuid)
			return 0;
		return m_CreatureStorage[guid];
	}

//////////////////////////////////////////////////////////
// Local (mapmgr) storage/generation of DynamicObjects
////////////////////////////////////////////
	uint32 m_DynamicObjectHighGuid;
	typedef UNORDERED_MAP<uint32, DynamicObject*> DynamicObjectStorageMap;
	DynamicObjectStorageMap m_DynamicObjectStorage;
	__inline DynamicObject * CreateDynamicObject()
	{
		return new DynamicObject(HIGHGUID_DYNAMICOBJECT, ++m_DynamicObjectHighGuid);
	}

	__inline DynamicObject * GetDynamicObject(uint32 guid)
	{
		DynamicObjectStorageMap::iterator itr = m_DynamicObjectStorage.find(guid);
		return (itr != m_DynamicObjectStorage.end()) ? itr->second : 0;
	}

//////////////////////////////////////////////////////////
// Local (mapmgr) storage of pets
///////////////////////////////////////////
	typedef UNORDERED_MAP<uint32, Pet*> PetStorageMap;
	PetStorageMap m_PetStorage;
	__inline Pet * GetPet(uint32 guid)
	{
		PetStorageMap::iterator itr = m_PetStorage.find(guid);
		return (itr != m_PetStorage.end()) ? itr->second : 0;
	}

//////////////////////////////////////////////////////////
// Local (mapmgr) storage of players for faster lookup
////////////////////////////////
	typedef UNORDERED_MAP<uint32, Player*> PlayerStorageMap;
	PlayerStorageMap m_PlayerStorage;
	__inline Player * GetPlayer(uint32 guid)
	{
		PlayerStorageMap::iterator itr = m_PlayerStorage.find(guid);
		return (itr != m_PlayerStorage.end()) ? itr->second : 0;
	}

//////////////////////////////////////////////////////////
// Local (mapmgr) storage of combats in progress
////////////////////////////////
	CombatProgressMap _combatProgress;
	void AddCombatInProgress(uint64 guid)
	{
		_combatProgress[guid] = guid;
	}
	void RemoveCombatInProgress(uint64 guid)
	{
		_combatProgress.erase(guid);
	}

//////////////////////////////////////////////////////////
// Lookup Wrappers
///////////////////////////////////
	Unit * GetUnit(const uint64 & guid);
	Object * _GetObject(const uint64 & guid);

	void run();
	void Do();

	MapMgr(Map *map, uint32 mapid, uint32 instanceid);
	~MapMgr();


	void PushObject(Object *obj);
	void RemoveObject(Object *obj);
	void ChangeObjectLocation(Object *obj); // update inrange lists
	void ChangeFarsightLocation(Player *plr, Creature *farsight);


	//! Mark object as updated
	void ObjectUpdated(Object *obj);
	void UpdateCellActivity(uint32 x, uint32 y, int radius);

	// Terrain Functions
	inline float  GetLandHeight(float x, float y) { return GetBaseMap()->GetTerrainMgr()->GetLandHeight(x, y); }
	inline float  GetWaterHeight(float x, float y) { return GetBaseMap()->GetTerrainMgr()->GetWaterHeight(x, y); }
	inline uint8  GetWaterType(float x, float y) { return GetBaseMap()->GetTerrainMgr()->GetWaterType(x, y); }
	inline uint8  GetWalkableState(float x, float y) { return GetBaseMap()->GetTerrainMgr()->GetWalkableState(x, y); }
	inline uint16 GetAreaID(float x, float y) { return GetBaseMap()->GetTerrainMgr()->GetAreaID(x, y); }

	inline uint32 GetMapId() { return _mapId; }

	void PushToProcessed(Player* plr);

	inline bool HasPlayers() { return (m_PlayerStorage.size() > 0); }
	inline bool IsCombatInProgress() { return (_combatProgress.size() > 0); }
	void TeleportPlayers();

	inline void SetResetPending(bool val) { reset_pending = val; }

	inline uint32 GetInstanceID() { return m_instanceID; }
	inline MapInfo *GetMapInfo() { return pMapInfo; }

	bool _shutdown;

	inline MapScriptInterface * GetInterface() { return ScriptInterface; }
	virtual int32 event_GetInstanceID() { return m_instanceID; }

	void LoadAllCells();
	inline uint32 GetPlayerCount() { return m_PlayerStorage.size(); }

	time_t CreationTime;
	time_t ExpiryTime;
	void _PerformObjectDuties();
	uint32 mLoopCounter;
	uint32 lastGameobjectUpdate;
	uint32 lastUnitUpdate;
	void EventCorpseDespawn(uint64 guid);
	void RespawnMapMgr();

	//Map Mgr Instance functions
	time_t RaidExpireTime;
	void SetCreator(Player *pPlayer);
	uint64 GetCreator() { return m_iCreator; }
	uint32 GetGroupSignature() { return m_GroupSignatureId; }
	void SetGroupSignature(uint32 iGroupSignature) { m_GroupSignatureId = iGroupSignature; }
	bool IsDeletionPending() { return (DeletionPending == true); }
	void SavePlayersToInstance();
	void SetNewExpireTime(time_t creation);
	bool bEncounterInProgress;
	time_t InactiveMoveTime;
    uint32 iInstanceMode;
	bool thread_is_alive;
	bool delete_pending;

protected:

	//! Collect and send updates to clients
	void _UpdateObjects();

private:
	//! Objects that exist on map
 
	uint32 _mapId;

	bool _CellActive(uint32 x, uint32 y);
	void UpdateInRangeSet(Object *obj, Player *plObj, MapCell* cell, ByteBuffer ** buf);

	// Distance a Player can "see" other objects and receive updates from them (!! ALREADY dist*dist !!)
	float m_UpdateDistance;

	/* Update System */
	UpdateQueue _updates;
	PUpdateQueue _processQueue;

	/* Sessions */
	
	SessionSet Sessions;

	/* Map Information */
	MapInfo *pMapInfo;
	uint32 m_instanceID;

	MapScriptInterface * ScriptInterface;
	bool reset_pending;
	bool DeletionPending;
	uint64 m_iCreator;
	uint32 m_GroupSignatureId;

public:
#ifdef WIN32
	DWORD threadid;
#endif
	GameObjectSet activeGameObjects;
	CreatureSet activeCreatures;
	EventableObjectHolder eventHolder;
	Battleground * m_battleground;
};

#endif
