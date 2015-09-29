/****************************************************************************
 *
 * General Object Type File
 *
 */

#include "StdAfx.h"

#define GROWL_RANK_1 2649
#define GROWL_RANK_2 14916

void Pet::CreateAsSummon(uint32 entry, CreatureInfo *ci, Creature* created_from_creature, Unit *owner, SpellEntry* created_by_spell, uint32 type, uint32 expiretime)
{
    SetIsPet(true);

    //std::string myname = sWorld.GenerateName();

    if(!ci) return;
    m_Owner = static_cast<Player*>(owner);
    m_OwnerGuid = m_Owner->GetGUID();
    creature_info = ci;
    myFamily = sCreatureFamilyStore.LookupEntry(creature_info->Family);
    m_name = sCreatureFamilyStore.LookupString(myFamily->name);

    // Create ourself    
    Create(m_name.c_str(), owner->GetMapId(), owner->GetPositionX(), owner->GetPositionY(), owner->GetPositionZ(), owner->GetOrientation());
    SetUInt32Value(OBJECT_FIELD_ENTRY, entry);
    SetFloatValue(UNIT_MOD_CAST_SPEED, 1.0f);   // better set this one

    // Fields common to both lock summons and pets
    if(type & 0x2 && created_from_creature != NULL)
        SetUInt32Value(UNIT_FIELD_LEVEL, created_from_creature->getLevel());
    else
        SetUInt32Value(UNIT_FIELD_LEVEL,owner->GetUInt32Value(UNIT_FIELD_LEVEL));

    SetUInt32Value(UNIT_FIELD_DISPLAYID,  ci->DisplayID);
    SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, ci->DisplayID);
    SetUInt64Value(UNIT_FIELD_SUMMONEDBY, owner->GetGUID());
    SetUInt64Value(UNIT_FIELD_CREATEDBY, owner->GetGUID());
    
    if(type & 0x1 && created_by_spell != NULL)
        SetUInt64Value(UNIT_CREATED_BY_SPELL, created_by_spell->Id);

    if(type & 0x1 || created_from_creature == NULL)
    {
        Summon = true;
        SetUInt32Value(UNIT_FIELD_BYTES_0, 2048 | (0 << 24));
        SetUInt32Value(UNIT_FIELD_FLAGS, 8);
        SetUInt32Value(UNIT_FIELD_BASEATTACKTIME, 2000);
        SetUInt32Value(UNIT_FIELD_BASEATTACKTIME_01, 2000);
        SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 0.5f);
        SetFloatValue(UNIT_FIELD_COMBATREACH, 0.75f);
        SetUInt32Value(UNIT_FIELD_BYTES_2, (0x01 | (0x28 << 8) | (0x2 << 24)));
        SetUInt32Value(UNIT_FIELD_PETNUMBER, GetGUIDLow());
        SetPowerType(POWER_TYPE_MANA);
        m_name = sWorld.GenerateName();

    } else {
        SetUInt32Value(UNIT_FIELD_BYTES_0, 2048 | (0 << 24));
        SetUInt32Value(UNIT_FIELD_BASEATTACKTIME, created_from_creature->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
        SetUInt32Value(UNIT_FIELD_BASEATTACKTIME_01, created_from_creature->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME_01));
        SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, created_from_creature->GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS));
        SetFloatValue(UNIT_FIELD_COMBATREACH, created_from_creature->GetFloatValue(UNIT_FIELD_COMBATREACH));

        // These need to be checked.
        SetUInt32Value(UNIT_FIELD_FLAGS, 0x00080008);
        SetUInt32Value(UNIT_FIELD_POWER5, 600000);
        SetUInt32Value(UNIT_FIELD_MAXPOWER5, 1000000);
        SetUInt32Value(UNIT_FIELD_PETEXPERIENCE, 0);
        SetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP, GetNextLevelXP(getLevel()));
        SetUInt32Value(UNIT_FIELD_BYTES_1, 0 | (0x1 << 8));

        // Focus
        SetUInt32Value(UNIT_FIELD_POWER3, 100);
        SetUInt32Value(UNIT_FIELD_MAXPOWER3, 100);

        // 0x3 -> Enable pet rename.
        SetUInt32Value(UNIT_FIELD_BYTES_2, 1 | (0x28 << 8) | (0x3 << 16));

        // Change the power type to FOCUS
        SetPowerType(POWER_TYPE_FOCUS);

        // create our spellz
        SetDefaultSpells();
    }

    // Apply stats.
    ApplyStatsForLevel();

    BaseDamage[0]=GetFloatValue(UNIT_FIELD_MINDAMAGE);
    BaseDamage[1]=GetFloatValue(UNIT_FIELD_MAXDAMAGE);
    BaseOffhandDamage[0]=GetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE);
    BaseOffhandDamage[1]=GetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE);
    BaseRangedDamage[0]=GetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE);
    BaseRangedDamage[1]=GetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE);

    SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, owner->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
    m_PartySpellsUpdateTimer = 0;

    m_PetNumber = static_cast<Player*>(owner)->GeneratePetNumber();
    SetUInt32Value(UNIT_FIELD_PETNUMBER, GetGUIDLow());

    m_ExpireTime = expiretime;
    bExpires = m_ExpireTime > 0 ? true : false;

    if(!bExpires)
    {
        // Create PlayerPet struct (Rest done by UpdatePetInfo)
        PlayerPet *pp = new PlayerPet;
        pp->number = m_PetNumber;
        static_cast<Player*>(owner)->AddPlayerPet(pp, pp->number);
    }    

    InitializeMe(true);
}


