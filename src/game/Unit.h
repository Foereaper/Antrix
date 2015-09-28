/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef __UNIT_H
#define __UNIT_H

class AIInterface;
class DynamicObject;

#define MAX_AURAS 56 // 40 buff slots, 16 debuff slots.
#define MAX_POSITIVE_AURAS 40 // ?
#define MAX_PASSIVE_AURAS 192   // grep: i mananged to break this.. :p seems we need more

bool SERVER_DECL Rand(float);

#define UF_TARGET_DIED  1
#define UF_ATTACKING	2 // this unit is attacking it's selection
#define SPELL_GROUPS 32//maximum possible is 32, may be less

class Aura;
class Spell;
class AIInterface;
class GameObject;

struct CreatureInfo;
struct FactionTemplateDBC;
struct FactionDBC;


typedef struct
{ 
	uint32 damage_type;
	int32 full_damage;
	uint32 resisted_damage;
}dealdamage;

struct ReflectSpellSchool
{
	uint32 spellId;
	int32 school;
	int32 chance;
};

typedef struct
{
	uint32 spellid;
	uint64 caster;//not yet in use
	int32 amt;
}Absorb;

typedef std::list<Absorb*> SchoolAbsorb;

typedef struct 
{
	uint32 spellid;
	uint32 mindmg;
	uint32 maxdmg;
} OnHitSpell;

struct AreaAura
{
	uint32 auraid;
	Unit* caster;
};

enum DeathState
{
	ALIVE = 0,  // Unit is alive and well
	JUST_DIED,  // Unit has JUST died
	CORPSE,	 // Unit has died but remains in the world as a corpse
	DEAD		// Unit is dead and his corpse is gone from the world
};

