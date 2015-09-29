/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef _OBJECTMGR_H
#define _OBJECTMGR_H
#include "../shared/Threading/RWLock.h"

inline bool FindXinYString(std::string& x, std::string& y)
{
    return y.find(x) != std::string::npos;
}

enum SpellSpecialType
{
    NOTHING=0,
    SEAL=1,
    BLESSING=2,
    CURSE=3,
    ASPECT=4,
    STING=5,
};

struct SpellExtraInfo
{
    uint32 Id;
    uint32 specialtype;
    uint32 enchantableslots;
    uint32 ExtraFlags;
};

struct GM_Ticket
{
    uint64 guid;
    std::string name;
    uint32 level;
    uint32 type;
    float posX;
    float posY;
    float posZ;
    std::string message;
    uint32 timestamp;
};

struct ThreatToSpellId
{
    uint32 spellId;
    int32 mod;
};

struct TrainerSpellOverride
{
    uint32 SpellID;
    uint32 Cost;
    uint32 RequiredSpell;
    uint32 DeleteSpell;
    uint32 RequiredSkill;
    uint32 RequiredSkillValue;
    uint8 RequiredLevel;
    int32 RequiredClass;
};

struct FishingZoneEntry
{
    uint32 ZoneID;
    uint32 MinSkill;
    uint32 MaxSkill;
};

struct ItemPage
{
    uint32 id;
    char * text;
    uint32 next_page;
};

struct SpellReplacement
{
    uint32 count;
    uint32 *spells;
};

class Group;

struct GossipMenuItem
{
    uint32 Id;
    uint32 IntId;
    uint16 Icon;
    string Text;
};

struct SpellEntry;
struct TrainerSpell
{

    uint32 SpellID;
    SpellEntry* pSpell;

    uint32 SpellRank;
    
    uint32 RequiredSpell;
    uint32 DeleteSpell;

    uint32 RequiredSkillLine;
    uint32 RequiredSkillLineValue;
    uint32 TeachingLine;
    uint32 IsProfession;

    uint32 Cost;
    uint32 RequiredLevel;

    uint32 SpellType;
    uint32 TeachingSpellID;
    SpellEntry* pTrainingSpell;

    int32 RequiredClass;
};

struct Trainer
{
    uint32 SpellCount;
    TrainerSpell** SpellList;

    char* TalkMessage;
    uint32 TrainerType;
    uint32 RequiredClass;
};

struct LevelInfo
{
    uint32 HP;
    uint32 Mana;
    uint32 Stat[5];
    uint32 XPToNextLevel;
};

struct ReputationMod
{
    uint32 faction[2];
    int32 value;
    uint32 replimit;
};

struct InstanceReputationMod
{
    uint32 mapid;
    uint32 mob_rep_reward;
    uint32 mob_rep_limit;
    uint32 boss_rep_reward;
    uint32 boss_rep_limit;
    uint32 faction[2];
};

struct ReputationModifier
{
    uint32 entry;
    vector<ReputationMod> mods;
};

struct InstanceReputationModifier
{
    uint32 mapid;
    vector<InstanceReputationMod> mods;
};

struct NpcMonsterSay
{
    float Chance;
    uint32 Language;
    uint32 Type;
    const char * MonsterName;

    uint32 TextCount;
    const char ** Texts;
};

enum MONSTER_SAY_EVENTS
{
    MONSTER_SAY_EVENT_ENTER_COMBAT        = 0,
    MONSTER_SAY_EVENT_RANDOM_WAYPOINT,
    NUM_MONSTER_SAY_EVENTS,
};

enum AREATABLE_FLAGS
{
    AREA_CITY_AREA          = 0x20,
    AREA_NEUTRAL_AREA       = 0x40,
    AREA_PVP_ARENA          = 0x80,
    AREA_CITY               = 0x200,
    AREA_SANCTUARY          = 0x800,
    AREA_ISLAND             = 0x1000,
    AREA_PVP_OBJECTIVE_AREA = 0x8000,
};

enum AREATABLE_CATEGORY
{
    AREAC_CONTESTED          = 0,
    AREAC_ALLIANCE_TERRITORY = 2,
    AREAC_HORDE_TERRITORY    = 4,
    AREAC_SANCTUARY          = 6,
};