Pet::Pet(uint32 high, uint32 low) : Creature(high, low)
{
    m_PetXP = 0;
    Summon = false;
    memset(ActionBar, 0, sizeof(uint32)*10);

    m_AutoCombatSpell = 0;

    m_PartySpellsUpdateTimer = 0;
    m_LoyaltyTimer = PET_LOYALTY_UPDATE_TIMER;
    m_PetNumber = 0;

    m_State = PET_STATE_DEFENSIVE;
    m_Action = PET_ACTION_FOLLOW;
    bHasLoyalty = false;
    m_ExpireTime = 0;
    bExpires = false;
    m_Diet = 0;
    m_Action = PET_ACTION_FOLLOW;
    m_State = PET_STATE_DEFENSIVE;
}

Pet::~Pet()
{
    for(std::map<uint32, AI_Spell*>::iterator itr = m_AISpellStore.begin(); itr != m_AISpellStore.end(); ++itr)
        delete itr->second;

    if(IsInWorld())
        this->Remove(false, true, true);
}

void Pet::Update(uint32 time)
{
    if(!m_Owner)
        return;

    Creature::Update(time); // passthrough

    if(bHasLoyalty)
    {
        if(m_LoyaltyTimer == 0)
        {
            // Update loyalty.....
            uint32 val = GetUInt32Value(UNIT_FIELD_POWER5);
            if(PET_LOYALTY_UPDATE_VALUE > val)
                val = 0;
            else
                val -= PET_LOYALTY_UPDATE_VALUE;
            
            // Set the value
            SetUInt32Value(UNIT_FIELD_POWER5, val);

            /*if(val <= 0)
            {
                Dismiss();
                return;
            }*/

            // reset timer
            m_LoyaltyTimer = PET_LOYALTY_UPDATE_TIMER;
        } else {
            if(time > m_LoyaltyTimer)
                m_LoyaltyTimer = 0;
            else
                m_LoyaltyTimer -= time;
        }
    }

    if(bExpires)
    {
        if(m_ExpireTime == 0)
        {
            // remove
            Dismiss(false);
            return;
        } else {
            if(time > m_ExpireTime)
            {
                m_ExpireTime = 0;
            } else {
                m_ExpireTime -= time;
            }
        }
    }
}

void Pet::SendSpellsToOwner()
{
    WorldPacket * data = new WorldPacket(SMSG_PET_SPELLS, mSpells.size() * 4 + 20);
    *data << GetGUID();
    *data << uint32(0x00000000);//unk1
    *data << uint32(0x00000101);//unk2

    // Send the actionbar
    for(uint32 i = 0; i < 10; ++i)
    {
        if(ActionBar[i] & 0x4000000)        // Command
            *data << uint32(ActionBar[i]);
        else
        {
            if(uint16(ActionBar[i]))
                *data << uint16(ActionBar[i]) << GetSpellState(ActionBar[i]);
            else
                *data << uint16(0) << uint8(0) << uint8(i+5);
        }
    }

    // Send the rest of the spells.
    *data << uint8(mSpells.size());
    for(PetSpellMap::iterator itr = mSpells.begin(); itr != mSpells.end(); ++itr)
    {
        *data << uint16(itr->first->Id) << uint16(itr->second);
    }
    *data << uint64(0);

    m_Owner->delayedPackets.add(data);
}

void Pet::SendNullSpellsToOwner()
{
    WorldPacket data;
    data.SetOpcode(SMSG_PET_SPELLS);
    data << uint64(0);
    m_Owner->GetSession()->SendPacket(&data);
}

void Pet::InitializeSpells()
{
    for(PetSpellMap::iterator itr = mSpells.begin(); itr != mSpells.end(); ++itr)
    {
        SpellEntry *info = itr->first;

        // Check that the spell isn't passive
        if(info->Attributes & 64)
        {
            // Cast on self..
            Spell * sp = new Spell(this, info, true, false);
            SpellCastTargets targets(this->GetGUID());
            sp->prepare(&targets);

            continue;
        }

        CreateAISpell(info);
    }

    SendSpellsToOwner();
}

void Pet::CreateAISpell(SpellEntry * info)
{
    // Create an AI_Spell
    AI_Spell *sp = new AI_Spell;
    sp->agent = AGENT_SPELL;
    sp->entryId = GetEntry();
    sp->floatMisc1 = 0;
    sp->maxrange = GetMaxRange(sSpellRange.LookupEntry(info->rangeIndex));
    sp->minrange = GetMinRange(sSpellRange.LookupEntry(info->rangeIndex));
    sp->Misc2 = 0;
    sp->procChance = 0;
    sp->spell = info;
    sp->spellType = STYPE_DAMAGE;
    sp->spelltargetType = TTYPE_SINGLETARGET;
    sp->cooldown = objmgr.GetPetSpellCooldown(info->Id);
    if(info->Effect[0] == SPELL_EFFECT_APPLY_AURA || info->Effect[0] == SPELL_EFFECT_APPLY_AREA_AURA)
        sp->agent = STYPE_BUFF;

    if(info->EffectImplicitTargetA[0] == 24)
    {
        float radius = ::GetRadius(sSpellRadius.LookupEntry(info->EffectRadiusIndex[0]));
        sp->maxrange = radius;
        sp->spelltargetType = TTYPE_SOURCE;
    }

    m_AISpellStore[info->Id] = sp;
    m_aiInterface->addSpellToList(sp);
}