#define HIGHEST_FACTION = 46
enum Factions {
	FACTION_BLOODSAIL_BUCCANEERS,
	FACTION_BOOTY_BAY,
	FACTION_GELKIS_CLAN_CENTAUR,
	FACTION_MAGRAM_CLAN_CENTAUR,
	FACTION_THORIUM_BROTHERHOOD,
	FACTION_RAVENHOLDT,
	FACTION_SYNDICATE,
	FACTION_GADGETZAN,
	FACTION_WILDHAMMER_CLAN,
	FACTION_RATCHET,
	FACTION_UNK1,
	FACTION_UNK2,
	FACTION_UNK3,
	FACTION_ARGENT_DAWN,
	FACTION_ORGRIMMAR,
	FACTION_DARKSPEAR_TROLLS,
	FACTION_THUNDER_BLUFF,
	FACTION_UNDERCITY,
	FACTION_GNOMEREGAN_EXILES,
	FACTION_STORMWIND,
	FACTION_IRONFORGE,
	FACTION_DARNASSUS,
	FACTION_LEATHERWORKING_DRAGON,
	FACTION_LEATHERWORKING_ELEMENTAL,
	FACTION_LEATHERWORKING_TRIBAL,
	FACTION_ENGINEERING_GNOME,
	FACTION_ENGINEERING_GOBLIN,
	FACTION_WINTERSABER_TRAINERS,
	FACTION_EVERLOOK,
	FACTION_BLACKSMITHING_ARMOR,
	FACTION_BLACKSMITHING_WEAPON,
	FACTION_BLACKSMITHING_AXE,
	FACTION_BLACKSMITHING_SWORD,
	FACTION_BLACKSMITHING_HAMMER,
	FACTION_CAER_DARROW,
	FACTION_TIMBERMAW_FURBOLGS,
	FACTION_CENARION_CIRCLE,
	FACTION_SHATTERSPEAR_TROLLS,
	FACTION_RAVASAUR_TRAINERS,
	FACTION_BATTLEGROUND_NEUTRAL,
	FACTION_STORMPIKE_GUARDS,
	FACTION_FROSTWOLF_CLAN,
	FACTION_HYDRAXIAN_WATERLORDS,
	FACTION_MORO_GAI,
	FACTION_SHEN_DRALAR,
	FACTION_SILVERWING_SENTINELS,
	FACTION_WARSONG_OUTRIDERS
};
typedef enum
{
	TEXTEMOTE_AGREE			= 1,
	TEXTEMOTE_AMAZE			= 2,
	TEXTEMOTE_ANGRY			= 3,
	TEXTEMOTE_APOLOGIZE		= 4,
	TEXTEMOTE_APPLAUD		  = 5,
	TEXTEMOTE_BASHFUL		  = 6,
	TEXTEMOTE_BECKON		   = 7,
	TEXTEMOTE_BEG			  = 8,
	TEXTEMOTE_BITE			 = 9,
	TEXTEMOTE_BLEED			= 10,
	TEXTEMOTE_BLINK			= 11,
	TEXTEMOTE_BLUSH			= 12,
	TEXTEMOTE_BONK			 = 13,
	TEXTEMOTE_BORED			= 14,
	TEXTEMOTE_BOUNCE		   = 15,
	TEXTEMOTE_BRB			  = 16,
	TEXTEMOTE_BOW			  = 17,
	TEXTEMOTE_BURP			 = 18,
	TEXTEMOTE_BYE			  = 19,
	TEXTEMOTE_CACKLE		   = 20,
	TEXTEMOTE_CHEER			= 21,
	TEXTEMOTE_CHICKEN		  = 22,
	TEXTEMOTE_CHUCKLE		  = 23,
	TEXTEMOTE_CLAP			 = 24,
	TEXTEMOTE_CONFUSED		 = 25,
	TEXTEMOTE_CONGRATULATE	 = 26,
	TEXTEMOTE_COUGH			= 27,
	TEXTEMOTE_COWER			= 28,
	TEXTEMOTE_CRACK			= 29,
	TEXTEMOTE_CRINGE		   = 30,
	TEXTEMOTE_CRY			  = 31,
	TEXTEMOTE_CURIOUS		  = 32,
	TEXTEMOTE_CURTSEY		  = 33,
	TEXTEMOTE_DANCE			= 34,
	TEXTEMOTE_DRINK			= 35,
	TEXTEMOTE_DROOL			= 36,
	TEXTEMOTE_EAT			  = 37,
	TEXTEMOTE_EYE			  = 38,
	TEXTEMOTE_FART			 = 39,
	TEXTEMOTE_FIDGET		   = 40,
	TEXTEMOTE_FLEX			 = 41,
	TEXTEMOTE_FROWN			= 42,
	TEXTEMOTE_GASP			 = 43,
	TEXTEMOTE_GAZE			 = 44,
	TEXTEMOTE_GIGGLE		   = 45,
	TEXTEMOTE_GLARE			= 46,
	TEXTEMOTE_GLOAT			= 47,
	TEXTEMOTE_GREET			= 48,
	TEXTEMOTE_GRIN			 = 49,
	TEXTEMOTE_GROAN			= 50,
	TEXTEMOTE_GROVEL		   = 51,
	TEXTEMOTE_GUFFAW		   = 52,
	TEXTEMOTE_HAIL			 = 53,
	TEXTEMOTE_HAPPY			= 54,
	TEXTEMOTE_HELLO			= 55,
	TEXTEMOTE_HUG			  = 56,
	TEXTEMOTE_HUNGRY		   = 57,
	TEXTEMOTE_KISS			 = 58,
	TEXTEMOTE_KNEEL			= 59,
	TEXTEMOTE_LAUGH			= 60,
	TEXTEMOTE_LAYDOWN		  = 61,
	TEXTEMOTE_MASSAGE		  = 62,
	TEXTEMOTE_MOAN			 = 63,
	TEXTEMOTE_MOON			 = 64,
	TEXTEMOTE_MOURN			= 65,
	TEXTEMOTE_NO			   = 66,
	TEXTEMOTE_NOD			  = 67,
	TEXTEMOTE_NOSEPICK		 = 68,
	TEXTEMOTE_PANIC			= 69,
	TEXTEMOTE_PEER			 = 70,
	TEXTEMOTE_PLEAD			= 71,
	TEXTEMOTE_POINT			= 72,
	TEXTEMOTE_POKE			 = 73,
	TEXTEMOTE_PRAY			 = 74,
	TEXTEMOTE_ROAR			 = 75,
	TEXTEMOTE_ROFL			 = 76,
	TEXTEMOTE_RUDE			 = 77,
	TEXTEMOTE_SALUTE		   = 78,
	TEXTEMOTE_SCRATCH		  = 79,
	TEXTEMOTE_SEXY			 = 80,
	TEXTEMOTE_SHAKE			= 81,
	TEXTEMOTE_SHOUT			= 82,
	TEXTEMOTE_SHRUG			= 83,
	TEXTEMOTE_SHY			  = 84,
	TEXTEMOTE_SIGH			 = 85,
	TEXTEMOTE_SIT			  = 86,
	TEXTEMOTE_SLEEP			= 87,
	TEXTEMOTE_SNARL			= 88,
	TEXTEMOTE_SPIT			 = 89,
	TEXTEMOTE_STARE			= 90,
	TEXTEMOTE_SURPRISED		= 91,
	TEXTEMOTE_SURRENDER		= 92,
	TEXTEMOTE_TALK			 = 93,
	TEXTEMOTE_TALKEX		   = 94,
	TEXTEMOTE_TALKQ			= 95,
	TEXTEMOTE_TAP			  = 96,
	TEXTEMOTE_THANK			= 97,
	TEXTEMOTE_THREATEN		 = 98,
	TEXTEMOTE_TIRED			= 99,
	TEXTEMOTE_VICTORY		  = 100,
	TEXTEMOTE_WAVE			 = 101,
	TEXTEMOTE_WELCOME		  = 102,
	TEXTEMOTE_WHINE			= 103,
	TEXTEMOTE_WHISTLE		  = 104,
	TEXTEMOTE_WORK			 = 105,
	TEXTEMOTE_YAWN			 = 106,
	TEXTEMOTE_BOGGLE		   = 107,
	TEXTEMOTE_CALM			 = 108,
	TEXTEMOTE_COLD			 = 109,
	TEXTEMOTE_COMFORT		  = 110,
	TEXTEMOTE_CUDDLE		   = 111,
	TEXTEMOTE_DUCK			 = 112,
	TEXTEMOTE_INSULT		   = 113,
	TEXTEMOTE_INTRODUCE		= 114,
	TEXTEMOTE_JK			   = 115,
	TEXTEMOTE_LICK			 = 116,
	TEXTEMOTE_LISTEN		   = 117,
	TEXTEMOTE_LOST			 = 118,
	TEXTEMOTE_MOCK			 = 119,
	TEXTEMOTE_PONDER		   = 120,
	TEXTEMOTE_POUNCE		   = 121,
	TEXTEMOTE_PRAISE		   = 122,
	TEXTEMOTE_PURR			 = 123,
	TEXTEMOTE_PUZZLE		   = 124,
	TEXTEMOTE_RAISE			= 125,
	TEXTEMOTE_READY			= 126,
	TEXTEMOTE_SHIMMY		   = 127,
	TEXTEMOTE_SHIVER		   = 128,
	TEXTEMOTE_SHOO			 = 129,
	TEXTEMOTE_SLAP			 = 130,
	TEXTEMOTE_SMIRK			= 131,
	TEXTEMOTE_SNIFF			= 132,
	TEXTEMOTE_SNUB			 = 133,
	TEXTEMOTE_SOOTHE		   = 134,
	TEXTEMOTE_STINK			= 135,
	TEXTEMOTE_TAUNT			= 136,
	TEXTEMOTE_TEASE			= 137,
	TEXTEMOTE_THIRSTY		  = 138,
	TEXTEMOTE_VETO			 = 139,
	TEXTEMOTE_SNICKER		  = 140,
	TEXTEMOTE_STAND			= 141,
	TEXTEMOTE_TICKLE		   = 142,
	TEXTEMOTE_VIOLIN		   = 143,
	TEXTEMOTE_SMILE			= 163,
	TEXTEMOTE_RASP			 = 183,
	TEXTEMOTE_PITY			 = 203,
	TEXTEMOTE_GROWL			= 204,
	TEXTEMOTE_BARK			 = 205,
	TEXTEMOTE_SCARED		   = 223,
	TEXTEMOTE_FLOP			 = 224,
	TEXTEMOTE_LOVE			 = 225,
	TEXTEMOTE_MOO			  = 226,
	TEXTEMOTE_COMMEND		  = 243,
	TEXTEMOTE_JOKE			 = 329
} TextEmoteType;

