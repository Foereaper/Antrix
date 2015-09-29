#include "StdAfx.h"

enum PartyUpdateFlags
{
    GROUP_UPDATE_FLAG_NONE                        = 0,        // 0x00000000
    GROUP_UPDATE_FLAG_ONLINE                    = 1,        // 0x00000001  uint8
    GROUP_UPDATE_FLAG_HEALTH                    = 2,        // 0x00000002  uint16
    GROUP_UPDATE_FLAG_MAXHEALTH                    = 4,        // 0x00000004  uint16
    GROUP_UPDATE_FLAG_POWER_TYPE                = 8,        // 0x00000008  uint16
    GROUP_UPDATE_FLAG_POWER                        = 16,        // 0x00000010  uint16
    GROUP_UPDATE_FLAG_MAXPOWER                    = 32,        // 0x00000020  uint16
    GROUP_UPDATE_FLAG_LEVEL                        = 64,        // 0x00000040  uint16
    GROUP_UPDATE_FLAG_ZONEID                    = 128,        // 0x00000080  uint16
    GROUP_UPDATE_FLAG_POSITION                    = 256,        // 0x00000100  uint16, uint16
    GROUP_UPDATE_FLAG_UNK_STRANGE                = 512,        // 0x00000200  uint64, uint16 for each uint64
    GROUP_UPDATE_FLAG_UNK_1                        = 1024,        // 0x00000400  uint64
    GROUP_UPDATE_FLAG_PET_NAME                    = 2048,        // 0x00000800  string
    GROUP_UPDATE_FLAG_PET_UNK_1                    = 4096,        // 0x00001000  uint16
    GROUP_UPDATE_FLAG_PET_UNK_2                    = 8192,        // 0x00002000  uint16
    GROUP_UPDATE_FLAG_PET_UNK_3                    = 16384,    // 0x00004000  uint16
    GROUP_UPDATE_FLAG_PET_UNK_4                    = 32768,    // 0x00008000  uint8
    GROUP_UPDATE_FLAG_UNK_3                        = 65535,    // 0x00010000  uint16
    GROUP_UPDATE_FLAG_UNK_4                        = 131070,    // 0x00020000  uint16
    GROUP_UPDATE_FLAG_UNK_5                        = 262144,    // 0x00040000  uint64, uint16 for each uint64
};

enum PartyUpdateFlagGroups
{
    GROUP_UPDATE_TYPE_FULL_CREATE                =    GROUP_UPDATE_FLAG_ONLINE | GROUP_UPDATE_FLAG_HEALTH | GROUP_UPDATE_FLAG_MAXHEALTH |
                                                    GROUP_UPDATE_FLAG_POWER | GROUP_UPDATE_FLAG_LEVEL |
                                                    GROUP_UPDATE_FLAG_ZONEID | GROUP_UPDATE_FLAG_MAXPOWER | GROUP_UPDATE_FLAG_POSITION,
    GROUP_UPDATE_TYPE_FULL_REQUEST_REPLY        =   0x7FFC1800,
};

Group::Group()
{
    m_GroupType = GROUP_TYPE_PARTY;     // Always init as party

    // Create initial subgroup
    m_SubGroups[0] = new SubGroup(this, 0);

    m_Leader = NULL;
    m_Looter = NULL;
    m_LootMethod = 0;
    m_LootThreshold = 2;
    m_SubGroupCount = 1;
    m_MemberCount = 0;

    //EventMgr::getSingleton().AddEvent(this, &Group::UpdatePositions, EVENT_GROUP_POSITION_UPDATE, 5000, 0);
    m_Id = objmgr.GenerateGroupId();
    ObjectMgr::getSingleton().AddGroup(this);
    lastRRlooter = NULL;
}

Group::~Group()
{
    // SAFE
    //EventMgr::getSingleton().RemoveEvents(this);
    ObjectMgr::getSingleton().RemoveGroup(this);
}

SubGroup::~SubGroup()
{
    GroupMembersSet::iterator itr = m_GroupMembers.begin();
    for(; itr != m_GroupMembers.end(); ++itr)
    {
        (*itr)->SetSubGroup(0);
    }

    m_GroupMembers.clear();
}

bool SubGroup::HasMember(uint64 guid)
{
    for(GroupMembersSet::iterator itr = m_GroupMembers.begin(); itr != m_GroupMembers.end(); ++itr)
       if((*itr)->GetGUID()==guid) return true;

    return false;
}

