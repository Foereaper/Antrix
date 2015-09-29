/****************************************************************************
 *
 * General Object Type File
 *
 */
#ifndef _PLAYER_H
#define _PLAYER_H
struct BattlegroundScore;
class Channel;
class Creature;
class Battleground;
class TaxiPath;
class GameObject;
class Transporter;
class Corpse;
class Guild;
class Pet;
class Charter;
struct LevelInfo;
#define myabs(a) (a<0)?(-a):a
#define MAX_PET_NO 3
#define PLAYER_NORMAL_RUN_SPEED 7.0
#define PLAYER_NORMAL_SWIM_SPEED 4.722222
#define PLAYER_NORMAL_FLIGHT_SPEED 7.0
#define PLAYER_HONORLESS_TARGET_SPELL 2479
//====================================================================
//  Inventory
//  Holds the display id and item type id for objects in
//  a character's inventory
//====================================================================
enum Classes
{
    WARRIOR = 1,
    PALADIN = 2,
    HUNTER = 3,
    ROGUE = 4,
    PRIEST = 5,
    SHAMAN = 7,
    MAGE = 8,
    WARLOCK = 9,
    DRUID = 11,
};
enum Races
{
    RACE_HUMAN = 1,
    RACE_ORC = 2,
    RACE_DWARF = 3,
    RACE_NIGHTELF = 4,
    RACE_UNDEAD = 5,
    RACE_TAUREN = 6,
    RACE_GNOME = 7,
    RACE_TROLL = 8,
    RACE_BLOODELF = 10,
    RACE_DRAENEI = 11,
};
enum PlayerStatus
{
    NONE             = 0,
    TRANSFER_PENDING = 1,
};

enum RankTitles
{
    PVPTITLE_NONE = 0x0,
    PVPTITLE_PRIVATE = 0x02,
    PVPTITLE_CORPORAL = 0x04,
    PVPTITLE_SERGEANT = 0x08,
    PVPTITLE_MASTER_SERGEANT = 0x10,
    PVPTITLE_SERGEANT_MAJOR = 0x20,
    PVPTITLE_KNIGHT = 0x40,
    PVPTITLE_KNIGHT_LIEUTENANT = 0x80,
    PVPTITLE_KNIGHT_CAPTAIN = 0x100,
    PVPTITLE_KNIGHT_CHAMPION = 0x200,
    PVPTITLE_LIEUTENANT_COMMANDER = 0x400,
    PVPTITLE_COMMANDER = 0x800,
    PVPTITLE_MARSHAL = 0x1000,
    PVPTITLE_FIELD_MARSHAL = 0x2000,
    PVPTITLE_GRAND_MARSHAL = 0x4000,
    PVPTITLE_SCOUT = 0x8000,
    PVPTITLE_GRUNT = 0x10000,
    PVPTITLE_HSERGEANT = 0x20000,
    PVPTITLE_SENIOR_SERGEANT = 0x40000,
    PVPTITLE_FIRST_SERGEANT = 0x80000,
    PVPTITLE_STONE_GUARD = 0x100000,
    PVPTITLE_BLOOD_GUARD = 0x200000,
    PVPTITLE_LEGIONNAIRE = 0x400000,
    PVPTITLE_CENTURION = 0x800000,
    PVPTITLE_CHAMPION = 0x1000000,
    PVPTITLE_LIEUTENANT_GENERAL = 0x2000000,
    PVPTITLE_GENERAL = 0x4000000,
    PVPTITLE_WARLORD = 0x8000000,
    PVPTITLE_HIGH_WARLORD = 0x10000000,

};
struct spells
{
    uint16 spellId;
    uint16 slotId;
};
struct aurloads
{
    uint16 id;
    uint32 dur;
};
#pragma pack(push,1)
struct ActionButton
{
    uint16 Action;
    uint8 Type;
    uint8 Misc;
};
#pragma pack(pop)
enum PvPAreaStatus
{
    AREA_ALLIANCE = 1,
    AREA_HORDE = 2,
    AREA_CONTESTED = 3,
    AREA_PVPARENA = 4,
};

struct CreateInfo_ItemStruct
{
    uint32 protoid;
    uint8 slot;
    uint32 amount;
};
struct CreateInfo_SkillStruct
{
    uint32 skillid;
    uint32 currentval;
    uint32 maxval;
};
struct CreateInfo_ActionBarStruct
{
    uint32 button;
    uint32 action;
    uint32 type;
    uint32 misc;
};
struct PlayerCreateInfo{
    uint8 index;
    uint8 race;
    uint32 factiontemplate;
    uint8 class_;
    uint32 mapId;
    uint32 zoneId;
    float positionX;
    float positionY;
    float positionZ;
    uint16 displayId;
    uint8 strength;
    uint8 ability;
    uint8 stamina;
    uint8 intellect;
    uint8 spirit;
    uint32 health;
    uint32 mana;
    uint32 rage;
    uint32 focus;
    uint32 energy;
    uint32 attackpower;
    float mindmg;
    float maxdmg;
    std::list<CreateInfo_ItemStruct> items;
    std::list<CreateInfo_SkillStruct> skills;
    std::list<CreateInfo_ActionBarStruct> actionbars;
    std::list<uint16> spell_list;
    //uint32 item[10];
    //uint8 item_slot[10];
    //uint16 spell[10];
};
struct DamageSplit
{
    Player* caster;
    Aura* aura;
    uint32 miscVal;
    union
    {
        uint32 damage;
        float damagePCT;
    };
};
enum PlayerMovementType
{
    MOVE_ROOT       = 1,
    MOVE_UNROOT     = 2,
    MOVE_WATER_WALK = 3,
    MOVE_LAND_WALK  = 4,
};
enum PlayerSpeedType
{
    RUN      = 1,
    RUNBACK  = 2,
    SWIM     = 3,
    SWIMBACK = 4,
    WALK     = 5,
    FLY      = 6,
};
enum Standing
{
    STANDING_HATED,
    STANDING_HOSTILE,
    STANDING_UNFRIENDLY,
    STANDING_NEUTRAL,
    STANDING_FRIENDLY,
    STANDING_HONORED,
    STANDING_REVERED,
    STANDING_EXALTED
};
enum PlayerFlags
{
    PLAYER_FLAG_PARTY_LEADER            = 0x01,
    PLAYER_FLAG_AFK                     = 0x02,
    PLAYER_FLAG_DND                     = 0x04,
    PLAYER_FLAG_GM                      = 0x08,
    PLAYER_FLAG_DEATH_WORLD_ENABLE      = 0x10,
    PLAYER_FLAG_RESTING                 = 0x20,
    PLAYER_FLAG_FREE_FOR_ALL_PVP        = 0x80,
    PLAYER_FLAG_PVP_TOGGLE              = 0x200,
    PLAYER_FLAG_NOHELM                  = 0x400,
    PLAYER_FLAG_NOCLOAK                 = 0x800,
    PLAYER_FLAG_NEED_REST_3_HOURS       = 0x1000,
    PLAYER_FLAG_NEED_REST_5_HOURS       = 0x2000,
};
/*
Exalted      1,000      Access to racial mounts. Capped at 999.7
Revered     21,000     Heroic mode keys for Outland dungeons
Honored     12,000     10% discount from faction vendors
Friendly     6,000
Neutral     3,000
Unfriendly     3,000     Cannot buy, sell or interact.
Hostile     3,000     You will always be attacked on sight
Hated     36,000 
*/
enum FactionRating
{
    HATED,
    HOSTILE,
    UNFRIENDLY,
    NEUTRAL,
    FRIENDLY,
    HONORED,
    REVERED,
    EXALTED
};
struct FactionReputation
{
    int32 standing;
    uint8 flag;
    int32 baseStanding;
    inline int32 CalcStanding() { return standing - baseStanding; }
    inline bool Positive() { return standing >= 0; }
    FactionRating CalcRating()
    {        
        register long st=CalcStanding();
        if(st>=42000)
            return EXALTED;
        if(st>=21000)
            return REVERED;
        if(st>=9000)
            return HONORED;
        if(st>=3000)
            return FRIENDLY;
        if(st>=0)
            return NEUTRAL;
        if(st>-3000)
            return UNFRIENDLY;
        if(st>-6000)
            return HOSTILE;
        return HATED;
    }
};
struct PlayerInfo
{
    uint64 guid;
    uint32 acct;
    std::string name;
    uint32 race;
    uint32 gender;
    uint32 cl;
    uint32 team;
    