typedef enum
{
	EMOTE_ONESHOT_NONE			 = 0,
	EMOTE_ONESHOT_TALK			 = 1,   //DNR
	EMOTE_ONESHOT_BOW			  = 2,
	EMOTE_ONESHOT_WAVE			 = 3,   //DNR
	EMOTE_ONESHOT_CHEER			= 4,   //DNR
	EMOTE_ONESHOT_EXCLAMATION	  = 5,   //DNR
	EMOTE_ONESHOT_QUESTION		 = 6,
	EMOTE_ONESHOT_EAT			  = 7,
	EMOTE_STATE_DANCE			  = 10,
	EMOTE_ONESHOT_LAUGH			= 11,
	EMOTE_STATE_SLEEP			  = 12,
	EMOTE_STATE_SIT				= 13,
	EMOTE_ONESHOT_RUDE			 = 14,  //DNR
	EMOTE_ONESHOT_ROAR			 = 15,  //DNR
	EMOTE_ONESHOT_KNEEL			= 16,
	EMOTE_ONESHOT_KISS			 = 17,
	EMOTE_ONESHOT_CRY			  = 18,
	EMOTE_ONESHOT_CHICKEN		  = 19,
	EMOTE_ONESHOT_BEG			  = 20,
	EMOTE_ONESHOT_APPLAUD		  = 21,
	EMOTE_ONESHOT_SHOUT			= 22,  //DNR
	EMOTE_ONESHOT_FLEX			 = 23,
	EMOTE_ONESHOT_SHY			  = 24,  //DNR
	EMOTE_ONESHOT_POINT			= 25,  //DNR
	EMOTE_STATE_STAND			  = 26,
	EMOTE_STATE_READYUNARMED	   = 27,
	EMOTE_STATE_WORK			   = 28,
	EMOTE_STATE_POINT			  = 29,  //DNR
	EMOTE_STATE_NONE			   = 30,
	EMOTE_ONESHOT_WOUND			= 33,
	EMOTE_ONESHOT_WOUNDCRITICAL	= 34,
	EMOTE_ONESHOT_ATTACKUNARMED	= 35,
	EMOTE_ONESHOT_ATTACK1H		 = 36,
	EMOTE_ONESHOT_ATTACK2HTIGHT	= 37,
	EMOTE_ONESHOT_ATTACK2HLOOSE	= 38,
	EMOTE_ONESHOT_PARRYUNARMED	 = 39,
	EMOTE_ONESHOT_PARRYSHIELD	  = 43,
	EMOTE_ONESHOT_READYUNARMED	 = 44,
	EMOTE_ONESHOT_READY1H		  = 45,
	EMOTE_ONESHOT_READYBOW		 = 48,
	EMOTE_ONESHOT_SPELLPRECAST	 = 50,
	EMOTE_ONESHOT_SPELLCAST		= 51,
	EMOTE_ONESHOT_BATTLEROAR	   = 53,
	EMOTE_ONESHOT_SPECIALATTACK1H  = 54,
	EMOTE_ONESHOT_KICK			 = 60,
	EMOTE_ONESHOT_ATTACKTHROWN	 = 61,
	EMOTE_STATE_STUN			   = 64,
	EMOTE_STATE_DEAD			   = 65,
	EMOTE_ONESHOT_SALUTE		   = 66,
	EMOTE_STATE_KNEEL			  = 68,
	EMOTE_STATE_USESTANDING		= 69,
	EMOTE_ONESHOT_WAVE_NOSHEATHE   = 70,
	EMOTE_ONESHOT_CHEER_NOSHEATHE  = 71,
	EMOTE_ONESHOT_EAT_NOSHEATHE	= 92,
	EMOTE_STATE_STUN_NOSHEATHE	 = 93,
	EMOTE_ONESHOT_DANCE			= 94,
	EMOTE_ONESHOT_SALUTE_NOSHEATH  = 113,
	EMOTE_STATE_USESTANDING_NOSHEATHE  = 133,
	EMOTE_ONESHOT_LAUGH_NOSHEATHE  = 153,
	EMOTE_STATE_WORK_NOSHEATHE	 = 173,
	EMOTE_STATE_SPELLPRECAST	   = 193,
	EMOTE_ONESHOT_READYRIFLE	   = 213,
	EMOTE_STATE_READYRIFLE		 = 214,
	EMOTE_STATE_WORK_NOSHEATHE_MINING  = 233,
	EMOTE_STATE_WORK_NOSHEATHE_CHOPWOOD= 234,
	EMOTE_zzOLDONESHOT_LIFTOFF	 = 253,
	EMOTE_ONESHOT_LIFTOFF		  = 254,
	EMOTE_ONESHOT_YES			  = 273, //DNR
	EMOTE_ONESHOT_NO			   = 274, //DNR
	EMOTE_ONESHOT_TRAIN			= 275, //DNR
	EMOTE_ONESHOT_LAND			 = 293,
	EMOTE_STATE_AT_EASE			= 313,
	EMOTE_STATE_READY1H			= 333,	
	EMOTE_STATE_SPELLKNEELSTART	= 353,
	EMOTE_STATE_SUBMERGED		  = 373,
	EMOTE_ONESHOT_SUBMERGE		 = 374,
	EMOTE_STATE_READY2H			= 375,
	EMOTE_STATE_READYBOW		   = 376,
	EMOTE_ONESHOT_MOUNTSPECIAL	 = 377,
	EMOTE_STATE_TALK			   = 378,
	EMOTE_STATE_FISHING			= 379,
	EMOTE_ONESHOT_FISHING		  = 380,
	EMOTE_ONESHOT_LOOT			 = 381,
	EMOTE_STATE_WHIRLWIND		  = 382,
	EMOTE_STATE_DROWNED			= 383,
	EMOTE_STATE_HOLD_BOW		   = 384,
	EMOTE_STATE_HOLD_RIFLE		 = 385,
	EMOTE_STATE_HOLD_THROWN		= 386,
	EMOTE_ONESHOT_DROWN			= 387,
	EMOTE_ONESHOT_STOMP			= 388,
	EMOTE_ONESHOT_ATTACKOFF		= 389,
	EMOTE_ONESHOT_ATTACKOFFPIERCE  = 390,
	EMOTE_STATE_ROAR			   = 391,
	EMOTE_STATE_LAUGH			  = 392,
	EMOTE_ONESHOT_CREATURE_SPECIAL = 393,
	EMOTE_ONESHOT_JUMPANDRUN	   = 394,
	EMOTE_ONESHOT_JUMPEND		  = 395,
	EMOTE_ONESHOT_TALK_NOSHEATHE   = 396,
	EMOTE_ONESHOT_POINT_NOSHEATHE  = 397,
	EMOTE_STATE_CANNIBALIZE		= 398,
	EMOTE_ONESHOT_JUMPSTART		= 399,
	EMOTE_STATE_DANCESPECIAL	   = 400,
	EMOTE_ONESHOT_DANCESPECIAL	 = 401,
	EMOTE_ONESHOT_CUSTOMSPELL01	= 402,
	EMOTE_ONESHOT_CUSTOMSPELL02	= 403,
	EMOTE_ONESHOT_CUSTOMSPELL03	= 404,
	EMOTE_ONESHOT_CUSTOMSPELL04	= 405,
	EMOTE_ONESHOT_CUSTOMSPELL05	= 406,
	EMOTE_ONESHOT_CUSTOMSPELL06	= 407,
	EMOTE_ONESHOT_CUSTOMSPELL07	= 408,
	EMOTE_ONESHOT_CUSTOMSPELL08	= 409,
	EMOTE_ONESHOT_CUSTOMSPELL09	= 410,
	EMOTE_ONESHOT_CUSTOMSPELL10	= 411,
	EMOTE_STATE_EXCLAIM			= 412,
} EmoteType;