void SubGroup::RemovePlayer(Player *pPlayer)
{
    GroupMembersSet::iterator itr = m_GroupMembers.find(pPlayer);
    if(itr != m_GroupMembers.end())
    {
        sLog.outDebug("GROUP: Removing player %s from subgroup %d", pPlayer->GetName(), m_Id);
        m_GroupMembers.erase(itr);
    }
    else
    {
        sLog.outDebug("GROUP: Tried to remove player %s from subgroup %d but he does not exist!", pPlayer->GetName(), m_Id);
    }
    pPlayer->SetSubGroup(0);
    m_Parent->m_MemberCount--;

    if(m_SubGroupLeader == pPlayer)
    {
        // Assign new subgroup leader
        if(m_GroupMembers.size() > 0)
            m_SubGroupLeader = (*m_GroupMembers.begin());
        else
            m_SubGroupLeader = NULL;
    }
}

void SubGroup::AddPlayer(Player* pPlayer)
{
    sLog.outDebug("GROUP: Adding player %s to subgroup %d", pPlayer->GetName(), m_Id);
    if(m_GroupMembers.size() == 0)
        m_SubGroupLeader = pPlayer;

    m_GroupMembers.insert(pPlayer);
    pPlayer->SetSubGroup(GetID());
    m_Parent->m_MemberCount++;
}

SubGroup * Group::FindFreeSubGroup()
{
    for(uint32 i = 0; i < m_SubGroupCount; i++)
        if(!m_SubGroups[i]->IsFull())
            return m_SubGroups[i];

    return NULL;
}

bool Group::AddMember(Player* pPlayer)
{
    if(!IsFull())
    {
        SubGroup* subgroup = FindFreeSubGroup();
        if(subgroup == NULL)
        {
            // weird shit..
            sLog.outDebug("GROUP: Tried to add member %s but FindFreeSubGroup returned NULL!", pPlayer->GetName());
            return false;
        }

        subgroup->AddPlayer(pPlayer);
        pPlayer->SetGroup(this);

        if(m_MemberCount == 1)
        {
            // We're the only member? Set us to the leader.
            SetLeader(pPlayer);
        }        

        UpdateAllOutOfRangePlayersFor(pPlayer);
        Update();    // Send group update

        return true;

    }
    else
    {
        return false;
    }
}

void Group::SetLeader(Player* pPlayer)
{
    m_Leader = pPlayer;
    WorldPacket *data = new WorldPacket;
    data->Initialize(SMSG_GROUP_SET_LEADER);
    *data << pPlayer->GetName();

    SendPacketToAll(data);
    delete data;

    Update();
}

void Group::Update()
{
    WorldPacket data(50 + (m_MemberCount * 20));
    GroupMembersSet::iterator itr1, itr2;

    uint32 i=0,j=0;
    SubGroup *sg1=NULL;
    SubGroup *sg2=NULL;

    for(i=0;i<m_SubGroupCount;i++)
    {
        sg1 = m_SubGroups[i];
        for(itr1 = sg1->GetGroupMembersBegin(); itr1!=sg1->GetGroupMembersEnd(); ++itr1)
        {
            /*          Check for Soulstone Caster            */
            /*          SoulStone effect removed if           */
            /* the giver and reciever are not in party / raid */
            bool removeSoulStone = true;
            uint32 SoulStoneGiver = (*itr1)->SoulStoneReciever;
            if(!SoulStoneGiver || (*itr1)->GetGUID() == SoulStoneGiver) removeSoulStone = false;

            data.Initialize(SMSG_GROUP_LIST);
            data << uint8(m_GroupType);    //0=party,1=raid
            data << uint8(0);   // unk
            data << uint8(sg1->GetID());
            data << uint8(0);    // unk2
            data << uint64(0);    // unk3
            data << uint32(m_MemberCount-1);    // we don't include self
            for(j=0;j<m_SubGroupCount;j++)
            {
                sg2 = m_SubGroups[j];
                for(itr2 = sg2->GetGroupMembersBegin(); itr2 != sg2->GetGroupMembersEnd(); ++itr2)
                {
                    if((*itr1) != (*itr2))
                    {
                        /*check the reciever id against all group members*/
                        if((*itr2)->GetGUID() == SoulStoneGiver) removeSoulStone = false;

                        data << (*itr2)->GetName() << (*itr2)->GetGUID();
                        data << uint8(1);                                  // online/offline flag maybe?
                        /*if(m_GroupType == GROUP_TYPE_RAID && (*itr2) == sg2->m_SubGroupLeader)
                            data << uint8(80 + sg2->GetID());
                        else*/      // how do we do this? 80 obviously doesn't work.
                            data << uint8(sg2->GetID());
                        data << uint8(0);
                    }
                }
            }

            if(m_Leader != NULL) data << m_Leader->GetGUID();
            else data << uint64(0);

            data << uint8(m_LootMethod);

            if(m_Looter != NULL) data << m_Looter->GetGUID();
            else data << uint64(0);

            data << uint16(m_LootThreshold);

            /*data << uint64(0);      // new in 2.0.3, dunno what it is
            data << uint64(0);      // new in 2.0.3, dunno what it is*/
            
            (*itr1)->GetSession()->SendPacket(&data);

            /* remove Soulstone Aura if the caster and recipient */
            /*        are not in the same group any more         */
            if(removeSoulStone)
                (*itr1)->removeSoulStone();
        }        
    }
}