    //guild stuff
    uint32 Rank;//guild rank
    std::string publicNote;
    std::string officerNote;
    time_t lastOnline;
    uint32 lastZone;
    uint32 lastLevel;
};
struct PlayerPet
{
    string name;
    uint32 entry;
    string fields;
    uint32 xp;
    bool active;
    uint32 number;
    uint32 level;
    uint32 loyalty;
    uint32 loyaltyupdate;
    string actionbar;
    bool summon;
    uint32 autocastspell;
};
enum MeetingStoneQueueStatus
{
    MEETINGSTONE_STATUS_NONE                                = 0,
    MEETINGSTONE_STATUS_JOINED_MEETINGSTONE_QUEUE_FOR       = 1,
    MEETINGSTONE_STATUS_PARTY_MEMBER_LEFT_LFG               = 2,
    MEETINGSTONE_STATUS_PARTY_MEMBER_REMOVED_PARTY_REMOVED  = 3,
    MEETINGSTONE_STATUS_LOOKING_FOR_NEW_PARTY_IN_QUEUE      = 4,
    MEETINGSTONE_STATUS_NONE_UNK                            = 5,
};
enum ItemPushResultTypes
{
    ITEM_PUSH_TYPE_LOOT             = 0x00000000,
    ITEM_PUSH_TYPE_RECEIVE          = 0x00000001,
    ITEM_PUSH_TYPE_CREATE           = 0x00000002,
};
struct WeaponModifier
{
    uint32 wclass;
    uint32 subclass;
    float value;
};
struct PetActionBar
{
    uint32 spell[10];
};
struct ItemCooldown
{
    uint16 SpellID;
    uint16 ItemEntry;
    uint16 SpellCategory;       //this maybe got from spell id, maybe saved for speed
    uint32 CooldownTimeStamp;
    uint32 Cooldown;
};
struct classScriptOverride
{
    uint32 id;
    uint32 effect;
    uint32 aura;
    uint32 damage;
    bool percent;
};
class Spell;
class Item;
class Container;
class WorldSession;
class ItemInterface;
class GossipMenu;
struct TaxiPathNode;
#define RESTSTATE_RESTED             1
#define RESTSTATE_NORMAL             2
#define RESTSTATE_TIRED100           3
#define RESTSTATE_TIRED50            4
#define RESTSTATE_EXHAUSTED          5
#define UNDERWATERSTATE_NONE         0
#define UNDERWATERSTATE_SWIMMING     1
#define UNDERWATERSTATE_UNDERWATER   2
#define UNDERWATERSTATE_RECOVERING   4
#define UNDERWATERSTATE_TAKINGDAMAGE 8
#define UNDERWATERSTATE_FATIGUE      16
#define UNDERWATERSTATE_LAVA         32
#define UNDERWATERSTATE_SLIME        64
enum TRADE_STATUS
{
    TRADE_STATUS_PLAYER_BUSY       = 0x00,
    TRADE_STATUS_PROPOSED          = 0x01,
    TRADE_STATUS_INITIATED         = 0x02,
    TRADE_STATUS_CANCELLED         = 0x03,
    TRADE_STATUS_ACCEPTED          = 0x04,
    TRADE_STATUS_ALREADY_TRADING   = 0x05,
    TRADE_STATUS_PLAYER_NOT_FOUND  = 0x06,
    TRADE_STATUS_STATE_CHANGED     = 0x07,
    TRADE_STATUS_COMPLETE          = 0x08,
    TRADE_STATUS_UNACCEPTED        = 0x09,
    TRADE_STATUS_TOO_FAR_AWAY      = 0x0A,
    TRADE_STATUS_WRONG_FACTION     = 0x0B,
    TRADE_STATUS_FAILED            = 0x0C,
    TRADE_STATUS_DEAD              = 0x0D,
    TRADE_STATUS_PETITION          = 0x0E,
    TRADE_STATUS_PLAYER_IGNORED    = 0x0F,
};
enum TRADE_DATA
{
    TRADE_GIVE        = 0x00,
    TRADE_RECEIVE     = 0x01,
};
enum DUEL_STATUS
{
    DUEL_STATUS_OUTOFBOUNDS,
    DUEL_STATUS_INBOUNDS
};
enum DUEL_STATE
{
    DUEL_STATE_REQUESTED,
    DUEL_STATE_STARTED,
    DUEL_STATE_FINISHED
};
enum DUEL_WINNER
{
    DUEL_WINNER_KNOCKOUT,
    DUEL_WINNER_RETREAT,
};
#define PLAYER_ATTACK_TIMEOUT_INTERVAL    5000
#define PLAYER_FORCED_RESURECT_INTERVAL    360000 // 1000*60*6= 6 minutes 
//====================================================================
//  Player
//  Class that holds every created character on the server.
//
//  TODO:  Attach characters to user accounts
//====================================================================
typedef std::set<uint32> SpellSet;
typedef std::set<ItemCooldown*> ItemCooldownSet;
typedef std::list<classScriptOverride*> ScriptOverrideList;
typedef std::set<uint32> SaveSet;
typedef std::map<uint32, uint32> SpellCooldownHolderMap;
typedef std::map<uint64, ByteBuffer*> SplineMap;
typedef std::map<uint32, ScriptOverrideList* > SpellOverrideMap;
typedef std::map<uint32, uint32> SpellOverrideExtraAuraMap;
typedef std::map<uint32, FactionReputation*> ReputationMap;
typedef std::map<uint32, uint64> SoloSpells;
class SERVER_DECL Player : public Unit
{
    friend class WorldSession;
public:
    Player ( uint32 high, uint32 low );
    ~Player ( );
    bool ok_to_remove;

