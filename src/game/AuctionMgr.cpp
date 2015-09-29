#include "StdAfx.h"

initialiseSingleton( AuctionMgr );

void AuctionMgr::LoadAuctionHouses()
{
    sLog.outString("Loading Auction Houses...");

    QueryResult * res = CharacterDatabase.Query("SELECT MAX(auctionId) FROM auctions");
    if(res)
    {
        maxId = res->Fetch()[0].GetUInt32();
        delete res;
    }

    res = WorldDatabase.Query("SELECT DISTINCT AHid FROM auctionhouse ORDER BY AHid");
    AuctionHouse * ah;
    map<uint32, AuctionHouse*> tempmap;
    if(res)
    {
        do
        {
            ah = new AuctionHouse(res->Fetch()[0].GetUInt32());
            ah->LoadAuctions();
            auctionHouses.push_back(ah);
            tempmap.insert( make_pair( res->Fetch()[0].GetUInt32(), ah ) );
        }while(res->NextRow());
        delete res;
    }

    res = WorldDatabase.Query("SELECT auctioneer, AHid FROM auctionhouse");
    if(res)
    {
        do 
        {
            auctionHouseEntryMap.insert( make_pair( res->Fetch()[0].GetUInt32(), tempmap[res->Fetch()[1].GetUInt32()] ) );
        } while(res->NextRow());
        delete res;
    }
}

AuctionHouse * AuctionMgr::GetAuctionHouse(uint32 Entry)
{
    UNORDERED_MAP<uint32, AuctionHouse*>::iterator itr = auctionHouseEntryMap.find(Entry);
    if(itr == auctionHouseEntryMap.end()) return NULL;
    return itr->second;
}

void AuctionMgr::Update()
{
    if((++loopcount % 100))
        return;
        
    vector<AuctionHouse*>::iterator itr = auctionHouses.begin();
    for(; itr != auctionHouses.end(); ++itr)
    {
        (*itr)->UpdateDeletionQueue();

        // Actual auction loop is on a seperate timer.
        if(!(loopcount % 1200))
            (*itr)->UpdateAuctions();
    }
}