enum StandState
{
	STANDSTATE_STAND			= 0,
	STANDSTATE_SIT			  = 1,
	STANDSTATE_SIT_CHAIR		= 2,
	STANDSTATE_SLEEP			= 3,
	STANDSTATE_SIT_LOW_CHAIR	= 4,
	STANDSTATE_SIT_MEDIUM_CHAIR = 5,
	STANDSTATE_SIT_HIGH_CHAIR   = 6,
	STANDSTATE_DEAD			 = 7,
	STANDSTATE_KNEEL			= 8
};

enum UnitFieldBytes1
{
	U_FIELD_BYTES_ANIMATION_FROZEN = 0x01,
};

enum UnitFieldBytes2
{
	U_FIELD_BYTES_HIDE_POS_AURAS = 0x01,
};

enum UnitFieldFlags
{										  //  = 0x01
										  //   = 0x02,
	U_FIELD_FLAG_LOCK_PLAYER				   = 0x04,
	U_FIELD_FLAG_PLAYER_CONTROLLED			 = 0x08,
								//			 = 0x10
										//	 = 0x20
	U_FIELD_FLAG_PLUS_MOB					  = 0x40,
	//										 = 0x80
	U_FIELD_FLAG_UNIT_UNTACKABLE_SELECT		= 0x100,
	//										 = 0x200,
	U_FIELD_ANIMATION_LOOTING				  = 0x400,
	U_FIELD_SELF_RES						   = 0x800,
	U_FIELD_FLAG_PVP						   = 0x1000,
	U_FIELD_FLAG_MOUNT_SIT					 = 0x2000,
	U_FIELD_FLAG_DEAD						  = 0x4000,
										//	 = 0x8000
	U_FIELD_FLAG_ALIVE						 = 0x10000,
	//										 = 0x20000,
	U_FIELD_FLAG_NO_ROTATE					 = 0x40000,
	U_FIELD_FLAG_ATTACK_ANIMATION			  = 0x80000,
	U_FIELD_FLAG_UNIT_UNTACKABLE_SELECT_2	  = 0x100000, //AI, UNIT can attack non players.
	//										 = 0x200000,
	//										 = 0x400000,
	//										 = 0x800000,
	U_FIELD_FLAG_PLAYER_CONTROLLED_CREATURE	= 0x1000000,
	U_FIELD_FLAG_UNIT_UNTACKABLE_NO_SELECT	 = 0x2000000, //AI, UNIT cant attack any unit, no name is displayed
	U_FIELD_FLAG_SKINNABLE					 = 0x4000000,
	U_FIELD_FLAG_MAKE_CHAR_UNTOUCHABLE		 = 0x8000000,
	U_FIELD_FLAG_WEAPON_OFF					= 0x40000000,
};

enum UnitDynamicFlags
{
	U_DYN_FLAG_LOOTABLE				 = 0x01,
	U_DYN_FLAG_UNIT_TRACKABLE		   = 0x02,
	U_DYN_FLAG_TAGGED_BY_OTHER		  = 0x04,
	U_DYN_FLAG_TAPPED_BY_PLAYER		 = 0x08,
	U_DYN_FLAG_PLAYER_INFO			  = 0x10,
	U_DYN_FLAG_DEAD					 = 0x20,
};

enum DamageFlags
{
	DAMAGE_FLAG_MELEE   = 1,
	DAMAGE_FLAG_HOLY	= 2,
	DAMAGE_FLAG_FIRE	= 4,
	DAMAGE_FLAG_NATURE  = 8,
	DAMAGE_FLAG_FROST   = 16,
	DAMAGE_FLAG_SHADOW  = 32,
	DAMAGE_FLAG_ARCANE  = 64
};

enum DamageType
{
	MELEE,
	DUALWIELD,
	RANGED,
};

enum VisualState
{
	ATTACK = 1,
	DODGE,
	PARRY,
	INTERRUPT,
	BLOCK,
	EVADE,
	IMMUNE,
	DEFLECT
};