    void AddToWorld();
    void RemoveFromWorld();
    bool Create ( WorldPacket &data );
    
    void Update( uint32 time );
    void BuildEnumData( WorldPacket * p_data );
    void BuildFlagUpdateForNonGroupSet(uint32 index, uint32 flag);
    std::string m_afk_reason;
    void SetAFKReason(std::string reason) { m_afk_reason = reason; };
    inline const char* GetName() { return m_name.c_str(); }
    inline std::string* GetNameString() { return &m_name; }
    void Die();
    //void KilledMonster(uint32 entry, const uint64 &guid);
    void GiveXP(uint32 xp, const uint64 &guid, bool allowbonus);   // to stop rest xp being given
    void ModifyBonuses(uint32 type,int32 val);
    std::map<uint32, uint32> m_wratings;
    // Taxi
    uint32 taxi_model_id;
    void TaxiStart(TaxiPath* path, uint32 modelid, uint32 start_node);
    uint32 lastNode;
    inline TaxiPath* GetTaxiPath() { return m_CurrentTaxiPath; }
    void EventDismount(uint32 money, float x, float y, float z);
    void SetTaxiState(bool state) { m_onTaxi = state; }
    inline bool GetTaxiState() { return m_onTaxi; }
    const uint32& GetTaximask( uint8 index ) const { return m_taximask[index]; }
    void SetTaximask( uint8 index, uint32 value ) { m_taximask[index] = value; }
    void LoadTaxiMask(const char* data);
    void EventTaxiInterpolate();
    inline void SetTaxiPath(TaxiPath *path) { m_CurrentTaxiPath = path; }
    void SetTaxiPos()
    {
        m_taxi_pos_x = m_position.x;
        m_taxi_pos_y = m_position.y;
        m_taxi_pos_z = m_position.z;
    }
    void UnSetTaxiPos()
    {
        m_taxi_pos_x = 0;
        m_taxi_pos_y = 0;
        m_taxi_pos_z = 0;
    }
    //Quest stuff
    bool HasQuests() 
    {
        for(int i = 0; i < 25; ++i)
        {
            if(m_questlog[i] != 0)
                return true;
        }
        return false;
    }

    void SetTriggerStunOrImmobilize(uint32 newtrigger,uint32 new_chance)
    {
        trigger_on_stun = newtrigger;
        trigger_on_stun_chance = new_chance;
    }
    void EventStunOrImmobilize(Unit *proc_target);

    int32 GetOpenQuestSlot();
    QuestLogEntry* GetQuestLogForEntry(uint32 quest);
    inline QuestLogEntry* GetQuestLogInSlot(uint32 slot) { return m_questlog[slot]; }
    void SetQuestLogSlot(QuestLogEntry *entry, uint32 slot);
    inline void PushToRemovedQuests(uint32 questid)
    {
        m_removequests.insert(questid);
    }
    //void ResetQuestSlots();
    void AddToFinishedQuests(uint32 quest_id);
    bool HasFinishedQuest(uint32 quest_id);
    bool HasQuestForItem(uint32 itemid);
    void SetQuestSharer(uint64 guid) { m_questSharer = guid; }
    inline uint64 GetQuestSharer() { return m_questSharer; }
    void EventPortToGM(Player *p);
    inline uint32 GetTeam()
    {
        uint32 r=getRace();
        if(r==RACE_DWARF || r== RACE_GNOME || r==RACE_HUMAN || r==RACE_NIGHTELF || r == RACE_DRAENEI)
            return 0;
        else return 1;
    }
    inline bool IsInFeralForm()
    {
        int s = GetShapeShift();
        if(!s)return false;
        //Fight forms that do not use player's weapon
        if(s==1 || s == 5 || s == 8)
            return true;
        else 
            return false;
    }
    void CalcDamage();
    const uint64& GetSelection( ) const { return m_curSelection; }
    const uint64& GetTarget( ) const { return m_curTarget; }
    void SetSelection(const uint64 &guid) { m_curSelection = guid; }
    void SetTarget(const uint64 &guid) { m_curTarget = guid; }
    // Spells
    bool HasSpell(uint32 spell);
    bool HasDeletedSpell(uint32 spell);
    uint32 GetMaxLearnedSpellLevel(uint32 spell);
    void smsg_InitialSpells();
    void addSpell(uint32 spell_idy);
    void removeSpellByHashName(uint32 hash);
    bool removeSpell(uint32 SpellID, bool MoveToDeleted, bool SupercededSpell, uint32 SupercededSpellID);
    //action bar
    void setAction(uint8 button, uint16 action, uint8 type, uint8 misc);
    //void addLoadAur(uint16 id, uint32 dur);
    bool m_actionsDirty;
    //std::list<struct aurloads>::iterator GetaurBegin() { return m_aurloads.begin();};
    //std::list<struct aurloads>::iterator GetaurEnd() { return m_aurloads.end();};
    void smsg_InitialActions();
    ///////////////////////////////////////
    // grep: Reputation
    ///////
    void ModStanding(uint32 Faction, int32 Value);
    int32 GetStanding(uint32 Faction);
    int32 GetBaseStanding(uint32 Faction);
    void SetStanding(uint32 Faction, int32 Value);
    void SetAtWar(uint32 Faction, bool Set);
    bool IsAtWar(uint32 Faction);
    Standing GetStandingRank(uint32 Faction);
    bool IsHostileBasedOnReputation(FactionDBC * dbc);
    void UpdateInrangeSetsBasedOnReputation();
    void Reputation_OnKilledUnit(Unit * pUnit);
    void Reputation_OnTalk(FactionDBC * dbc);
    static Standing GetReputationRankFromStanding(int32 Standing_);
    // factions
    void smsg_InitialFactions();
    int32 pctReputationMod;
    uint32 GetFactionId();
    inline uint8 GetPVPRank()
    {
        return (uint8)((GetUInt32Value(PLAYER_BYTES_3) >> 24) & 0xFF);
    }
    inline void SetPVPRank(int newrank)
    {
        SetUInt32Value(PLAYER_BYTES_3, ((GetUInt32Value(PLAYER_BYTES_3) & 0x00FFFFFF) | (uint8(newrank) << 24)));
    }
    // groups
    void SetInviter(uint64 pInviter) { m_GroupInviter = pInviter; }
    uint64 GetInviter() { return m_GroupInviter; }
    inline bool InGroup() { return (m_Group != NULL && !m_GroupInviter); }
    bool IsGroupLeader()
    {
        if(m_Group != NULL)
        {
            if(m_Group->GetLeader() == this)
                return true;
        }
        return false;
    }
    int HasBeenInvited() { return m_GroupInviter != 0; }
    inline Group* GetGroup() { return m_Group; }
    void SetGroup(Group* grp) { m_Group = grp; }
    uint32 GetSubGroup() { return m_SubGroup; }
    void SetSubGroup(uint32 group) { m_SubGroup = group; }
    std::set<uint32> OnMeleeAuras;
    // DK isGroupMember(plyr)
    bool IsGroupMember(Player *plyr);
    //DK ban
    void SetBanned() { m_banned = 4;}
    void SetBanned(string Reason) { m_banned = 4; m_banreason = Reason;}
    void UnSetBanned() { m_banned = 0; }
    inline bool IsBanned() { return ((m_banned > 0) ? true : false); }
    string GetBanReason() {return m_banreason;}
    //DK:Guild
    inline  bool IsInGuild() {return (bool)GetUInt32Value(PLAYER_GUILDID);}
    inline uint32 GetGuildId() { return m_uint32Values[PLAYER_GUILDID]; }
    void SetGuildId(uint32 guildId);
    inline uint32 GetGuildRank() { return m_uint32Values[PLAYER_GUILDRANK]; }
    void SetGuildRank(uint32 guildRank) { SetUInt32Value(PLAYER_GUILDRANK, guildRank); }
    uint64 GetGuildInvitersGuid() { return m_invitersGuid; }
    void SetGuildInvitersGuid( uint64 guid ) { m_invitersGuid = guid; }
    void UnSetGuildInvitersGuid() { m_invitersGuid = 0; }
  