void Group::Disband()
{
    uint32 i = 0;
    for(i = 0; i < m_SubGroupCount; i++)
    {
        SubGroup *sg = m_SubGroups[i];
        sg->Disband(true);
    }

    delete this;    // destroy ourselves, the destructor removes from eventmgr and objectmgr.
}

void SubGroup::Disband(bool bRemoveGroup)
{
    WorldPacket data;
    data.SetOpcode(SMSG_GROUP_DESTROYED);

    WorldPacket data2;
    data2.SetOpcode(SMSG_PARTY_COMMAND_RESULT);
    data2 << uint32(2) << uint8(0) << uint32(0);    // you leave the group

    GroupMembersSet::iterator itr = m_GroupMembers.begin();
    for(; itr != m_GroupMembers.end(); ++itr)
    {
        (*itr)->GetSession()->SendPacket(&data);
        (*itr)->GetSession()->SendPacket(&data2);
        (*itr)->SetSubGroup(0);
        m_Parent->m_MemberCount--;

        if(bRemoveGroup)
        {
            (*itr)->SetGroup(NULL);
            m_Parent->SendNullUpdate((*itr));
        }
        /* remove SoulStones if caster and reciever are not the same player */
        if((*itr)->SoulStoneReciever && (*itr)->SoulStoneReciever!=(*itr)->GetGUID())
            (*itr)->removeSoulStone();
    }

    m_Parent->m_SubGroups[m_Id] = NULL;
    delete this;
}

Player* Group::FindFirstPlayer()
{
//    SubGroup *sg = NULL;
    GroupMembersSet::iterator itr;

    uint32 i = 0;
    for(; i < m_SubGroupCount; i++)
        for(itr = m_SubGroups[i]->GetGroupMembersBegin(); itr != m_SubGroups[i]->GetGroupMembersEnd(); ++itr)
            return (*itr);   // return first

    return NULL;
}

void Group::RemovePlayer(Player* pPlayer)
{
    WorldPacket data;
    
    SubGroup *sg = GetSubGroup(pPlayer->GetSubGroup());
    ASSERT(sg); // something wrong here if that isn't right

    sg->RemovePlayer(pPlayer);
    pPlayer->SetGroup(NULL);
    if(pPlayer->GetSession() != NULL)
    {
        SendNullUpdate(pPlayer);

        //pPlayer->RemoveAllAreaAuras();

        data.SetOpcode(SMSG_GROUP_DESTROYED);
        pPlayer->GetSession()->SendPacket(&data);

        data.Initialize(SMSG_PARTY_COMMAND_RESULT);
        data << uint32(2) << uint8(0) << uint32(0);  // you leave the group
        pPlayer->GetSession()->SendPacket(&data);
    }

    if(m_MemberCount < 2)
    {
        Disband();
        return;
    }

    Player *newPlayer = FindFirstPlayer();

    if(m_Looter == pPlayer)
        m_Looter = newPlayer;

    if(m_Leader == pPlayer)
        SetLeader(newPlayer);
    else
        Update();
}

void Group::SendPacketToAll(WorldPacket *packet)
{
    SendPacketToAllButOne(packet, NULL);
}