void Pet::LoadFromDB(Player* owner, PlayerPet * pi)
{
    m_Owner = owner;
    m_OwnerGuid = m_Owner->GetGUID();
    mPi = pi;
    creature_info = CreatureNameStorage.LookupEntry(mPi->entry);

    Create(pi->name.c_str(), owner->GetMapId(), owner->GetPositionX() + 2 , owner->GetPositionY() +2, owner->GetPositionZ(), owner->GetOrientation());

    LoadValues(mPi->fields.c_str());
    m_PetNumber = mPi->number;
    m_PetXP = mPi->xp;
    m_name = mPi->name;
    Summon = mPi->summon;
    SetIsPet(true);

    // Setup actionbar
    uint32 pos = 0;
    string::size_type sp = mPi->actionbar.find(",");
    string::size_type lp = 0;
    while(sp != string::npos)
    {
        uint32 spell = atol(mPi->actionbar.substr(lp, sp).c_str());
        ActionBar[pos] = spell;
        ++pos;

        lp = sp+1;
        sp = mPi->actionbar.find(",", lp);
    }

    SetIsPet(true);
    InitializeMe(false);
    bExpires = false;   
    if(pi->autocastspell)
    {
        AI_Spell * sp = GetAISpellForSpellId(pi->autocastspell);
        if(sp)
        {
            sp->procChance = 100;
            m_aiInterface->disable_melee = true;
        }
    }
    
    if(m_Owner && getLevel() > m_Owner->getLevel())
    {
        SetUInt32Value(UNIT_FIELD_LEVEL, m_Owner->getLevel());
        SetUInt32Value(UNIT_FIELD_PETEXPERIENCE, 0);
        SetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP, GetNextLevelXP(m_Owner->getLevel()));
        ApplyStatsForLevel();
    }
    
    // Nuke auras
    for(uint32 x = UNIT_FIELD_AURA_01; x <= UNIT_FIELD_AURA_55; x++)
        SetUInt32Value(x, 0);
}

void Pet::InitializeMe(bool first)
{
    // set up ai and shit
    
    GetAIInterface()->Init(this,AITYPE_PET,MOVEMENTTYPE_NONE,m_Owner);
    GetAIInterface()->SetUnitToFollow(m_Owner);
    GetAIInterface()->SetFollowDistance(3.0f);

    SetCreatureName(CreatureNameStorage.LookupEntry(GetEntry()));
    m_Owner->SetSummon(this);
    m_Owner->SetUInt64Value(UNIT_FIELD_SUMMON, this->GetGUID());
    SetUInt32Value(UNIT_FIELD_PETNUMBER, GetGUIDLow());
    SetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP, (uint32)time(NULL));
    myFamily = sCreatureFamilyStore.LookupEntry(creature_info->Family);
    bHasLoyalty = m_Owner->getClass() == HUNTER ? true : false;
    SetPetDiet();
    _setFaction();
    m_State = 1;        // dont set agro on spawn
    
    if(first)
    {
        // Set up default actionbar
        SetDefaultActionbar();
    }

    PushToWorld(m_Owner->GetMapMgr());
    InitializeSpells(); 

    // Load our spells
    if(Summon)
    {
        SetDefaultSpells();
    }
    else
    {
        // Pull from database... :/
        QueryResult * query = CharacterDatabase.Query("SELECT * FROM playerpetspells WHERE ownerguid=%u and petnumber=%u",
            m_Owner->GetGUIDLow(), m_PetNumber);
        if(query)
        {
            do 
            {
                Field * f = query->Fetch();
                SpellEntry* spell = sSpellStore.LookupEntry(f[2].GetUInt32());
                uint16 flags = f[3].GetUInt16();
                mSpells.insert ( make_pair( spell, flags ) );
            } while(query->NextRow());
        }
        delete query;
    }


    sEventMgr.AddEvent(this, &Pet::Update, (uint32)100, EVENT_PET_UPDATE, 100, 0);

    // set to active
    if(!bExpires)
        UpdatePetInfo(false);
}

void Pet::UpdatePetInfo(bool bSetToOffline)
{
    if(bExpires)
        return;    // don't update expiring pets

    PlayerPet *pi = m_Owner->GetPlayerPet(m_PetNumber);
    pi->active = !bSetToOffline;
    pi->entry = GetEntry();
    std::stringstream ss;
    for( uint32 index = 0; index < UNIT_END; index ++ )
        ss << GetUInt32Value(index) << " ";
    pi->fields = ss.str();
    pi->name = GetName();
    pi->number = m_PetNumber;
    pi->xp = m_PetXP;
    pi->level = GetUInt32Value(UNIT_FIELD_LEVEL);
    pi->loyalty = GetUInt32Value(UNIT_FIELD_POWER5);
    pi->loyaltyupdate = m_LoyaltyTimer;

    // save actionbar
    ss.rdbuf()->str("");
    for(uint32 i = 0; i < 10; ++i)
    {
        ss << ActionBar[i] << ",";
    }

    pi->actionbar = ss.str();
    pi->summon = Summon;
    /*AI_Spell * sp = m_aiInterface->GetDefaultSpell();
    if(sp)
    {
        if(sp->agent == AGENT_SPELL)
            pi->autocastspell = sp->spell->Id;
        else
            pi->autocastspell = 0;
    }*/
    //FIXME
}

void Pet::Dismiss(bool bSafeDelete)
{
    // Delete any petspells for us.
    if(!Summon && m_Owner)
    {
        CharacterDatabase.Execute("DELETE FROM playerpetspells WHERE ownerguid=%u AND petnumber=%u",
            m_Owner->GetGUIDLow(), m_PetNumber);
    }

    if(m_Owner)
        m_Owner->RemovePlayerPet(m_PetNumber);

    // find out playerpet entry, delete it
    Remove(bSafeDelete, false, true);
}

void Pet::Remove(bool bSafeDelete, bool bUpdate, bool bSetOffline)
{
    if(m_Owner)
    {
        // remove association with player
        m_Owner->SetUInt64Value(UNIT_FIELD_SUMMON, 0);

        if(bUpdate && !bExpires) UpdatePetInfo(bSetOffline);
        m_Owner->SetSummon(NULL);
        SendNullSpellsToOwner();
    }
    ClearPetOwner();
/*    if(bSafeDelete)
        
    else*/
/*        PetSafeDelete();*/

    // has to be next loop - reason because of RemoveFromWorld, iterator gets broke.
    if(IsInWorld() && Active) Deactivate(m_mapMgr);
    sEventMgr.AddEvent(this, &Pet::PetSafeDelete, EVENT_CREATURE_SAFE_DELETE, 1, 1);
}