    //Duel
    Player* DuelingWith;
    
    void RequestDuel(Player *pTarget);
    void DuelBoundaryTest();
    void EndDuel(uint8 WinCondition);
    void DuelCountdown();
    void SetDuelStatus(uint8 status) { m_duelStatus = status; }
    inline uint8 GetDuelStatus() { return m_duelStatus; }
    void SetDuelState(uint8 state) { m_duelState = state; }
    inline uint8 GetDuelState() { return m_duelState; }
    void SendTradeUpdate(void);
    inline void ResetTradeVariables()
    {
        mTradeGold = 0;
        memset(&mTradeItems, 0, sizeof(Item*) * 8);
        mTradeStatus = 0;
        mTradeTarget = 0;
    }
    //Pet
    inline void SetSummon(Pet *pet) { m_Summon = pet; }
    inline Pet* GetSummon(void) { return m_Summon; }
    uint32 GeneratePetNumber(void);
    void RemovePlayerPet(uint32 pet_number);
    inline void AddPlayerPet(PlayerPet* pet, uint32 index) { m_Pets[index] = pet; }
    inline PlayerPet* GetPlayerPet(uint32 idx)
    {
        std::map<uint32, PlayerPet*>::iterator itr = m_Pets.find(idx);
        if(itr != m_Pets.end()) return itr->second;
        else
            return NULL;
    }
    void SpawnPet(uint32 pet_number);
    void DespawnPet();
    uint32 GetFirstPetNumber(void)
    {
        if(m_Pets.size() == 0) return 0;
        std::map<uint32, PlayerPet*>::iterator itr = m_Pets.begin();
        return itr->first;
    }
    inline PlayerPet* GetFirstPet(void) { return GetPlayerPet(GetFirstPetNumber()); }
    inline void SetStableSlotCount(uint8 count) { m_StableSlotCount = count; }
    inline uint8 GetStableSlotCount(void) { return m_StableSlotCount; }
    // Items
    //Item Interface
    inline ItemInterface* GetItemInterface() { return m_ItemInterface; } // Player Inventory Item storage
    inline void ApplyItemMods(Item *item, int8 slot, bool apply,bool justdrokedown=false) {  _ApplyItemMods(item, slot, apply,justdrokedown); }
    // looting
    inline const uint64& GetLootGUID() const { return m_lootGuid; }
    void SetLootGUID(const uint64 &guid) { m_lootGuid = guid; }
    void SendLoot(uint64 guid,uint8 loot_type);
    inline WorldSession* GetSession() const { return m_session; }
    void SetSession(WorldSession *s) { m_session = s; }
    void SetBindPoint(float x, float y, float z, uint32 m, uint32 v) { m_bind_pos_x = x; m_bind_pos_y = y; m_bind_pos_z = z; m_bind_mapid = m; m_bind_zoneid = v;}
    void SendDelayedPacket(WorldPacket *data, bool bDeleteOnSend)
    {
        if(data == NULL) return;
        if(GetSession() != NULL) GetSession()->SendPacket(data);
        if(bDeleteOnSend) delete data;
    }
    float offhand_dmg_mod;
    float GetSpellTimeMod(uint32 id);
    int GetSpellDamageMod(uint32 id);
    int32 GetSpellManaMod(uint32 id);
    
    // Talents
    // These functions build a specific type of A9 packet
    uint32 __fastcall BuildCreateUpdateBlockForPlayer( ByteBuffer *data, Player *target );
    void DestroyForPlayer( Player *target ) const;
    struct LoginAura{
        uint32 id;
        uint32 dur;};
    std::list<LoginAura> loginauras;
    // Serialize character to db
    void SaveToDB(bool bNewCharacter);
    void SaveAuras(stringstream&);
    bool LoadFromDB(uint32 guid);
    void LoadFromDB_Light(Field *fields, uint32 guid);
    void LoadPropertiesFromDB();
    void LoadNamesFromDB(uint32 guid);
    void DeleteFromDB();
    bool m_FirstLogin;
    //Death Stuff
    void SpawnCorpseBody();
    void SpawnCorpseBones();
    void CreateCorpse();
    void KillPlayer();
    void ResurrectPlayer();
    void BuildPlayerRepop();
    void RepopRequestedPlayer();
    void DeathDurabilityLoss(double percent);
    void RepopAtGraveyard(float ox, float oy, float oz, uint32 mapid);
    //Movement stuff
    void SetMovement(uint8 pType, uint32 flag);
    void SetPlayerSpeed(uint8 SpeedType, float value);
    float GetPlayerSpeed(){return m_runSpeed;}
    uint8 m_currentMovement;
    bool m_isMoving;
    //Invisibility stuff
    bool m_isGmInvisible;
    //Channel stuff
    void JoinedChannel(Channel *c);
    void LeftChannel(Channel *c);
    void CleanupChannels();
    //Attack stuff
    void EventAttackStart();
    void EventAttackStop();
    void EventAttackUpdateSpeed() { }
    void EventDeath();
    // skilllines
    void AddLanguage(uint32 id);
    void AddLanguages();
    bool HasSkillLine(uint32 id);
    void AddSkillLine(uint32 id, uint32 currVal, uint32 maxVal);
    void AdvanceSkillLine(uint32 id);
    void ModSkillMax(uint32 id, uint32 amt, uint32 setcur = 0);
    //Note:ModSkillLine -> value+=amt;ModSkillMax -->value=amt; --wierd
    float GetSkillUpChance(uint32 id);
    uint32 GetSkillAmt(uint32 id);
    uint32 GetSkillPlace(uint32 id);
    uint32 GetSkillMax(uint32 id);
    void RemoveSkillLine(uint32 id);
    uint32 GetBaseSkillAmt(uint32 id);
    void ModSkillBonus(uint32 id,int32 bonus);
    void ModSkillBonusType(uint32 type,int32 bonus);
    void UpdateMaxSkills();
    //inline std::list<struct skilllines>getSkillLines() { return m_skilllines; }
    float SpellCrtiticalStrikeRatingBonus;
    float SpellHasteRatingBonus;
    void UpdateAttackSpeed();
    void UpdateChances();
    void UpdateStats();
    void UpdateHit(int32 hit);
   