enum HitStatus
{
	HITSTATUS_HITANIMATION   = 0x02,
	HITSTATUS_DUALWIELD	   = 0x04,
	HITSTATUS_MISS			= 0x10,
	HITSTATUS_ABSORBED		= 0x20,
	HITSTATUS_RESIST		  = 0x40,
	HITSTATUS_CRICTICAL	   = 0x80,
	HITSTATUS_GLANCING		= 0x4000,
	HITSTATUS_CRUSHINGBLOW	= 0x8000,
	HITSTATUS_NOACTION		= 0x10000,
	HITSTATUS_SWINGNOHITSOUND = 0x80000 // as in miss?
};

enum INVISIBILTY_FLAG
{
	INVISIBILTY_FLAG_NONE,
	INVISIBILTY_FLAG_UNIT_SPIRIT,
	INVISIBILTY_FLAG_UNK_SPIRIT,
	INVISIBILTY_FLAG_TRAP,
	INVISIBILTY_FLAG_QUEST_INVISIBILITY,
	INVISIBILTY_FLAG_GHOSTS,
	INVISIBILTY_FLAG_UNK1,
	INVISIBILTY_FLAG_UNK2,
	INVISIBILTY_FLAG_SHADOWMOON_GHOSTWORLD,
	INVISIBILTY_FLAG_NETHERSTORM_UNK,
	INVISIBILTY_FLAG_TOTAL
};

enum FIELD_PADDING//Since this field isnt used you can expand it for you needs
{
	PADDING_NONE,
	PADDING_INVISIBILTY_UNIT_SPIRIT,
	PADDING_INVISIBILTY_UNK_SPIRIT,
	PADDING_INVISIBILTY_TRAP,
	PADDING_INVISIBILTY_QUEST_INVISIBILITY,
	PADDING_INVISIBILTY_GHOSTS,
	PADDING_INVISIBILTY_TOTAL
};

struct AuraCheckResponse
{
	uint32 Error;
	uint32 Misc;
};

enum AURA_CHECK_RESULT
{
	AURA_CHECK_RESULT_NONE				  = 1,
	AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT   = 2,
	AURA_CHECK_RESULT_LOWER_BUFF_PRESENT	= 3,
};

typedef std::set<uint64> AttackerSet;
typedef std::list<struct ProcTriggerSpellOnSpell> ProcTriggerSpellOnSpellList;
//====================================================================
//  Unit
//  Base object for Players and Creatures
//====================================================================
class SERVER_DECL Unit : public Object
{
public:
	virtual ~Unit ( );

	friend class AIInterface;
	friend class Aura;

	virtual void Update( uint32 time );
	virtual void AddToWorld();
	virtual void RemoveFromWorld();
	virtual void OnPushToWorld();

	inline void setAttackTimer(int32 time, bool offhand)
	{
		if(!time)
			time = offhand ? m_uint32Values[UNIT_FIELD_BASEATTACKTIME_01] : m_uint32Values[UNIT_FIELD_BASEATTACKTIME];

		time += (time*modAttackTimeIncreasePCT)/100;

		if(offhand)
			m_attackTimer_1 = getMSTime() + time;
		else
			m_attackTimer = getMSTime() + time;
	}

	inline bool isAttackReady(bool offhand) const
	{
		if(!offhand)
			return getMSTime() >= m_attackTimer;
		else
			return getMSTime() >= m_attackTimer_1;
	}

	inline void SetDuelWield(bool enabled)
	{
		m_duelWield = enabled;
	}

	bool __fastcall canReachWithAttack(Unit *pVictim);

  //  void StrikeWithAbility(Unit *pVictim,Spell*spell,uint32 addspelldmg,uint32 damage_type);

	/// State flags are server-only flags to help me know when to do stuff, like die, or attack
	inline void addStateFlag(uint32 f) { m_state |= f; };
	inline bool hasStateFlag(uint32 f) { return (m_state & f ? true : false); }
	inline void clearStateFlag(uint32 f) { m_state &= ~f; };

	/// Stats
	inline uint32 getLevel() { return m_uint32Values[ UNIT_FIELD_LEVEL ]; };
	inline uint8 getRace() { return ((uint8)m_uint32Values[ UNIT_FIELD_BYTES_0]); }
	inline uint8 getClass() { return GetByte(UNIT_FIELD_BYTES_0,1); }
	inline void setRace(uint8 race) { SetByte(UNIT_FIELD_BYTES_0,0,race); }
	inline void setClass(uint8 class_) { SetByte(UNIT_FIELD_BYTES_0,1, class_ ); }
	inline uint32 getClassMask() { return 1 << (getClass() - 1); }
	inline uint32 getRaceMask() { return 1 << (getRace() - 1); }
	inline uint8 getGender() { return GetByte(UNIT_FIELD_BYTES_0,2); }
	inline void setGender(uint8 gender) { SetByte(UNIT_FIELD_BYTES_0,2,gender); }
	inline uint8 getStandState() { return ((uint8)m_uint32Values[UNIT_FIELD_BYTES_1]); }
 
	//// Combat
   // void DealDamage(Unit *pVictim, uint32 damage, uint32 targetEvent, uint32 unitEvent, uint32 spellId = 0);   // to stop from falling, etc
	//void AttackerStateUpdate(Unit *pVictim,uint32 damage_type);//0-melee,1-offhand(dual wield),2-ranged
	void Strike(Unit *pVictim,uint32 damage_type,SpellEntry *ability,int32 add_damage,int32 pct_dmg_mod,uint32,bool);
//	void PeriodicAuraLog(Unit *pVictim, SpellEntry* spellID, uint32 damage, uint32 damageType);
	//void SpellNonMeleeDamageLog(Unit *pVictim, uint32 spellID, uint32 damage);
	void HandleProc(uint32 flag, Unit* Victim, SpellEntry* CastingSpell,uint32 dmg=-1);
	void HandleProcDmgShield(uint32 flag, Unit* Victim);//almost the same as handleproc :P
//	void HandleProcSpellOnSpell(Unit* Victim,uint32 damage,bool critical);//nasty, some spells proc other spells

	int32 GetAP();
	int32 GetRAP();