void Pet::PetSafeDelete()
{
    if(this->IsInWorld())
    {
        // remove from world, and delete
        RemoveFromWorld(false);
    }

    //sEventMgr.AddEvent(World::getSingletonPtr(), &World::DeleteObject, ((Object*)this), EVENT_CREATURE_SAFE_DELETE, 1000, 1);
    Creature::SafeDelete();
}

void Pet::DelayedRemove(bool bTime, bool bDeath)
{
    m_Owner = objmgr.GetPlayer(m_OwnerGuid);
    if(bTime)
    {
        if(GetUInt32Value(UNIT_CREATED_BY_SPELL) > 0 || bDeath)
            Dismiss(true);  // remove us..
        else
            Remove(true, true, true);
    }
    else
        sEventMgr.AddEvent(this, &Pet::DelayedRemove, true, bDeath, EVENT_PET_DELAYED_REMOVE, PET_DELAYED_REMOVAL_TIME, 1);
}

void Pet::GiveXP(uint32 xp)
{
    if(!m_Owner || getLevel() >= myFamily->maxlevel || getLevel() > m_Owner->getLevel()) return;
    
    xp += m_uint32Values[UNIT_FIELD_PETEXPERIENCE];
    uint32 nxp = m_uint32Values[UNIT_FIELD_PETNEXTLEVELEXP];
    bool changed = false;

    while(xp >= nxp)
    {
        ModUInt32Value(UNIT_FIELD_LEVEL, 1);
        xp -= nxp;
        nxp = GetNextLevelXP(m_uint32Values[UNIT_FIELD_LEVEL]);
        changed = true;
    }

    SetUInt32Value(UNIT_FIELD_PETEXPERIENCE, xp);
    SetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP, nxp);
    if(changed) ApplyStatsForLevel();
}

uint32 Pet::GetNextLevelXP(uint32 currentlevel)
{
    uint32 level = currentlevel + 1;
    uint32 nextLvlXP = 0;
    if( level > 0 && level <= 30 )
    {
        nextLvlXP = ((int)((((double)(8 * level * ((level * 5) + 45)))/100)+0.5))*100;
    }
    else if( level == 31 )
    {
        nextLvlXP = ((int)((((double)(((8 * level) + 3) * ((level * 5) + 45)))/100)+0.5))*100;
    }
    else if( level == 32 )
    {
        nextLvlXP = ((int)((((double)(((8 * level) + 6) * ((level * 5) + 45)))/100)+0.5))*100;
    }
    else
    {
        nextLvlXP = ((int)((((double)(((8 * level) + ((level - 30) * 5)) * ((level * 5) + 45)))/100)+0.5))*100;
    }
    double xp = double(nextLvlXP) / 4.0;
    return FL2UINT(xp);
}

void Pet::SetDefaultSpells()
{
    if(Summon)
    {
        // this one's easy :p we just pull em from the owner.
        map<uint32, set<uint32> >::iterator it1;
        set<uint32>::iterator it2;
        it1 = m_Owner->SummonSpells.find(GetEntry());
        if(it1 != m_Owner->SummonSpells.end())
        {
            it2 = it1->second.begin();
            for(; it2 != it1->second.end(); ++it2)
            {
                AddSpell((*it2));
            }
        }
    }
    else
    {
        // add growl (rank 1 for <=10, rank 2 for > 10)
        /*if(getLevel() <= 10)
            AddSpell(GROWL_RANK_1);
        else
            AddSpell(GROWL_RANK_2);

        // pull from objectmgr
        set<SpellEntry*> * spells = objmgr.GetDefaultPetSpells(GetEntry());
        if(spells != 0)
        {
            for(set<SpellEntry*>::iterator itr = spells->begin(); itr != spells->end(); ++itr)
            {
                AddSpell((*itr));
            }
        }*/

        uint32 Line = GetCreatureName()->SpellDataID;
        if(Line)
        {
            CreatureSpellDataEntry * SpellData = CreatureSpellDataStore::getSingleton().LookupEntry(Line);
            if(SpellData)
            {
                for(uint32 i = 0; i < 3; ++i)
                {
                    if(SpellData->Spells[i] != 0)
                    {
                        // add it to the player, so they can teach it to other pets
                        if(!m_Owner->HasSpell(SpellData->Spells[i]))
                        {
                            m_Owner->addSpell(SpellData->Spells[i]);
                        }

                        AddSpell(SpellData->Spells[i]);
                    }
                }
            }
        }
    }
}

void Pet::AddSpell(SpellEntry * sp)
{
    // Cast on self if we're a passive spell
    if(sp->Attributes & 64 && IsInWorld())
    {
        Spell * spell = new Spell(this, sp, true, false);
        SpellCastTargets targets(this->GetGUID());
        spell->prepare(&targets);
        mSpells[sp] = 0x0100;
    }
    else
    {
        mSpells[sp] = DEFAULT_SPELL_STATE;
        // Create the AI_Spell
        CreateAISpell(sp);
    }
    
    if(IsInWorld() && sp->Effect[0] == SPELL_EFFECT_APPLY_AREA_AURA)
    {
        // Autocast by default
        SetSpellState(sp, PET_ACTION_SPELL);

        // Add to the actionbar.
        for(int i = 0; i < 10; ++i)
            if(ActionBar[i] == 0)
                ActionBar[i] = sp->Id;

        // Cast it.
        CastSpell(this, sp, true);
    }
    if(IsInWorld())
        SendSpellsToOwner();
}

void Pet::SetSpellState(SpellEntry* sp, uint16 State)
{
    PetSpellMap::iterator itr = mSpells.find(sp);
    if(itr == mSpells.end())
        return;

    itr->second = State;
}