    bool canCast(SpellEntry *m_spellInfo);
    inline float GetBlockFromSpellPCT() { return m_blockfromspellPCT; }
    inline float GetBlockFromSpell() { return m_blockfromspell; }
    inline float GetSpellCritFromSpell() { return m_spellcritfromspell; }
    inline float GetHitFromMeleeSpell() { return m_hitfrommeleespell; }
    inline float GetHitFromSpell() { return m_hitfromspell; }
    inline float GetParryFromSpell() { return m_parryfromspell; }
    inline float GetDodgeFromSpell() { return m_dodgefromspell; }
    void SetBlockFromSpellPCT(float value) { m_blockfromspellPCT = value; }
    void SetBlockFromSpell(float value) { m_blockfromspell = value; }
    void SetSpellCritFromSpell(float value) { m_spellcritfromspell = value; }
    void SetParryFromSpell(float value) { m_parryfromspell = value; }
    void SetDodgeFromSpell(float value) { m_dodgefromspell = value; }
    void SetHitFromMeleeSpell(float value) { m_hitfrommeleespell = value; }
    void SetHitFromSpell(float value) { m_hitfromspell = value; }
    inline uint32 GetHealthFromSpell() { return m_healthfromspell; }
    inline uint32 GetManaFromSpell() { return m_manafromspell; }
    void SetHealthFromSpell(uint32 value) { m_healthfromspell = value;}
    void SetManaFromSpell(uint32 value) { m_manafromspell = value;}
    uint32 CalcTalentResetCost(uint32 resetnum);
    void SendTalentResetConfirm();
    uint32 GetTalentResetTimes() { return m_talentresettimes; }
    inline void SetTalentResetTimes(uint32 value) { m_talentresettimes = value; }
    void SetPlayerStatus(uint8 pStatus) { m_status = pStatus; }
    inline uint8 GetPlayerStatus() { return m_status; }
    const float& GetBindPositionX( ) const { return m_bind_pos_x; }
    const float& GetBindPositionY( ) const { return m_bind_pos_y; }
    const float& GetBindPositionZ( ) const { return m_bind_pos_z; }
    const uint32& GetBindMapId( ) const { return m_bind_mapid; }
    const uint32& GetBindZoneId( ) const { return m_bind_zoneid; }
    inline uint8 GetShapeShift()
    {
        return GetByte(UNIT_FIELD_BYTES_1,2);
    }
    inline void setAttackTimer(int32 time, bool offhand)
    {
        if(!time)
            time = offhand ? m_uint32Values[UNIT_FIELD_BASEATTACKTIME_01] : m_uint32Values[UNIT_FIELD_BASEATTACKTIME];

        time += (time*modAttackTimeIncreasePCT)/100;

        if(offhand)
            m_attackTimer_1 = getMSTime() + time;
        else
            m_attackTimer = getMSTime() + time;
        //do not exit combat just because we are trying to delay attack (for whatever reason, like spellcasting)
        if(!sEventMgr.HasEvent(this,EVENT_ATTACK_TIMEOUT)) //do not add excesive attack events 
            sEventMgr.AddEvent(this,&Player::EventAttackStop,EVENT_ATTACK_TIMEOUT,time+PLAYER_ATTACK_TIMEOUT_INTERVAL,1); //attack timeout on no attack after 5 seconds
        else sEventMgr.ModifyEventTimeLeft(this,EVENT_ATTACK_TIMEOUT,time+PLAYER_ATTACK_TIMEOUT_INTERVAL,true);
    }
    
    std::set<uint32> m_SSSPecificSpells;
    void SetShapeShift(uint8 ss);

    uint32 m_furorChance;
    //inline uint32 GetEating() { return eating; }
    //void SetEating(uint32 spell) { eating = spell; }
    //Showing Units WayPoints
    AIInterface* waypointunit;
    void SaveGuild();
    
    uint32 m_nextSave;
    //Tutorials
    uint32 GetTutorialInt(uint32 intId );
    void SetTutorialInt(uint32 intId, uint32 value);
    //Base stats calculations
    //void CalcBaseStats();
    // Rest
    void AddRestXP(uint32 amount);
    uint32 SubtractRestXP(uint32 amount);
    uint32 CalculateRestXP(uint32 seconds);
    uint32 m_lastRestUpdate;
    void EventPlayerRest();
    void ApplyPlayerRestState(bool apply);
    void UpdateRestState();
    //falling?
    uint32 m_fallTime;
    bool bSafeFall;
    // Gossip
    GossipMenu* CurrentGossipMenu;
    void CleanupGossipMenu();
    void Gossip_Complete();
    void Gossip_SendPOI(float X, float Y, uint32 Icon, uint32 Flags, uint32 Data, const char* Name);
    int m_lifetapbonus;
    uint32 m_lastShotTime;
    
    bool m_bUnlimitedBreath;
    uint32 m_UnderwaterTime;
    uint32 m_UnderwaterState;
    uint32 m_SwimmingTime;
    uint32 m_BreathDamageTimer;
    // Visible objects
    bool CanSee(Object* obj);
    inline bool IsVisible(Object* pObj) { return !(m_visibleObjects.find(pObj) == m_visibleObjects.end()); }
    void AddInRangeObject(Object* pObj);
    void RemoveInRangeObject(Object* pObj);
    void ClearInRangeSet();
    void AddVisibleObject(Object* pObj) { m_visibleObjects.insert(pObj); }
    void RemoveVisibleObject(Object* pObj) { m_visibleObjects.erase(pObj); }

    inline InRangeSet::iterator GetVisibleSetBegin() { return m_visibleObjects.begin(); }
    inline InRangeSet::iterator GetVisibleSetEnd() { return m_visibleObjects.end(); }
    std::set<Player*> m_KnownGroupMembers;
    inline bool KnowsGroupMember(Player *plr) { return m_KnownGroupMembers.count(plr) > 0 ? true : false; }
    