void Group::ExpandToRaid()
{
    // Very simple ;)

    uint32 i = 1;
    m_SubGroupCount = 8;

    for(; i < m_SubGroupCount; i++)
        m_SubGroups[i] = new SubGroup(this, i);

    m_GroupType = GROUP_TYPE_RAID;
    Update();
}

void Group::SetLooter(Player *pPlayer, uint8 method, uint16 threshold)
{ 
    m_LootMethod = method;
    m_Looter = pPlayer;
    m_LootThreshold  = threshold;
    Update();
}

//!! function is not fair. If new player pops in/out he might get a piece of the action to soon or let first player get more loots :)
Player* Group::GetnextRRlooter()
{
    //another methode would be to directly store a node from list so we can jump directly to next one. But that is not safe :P
    GroupMembersSet::iterator itr1;
    Player *firsthit=NULL,*prevp=NULL;
    for(int i = 0; i < m_SubGroupCount; i++)
    {
        for(itr1 = m_SubGroups[i]->GetGroupMembersBegin(); itr1 != m_SubGroups[i]->GetGroupMembersEnd(); ++itr1)
        {
            if(firsthit==NULL)
                firsthit = (*itr1);
            if(prevp==lastRRlooter)
                return (*itr1);
            prevp = (*itr1);
        }
    }
    //if we got here it means player eighter exited group or it was last one
    return firsthit;
}

void Group::SendPacketToAllButOne(WorldPacket *packet, Player *pSkipTarget)
{
    GroupMembersSet::iterator itr;
    uint32 i = 0;
    for(; i < m_SubGroupCount; i++)
        for(itr = m_SubGroups[i]->GetGroupMembersBegin(); itr != m_SubGroups[i]->GetGroupMembersEnd(); ++itr)
            if((*itr) != pSkipTarget) (*itr)->GetSession()->SendPacket(packet);
}

bool Group::HasMember(Player * pPlayer)
{
    GroupMembersSet::iterator itr;
    uint32 i = 0;
    for(; i < m_SubGroupCount; i++)
        for(itr = m_SubGroups[i]->GetGroupMembersBegin(); itr != m_SubGroups[i]->GetGroupMembersEnd(); ++itr)
            if((*itr) == pPlayer) return true;

    return false;
}

void Group::MovePlayer(Player *pPlayer, uint8 subgroup)
{
    ASSERT(subgroup < m_SubGroupCount);
    SubGroup *sgr = GetSubGroup(pPlayer->GetSubGroup());
    
    sgr->RemovePlayer(pPlayer);

    // Grab the new group, and insert
    sgr = m_SubGroups[subgroup];
    sgr->AddPlayer(pPlayer);

    Update();
}

void Group::SetSubGroupLeader(Player *pPlayer, uint8 subgroup)
{
    sLog.outString("Set subgroup %d leader to %s", (uint32)subgroup, pPlayer->GetName());
    ASSERT(subgroup < m_SubGroupCount);
    SubGroup *group = m_SubGroups[subgroup];
    if(group->GetID() != pPlayer->GetSubGroup())
    {
        sLog.outString("GROUP: Tried to set leader of subgroup %d and player %s is not in that group", group->GetID(), pPlayer->GetName());
        return;
    }

    group->m_SubGroupLeader = pPlayer;
    Update();
}

void Group::SendNullUpdate(Player *pPlayer)
{
    // this packet is 24 bytes long.        // AS OF 2.1.0
    uint8 buffer[24];
    memset(buffer, 0, 24);
    pPlayer->GetSession()->OutPacket(SMSG_GROUP_LIST, 24, buffer);
}

// player is object class becouse its called from unit class
void Group::SendPartyKillLog(Object * player, Object * Unit)
{
    if (!player || !Unit || !HasMember(((Player*)player)))
        return;

    WorldPacket data(SMSG_PARTYKILLLOG, 16);
    data << player->GetGUID();
    data << Unit->GetGUID();
    SendPacketToAll(&data);
}