class SERVER_DECL GossipMenu
{
public:
    GossipMenu(uint64 Creature_Guid, uint32 Text_Id);
    void AddItem(GossipMenuItem* GossipItem);
    void AddItem(uint16 Icon, const char* Text, int32 Id = -1);
    void BuildPacket(WorldPacket& Packet);
    void SendTo(Player* Plr);
    GossipMenuItem GetItem(uint32 Id);
    inline void SetTextID(uint32 TID) { TextId = TID; }

protected:
    uint32 TextId;
    uint64 CreatureGuid;
    std::vector<GossipMenuItem> Menu;
};

class Charter
{
public:
    uint32 SignatureCount;
    uint32 Signatures[9];
    uint32 LeaderGuid;
    uint64 ItemGuid;
    uint32 CharterId;
    string GuildName;

    Charter(Field * fields);
    Charter(uint32 id, uint32 leader) : CharterId(id)
    {
        SignatureCount = 0;
        memset(Signatures, 0, sizeof(Signatures));
        LeaderGuid = ItemGuid = 0;
    }
    
    void SaveToDB();
    void Destroy();         // When item is deleted.

    void AddSignature(uint32 PlayerGuid);
    void RemoveSignature(uint32 PlayerGuid);

    inline uint32 GetLeader() { return LeaderGuid; }
    inline uint32 GetID() { return CharterId; }

    inline bool IsFull() { return (SignatureCount == 9); }
};

typedef std::map<uint32, std::list<SpellEntry*>* > OverrideIdMap;

class SERVER_DECL ObjectMgr : public Singleton < ObjectMgr >, public EventableObject
{
public:
    ObjectMgr();
    ~ObjectMgr();
    void LoadCreatureWaypoints();

    // other objects
    typedef std::set< Group * > GroupSet;
    typedef UNORDERED_MAP<uint64, Item*> ItemMap;
    typedef UNORDERED_MAP<uint32, CorpseData*> CorpseCollectorMap;
    typedef UNORDERED_MAP<uint32, PlayerInfo*> PlayerNameMap;
    typedef UNORDERED_MAP<uint32, PlayerCreateInfo*> PlayerCreateInfoMap;
    typedef UNORDERED_MAP<uint32, Guild*> GuildMap;
    typedef UNORDERED_MAP<uint32, skilllinespell*> SLMap;
    typedef UNORDERED_MAP<uint32, std::vector<CreatureItem>*> VendorMap;
    typedef UNORDERED_MAP<uint32, Creature*> CreatureSqlIdMap;
    
    typedef UNORDERED_MAP<uint32, Trainer*> TrainerMap;
    typedef UNORDERED_MAP<uint32, std::vector<TrainerSpell*> > TrainerSpellMap;
    typedef std::map<uint32, LevelInfo*> LevelMap;
    typedef std::map<pair<uint32, uint32>, LevelMap* > LevelInfoMap;

    typedef std::map<uint32, std::list<ItemPrototype*>* > ItemSetContentMap;
    typedef std::map<uint32, uint32> NpcToGossipTextMap;
    typedef std::map<uint32, set<SpellEntry*> > PetDefaultSpellMap;
    typedef std::map<uint32, uint32> PetSpellCooldownMap;
    typedef std::map<uint32, SpellEntry*> TotemSpellMap;
    
    std::list<GM_Ticket*> GM_TicketList;
    TotemSpellMap m_totemSpells;
    std::list<ThreatToSpellId*> threatToSpells;
    OverrideIdMap mOverrideIdMap;

    Player* GetPlayer(const char* name, bool caseSensitive = true);
    Player* GetPlayer(uint32 guid);
    
    UNORDERED_MAP<uint32, Corpse*>m_corpses;
    Mutex _corpseslock;
    Mutex m_corpseguidlock;
    uint32 m_hiCorpseGuid;
    
    Item * CreateItem(uint32 entry,Player * owner);
    Item * LoadItem(uint64 guid);
  
    // Groups
    Group * GetGroupByLeader(Player *pPlayer);
    Group * GetGroupById(uint32 id);
    inline uint32 GenerateGroupId()
    {
        return ++m_hiGroupId;
    }
    void AddGroup(Group* group) { mGroupSet.insert( group ); }
    void RemoveGroup(Group* group) { mGroupSet.erase( group ); }

    // player names
    void AddPlayerInfo(PlayerInfo *pn);
    PlayerInfo *GetPlayerInfo(uint32 guid );
    PlayerInfo *GetPlayerInfoByName(std::string & name);
    void DeletePlayerInfo(uint32 guid);
    PlayerCreateInfo* GetPlayerCreateInfo(uint8 race, uint8 class_) const;