uint16 Pet::GetSpellState(SpellEntry* sp)
{
    PetSpellMap::iterator itr = mSpells.find(sp);
    if(itr == mSpells.end())
        return DEFAULT_SPELL_STATE;

    return itr->second;
}

void Pet::SetDefaultActionbar()
{
    // Set up the default actionbar.
    ActionBar[0] = PET_SPELL_ATTACK;
    ActionBar[1] = PET_SPELL_FOLLOW;
    ActionBar[2] = PET_SPELL_STAY;

    // Fill up 4 slots with our spells
    if(mSpells.size() > 0)
    {
        PetSpellMap::iterator itr = mSpells.begin();
        uint32 pos = 0;
        for(; itr != mSpells.end() && pos < 4; ++itr, ++pos)
            ActionBar[3+pos] = itr->first->Id;
    }

    ActionBar[7] = PET_SPELL_AGRESSIVE;
    ActionBar[8] = PET_SPELL_DEFENSIVE;
    ActionBar[9] = PET_SPELL_PASSIVE;
}

void Pet::RemoveSpell(SpellEntry * sp)
{
    mSpells.erase(sp);
    map<uint32, AI_Spell*>::iterator itr = m_AISpellStore.find(sp->Id);
    if(itr != m_AISpellStore.end())
    {
        delete itr->second;
        for(list<AI_Spell*>::iterator it = m_aiInterface->m_spells.begin(); it != m_aiInterface->m_spells.end(); ++it)
        {
            if((*it) == itr->second)
            {
                m_aiInterface->m_spells.erase(it);
                m_aiInterface->CheckNextSpell(itr->second);
                break;
            }
        }

        m_AISpellStore.erase(itr);
    }
}

void Pet::Rename(string NewName)
{
    m_name = NewName;
    // update petinfo
    UpdatePetInfo(false);

    // update timestamp to force a re-query
    SetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP, time(NULL));
}