void Group::LoadFromDB(Field *fields)
{
    m_Id = fields[0].GetUInt32();
//    uint64 leader = fields[1].GetUInt64();
    //uint64 looter = fields[2].GetUInt64();
    m_LootMethod = fields[3].GetUInt32();
    m_LootThreshold = fields[4].GetUInt32();
    m_GroupType = fields[5].GetUInt32();
    m_SubGroupCount = fields[6].GetUInt32();
    // create groups
    for(int i = 1; i < m_SubGroupCount; ++i)
        m_SubGroups[i] = new SubGroup(this, i);

    // assign players into groups
    for(int i = 0; i < m_SubGroupCount; ++i)
    {
        std::string memberguids = fields[7+i].GetString();
    }
}

void Group::UpdateOutOfRangePlayer(Player * pPlayer, uint32 Flags, bool Distribute, WorldPacket * Packet)
{
    WorldPacket * data = Packet;
    if(!Packet)
        data = new WorldPacket(SMSG_PARTY_MEMBER_STATS, 500);

    if(pPlayer->GetPowerType() != POWER_TYPE_MANA)
        Flags |= GROUP_UPDATE_FLAG_POWER_TYPE;

    /*Flags |= GROUP_UPDATE_FLAG_PET_NAME;
    Flags |= GROUP_UPDATE_FLAG_PET_UNK_1;*/

    data->Initialize(SMSG_PARTY_MEMBER_STATS);
    *data << pPlayer->GetNewGUID();
    *data << Flags;

    if(Flags & GROUP_UPDATE_FLAG_ONLINE)
    {
        if(pPlayer->IsPvPFlagged())
            *data << uint8(3);
        else
            *data << uint8(1);
    }

    if(Flags & GROUP_UPDATE_FLAG_HEALTH)
        *data << uint16(pPlayer->GetUInt32Value(UNIT_FIELD_HEALTH));

    if(Flags & GROUP_UPDATE_FLAG_MAXHEALTH)
        *data << uint16(pPlayer->GetUInt32Value(UNIT_FIELD_MAXHEALTH));

    if(Flags & GROUP_UPDATE_FLAG_POWER_TYPE)
        *data << uint8(pPlayer->GetPowerType());

    if(Flags & GROUP_UPDATE_FLAG_POWER)
        *data << uint16(pPlayer->GetUInt32Value(UNIT_FIELD_POWER1 + pPlayer->GetPowerType()));

    if(Flags & GROUP_UPDATE_FLAG_MAXPOWER)
        *data << uint16(pPlayer->GetUInt32Value(UNIT_FIELD_MAXPOWER1 + pPlayer->GetPowerType()));

    if(Flags & GROUP_UPDATE_FLAG_LEVEL)
        *data << uint16(pPlayer->getLevel());

    if(Flags & GROUP_UPDATE_FLAG_ZONEID)
        *data << uint16(pPlayer->GetZoneId());

    if(Flags & GROUP_UPDATE_FLAG_POSITION)
    {
        *data << int16(pPlayer->GetPositionX()) << int16(pPlayer->GetPositionY());            // wtf packed floats? O.o
        pPlayer->m_last_group_position = pPlayer->GetPosition();
    }

    if(Flags & GROUP_UPDATE_TYPE_FULL_REQUEST_REPLY)
    {
        // Full update - we have to put some weird extra shit on the end :/
        
        /*
        {SERVER} Packet: (0x02F2) CMSG_PET_UNLEARN PacketSize = 46

        07 EB BB 69 - guid
        F7 1B FC 7F - mask - 1111111111111000001101111110111 - full
        // known parts
        0000000000000000000000000000001 - online
        0000000000000000000000000000010 - health
        0000000000000000000000000000100 - max health
        0000000000000000000000000010000 - power
        0000000000000000000000000100000 - max power
        0000000000000000000000001000000 - level
        0000000000000000000000010000000 - zoneid
        0000000000000000000000100000000 - level
        0000000000000000000001000000000 - position

        // unknown parts
        1111111111111000001101111110111 - full
        0000000000001000000000000000000 - GROUP_UPDATE_FLAG_UNK_5 = 262144,    // 0x00040000  uint64, uint16 for each uint64
        1111111111111000000000000000000 - 

        03 - online
        7D 02 - health
        0E 04 - max health
        37 05 - power
        BA|07 - max power
        1B 00 - level
        28 00 - zoneid
        39 D8 B9 03 - position

        -- this is what we append on the end of a full update.. no idea what is is
        01 00 00 00
        00 00 00 FF
        4A 78 00 58
        26 00 00 00
        00 00 00 00
        FF
        -------------------------------------------------------------------

        */
        *data << uint32(0x00000001);
        *data << uint32(0xFF000000);
        *data << uint32(0x5800784A);
        *data << uint32(0x00000026);
        *data << uint32(0x00000000);
        *data << uint8(0xFF);
    }

    if(Distribute)
    {
        Player * plr;
        for(uint32 i = 0; i < m_SubGroupCount; ++i)
        {
            for(GroupMembersSet::iterator itr = m_SubGroups[i]->GetGroupMembersBegin(); itr != m_SubGroups[i]->GetGroupMembersEnd(); ++itr)
            {
                plr = *itr;
                if(plr != pPlayer && !plr->IsVisible(pPlayer))
                    plr->GetSession()->SendPacket(data);
            }
        }
    }

    if(!Packet)
        delete data;
}