    // DK:Guild
    void AddGuild(Guild *pGuild);
    uint32 GetTotalGuildCount();
    bool RemoveGuild(uint32 guildId);
    Guild* GetGuild(uint32 guildId);  
    Guild* GetGuildByLeaderGuid(uint64 leaderGuid);  
    Guild* GetGuildByGuildName(std::string guildName);

    //Corpse Stuff
    Corpse *GetCorpseByOwner(uint32 ownerguid);
    void CorpseCollectorLoad();
    void CorpseCollectorUnload();
    void DespawnCorpse(uint64 Guid);
    void CorpseAddEventDespawn(Corpse *pCorpse);
    void DelinkPlayerCorpses(Player *pOwner);
    Corpse * CreateCorpse();
    void AddCorpse(Corpse*);
    void RemoveCorpse(Corpse*);
    Corpse * GetCorpse(uint32 corpseguid);

    uint32 GetGossipTextForNpc(uint32 ID);

    // Gm Tickets
    void AddGMTicket(GM_Ticket *ticket);
    void remGMTicket(uint64 guid);
    GM_Ticket* GetGMTicket(uint64 guid);

    skilllinespell* GetSpellSkill(uint32 id);

    //Vendors
    std::vector<CreatureItem> *GetVendorList(uint32 entry);
    void SetVendorList(uint32 Entry, std::vector<CreatureItem>* list_);

    //Totem
    SpellEntry* GetTotemSpell(uint32 spellId);

    // AI Threat by SpellId
    int32 GetAIThreatToSpellId(uint32 spellId);

    std::list<ItemPrototype*>* GetListForItemSet(uint32 setid);

      Creature * GetCreatureBySqlId(uint32 Sql_Id);
    void SetCreatureBySqlId(uint32 Sql_Id, Creature * pCreature);

    Pet * CreatePet();
    uint32 m_hiPetGuid;
    Mutex m_petlock;

    Player * CreatePlayer();
     Mutex m_playerguidlock;
     UNORDERED_MAP<uint32, Player*> _players;
    RWLock _playerslock;
    uint32 m_hiPlayerGuid;
    
    void AddPlayer(Player * p);//add it to global storage
    void RemovePlayer(Player *p);


    // Serialization

    void LoadQuests();
    void LoadPlayersInfo();
    void LoadPlayerCreateInfo();
    void LoadGuilds();
    Corpse* LoadCorpse(uint32 guid);
    void LoadGMTickets();
    void SaveGMTicket(uint64 guid);
    void LoadAuctions();
    void LoadAuctionItems();
    void LoadSpellSkills();
    void LoadVendors();
    void LoadTotemSpells();
    void LoadAIThreatToSpellId();
    void LoadReputationModifierTable(const char * tablename, UNORDERED_MAP<uint32, ReputationModifier*> * dmap);
    void LoadReputationModifiers();
    ReputationModifier * GetReputationModifier(uint32 entry_id, uint32 faction_id);

    void SetHighestGuids();
    uint32 GenerateLowGuid(uint32 guidhigh);
    uint32 GenerateMailID();
    
    void LoadTransporters();
    void ProcessGameobjectQuests();
   
    void GenerateTrainerSpells();
    bool AddTrainerSpell(uint32 entry, SpellEntry *pSpell);
    void LoadTrainers();
    Trainer* GetTrainer(uint32 Entry);

    void LoadExtraItemStuff();
    void LoadExtraCreatureProtoStuff();
    void CreateGossipMenuForPlayer(GossipMenu** Location, uint64 Guid, uint32 TextID, Player* Plr); 

    LevelInfo * GetLevelInfo(uint32 Race, uint32 Class, uint32 Level);
    void GenerateLevelUpInfo();
    void LoadDefaultPetSpells();
    set<SpellEntry*>* GetDefaultPetSpells(uint32 Entry);
    uint32 GetPetSpellCooldown(uint32 SpellId);
    void LoadPetSpellCooldowns();
    void LoadSpellFixes();
    WayPointMap * GetWayPointMap(uint32 spawnid);
    void LoadSpellOverride();

    uint32 GenerateCreatureSpawnID()
    {
        m_CreatureSpawnIdMutex.Acquire();
        uint32 r = ++m_hiCreatureSpawnId;
        m_CreatureSpawnIdMutex.Release();
        return r;
    }