	void CastSpell(Unit* Target, uint32 SpellID, bool triggered);
	void CastSpell(Unit* Target, SpellEntry* Sp, bool triggered);
	void CastSpell(uint64 targetGuid, uint32 SpellID, bool triggered);
	void CastSpell(uint64 targetGuid, SpellEntry* Sp, bool triggered);
	void CastSpellAoF(float x,float y,float z,SpellEntry* Sp, bool triggered);

	bool isCasting();
	   void CalculateResistanceReduction(Unit *pVictim,dealdamage *dmg) ;
	void RegenerateHealth();
	void RegeneratePower();
	inline void setHRegenTimer(uint32 time) {m_H_regenTimer = time; }
	inline void setPRegenTimer(uint32 time) {m_P_regenTimer = time; }
	void DeMorph();
	uint32 ManaShieldAbsorb(uint32 dmg);
	void smsg_AttackStart(Unit* pVictim);
	void smsg_AttackStop(Unit* pVictim);
	void smsg_AttackStop(uint64 victimGuid);
	
	bool IsDazed();
	

	// Stealth  
	inline uint32 GetStealthLevel() { return m_stealthLevel+ 5* m_uint32Values[UNIT_FIELD_LEVEL]; }
	inline int32 GetStealthDetect() { return 5 * getLevel() + m_stealthDetectBonus; }
	inline uint32 GetStealthDetectBonus() { return m_stealthDetectBonus; }
	inline void SetStealth(uint32 id) { m_stealth = id; }
	inline bool IsStealth() { return (bool)m_stealth; }
	bool HasAura(uint32 visualid);//not spell id!!!
	bool HasActiveAura(uint32 spelllid);
	bool HasActiveAura(uint32 spelllid,uint64);
	
	uint16 InvisibilityDetectBonus[INVISIBILTY_FLAG_TOTAL];
	inline uint32 GetInvisibiltyDetection(INVISIBILTY_FLAG flag) { return getLevel() + InvisibilityDetectBonus[flag] - 1; }

	void GiveGroupXP(Unit *pVictim, Player *PlayerInGroup);

	/// Combat / Death Status
	inline bool isAlive() { return m_deathState == ALIVE; };
	inline bool isDead() { return  m_deathState !=ALIVE; };
	virtual void setDeathState(DeathState s) {
		m_deathState = s;
	};
	DeathState getDeathState() { return m_deathState; }
	void OnDamageTaken();

	//! Add Aura to unit
	void AddAura(Aura *aur);
	//! Remove aura from unit
	bool RemoveAura(Aura *aur);
	bool RemoveAura(uint32 spellId);
	bool RemoveAura(uint32 spellId,uint64 guid);
	bool RemoveAuraByNameHash(uint32 namehash);//required to remove weaker instances of a spell
	bool RemoveAuraPosByNameHash(uint32 namehash);//required to remove weaker instances of a spell
	bool RemoveAuraNegByNameHash(uint32 namehash);//required to remove weaker instances of a spell
	void EventRemoveAura(uint32 SpellId)
	{
		RemoveAura(SpellId);
	}

	//! Remove all auras
	void RemoveAllAuras();
    void RemoveAllAuraType(uint32 auratype);//ex:to remove morph spells
	bool RemoveAllAuraByNameHash(uint32 namehash);//required to remove weaker instances of a spell
	bool RemoveAllPosAuraByNameHash(uint32 namehash);//required to remove weaker instances of a spell
	bool RemoveAllNegAuraByNameHash(uint32 namehash);//required to remove weaker instances of a spell
	void RemoveNegativeAuras();
	void RemoveAllAreaAuras();
	// Temporary remove all auras
	   // Find auras
	Aura* FindAura(uint32 spellId);
	Aura* FindAura(uint32 spellId, uint64 guid);
	bool SetAurDuration(uint32 spellId,Unit* caster,uint32 duration);
	bool SetAurDuration(uint32 spellId,uint32 duration);
	   void DropAurasOnDeath();
	   
	void castSpell(Spell * pSpell);
	void InterruptSpell();
   
	uint32 m_addDmgOnce;
	Creature *m_TotemSlots[4];
	uint32 m_ObjectSlots[4];
	uint32 m_triggerSpell;
	uint32 m_triggerDamage;
	uint32 m_canMove;
	
	// Spell Effect Variables
	uint16 m_silenced;
	std::list<struct DamageProc> m_damageShields;
	std::list<struct ReflectSpellSchool*> m_reflectSpellSchool;
 
	std::list<struct ProcTriggerSpell> m_procSpells;
//	std::map<uint32,ProcTriggerSpellOnSpellList> m_procSpellonSpell; //index is namehash
	std::map<uint32,struct SpellCharge> m_chargeSpells;
	inline void SetOnMeleeSpell(uint32 spell ) { m_meleespell = spell; }
	inline uint32 GetOnMeleeSpell() { return m_meleespell; }

	// Spell Crit
	float spellcritperc;

	// AIInterface
	AIInterface *GetAIInterface() { return m_aiInterface; }
	void WipeHateList();
	void WipeTargetList();
	inline void setAItoUse(bool value){m_useAI = value;}


	int32 GetThreatModifyer() { return m_threatModifyer; }
	void ModThreatModifyer(int32 mod) { m_threatModifyer += mod; }
	int32 GetGeneratedThreatModifyer() { return m_generatedThreatModifyer; }
	void ModGeneratedThreatModifyer(int32 mod) { m_generatedThreatModifyer += mod; }

	// DK:Affect
	inline uint32 IsPacified() { return m_pacified; }
	inline uint32 IsStunned() { return m_stunned; }
	inline uint32 GetResistChanceMod() { return m_resistChance; }
	inline void SetResistChanceMod(uint32 amount) { m_resistChance=amount; }
	
	inline uint16 HasNoInterrupt() { return m_noInterrupt; }
	bool setDetectRangeMod(uint64 guid, int32 amount);
	void unsetDetectRangeMod(uint64 guid);
	int32 getDetectRangeMod(uint64 guid);

	void RemoveBySpecialType(uint32 id,uint64 guid);
   