void Pet::ApplySummonLevelAbilities()
{
    uint32 level = m_uint32Values[UNIT_FIELD_LEVEL];
    double pet_level = (double)level;

    // Determine our stat index.
    int stat_index = -1;
    //float scale = 1;
    bool has_mana = true;

    switch(m_uint32Values[OBJECT_FIELD_ENTRY])
    {
    case 416: //Imp
        stat_index = 0;
        break;
    case 1860: //VoidWalker
        stat_index = 1;
        break;
    case 1863: //Succubus
        stat_index = 2;
        break;
    case 417: //Felhunter
        stat_index = 3;
        break;
    case 11859: // Doomguard
    case 89:    // Infernal
    case 17252: // Felguard
        stat_index = 4;
        break;
    /*case 11859: // Doomguard
        stat_index = 4;
        break;
    case 89:    // Infernal
        stat_index = 5;
        has_mana = false;
        break;
    case 17252: // Felguard
        stat_index = 6;
        break;*/
    }
    if(m_uint32Values[OBJECT_FIELD_ENTRY] == 89)
        has_mana = false;

    if(stat_index < 0)
    {
        sLog.outError("PETSTAT: No stat index found for entry %u, `%s`!", GetEntry(), creature_info->Name);
        return;
    }

    /*
    ----------------------------
    ------- Warlock Pets -------
    ----------------------------
    pet_str = base_str + pet_lvl * mod_str
    pet_agi = base_agi + pet_lvl * mod_agi
    pet_sta = base_sta + pet_lvl * mod_sta + pet_sta_bonus
    pet_int = base_int + pet_lvl * mod_int + pet_int_bonus
    pet_spr = base_spr + pet_lvl * mod_spr
    pet_pwr = base_pwr + pet_lvl * mod_pwr
    pet_arm = base_arm + pet_lvl * mod_arm + pet_arm_bonus

    pet_sta_bonus = 0.3 * plyr_sta + sta_buffs
    pet_int_bonus = 0.3 * plyr_int + int_buffs
    pet_arm_bonus = 0.35 * plyr_arm + arm_buffs

    --[Imp]--
    base_str = 18.0    
    mod_str = 2.0
    base_agi = 20.2    
    mod_agi = 0.2
    base_sta = 19.5    
    mod_sta = 0.5
    base_int = 21.0    
    mod_int = 3.0
    base_spr = 19.0    
    mod_spr = 4.0
    base_pwr = 9.0    
    mod_pwr = 1.0
    base_arm = 47.0    
    mod_arm = 13.0

    --[Voidwalker]--
    base_str = 19.0    
    mod_str = 2.0
    base_agi = 15.0    
    mod_agi = 1.0
    base_sta = -13.0    
    mod_sta = 4.0
    base_int = 17.3    
    mod_int = 1.7
    base_spr = 9.0    
    mod_spr = 2.0
    base_pwr = -16.0
    mod_pwr = 4.0
    base_arm = 177.0    
    mod_arm = 50.0

    --[Succubus]--
    base_str = 2.0    
    mod_str = 2.0
    base_agi = 16.0    
    mod_agi = 1.0
    base_sta = -17.0    
    mod_sta = 4.5
    base_int = 9.0    
    mod_int = 2.0
    base_spr = 12.0    
    mod_spr = 1.3
    base_pwr = -26.0    
    mod_pwr = 4.0
    base_arm = 125.0    
    mod_arm = 23.0

    --[Felhunter]--
    base_str = -3.0    
    mod_str = 2.0
    base_agi = 16.0    
    mod_agi = 1.0
    base_sta = 36.0    
    mod_sta = 3.0
    base_int = 9.0    
    mod_int = 2.0
    base_spr = 21.0    
    mod_spr = 1.0
    base_pwr = -26.0    
    mod_pwr = 4.0
    base_arm = -910.0
    mod_arm = 57.0

    --[Doomguard]--
    base_str = 9.0    
    mod_str = 2.0
    base_agi = -5.0    
    mod_agi = 1.5
    base_sta = -66.0
    mod_sta = 5.0
    base_int = 10.0
    mod_int = 1.0
    base_spr = 30.0
    mod_spr = 2.0
    base_pwr = -62.0
    mod_pwr = 5.0
    base_arm = -187.0
    mod_arm = 65.0

    --[Infernal]--
    base_str = -14.0
    mod_str = 2.5
    base_agi = -20.0
    mod_agi = 2.0
    base_sta = -44.0
    mod_sta = 5.0
    base_int = 20.0    
    mod_int = 0.5
    base_spr = -40.0
    mod_spr = 2.0
    base_pwr = -48.0
    mod_pwr = 5.0
    base_arm = 1605.0
    mod_arm = 50.0

    --[Felguard]--
    base_str = -39.0
    mod_str = 3.0
    base_agi = 7.0    
    mod_agi = 1.5
    base_sta = -14.0    
    mod_sta = 6.0
    base_int = 82.0    
    mod_int = 2.0
    base_spr = -12.0    
    mod_spr = 2.0
    base_pwr = -68.0    
    mod_pwr = 5.5
    base_arm = 1208.0
    mod_arm = 47.0
    */

    // Imp,Voidwalker,Succubus,Felhunter,Doomguard,Infernal,Felguard
    /*static double R_base_str[7] = { 18.1884058,-15,-15,-15,-15, -14, -39 };
    static double R_mod_str[7] = { 1.811594203,2.4,2.4,2.4,2.4, 2.5, 3 };
    static double R_base_agi[7] = { 20.2, 15, 16, 16, -5, -20, 7 };
    static double R_mod_agi[7] = { 0.2, 1, 1, 1, 1.5, 2, 1.5 };
    static double R_base_sta[7] = { 19.5, -13, -17, 36, -66, -44, -14 };
    static double R_mod_sta[7] = { 0.5, 4, 4.5, 3, 5, 5, 6 };
    static double R_base_int[7] = { 21, 17.3, 9, 9, 10, 20, 82 };
    static double R_mod_int[7] = { 3, 1.7, 2, 2, 1, 0.5, 2 };
    static double R_base_spr[7] = { 19, 9, 12, 21, 30, -40, -12 };
    static double R_mod_spr[7] = { 4, 2, 1.3, 1, 2, 2, 2 };
    static double R_base_pwr[7] = { 9, -16, -26, -26, -62, -48, -68 };
    static double R_mod_pwr[7] = { 1, 4, 4, 4, 5, 5, 5.5 };
    static double R_base_arm[7] = { 47, 177, 125, -910, -187, 1605, 1208 };
    static double R_mod_arm[7] = { 13, 50, 23, 57, 65, 50, 47 };

    double base_str = R_base_str[stat_index];
    double mod_str = R_mod_str[stat_index];
    double base_agi = R_base_agi[stat_index];
    double mod_agi = R_mod_agi[stat_index];
    double base_sta = R_base_sta[stat_index];
    double mod_sta = R_mod_sta[stat_index];
    double base_int = R_base_int[stat_index];
    double mod_int = R_mod_int[stat_index];
    double base_spr = R_base_spr[stat_index];
    double mod_spr = R_mod_spr[stat_index];
    double base_pwr = R_base_pwr[stat_index];
    double mod_pwr = R_mod_pwr[stat_index];
    double base_arm = R_base_arm[stat_index];
    double mod_arm = R_mod_arm[stat_index];

    // Calculate bonuses
    double pet_sta_bonus = 0.3 * (double)m_Owner->BaseStats[STAT_STAMINA];
    double pet_int_bonus = 0.3 * (double)m_Owner->BaseStats[STAT_INTELLECT];
    double pet_arm_bonus = 0.35 * (double)m_Owner->BaseResistance[0];

    double pet_str = base_str + pet_level * mod_str;
    double pet_agi = base_agi + pet_level * mod_agi;
    double pet_sta = base_sta + pet_level * mod_str + pet_sta_bonus;
    double pet_int = base_int + pet_level * mod_int + pet_int_bonus;
    double pet_spr = base_spr + pet_level * mod_spr;
    double pet_pwr = base_pwr + pet_level * mod_pwr;
    double pet_arm = base_arm + pet_level * mod_arm;
    
    // Calculate actual values.
    BaseStats[STAT_STRENGTH] = FL2UINT(pet_str);
    BaseStats[STAT_AGILITY] = FL2UINT(pet_agi);
    BaseStats[STAT_STAMINA] = FL2UINT(pet_sta);
    BaseStats[STAT_INTELLECT] = FL2UINT(pet_int);
    BaseStats[STAT_SPIRIT] = FL2UINT(pet_spr);
    
    for(uint32 x = 0; x < 5; ++x)
        CalcStat(x);

    // Apply armor and attack power.
    SetUInt32Value(UNIT_FIELD_ATTACK_POWER, FL2UINT(pet_pwr));
    BaseResistance[0] = FL2UINT(pet_arm);
    CalcResistance(0);
    CalcDamage();

    // Calculate health / mana
    double health = pet_sta * 10;
    double mana = has_mana ? (base_int * 15) : 0.0;
    SetUInt32Value(UNIT_FIELD_BASE_HEALTH, FL2UINT(health));
    SetUInt32Value(UNIT_FIELD_BASE_MANA, FL2UINT(mana));*/

    static double R_base_str[5] = {18.1884058, -15, -15, -15, -15};
    static double R_mod_str[5] = {1.811594203, 2.4, 2.4, 2.4, 2.4};
    static double R_base_agi[5] = {19.72463768, -1.25, -1.25, -1.25, -1.25};
    static double R_mod_agi[5] = {0.275362319, 1.575, 1.575, 1.575, 1.575};
    static double R_base_sta[5] = {17.23188406, -17.75, -17.75, -17.75, -17.75};
    static double R_mod_sta[5] = {2.768115942, 4.525, 4.525, 4.525, 4.525};
    static double R_base_int[5] = {19.44927536, 12.75, 12.75, 12.75, 12.75};
    static double R_mod_int[5] = {4.550724638, 1.875, 1.875, 1.875, 1.875};
    static double R_base_spr[5] = {19.52173913, -2.25, -2.25, -2.25, -2.25};
    static double R_mod_spr[5] = {3.47826087, 1.775, 1.775, 1.775, 1.775};
    static double R_base_pwr[5] = {7.202898551, -101, -101, -101, -101};
    static double R_mod_pwr[5] = {2.797101449, 6.5, 6.5, 6.5, 6.5};
    static double R_base_armor[5] = {-11.69565217, -702, -929.4, -1841.25, -1157.55};
    static double R_mod_armor[5] = {31.69565217, 139.6, 74.62, 89.175, 101.1316667};
    static double R_pet_sta_to_hp[5] = {6.405982906, 15.91304348, 7.956521739, 10.79813665, 11.55590062};
    static double R_base_min_dmg[5] = {0.550724638, 4.566666667, 26.82, 29.15, 20.17888889};
    static double R_mod_min_dmg[5] = {1.449275362, 1.433333333, 2.18, 1.85, 1.821111111};
    static double R_base_max_dmg[5] = {1.028985507, 7.133333333, 36.16, 39.6, 27.63111111};
    static double R_mod_max_dmg[5] = {1.971014493, 1.866666667, 2.84, 2.4, 2.368888889};

    double base_str = R_base_str[stat_index];
    double mod_str = R_mod_str[stat_index];
    double base_agi = R_base_agi[stat_index];
    double mod_agi = R_mod_agi[stat_index];
    double base_sta = R_base_sta[stat_index];
    double mod_sta = R_mod_sta[stat_index];
    double base_int = R_base_int[stat_index];
    double mod_int = R_mod_int[stat_index];
    double base_spr = R_base_spr[stat_index];
    double mod_spr = R_mod_spr[stat_index];
    double base_pwr = R_base_pwr[stat_index];
    double mod_pwr = R_mod_pwr[stat_index];
    double base_armor = R_base_armor[stat_index];
    double mod_armor = R_mod_armor[stat_index];
    double base_min_dmg = R_base_min_dmg[stat_index];
    double mod_min_dmg = R_mod_min_dmg[stat_index];
    double base_max_dmg = R_base_max_dmg[stat_index];
    double mod_max_dmg = R_mod_max_dmg[stat_index];
    double pet_sta_to_hp = R_pet_sta_to_hp[stat_index];

    // Calculate bonuses
    double pet_sta_bonus = 0.3 * (double)m_Owner->BaseStats[STAT_STAMINA];      // + sta_buffs
    double pet_int_bonus = 0.3 * (double)m_Owner->BaseStats[STAT_INTELLECT];    // + int_buffs
    double pet_arm_bonus = 0.35 * (double)m_Owner->BaseResistance[0];           // + arm_buffs

    double pet_str = base_str + pet_level * mod_str;
    double pet_agi = base_agi + pet_level * mod_agi;
    double pet_sta = base_sta + pet_level * mod_sta + pet_sta_bonus;
    double pet_int = base_int + pet_level * mod_int + pet_int_bonus;
    double pet_spr = base_spr + pet_level * mod_spr;
    double pet_pwr = base_pwr + pet_level * mod_pwr;
    double pet_arm = base_armor + pet_level * mod_armor + pet_arm_bonus;

    // Calculate values
    BaseStats[STAT_STRENGTH] = FL2UINT(pet_str);
    BaseStats[STAT_AGILITY] = FL2UINT(pet_agi);
    BaseStats[STAT_STAMINA] = FL2UINT(pet_sta);
    BaseStats[STAT_INTELLECT] = FL2UINT(pet_int);
    BaseStats[STAT_SPIRIT] = FL2UINT(pet_spr);

    double pet_min_dmg = base_min_dmg + pet_level * mod_min_dmg;
    double pet_max_dmg = base_max_dmg + pet_level * mod_max_dmg;
    BaseDamage[0] = FL2UINT(pet_min_dmg);
    BaseDamage[1] = FL2UINT(pet_max_dmg);

    for(uint32 x = 0; x < 5; ++x)
        CalcStat(x);

    // Apply armor and attack power.
    SetUInt32Value(UNIT_FIELD_ATTACK_POWER, FL2UINT(pet_pwr));
    BaseResistance[0] = FL2UINT(pet_arm);
    CalcResistance(0);
    CalcDamage();

    // Calculate health / mana
    double health = pet_sta * pet_sta_to_hp;
    double mana = has_mana ? (base_int * 15) : 0.0;
    SetUInt32Value(UNIT_FIELD_BASE_HEALTH, FL2UINT(health));
    SetUInt32Value(UNIT_FIELD_BASE_MANA, FL2UINT(mana));
}