    //Transporters
    bool m_lockTransportVariables;
    uint64 m_TransporterGUID;
    float m_TransporterX;
    float m_TransporterY;
    float m_TransporterZ;
    float m_TransporterO;
    float m_TransporterUnk;
    // Misc
    void EventCannibalize(uint32 amount);
    void EventReduceDrunk(bool full);
    bool m_AllowAreaTriggerPort;
    void EventAllowTiggerPort(bool enable);
    int32 m_rangedattackspeedmod;
    int32 m_meleeattackspeedmod;
    uint32 m_modblockvalue;
    void SendInitialLogonPackets();
    void Reset_Spells();
    void Reset_Talents();
    void Reset_ToLevel1();
    // Battlegrounds xD
    bool m_bgInBattleground;
    uint32 m_bgBattlegroundID;
    uint32 m_bgLastBattlegroundID;
    uint32 m_bgEntryPointMap;
    float m_bgEntryPointX;    
    float m_bgEntryPointY;
    float m_bgEntryPointZ;
    float m_bgEntryPointO;
    int32 m_bgEntryPointInstance;
    uint32 m_bgTeam;
    Battleground* GetCurrentBattleground();
    bool m_bgHasFlag;
    void EventRepeatSpell();
    void EventCastRepeatedSpell(uint32 spellid, Unit *target);
    bool CanShootRangedWeapon(uint32 spellid, Unit *target, bool autoshot);
    uint32 m_AutoShotDuration;
    uint32 m_AutoShotAttackTimer;
    bool m_onAutoShot;
    uint64 m_AutoShotTarget;
    float m_AutoShotStartX;
    float m_AutoShotStartY;
    float m_AutoShotStartZ;
    SpellEntry *m_AutoShotSpell;
    void _InitialReputation();
    void EventActivateGameObject(GameObject* obj);
    void EventDeActivateGameObject(GameObject* obj);
    void UpdateNearbyGameObjects();
    void EventTimedQuestExpire(Quest *qst, QuestLogEntry *qle, uint32 log_slot);
    uint32 timed_quest_slot;    
    void CalcResistance(uint32 type);
    inline float res_M_crit_get(){return m_resist_critical[0];}
    inline void res_M_crit_set(float newvalue){m_resist_critical[0]=newvalue;}
    inline float res_R_crit_get(){return m_resist_critical[1];}
    inline void res_R_crit_set(float newvalue){m_resist_critical[1]=newvalue;}
    uint32 FlatResistanceModifierPos[7];
    uint32 FlatResistanceModifierNeg[7];
    uint32 BaseResistanceModPctPos[7];
    uint32 BaseResistanceModPctNeg[7];
    uint32 ResistanceModPctPos[7];
    uint32 ResistanceModPctNeg[7];
    float m_resist_critical[2];//when we are a victim we can have talents to decrese chance for critical hit. This is a negative value and it's added to critshances
    float SpellDmgDoneByInt[7];
    float SpellHealDoneByInt[7];
    float SpellDmgDoneBySpr[7];
    float SpellHealDoneBySpr[7];
    uint32 m_modphyscritdmgPCT;
    uint32 m_RootedCritChanceBonus;
    
    uint32 FlatStatModPos[5];
    uint32 FlatStatModNeg[5];
    uint32 StatModPctPos[5];
    uint32 StatModPctNeg[5];
    uint32 TotalStatModPctPos[5];
    uint32 TotalStatModPctNeg[5];
    int32 IncreaseDamageByType[12]; //mod dmg by creature type
    float IncreaseDamageByTypePCT[12];
    float IncreaseCricticalByTypePCT[12];
    int32 DetectedRange;
    float PctIgnoreRegenModifier;
    uint32 m_retainedrage;
/*    
    union {
        float mRatingToPct[37];
        uint32 mRatingToPoint[37]; //block, skill.. cant be decimal values
    };
*/
    inline uint32* GetPlayedtime() { return m_playedtime; };
    void CalcStat(uint32 t);
    float CalcRating(uint32 t);
    void RecalcAllRatings();
    void RegenerateMana();
    void RegenerateHealth(bool inCombat);
    void RegenerateEnergy();
    void LooseRage();
    uint32 SoulStone;
    uint32 SoulStoneReciever;
    void removeSoulStone();

    bool bReincarnation;

    map<uint32, WeaponModifier> damagedone;
    map<uint32, WeaponModifier> tocritchance;
    uint32 Seal;
    uint32 judgespell;
    bool cannibalize;
    uint8 cannibalizeCount;
    int32 rageFromDamageDealt;
    // GameObject commands
    GameObject *m_GM_SelectedGO;
    
    void _Relocate(uint32 mapid,const LocationVector & v, bool sendpending, bool force_new_world);
    void AddItemsToWorld();
    void RemoveItemsFromWorld();
    bool bShouldHaveLootableOnCorpse;
    uint32 m_ShapeShifted;
    uint32 m_MountSpellId;
    bool bHasBindDialogOpen;
    void RemoveSpellsFromLine(uint32 skill_line);
    bool bGMTagOn;
    uint32 TrackingSpell;
    void _EventCharmAttack();
    void _Kick();
    void Kick(uint32 delay = 0);
    void SoftDisconnect();
    uint32 m_KickDelay;
    Unit * m_CurrentCharm;
    Transporter * m_CurrentTransporter;
    
    Object * GetSummonedObject () {return m_SummonedObject;};
    void SetSummonedObject (Object * t_SummonedObject) {m_SummonedObject = t_SummonedObject;};
    uint32 roll;
    void AddRecoverCooldown(SpellEntry * spellInfo);
    void AddCooldown(uint32 spell,uint32 time);
    void AddCategoryCooldown(uint32 cat, uint32 time);
    void AddGlobalCooldown(uint32 time);
    uint32 GetGlobalCooldown() { return GlobalCooldown; }
    void SetGlobalCooldown(uint32 time) { GlobalCooldown = time; }
    void ClearCooldownsOnLine(uint32 skill_line, uint32 called_from);
    void ClearCooldownForSpell(uint32 spell_id);
    bool bProcessPending;
    Mutex _bufferS;
    void PushUpdateData(ByteBuffer *data, uint32 updatecount);
    void PushOutOfRange(const WoWGuid & guid);
    void ProcessPendingUpdates();
    bool __fastcall CompressAndSendUpdateBuffer(uint32 size, const uint8* update_buffer);
    void ClearAllPendingUpdates();
    bool CanFinishQuest(Quest* qst);
    uint32 GetArmorProficiency() { return armor_proficiency; }
    uint32 GetWeaponProficiency() { return weapon_proficiency; }
    void ResetHeartbeatCoords();
    float _lastHeartbeatX;
    float _lastHeartbeatY;
    float _lastHeartbeatZ;
    uint32 _lastHeartbeatTime;
    void AddSplinePacket(uint64 guid, ByteBuffer* packet);
    ByteBuffer* GetAndRemoveSplinePacket(uint64 guid);
    void ClearSplinePackets();
    bool ExitInstance();
    void SaveEntryPoint(uint32 mapId);
    bool CooldownCheat;
    bool CastTimeCheat;
    bool GodModeCheat;
    bool PowerCheat;
    bool FlyCheat;
    void ZoneUpdate(uint32 ZoneId);
    inline uint32 GetAreaID() { return m_AreaID; }
    void SetAreaID(uint32 area) { m_AreaID = area; }
    SpellSet mSpells;
    SpellSet mDeletedSpells;
    SpellOverrideMap mSpellOverrideMap;
    