	Loot loot;
	uint32 SchoolCastPrevent[7];
	int32 GetDamageDoneMod(uint32 school);
	float GetDamageDonePctMod(uint32 school);
	int32 DamageTakenMod[7];
	float DamageTakenPctMod[7];
	float DamageTakenPctModOnHP;
	int32 RangedDamageTaken;
	void CalcDamage();
	float BaseDamage[2];
	float BaseOffhandDamage[2];
	float BaseRangedDamage[2];
	std::set<uint64> VampEmbCaster;
	uint64 VampTchCaster;
	void VampiricEmbrace(uint32 dmg,Unit* tgt);
	void VampiricTouch(uint32 dmg,Unit* tgt);
	SchoolAbsorb Absorbs[7];
	uint32 AbsorbDamage(uint32 School,uint32 * dmg);//returns amt of absorbed dmg, decreases dmg by absorbed value
	int32 RAPvModifier;
	int32 APvModifier;
	uint64 stalkedby;
	uint32 dispels[10];
	bool trackStealth;
	uint32 MechanicsDispels[27];
	float MechanicsResistancesPCT[27]; 
	int32 modAttackTimeIncreasePCT;
	int32 RangedDamageTakenPct; 

	//SM
	int32 * SM_CriticalChance;//flat
	int32 * SM_FDur;//flat
	int32 * SM_PDur;//pct
	int32 * SM_PRadius;//pct
	int32 * SM_FRadius;//flat
	int32 * SM_PRange;//pct
	int32 * SM_FRange;//flat
	int32 * SM_PCastTime;//pct
	int32 * SM_FCastTime;//flat
	int32 * SM_PCriticalDamage;
	int32 * SM_PDOT;//pct
	int32 * SM_FDOT;//flat
	int32 * SM_FEffectBonus;//flat
	int32 * SM_PEffectBonus;//pct
	int32 * SM_FDamageBonus;//flat
	int32 * SM_PDamageBonus;//pct
	int32 * SM_PDummy;//pct
	int32 * SM_FDummy;//flat
	int32 * SM_FResist;//flat
	int32 * SM_PAPBonus;//pct
	int32 * SM_PCost;
	int32 * SM_FCost;
	int32 * SM_PNonInterrupt;
	int32 * SM_PJumpReduce;
	int32 * SM_FSpeedMod;
	int32 * SM_FAdditionalTargets;
	int32 * SM_FPenalty;//flat
	int32 * SM_PPenalty;//Pct
	int32 * SM_PCooldownTime;
	int32 * SM_FCooldownTime;
	int32 * SM_FChanceOfSuccess;

	//Events
	void Emote (EmoteType emote);
	void EventAddEmote(EmoteType emote, uint32 time);
	void EmoteExpire();
	inline void setEmoteState(uint8 emote) { m_emoteState = emote; };
	inline uint32 GetOldEmote() { return m_oldEmote; }
	void EventSummonPetExpire();
	void EventAurastateExpire(uint32 aurastateflag){RemoveFlag(UNIT_FIELD_AURASTATE,aurastateflag);} //hmm this looks like so not necesary :S
	void EventHealthChangeSinceLastUpdate();

	void SetStandState (uint8 standstate);

	inline StandState GetStandState()
	{
		uint32 bytes1 = GetUInt32Value (UNIT_FIELD_BYTES_1);
		return StandState (uint8 (bytes1));
	}

	void SendChatMessage(uint8 type, uint32 lang, const char *msg);
	void SendChatMessageAlternateEntry(uint32 entry, uint8 type, uint32 lang, const char * msg);
	void RegisterPeriodicChatMessage(uint32 delay, uint32 msgid, std::string message, bool sendnotify);

	void DelayedChatMessage(uint32 delay, uint32 msgid, std::string message, bool sendnotify);
	void SendNotifyToNearby(uint32 msgid);
	void SendNotifyToNearbyCreature(uint32 msgid, uint32 entryid);

	inline int GetHealthPct() { return (int)(GetUInt32Value(UNIT_FIELD_HEALTH) * 100 / GetUInt32Value(UNIT_FIELD_MAXHEALTH)); };
	inline int GetManaPct() { return (int)(GetUInt32Value(UNIT_FIELD_POWER1) * 100 / GetUInt32Value(UNIT_FIELD_MAXPOWER1)); };
		
	uint32 GetResistance(uint32 type);	
	
	//Pet
	inline void SetIsPet(bool chck) { m_isPet = chck; }
	
	inline AttackerSet::iterator GetAttackersetBegin() { return m_attackers.begin(); }
	inline AttackerSet::iterator GetAttackersetEnd() { return m_attackers.end(); }
	inline int GetAttackersetSize() { return m_attackers.size(); }
	inline uint64 getAttackTarget() { return m_attackTarget; }
	inline bool IsBeingAttackedBy(Unit *pUnit) { return m_attackers.count(pUnit->GetGUID()) > 0; }

	virtual bool isInCombat() { return (m_attackers.size() > 0 || m_attackTarget != 0); }

	//In-Range
	virtual void AddInRangeObject(Object* pObj);
	virtual void RemoveInRangeObject(Object* pObj);
	void ClearInRangeSet();

	inline Spell * GetCurrentSpell(){return m_currentSpell;}
	inline void SetCurrentSpell(Spell* cSpell) { m_currentSpell = cSpell; }

	uint32 m_CombatUpdateTimer;

	// Attacker stuff
	void addAttacker(Unit *pUnit);
	void removeAttacker(Unit *pUnit);
	void setAttackTarget(Unit* pUnit);
	void clearAttackers(bool bFromOther);
	inline void setcanperry(bool newstatus){can_parry=newstatus;}
		
	std::map<uint32,Aura*> tmpAura;

	uint32 BaseResistance[7]; //there are resistances for silence, fear, mechanics ....
	uint32 BaseStats[5];
	int32 HealDoneMod[7];
	int32 HealDonePctMod[7];
	int32 HealTakenMod[7];
	float HealTakenPctMod[7];
	uint32 SchoolImmunityList[7];
	float SpellCritChanceSchool[7];
	int32 PowerCostMod[7];
	float PowerCostPctMod[7];
	int32 AttackerSpellCritChanceMod[7];
	uint32 SpellDelayResist[7];
	int32 CreatureAttackPowerMod[12];
	int32 CreatureRangedAttackPowerMod[12];