void Group::UpdateAllOutOfRangePlayersFor(Player * pPlayer)
{
    WorldPacket data(150);
    WorldPacket data2(150);

    /* tell the other players about us */
    UpdateOutOfRangePlayer(pPlayer, GROUP_UPDATE_TYPE_FULL_CREATE, true, &data2);

    /* tell us any other players we don't know about */
    Player * plr;
    for(uint32 i = 0; i < m_SubGroupCount; ++i)
    {
        for(GroupMembersSet::iterator itr = m_SubGroups[i]->GetGroupMembersBegin(); itr != m_SubGroups[i]->GetGroupMembersEnd(); ++itr)
        {
            plr = *itr;
            if(plr == pPlayer) continue;

            if(!plr->IsVisible(pPlayer))
            {
                UpdateOutOfRangePlayer(plr, GROUP_UPDATE_TYPE_FULL_CREATE, false, &data);
                pPlayer->GetSession()->SendPacket(&data);
            }
        }
    }
}

void Group::HandleUpdateFieldChange(uint32 Index, Player * pPlayer)
{
    uint32 Flags = 0;
    switch(Index)
    {
    case UNIT_FIELD_HEALTH:
        Flags = GROUP_UPDATE_FLAG_HEALTH;
        break;
        
    case UNIT_FIELD_MAXHEALTH:
        Flags = GROUP_UPDATE_FLAG_MAXHEALTH;
        break;

    case UNIT_FIELD_POWER1:
    case UNIT_FIELD_POWER2:
    case UNIT_FIELD_POWER3:
    case UNIT_FIELD_POWER4:
        Flags = GROUP_UPDATE_FLAG_POWER;
        break;

    case UNIT_FIELD_MAXPOWER1:
    case UNIT_FIELD_MAXPOWER2:
    case UNIT_FIELD_MAXPOWER3:
    case UNIT_FIELD_MAXPOWER4:
        Flags = GROUP_UPDATE_FLAG_MAXPOWER;
        break;

    case UNIT_FIELD_LEVEL:
        Flags = GROUP_UPDATE_FLAG_LEVEL;
        break;
    }

    if(Flags)
        UpdateOutOfRangePlayer(pPlayer, Flags, true, 0);
}

void Group::HandlePartialChange(uint32 Type, Player * pPlayer)
{
    uint32 Flags = 0;
    switch(Type)
    {
    case PARTY_UPDATE_FLAG_POSITION:
        Flags = GROUP_UPDATE_FLAG_POSITION;
        break;

    case PARTY_UPDATE_FLAG_ZONEID:
        Flags = GROUP_UPDATE_FLAG_ZONEID;
        break;
    }

    if(Flags)
        UpdateOutOfRangePlayer(pPlayer, Flags, true, 0);
}

void WorldSession::HandlePartyMemberStatsOpcode(WorldPacket & recv_data)
{
    if(!_player->IsInWorld())
        return;

    uint64 guid;
    recv_data >> guid;

    Player * plr = _player->GetMapMgr()->GetPlayer(guid);

    if(!_player->GetGroup() || !plr)
        return;

    WorldPacket data(200);
    if(!_player->GetGroup()->HasMember(plr))
        return;            // invalid player

    _player->GetGroup()->UpdateOutOfRangePlayer(plr, GROUP_UPDATE_TYPE_FULL_CREATE | GROUP_UPDATE_TYPE_FULL_REQUEST_REPLY, false, &data);
    data.SetOpcode(CMSG_PET_UNLEARN);
    SendPacket(&data);
}