    std::string Lfgcomment;
    uint16 LfgDungeonId[3];
    uint8 LfgType[3];
    bool m_Autojoin;
    bool m_AutoAddMem;
    void StopMirrorTimer(uint32 Type);
    BattlegroundScore* m_bgScore;
    void UpdateChanceFields();
    //Honor Variables
    uint32 m_honorToday;
    uint32 m_honorYesterday;
    
    uint32 m_honorPoints;
    uint32 m_killsToday;
    uint32 m_killsYesterday;
    uint32 m_killsLifetime;
    bool m_honorless;
    uint32 m_lastSeenWeather;
    set<Object*> m_visibleFarsightObjects;
    void EventTeleport(uint32 mapid, float x, float y, float z);
    void ApplyLevelInfo(LevelInfo* Info, uint32 Level);
    void BroadcastMessage(const char* Format, ...);
    map<uint32, set<uint32> > SummonSpells;
    map<uint32, PetSpellMap*> PetSpells;
    void AddSummonSpell(uint32 Entry, uint32 SpellID);
    void RemoveSummonSpell(uint32 Entry, uint32 SpellID);
    set<uint32>* GetSummonSpells(uint32 Entry);
    LockedQueue<WorldPacket*> delayedPackets;
    set<Player *> gmTargets;
    uint32 m_UnderwaterMaxTime;
    uint32 m_UnderwaterLastDmg;
    inline void setMyCorpse(Corpse * corpse) { myCorpse = corpse; }
    inline Corpse * getMyCorpse() { return myCorpse; }
    bool bCorpseCreateable;
    uint32 m_resurrectHealth, m_resurrectMana;
    uint64 resurrector;
    bool blinked;
    uint16 m_speedhackChances;
    uint32 m_explorationTimer;
    // DBC stuff
    CharRaceEntry * myRace;
    CharClassEntry * myClass;
    Unit * linkTarget;
    bool stack_cheat;
    bool SafeTeleport(uint32 MapID, uint32 InstanceID, float X, float Y, float Z, float O);
    bool SafeTeleport(uint32 MapID, uint32 InstanceID, const LocationVector & vec);
    
    void EventSafeTeleport(uint32 MapID, uint32 InstanceID, LocationVector vec)
    {
        SafeTeleport(MapID, InstanceID, vec);
    }

    Guild * myGuild;
    /*****************
      PVP Stuff
    ******************/
    uint32 m_pvpTimer;
    
    //! Is PVP flagged?
    inline bool IsPvPFlagged() { return HasFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_PVP); }
    inline void SetPvPFlag()
    {
        // reset the timer as well..
        StopPvPTimer();
        SetFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_PVP);
    }
    //! Removal
    inline void RemovePvPFlag()
    {
        StopPvPTimer();
        RemoveFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_PVP);            
    }
    //! Do this on /pvp off
    inline void ResetPvPTimer();
    //! Stop the timer for pvp off
    inline void StopPvPTimer() { m_pvpTimer = 0; }
    
    //! Called at login to add the honorless buff, etc.
    void LoginPvPSetup();
    //! Update our pvp area (called when zone changes)
    void UpdatePvPArea();
    //! PvP Toggle (called on /pvp)
    void PvPToggle();
    bool CanCastDueToCooldown(SpellEntry * spellid);
    void SaveHonorFields();
    inline uint32 LastHonorResetTime() const { return m_lastHonorResetTime; }
    inline void LastHonorResetTime(uint32 val) { m_lastHonorResetTime = val; }
    uint32 OnlineTime;
    bool tutorialsDirty;
    LevelInfo * lvlinfo;
    void CalculateBaseStats();
    uint32 load_health;
    uint32 load_mana;
    void CompleteLoading();
    set<SpellEntry *> castSpellAtLogin;
    void OnPushToWorld();
    void OnWorldPortAck();
    uint32 m_TeleportState;
    set<Unit*> visiblityChangableSet;
    bool m_beingPushed;
    bool CanSignCharter(Charter * charter, Player * requester);
    Charter * m_charter;
    uint32 flying_aura;
    stringstream LoadAuras;
    bool resend_speed;
    bool rename_pending;
    uint32 iInstanceType;
    inline void SetName(string& name) { m_name = name; }
    // spell to (delay, last time)
    map< SpellEntry*, pair<uint32, uint32> > m_onStrikeSpells;
    map< uint32, OnHitSpell > m_onStrikeSpellDmg;
    // PLEASE DO NOT INLINE!
    void AddOnStrikeSpell(SpellEntry* sp, uint32 delay)
    {
        m_onStrikeSpells.insert( map< SpellEntry*, pair<uint32, uint32> >::value_type( sp, make_pair( delay, 0 ) ) );
    }
    void RemoveOnStrikeSpell(SpellEntry *sp)
    {
        m_onStrikeSpells.erase(sp);
    }
    void AddOnStrikeSpellDamage(uint32 spellid, uint32 mindmg, uint32 maxdmg)
    {
        OnHitSpell sp;
        sp.spellid = spellid;
        sp.mindmg = mindmg;
        sp.maxdmg = maxdmg;
        m_onStrikeSpellDmg[spellid] = sp;
    }
    void RemoveOnStrikeSpellDamage(uint32 spellid)
    {
        m_onStrikeSpellDmg.erase(spellid);
    }
    FactionReputation * reputationByListId[128];
    vector<TaxiPath*> m_taxiPaths;
    uint64 m_comboTarget;
    int8 m_comboPoints;
    void UpdateComboPoints();
    inline void AddComboPoint(uint64 target, int8 count)
    {
        if(m_comboTarget == target)
            m_comboPoints += count;
        else
        {
            m_comboTarget = target;
            m_comboPoints = count;
        }
        UpdateComboPoints();
    }
    inline void SetComboPoint(uint64 target, int8 count) { m_comboTarget = target; m_comboPoints = count; UpdateComboPoints(); }
    inline void ResetComboPoints() { m_comboTarget = 0; m_comboPoints = 0; UpdateComboPoints(); }
    Unit *GetSoloSpellTarget(uint32 spell_id);
    void  SetSoloSpellTarget(uint32 spellid,uint64 newtarget);
    uint32 m_speedChangeCounter;

    void SendAreaTriggerMessage(const char * message, ...);
    void Set_Mute_on_player(uint32 until);
    void Remove_Mute_on_player();
    uint32 HasMuteOnPlayer(){return chat_disabled_until;};
        
    // Trade Target
    //Player *getTradeTarget() {return mTradeTarget;};

    inline Player * GetTradeTarget()
    {
        if(!IsInWorld()) return 0;
        return m_mapMgr->GetPlayer(mTradeTarget);
    }

    Item *getTradeItem(uint32 slot) {return mTradeItems[slot];};
        
    // Water level related stuff (they are public because they need to be accessed fast)
    // Nose level of the character (needed for proper breathing)
    float m_noseLevel;

    /* Mind Control */
    void Possess(Unit * pTarget);
    void UnPossess();

    /* Last Speeds */
    inline void UpdateLastSpeeds()
    {
        m_lastRunSpeed = m_runSpeed;
        m_lastRunBackSpeed = m_backWalkSpeed;
        m_lastSwimSpeed = m_swimSpeed;
        m_lastRunBackSpeed = m_backSwimSpeed;
        m_lastFlySpeed = m_flySpeed;
    }

    void RemoteRevive()
    {
        ResurrectPlayer();
        SetMovement(MOVE_UNROOT, 5);
        SetPlayerSpeed(RUN, (float)7);
        SetPlayerSpeed(SWIM, (float)4.9);
        SetMovement(MOVE_LAND_WALK, 8);
        SetUInt32Value(UNIT_FIELD_HEALTH, GetUInt32Value(UNIT_FIELD_MAXHEALTH) );
    }

    LocationVector m_last_group_position;
    int32 m_rap_mod_pct;
    void SummonRequest(uint32 Requestor, uint32 ZoneID, uint32 MapID, uint32 InstanceID, const LocationVector & Position);
    uint8 m_lastMoveType;