	float PctRegenModifier;//1.0 by default
	float PctPowerRegenModifier[4];
	inline uint32 GetPowerType(){ return (GetUInt32Value(UNIT_FIELD_BYTES_0)>> 24);}

	void RemoveSoloAura(uint32 type);

	void RemoveAurasByInterruptFlag(uint32 flag);
	void RemoveAurasByInterruptFlagButSkip(uint32 flag, uint32 skip);
	// Auras Modifiers
	int32 m_pacified;
	int32 m_interruptRegen;
	int32 m_resistChance;
	int32 m_powerRegenPCT;
	int32 m_stunned;
	bool m_invisible;
	int32 m_extraattacks;   
	//std::set<SpellEntry*> m_onStrikeSpells;

	int32 m_noInterrupt;
	   uint32 m_sleep;
	uint32 m_rooted;
	bool disarmed;
	uint64 m_detectRangeGUID[5];
	int32  m_detectRangeMOD[5];
	// Affect Speed
	int32 m_speedModifier;
	int32 m_slowdown;
	map< uint32, pair<SpellEntry*, uint32> > speedReductionMap;
	void GetSpeedDecrease();
	int32 m_mountedspeedModifier;
	int32 m_flyspeedModifier;
	void UpdateSpeed(bool delay = false);
	void EnableFlight(bool delay = false);
	void DisableFlight(bool delay = false);

	// Escort Quests
	//uint32 m_escortquestid;
	//uint32 m_escortupdatetimer;
	//bool bHasEscortQuest;
	//bool bEscortActive;
	//bool bStopAtEndOfWaypoints;
	//bool bReturnOnDie;
	//Player *q_AttachedPlayer;
	//uint16 m_escortStartWP;
	//uint16 m_escortEndWP;
	/*void InitializeEscortQuest(uint32 questid, bool stopatend, bool returnondie);
	void EscortSetStartWP(uint32 wp);
	void EscortSetEndWP(uint32 wp);
	void StartEscortQuest();
	void PauseEscortQuest();
	void EndEscortQuest();*/
	void MoveToWaypoint(uint32 wp_id);	
	void PlaySoundToSet(uint32 sound_entry);
	void PlaySpellVisual(uint64 target, uint32 spellVisual);
	bool m_isPet;
	uint32 m_stealth;

	Aura* m_auras[MAX_AURAS+MAX_PASSIVE_AURAS];   

	int32 m_modlanguage;
	
	Creature *critterPet;
	Creature *summonPet;

	inline uint32 GetCharmTempVal() { return m_charmtemp; }
	inline void SetCharmTempVal(uint32 val) { m_charmtemp = val; }
	set<uint32> m_SpellList;

	inline void DisableAI() { m_useAI = false; }
	inline void EnableAI() { m_useAI = true; }

	inline void SetPowerType(uint8 type)
	{
		SetByte(UNIT_FIELD_BYTES_0,3,type);
	}

	inline bool IsSpiritHealer()
	{
		switch(GetEntry())
		{
		case 6491:  // Spirit Healer
		case 13116: // Alliance Spirit Guide
		case 13117: // Horde Spirit Guide
			{
				return true;
			}break;
		}
		return false;
	}

	void Root();
	void Root(uint32 time);
	void Unroot();

	void RemoveAurasByBuffType(uint32 buff_type, uint64 guid);
	bool HasAurasOfBuffType(uint32 buff_type, uint64 guid);
	bool HasAurasWithNameHash(uint32 name_hash);
	bool HasNegativeAuraWithNameHash(uint32 name_hash); //just to reduce search range in some cases

	AuraCheckResponse AuraCheck(uint32 name_hash, uint32 rank);
	AuraCheckResponse AuraCheck(uint32 name_hash, uint32 rank, Aura* aur);

	uint16 m_diminishCount[16];
	uint8  m_diminishAuraCount[16];
	uint16 m_diminishTimer[16];
	bool   m_diminishActive;

	void SetDiminishTimer(uint32 index)
	{
		m_diminishTimer[index] = 15000;
	}

	DynamicObject * dynObj;

	uint32 AddAuraVisual(uint32 spellid, uint32 count, bool positive);
	void SetAuraSlotLevel(uint32 slot, bool positive);

	void RemoveAuraVisual(uint32 spellid, uint32 count);
	bool HasVisibleAura(uint32 spellid);

	//! returns: aura stack count
	uint32 ModAuraStackCount(uint32 slot, int32 count);
	uint8 m_auraStackCount[MAX_AURAS];

	void RemoveAurasOfSchool(uint32 School, bool Positive);
	SpellEntry * pLastSpell;
	bool bProcInUse;
	bool bInvincible;
	Player * m_redirectSpellPackets;
	void UpdateVisibility();

	//solo target auras
	uint32 polySpell;
//	uint32 fearSpell;
	
protected:
	Unit ();

	uint32 m_meleespell;
	void _UpdateSpells(uint32 time);

	uint32 m_H_regenTimer;
	uint32 m_P_regenTimer;
	uint32 m_state;		 // flags for keeping track of some states
	uint32 m_attackTimer;   // timer for attack
	uint32 m_attackTimer_1;
	bool m_duelWield;

	/// Combat
	DeathState m_deathState;

	// Stealth
	uint32 m_stealthLevel;
	uint32 m_stealthDetectBonus;	
	
	// DK:pet
	//uint32 m_pet_state;
	//uint32 m_pet_action;

	// Spell currently casting
	Spell * m_currentSpell;

	// AI
	AIInterface *m_aiInterface;
	bool m_useAI;
	bool can_parry;//will be enabled by block spell
	int32 m_threatModifyer;
	int32 m_generatedThreatModifyer;

	//	float getDistance( float Position1X, float Position1Y, float Position2X, float Position2Y );	

	int32 m_manashieldamt;
	uint32 m_manaShieldId;

	// Quest emote
	uint8 m_emoteState;
	uint32 m_oldEmote;

	uint32 m_charmtemp;

	AttackerSet m_attackers;
	uint64 m_attackTarget;
};



#endif
