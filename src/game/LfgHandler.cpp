/****************************************************************************
 *
 * LFG System
 *
 */

#include "StdAfx.h"

void WorldSession::HandleSetLookingForGroupComment(WorldPacket& recvPacket)
{
    std::string comment;
        
    recvPacket >> comment;
    
    GetPlayer()->Lfgcomment = comment;    
}

void WorldSession::HandleEnableAutoJoin(WorldPacket& recvPacket)
{
    GetPlayer()->m_Autojoin = true;
}

void WorldSession::HandleDisableAutoJoin(WorldPacket& recvPacket)
{
    GetPlayer()->m_Autojoin = false;    
}

void WorldSession::HandleEnableAutoAddMembers(WorldPacket& recvPacket)
{
    GetPlayer()->m_AutoAddMem = true;
}

void WorldSession::HandleDisableAutoAddMembers(WorldPacket& recvPacket)
{
    GetPlayer()->m_AutoAddMem = false;    
}

void WorldSession::HandleMsgLookingForGroup(WorldPacket& recvPacket)
{
    uint32 LfgType,LfgDungeonId,unk1;
    WorldPacket data;
    std::set<Player*>::iterator itr;
    Player *pl;
    int i=0;
    
    recvPacket >> LfgType >> LfgDungeonId >> unk1;
    
    if(LfgDungeonId >= MAX_DUNGEONS)
        return;
    
    uint32 qsize = sLfgMgr.GetLfgQueueSize(LfgDungeonId);
    
    data.Initialize(MSG_LOOKING_FOR_GROUP);
    data << LfgType << LfgDungeonId;
    data << qsize << qsize;
    
    for(itr = sLfgMgr.GetLfgQueueBegin(LfgDungeonId); itr != sLfgMgr.GetLfgQueueEnd(LfgDungeonId) ; ++itr)
    {
        pl = *itr;
        data << pl->GetNewGUID();
        data << uint32(pl->getLevel());
        data << pl->GetZoneId() << uint8(0);
        for(i=0;i<3;i++)
            data << pl->LfgDungeonId[i] << uint8(0) << pl->LfgType[i];
        
        data << pl->Lfgcomment << uint32(0);
    }   

    SendPacket(&data);
}

void WorldSession::HandleSetLookingForGroup(WorldPacket& recvPacket)
{
    uint32 LfgQueueId;
    uint16 LfgDungeonId;
    uint8 LfgType,unk1;
    
    WorldPacket data;
    
    recvPacket >> LfgQueueId >> LfgDungeonId >> unk1 >> LfgType;
    
    if(LfgDungeonId >= MAX_DUNGEONS || LfgQueueId > 2)
        return;
    
    sLfgMgr.RemoveFromLfgQueue(GetPlayer(),GetPlayer()->LfgDungeonId[LfgQueueId]);
    
    GetPlayer()->LfgDungeonId[LfgQueueId]=LfgDungeonId;
    GetPlayer()->LfgType[LfgQueueId]=LfgType;

    sLfgMgr.SetPlayerInLFGqueue(GetPlayer(),LfgDungeonId);
}