protected:
    LocationVector m_summonPos;
    uint32 m_summonInstanceId;
    uint32 m_summonMapId;
    uint32 m_summoner;

    uint32 iActivePet;
    void _SetCreateBits(UpdateMask *updateMask, Player *target) const;
    void _SetUpdateBits(UpdateMask *updateMask, Player *target) const;
    void _SetVisibleBits(UpdateMask *updateMask, Player *target) const;
/* Update system components */
    ByteBuffer bUpdateBuffer;
    uint32 mUpdateCount;
    uint32 mOutOfRangeIdCount;
    ByteBuffer mOutOfRangeIds;
    SplineMap _splineMap;
/* End update system */
    void _LoadTutorials();
    void _SaveTutorials();
    void _SaveInventory(bool firstsave);
    void _LoadBagInventory(uint32 playerguid, uint8 bagslot);
    void _SaveQuestLogEntry();
    void _LoadQuestLogEntry();
    void _LoadInventoryLight();
    // DK
    void _LoadGuild();
    void _LoadPet();
    void _LoadPetNo();
    void _LoadPetSpells();
    void _SavePet();
    void _SavePetSpells();
    void _SaveItemCooldown();
    void _LoadItemCooldown();
    void _SaveSpellCoolDownSecurity();
    void _LoadSpellCoolDownSecurity();
    void _ApplyItemMods(Item *item, int8 slot,bool apply,bool justdrokedown=false);
   
    void _EventAttack(bool offhand);
    void _EventExploration();
    void UpdateCooldowns();
    // Water level related stuff
    void SetNoseLevel();
    // Cooldown stuff
    std::map<uint32,uint32>     SpellCooldownMap;
    std::map<uint32,uint32>     SpellCooldownCategoryMap;
    ItemCooldownSet             m_itemcooldown;
    uint32                      GlobalCooldown;
    /************************************************************************/
    /* Trade                                                                */
    /************************************************************************/
    Item* mTradeItems[8];
   
    uint32 mTradeGold;
    uint64 mTradeTarget;
    uint32 mTradeStatus;
    PlayerCreateInfo *info;
    uint32 m_AttackMsgTimer;    // "too far away" and "wrong facing" timer
    bool m_attacking;
    
    uint64 m_lootGuid;
    //uint32 eating;
    std::string m_name;    // max 21 character name
    uint32 m_Tutorials[8];
    //uint32 m_mod_damage_done[7];
 
    uint64 m_invitersGuid; // It is guild inviters guid ,0 when its not used
    // Character Ban
    uint32 m_banned;
    string m_banreason;
    uint32 m_AreaID;
    Pet* m_Summon;
    uint32 m_PetNumberMax;
    std::map<uint32, PlayerPet*> m_Pets;
    //Taxi
    bool m_onTaxi;
    uint32 m_taximask[8];
    TaxiPath* m_CurrentTaxiPath;
    float m_taxi_pos_x;
    float m_taxi_pos_y;
    float m_taxi_pos_z;
    uint32 m_taxi_ride_time;
    float m_bind_pos_x;
    float m_bind_pos_y;
    float m_bind_pos_z;
    uint32 m_bind_mapid;
    uint32 m_bind_zoneid;
    std::list<ItemSet> m_itemsets;
    //Duel
    uint32 m_duelCountdownTimer;
    uint8 m_duelStatus;
    uint8 m_duelState;
    // Rested State Stuff
    uint32 m_timeLogoff;
    // Played time
    uint32 m_playedtime[3];
    uint8 m_isResting;
    uint8 m_restState;
    uint32 m_restAmount;
    //combat mods
    float m_blockfromspell;
    float m_blockfromspellPCT;
    float m_critfromspell;
    float m_spellcritfromspell;
    float m_dodgefromspell;
    float m_parryfromspell;
    float m_hitfromspell;
    float m_hitfrommeleespell;
    //stats mods
    uint32 m_healthfromspell;
    uint32 m_manafromspell;
    uint32 m_healthfromitems;
    uint32 m_manafromitems;
    
    uint32  armor_proficiency;
    uint32  weapon_proficiency;
    // Talents
    uint32 m_talentresettimes;
    // STATUS
    uint8 m_status;
    // guid of current target
    uint64 m_curTarget;
    // guid of current selection
    uint64 m_curSelection;
    //Quests
    QuestLogEntry* m_questlog[25];
    std::set<uint32> m_removequests;
    std::set<uint32> m_finishedQuests;
    uint64 m_questSharer;
    // Raid
    uint8 m_targetIcon;
    std::list<struct aurloads> m_aurloads;
    //Player Action Bar
    ActionButton mActions[120];
    // Player Reputation
    ReputationMap m_reputation;
    // Pointer to this char's game client
    WorldSession *m_session;
    // Channels
    std::list<Channel*> m_channels;
    // Visible objects
    std::set<Object*> m_visibleObjects;
    // Groups/Raids
    Group* m_Group;
    uint32 m_SubGroup;
    uint64 m_GroupInviter;
    uint8 m_StableSlotCount;
    std::set<uint32> m_QuestGOInProgress;
    // Fishing related
    Object *m_SummonedObject;
    // loot related
    uint64 m_currentLoot;
    ItemInterface *m_ItemInterface;
    
    Corpse * myCorpse;
    uint32 m_cooldownTimer;
    uint32 m_lastHonorResetTime;
    uint32 _fields[PLAYER_END];
    void JumpToEndTaxiNode(TaxiPath * path);
    SoloSpells    solospelltarget;
    uint32    chat_disabled_until;//force player to be silent. Yeah i'm pissed of on noobs
    uint32    trigger_on_stun; //bah, warrior talent but this will not get triggered on trigered spells if used on proc so i'm forced to used a special variable
    uint32    trigger_on_stun_chance; //also using this for mage "Frostbite" talent

    float m_lastRunSpeed;
    float m_lastRunBackSpeed;
    float m_lastSwimSpeed;
    float m_lastBackSwimSpeed;
    float m_lastFlySpeed;

};

#endif