    uint32 GenerateGameObjectSpawnID()
    {
        m_GOSpawnIdMutex.Acquire();
        uint32 r = ++m_hiGameObjectSpawnId;
        m_GOSpawnIdMutex.Release();
        return r;
    }

    Transporter * GetTransporter(uint32 guid);
    Transporter * GetTransporterByEntry(uint32 entry);

    Charter * CreateCharter(uint32 LeaderGuid);
    Charter * GetCharter(uint32 CharterId);
    void RemoveCharter(Charter *);
    void LoadGuildCharters();
    Charter * GetCharterByName(string &charter_name);
    Charter * GetCharterByItemGuid(uint64 guid);


    typedef UNORDERED_MAP<uint32, NpcMonsterSay*> MonsterSayMap;
    MonsterSayMap mMonsterSays[NUM_MONSTER_SAY_EVENTS];

    void HandleMonsterSayEvent(Creature * pCreature, MONSTER_SAY_EVENTS Event);
    bool HasMonsterSay(uint32 Entry, MONSTER_SAY_EVENTS Event);
    void LoadMonsterSay();

    bool HandleInstanceReputationModifiers(Player * pPlayer, Unit * pVictim);
    void LoadInstanceReputationModifiers();

    inline bool IsSpellDisabled(uint32 spellid)
    {
        if(m_disabled_spells.find(spellid) != m_disabled_spells.end())
            return true;
        return false;
    }

    void LoadDisabledSpells();
    vector<TrainerSpell*> * GetTrainerSpellsForLine(uint32 line)
    {
        TrainerSpellMap::iterator itr = mNormalSpells.find(line);
        return (itr == mNormalSpells.end()) ? 0 : &itr->second;
    }

    inline GuildMap::iterator GetGuildsBegin() { return mGuild.begin(); }
    inline GuildMap::iterator GetGuildsEnd() { return mGuild.end(); }

protected:
    RWLock playernamelock;
    uint32 m_mailid;
    // highest GUIDs, used for creating new objects
    Mutex m_guidGenMutex;
    uint32 m_hiItemGuid;
    uint32 m_hiContainerGuid;
    uint32 m_hiGroupId;
    uint32 m_hiCharterId;
    RWLock m_charterLock;
    UNORDERED_MAP<uint32, ReputationModifier*> m_reputation_faction;
    UNORDERED_MAP<uint32, ReputationModifier*> m_reputation_creature;
    UNORDERED_MAP<uint32, InstanceReputationModifier*> m_reputation_instance;

    UNORDERED_MAP<uint32, Charter*> m_charters;
    
    set<uint32> m_disabled_spells;
    set<uint32> m_disabled_trainer_spells;

    Transporter ** m_transporters;
    uint32 TransportersCount;
    UNORDERED_MAP<uint32,PlayerInfo*> m_playersinfo;
    
    UNORDERED_MAP<uint32,WayPointMap*> m_waypoints;//stored by spawnid
    uint32 m_hiCreatureSpawnId;
    
    Mutex m_CreatureSpawnIdMutex;
    Mutex m_GOSpawnIdMutex;

    uint32 m_hiGameObjectSpawnId;
    
    ///// Object Tables ////
    // These tables are modified as creatures are created and destroyed in the world

    // Group List
    GroupSet            mGroupSet;

    // Map of all starting infos needed for player creation
    PlayerCreateInfoMap mPlayerCreateInfo;

    // DK: Map of all Guild's
    GuildMap mGuild;

    // Map of all vendor goods
    VendorMap mVendors;

    // Maps for Gossip stuff
    NpcToGossipTextMap  mNpcToGossipText;

    SLMap                mSpellSkills;

    //Corpse Collector
    CorpseCollectorMap mCorpseCollector;

    ItemSetContentMap mItemSets;

    TrainerSpellMap mNormalSpells;
    TrainerSpellMap mPetSpells;

    TrainerMap mTrainers;
    LevelInfoMap mLevelInfo;
    PetDefaultSpellMap mDefaultPetSpells;
    PetSpellCooldownMap mPetSpellCooldowns;
    CreatureSqlIdMap mCreatureSqlIds;
    Mutex CreatureSqlIdMapMutex;
};


#define objmgr ObjectMgr::getSingleton()

//void SetProgressBar(int, int, const char*);
//void ClearProgressBar();

#endif