void Pet::ApplyPetLevelAbilities()
{
    uint32 level = m_uint32Values[UNIT_FIELD_LEVEL];
    double dlevel = (double)level;

    /*
    ----------[Pets]----------
        Family         pet_mod_sta             pet_mod_arm           pet_mod_dps
    (1)    Wolf             1.00                  1.05                  1.00
    (2)     Cat             0.98                1.00                1.10
    (3)     Spider             1.00                  1.00                 1.07
    (4)     Bear             1.08                 1.05                 0.91
    (5)     Boar             1.04                1.09                0.90
    (6)     Crocolisk       0.95                1.10                1.00
    (7)     Carrion Bird    1.00                 1.05                 1.00
    (8)     Crab            0.96                1.13                0.95
    (9)     Gorilla         1.04                1.00                1.02
    (10)
    (11)    Raptor              0.95                  1.03                  1.10     
    (12)    Tallstrider     1.05                  1.00                  1.00
    (13)
    (14)
    (15)    Felhunter
    (16)    Voidwalker
    (17)    Succubus
    (18)
    (19)    Doomguard
    (20)    Scorpid         1.00                 1.10                  0.94
    (21)    Turtle             1.00                  1.13                  0.90
    (22)
    (23)    Imp
    (24)    Bat             1.00                     1.00                     1.07
    (25)    Hyena           1.00                  1.05                  1.00    
    (26)    Owl             1.00                     1.00                  1.07
    (27)    Wind Serpent    1.00                  1.00                  1.07
    (28)    Remote Control
    (29)    Felguard
    (30)    Dragonhawk      1.00                    1.00                    1.00
    (31)    Ravager     0.93                  1.05                  1.10
    (32)    Warp Stalker    1.00                  1.05                  0.94
    (33)    Spore Bat       1.00                  1.00                  1.00
    (34)    Nether Ray     1.10                 0.90                  1.03     
    (35)    Serpent     1.00                 1.00                  1.00
    */

    static double R_pet_mod_sta[36] = { 0, 1, 0.98, 1, 1.08, 1.04, 0.95, 1, 0.96, 1.04, 0, 0.95, 1.05, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0.93, 1, 1, 1.1, 1 };
    static double R_pet_mod_arm[36] = { 0, 1.05, 1, 1, 1.05, 1.09, 1.1, 1.05, 1.13, 1, 0, 1.03, 1, 0, 0, 0, 0, 0, 0, 0, 1.1, 1.13, 0, 0, 1, 1.05, 1, 1, 0, 0, 1, 1.05, 1.05, 1, 0.9, 1 };
    static double R_pet_mod_dps[36] = { 0, 1, 1.10, 1.07, 0.91, 0.9, 1, 1, 0.95, 1.02, 0, 1.1, 1, 0, 0, 0, 0, 0, 0, 0, 0.94, 0.9, 0, 0, 1.07, 1, 1.07, 1.07, 0, 0, 1, 1.1, 0.94, 1, 1.03, 1 };

    double pet_mod_sta = 1, pet_mod_arm = 1, pet_mod_dps = 1;
    if(creature_info->Family > 35 || R_pet_mod_sta[creature_info->Family] == 0)
        sLog.outError("PETSTAT: Creature family %u [%s] has missing data. Assuming to be 1.", creature_info->Family);
    else
    {
        pet_mod_sta = R_pet_mod_sta[creature_info->Family];
        pet_mod_arm = R_pet_mod_arm[creature_info->Family];
        pet_mod_dps = R_pet_mod_dps[creature_info->Family];
    }

    // Calculate Bonuses
    double pet_sta_bonus = 0.3 * (double)m_Owner->BaseStats[STAT_STAMINA];
    double pet_arm_bonus = 0.35 * (double)m_Owner->BaseResistance[0];       // Armor
    double pet_ap_bonus = 0.22 * (double)m_Owner->GetUInt32Value(UNIT_FIELD_ATTACK_POWER);

    // Calculate HP
    double pet_hp    = ( ( ( 0.6 * dlevel * dlevel + 10.6 * dlevel + 33 ) + ( pet_sta_bonus * 10 ) ) * pet_mod_sta);
    double pet_armor = ( ( -75 + 50 * dlevel ) * pet_mod_arm + pet_arm_bonus );
    double pet_attack_power = ( ( ( 20 * dlevel) - 60 ) + pet_ap_bonus ) * pet_mod_dps;

    if(pet_attack_power <= 0.0f) pet_attack_power = 1;
    if(pet_armor <= 0.0f) pet_armor = 1;

    // Set base values.
    SetUInt32Value(UNIT_FIELD_BASE_HEALTH, FL2UINT(pet_hp));
    BaseResistance[0] = FL2UINT(pet_armor);
    CalcResistance(0);

    // Calculate damage.
    SetUInt32Value(UNIT_FIELD_ATTACK_POWER, FL2UINT(pet_attack_power));
    CalcDamage();

    // These are just for visuals, no other actual purpose.
    BaseStats[0] = uint32(20+getLevel()*1.55);
    BaseStats[1] = uint32(20+getLevel()*0.64);
    BaseStats[3] = uint32(20+getLevel()*0.18);
    BaseStats[4] = uint32(20+getLevel()*0.36);

    // Reverse the health value to calculate stamina
    BaseStats[STAT_STAMINA] = FL2UINT(pet_hp / 10);

    for(uint32 x = 0; x < 5; ++x)
        CalcStat(x);
}

void Pet::ApplyStatsForLevel()
{
    if(m_uint32Values[UNIT_CREATED_BY_SPELL])       // Summon
        ApplySummonLevelAbilities();
    else
        ApplyPetLevelAbilities();

    // Apply common stuff
    float pet_level = m_uint32Values[UNIT_FIELD_LEVEL];

    // Apply scale for this family.
    float level_diff = myFamily->maxlevel - myFamily->minlevel;
    float scale_diff = myFamily->maxsize - myFamily->minsize;
    float factor = scale_diff / level_diff;
    float scale = factor * pet_level + myFamily->minsize;
    SetFloatValue(OBJECT_FIELD_SCALE_X, scale);

    // Apply health fields.
    SetUInt32Value(UNIT_FIELD_HEALTH, m_uint32Values[UNIT_FIELD_BASE_HEALTH]);
    SetUInt32Value(UNIT_FIELD_MAXHEALTH, m_uint32Values[UNIT_FIELD_BASE_HEALTH]);
    SetUInt32Value(UNIT_FIELD_POWER1, m_uint32Values[UNIT_FIELD_BASE_MANA]);
    SetUInt32Value(UNIT_FIELD_MAXPOWER1, m_uint32Values[UNIT_FIELD_BASE_MANA]);
}
