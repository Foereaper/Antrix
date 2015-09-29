#ifndef _GROUP_H_
#define _GROUP_H_

enum PartyErrors
{
    ERR_PARTY_NO_ERROR                  = 0,
    ERR_PARTY_CANNOT_FIND               = 1,
    ERR_PARTY_IS_NOT_IN_YOUR_PARTY      = 2,
    ERR_PARTY_IS_FULL                   = 3,
    ERR_PARTY_ALREADY_IN_GROUP          = 4,
    ERR_PARTY_YOU_ARENT_IN_A_PARTY      = 5,
    ERR_PARTY_YOU_ARE_NOT_LEADER        = 6,
    ERR_PARTY_WRONG_FACTION             = 7,
    ERR_PARTY_IS_IGNORING_YOU           = 8,
};

enum GroupTypes
{
    GROUP_TYPE_PARTY                    = 0,
    GROUP_TYPE_RAID                     = 1,
};

enum MaxGroupCount
{
    MAX_GROUP_SIZE_PARTY                = 5,
    MAX_GROUP_SIZE_RAID                 = 40,
};

enum QuickGroupUpdateFlags
{
    PARTY_UPDATE_FLAG_POSITION            = 1,
    PARTY_UPDATE_FLAG_ZONEID            = 2,
};

class Group;
class Player;

typedef std::set<Player*> GroupMembersSet;

class SubGroup      // Most stuff will be done through here, not through the "Group" class.
{
public:
    friend class Group;

    SubGroup(Group* parent, uint32 id):m_Parent(parent),m_Id(id)
    {
    }

    ~SubGroup();

    inline GroupMembersSet::iterator GetGroupMembersBegin(void) { return m_GroupMembers.begin(); }
    inline GroupMembersSet::iterator GetGroupMembersEnd(void)   { return m_GroupMembers.end();   }

    void AddPlayer(Player *pPlayer);
    void RemovePlayer(Player *pPlayer);
    bool HasMember(uint64 guid);
    

    inline bool IsFull(void)                { return m_GroupMembers.size() >= MAX_GROUP_SIZE_PARTY; }
    inline uint32 GetMemberCount(void)        { return m_GroupMembers.size(); }
    
    inline uint32 GetID(void)               { return m_Id; }
    inline void SetID(uint32 newid)         { m_Id = newid; }

    inline void   SetParent(Group* parent)  { m_Parent = parent; }
    inline Group* GetParent(void)           { return m_Parent; }

    void   Disband(bool bRemoveGroup);

protected:

    GroupMembersSet     m_GroupMembers;
    Group*              m_Parent;
    uint32              m_Id;

    Player*             m_SubGroupLeader;

};

class Group
{
public:
    friend class SubGroup;

    Group();
    ~Group();

    // Adding/Removal Management
    bool AddMember(Player* pPlayer);
    void RemovePlayer(Player* pPlayer);

    // Leaders and Looting
    void SetLeader(Player* pPlayer);
    void SetLooter(Player *pPlayer, uint8 method, uint16 threshold);
    Player* GetnextRRlooter();

    // Transferring data to clients
    void Update();

    void SendPacketToAll(WorldPacket *packet);
    void SendPacketToAllButOne(WorldPacket *packet, Player *pSkipTarget);
    void SendNullUpdate(Player *pPlayer);

    // Group Combat
    void SendPartyKillLog(Object * player, Object * Unit);

    // Destroying/Converting
    void Disband();
    Player* FindFirstPlayer();
    
    // Accessing functions
    inline SubGroup* GetSubGroup(uint32 Id)
    {
        if(Id >= 8)
            return 0;

        return m_SubGroups[Id];
    }

    inline uint32 GetSubGroupCount(void) { return m_SubGroupCount; }

    inline uint8 GetMethod(void) { return m_LootMethod; }
    inline uint8 GetThreshold(void) { return m_LootThreshold; }
    inline Player* GetLeader(void) { return m_Leader; }
    inline Player* GetLooter(void) { return m_Looter; }

    void SetSubGroupLeader(Player *pPlayer, uint8 subgroup);
    void MovePlayer(Player* pPlayer, uint8 subgroup);

    bool HasMember(Player *pPlayer);
    inline uint32 MemberCount(void) { return m_MemberCount; }
    inline bool IsFull() { return ((m_GroupType == GROUP_TYPE_PARTY && m_MemberCount >= MAX_GROUP_SIZE_PARTY) || (m_GroupType == GROUP_TYPE_RAID && m_MemberCount >= MAX_GROUP_SIZE_RAID)); }

    SubGroup* FindFreeSubGroup();

    void ExpandToRaid();

    void SaveToDB();
    void LoadFromDB(Field *fields);

    inline uint8 GetGroupType() { return m_GroupType; }
    inline uint32 GetID() { return m_Id; }

    void UpdateOutOfRangePlayer(Player * pPlayer, uint32 Flags, bool Distribute, WorldPacket * Packet);
    void UpdateAllOutOfRangePlayersFor(Player * pPlayer);
    void HandleUpdateFieldChange(uint32 Index, Player * pPlayer);
    void HandlePartialChange(uint32 Type, Player * pPlayer);

    uint64 m_targetIcons[8];

protected:
    
    Player* m_Leader;
    Player* m_Looter;
    Player* lastRRlooter; //used to determine next RR looter
    uint8 m_LootMethod;
    uint16 m_LootThreshold;
    uint8 m_GroupType;
    uint32 m_Id;

    SubGroup* m_SubGroups[8];
    uint8 m_SubGroupCount;
    uint32 m_MemberCount;
};

#endif  // _GROUP_H_
