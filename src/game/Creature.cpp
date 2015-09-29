#include "StdAfx.h"

#define M_PI       3.14159265358979323846

Creature::Creature(uint32 high, uint32 low)
{
    proto=0;
    m_valuesCount = UNIT_END;
    m_objectTypeId = TYPEID_UNIT;
    m_uint32Values = _fields;
    memset(m_uint32Values, 0,(UNIT_END)*sizeof(uint32));
    m_updateMask.SetCount(UNIT_END);
    SetUInt32Value( OBJECT_FIELD_TYPE,TYPE_UNIT|TYPE_OBJECT);
    SetUInt32Value( OBJECT_FIELD_GUID,low);
    SetUInt32Value( OBJECT_FIELD_GUID+1,high);
    m_wowGuid.Init(GetGUID());


    m_quests = NULL;
    proto = NULL;
    spawnid=0;
 
    creature_info=NULL;
    m_H_regenTimer=0;
    m_P_regenTimer=0;
    m_useAI = true;
    mTaxiNode = 0;

    Tagged = false;
    TaggerGuid = 0;

    Skinned = false;
    
    m_enslaveCount = 0;
    m_enslaveSpell = 0;
    
    for(uint32 x=0;x<7;x++)
    {
        FlatResistanceMod[x]=0;
        BaseResistanceModPct[x]=0;
        ResistanceModPct[x]=0;
        ModDamageDone[x]=0;
        ModDamageDonePct[x]=1.0;
    }

    for(uint32 x=0;x<5;x++)
    {
        TotalStatModPct[x]=0;
        StatModPct[x]=0;
        FlatStatMod[x]=0;
    }
    m_runSpeed=PLAYER_NORMAL_RUN_SPEED;

    totemOwner = NULL;
    totemSlot = -1;

    m_PickPocketed = false;
    m_SellItems = NULL;
    _myScriptClass = NULL;
    m_TaxiNode = 0;
    _gossipScript = NULL;
    myFamily = 0;

    loot.gold = 0;
    haslinkupevent = false;
    original_emotestate = 0;
    mTrainer = 0;
    m_spawn = 0;
    spawnid = 0;
    auctionHouse = 0;
    has_waypoint_text = has_combat_text = false;
    SetFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER,1);
    SetFloatValue(UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER,1);
    m_custom_waypoint_map = 0;
    m_escorter = 0;
}


Creature::~Creature()
{
    sEventMgr.RemoveEvents(this);

    if(IsTotem())
        totemOwner->m_TotemSlots[totemSlot] = 0;

    if(_gossipScript != 0)
        _gossipScript->Destroy();
    
    if(_myScriptClass != 0)
        _myScriptClass->Destroy();

    if(m_custom_waypoint_map != 0)
    {
        for(WayPointMap::iterator itr = m_custom_waypoint_map->begin(); itr != m_custom_waypoint_map->end(); ++itr)
            delete itr->second;
        delete m_custom_waypoint_map;
    }
}

void Creature::Update( uint32 p_time )
{
    Unit::Update( p_time );
    if(IsTotem() && isDead())
    {
        RemoveFromWorld(false);
        delete this;
    }
}

void Creature::SafeDelete()
{
    sEventMgr.RemoveEvents(this);
    //sEventMgr.AddEvent(World::getSingletonPtr(), &World::DeleteObject, ((Object*)this), EVENT_CREATURE_SAFE_DELETE, 1000, 1);
    sEventMgr.AddEvent(this, &Creature::DeleteMe, EVENT_CREATURE_SAFE_DELETE, 1000, 1);
}

void Creature::DeleteMe()
{
    if(IsInWorld())
        RemoveFromWorld(false);

    delete this;
}

void Creature::OnRemoveCorpse()
{
    // time to respawn!
    if (IsInWorld() && (int32)m_mapMgr->GetInstanceID() == m_instanceId)
    {

        sLog.outDetail("Removing corpse of " I64FMT "...", GetGUID());
       
            if(GetMapMgr()->GetMapInfo() && GetMapMgr()->GetMapInfo()->type == INSTANCE_RAID && this->GetCreatureName() && this->GetCreatureName()->Rank == 3)
            {
                RemoveFromWorld(false);
            }
            else
            {
                if(proto && proto->RespawnTime)
                    RemoveFromWorld(true);
                else
                    RemoveFromWorld(false);
            }
        
       
        setDeathState(DEAD);

        m_position = m_spawnLocation;
    }
    else
    {
        // if we got here it's pretty bad
    }
}

void Creature::OnRespawn()
{
    if (!IsInWorld())
    {
        sLog.outDetail("Respawning " I64FMT "...", GetGUID());
        SetUInt32Value(UNIT_FIELD_HEALTH, GetUInt32Value(UNIT_FIELD_MAXHEALTH));
        SetUInt32Value(UNIT_DYNAMIC_FLAGS, 0); // not tagging shiat
        if(proto && m_spawn)
        {
            SetUInt32Value(UNIT_NPC_FLAGS, proto->NPCFLags);
            SetUInt32Value(UNIT_NPC_EMOTESTATE, m_spawn->emote_state);
        }

        RemoveFlag(UNIT_FIELD_FLAGS,U_FIELD_FLAG_SKINNABLE);
        Skinned = false;
        Tagged = false;
        TaggerGuid = 0;

        //empty loot
        loot.items.clear();

        AddToWorld();
        setDeathState(ALIVE);
        GetAIInterface()->StopMovement(0); // after respawn monster can move
        m_PickPocketed = false;
    }
    else
    {
        // if we got here it's pretty bad
    }
}
/*
void Creature::Despawn()
{
    GetAIInterface()->SetUnitToFollow(NULL);
    if(IsInWorld())
    {
        RemoveFromWorld(true);
    }
   
    setDeathState(DEAD);

    m_position = m_spawnLocation;
}*/

void Creature::Create (const char* name, uint32 mapid, float x, float y, float z, float ang)
{
    Object::_Create( mapid, x, y, z, ang );
}

void Creature::CreateWayPoint (uint32 WayPointID, uint32 mapid, float x, float y, float z, float ang)
{
    Object::_Create( mapid, x, y, z, ang);
}

///////////
/// Looting

void Creature::generateLoot()
{
    lootmgr.FillCreatureLoot(&loot,GetEntry());
    
    loot.gold = proto ? proto->money : 0;

    //For now let fill according to entry
    if(!loot.gold)
    {
        CreatureInfo *info=GetCreatureName();
        if (info && info->Type != BEAST)
        {
            if(m_uint32Values[UNIT_FIELD_MAXHEALTH] <= 1667)
                loot.gold = (uint32)((info->Rank+1)*getLevel()*(rand()%5 + 1)); //generate copper
            else
                loot.gold = (uint32)((info->Rank+1)*getLevel()*(rand()%5 + 1)*(this->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*0.0006)); //generate copper
        }
    }
    
    if(loot.gold)
        loot.gold = int32(float(loot.gold) * sWorld.getRate(RATE_MONEY));
}

void Creature::SaveToDB()
{
    if(!spawnid)
        spawnid = objmgr.GenerateCreatureSpawnID();
     
    std::stringstream ss;
    ss << "REPLACE INTO creature_spawns VALUES("
        << spawnid << ","
        << GetEntry() << ","
        << GetMapId() << ","
        << m_position.x << ","
        << m_position.y << ","
        << m_position.z << ","
        << m_position.o << ","
        << m_aiInterface->getMoveType() << ","
        << m_uint32Values[UNIT_FIELD_DISPLAYID] << ","
        << m_uint32Values[UNIT_FIELD_FACTIONTEMPLATE] << ","
        << m_uint32Values[UNIT_FIELD_FLAGS] << ","
        << m_uint32Values[UNIT_FIELD_BYTES_0] << ","
        << m_uint32Values[UNIT_FIELD_BYTES_2] << ","
        << m_uint32Values[UNIT_NPC_EMOTESTATE] << ","
        << ((this->m_spawn ? m_spawn->respawnNpcLink : uint32(0))) << ")";

    WorldDatabase.Execute(ss.str().c_str());
}

void Creature::SaveToFile(std::stringstream & name)
{
/*    FILE * OutFile;

    OutFile = fopen(name.str().c_str(), "wb");
    if (!OutFile) return;
    
    uint32 creatureEntry = GetUInt32Value(OBJECT_FIELD_ENTRY);
    if (!m_sqlid)
        m_sqlid = objmgr.GenerateLowGuid(HIGHGUID_UNIT);

    std::stringstream ss;
    ss << "DELETE FROM creatures WHERE id=" << m_sqlid;
    fwrite(ss.str().c_str(),1,ss.str().size(),OutFile);

    ss.rdbuf()->str("");
    ss << "\nINSERT INTO creatures (id, mapId, zoneId, name_id, positionX, positionY, positionZ, orientation, moverandom, running, data) VALUES ( "
        << m_sqlid << ", "
        << GetMapId() << ", "
        << GetZoneId() << ", "
        << GetUInt32Value(OBJECT_FIELD_ENTRY) << ", "
        << m_position.x << ", "
        << m_position.y << ", "
        << m_position.z << ", "
        << m_position.o << ", "
        << GetAIInterface()->getMoveType() << ", "
        << GetAIInterface()->getMoveRunFlag() << ", '";
    for( uint16 index = 0; index < m_valuesCount; index ++ )
        ss << GetUInt32Value(index) << " ";

    ss << "' )";
    fwrite(ss.str().c_str(),1,ss.str().size(),OutFile);
    fclose(OutFile);*/
}


void Creature::LoadScript()
{
    _myScriptClass = sScriptMgr.CreateAIScriptClassForEntry(this);
}

void Creature::DeleteFromDB()
{
    if(!GetSQL_id())return;
    WorldDatabase.Execute("DELETE FROM creature_spawns WHERE id=%u", GetSQL_id());
    WorldDatabase.Execute("DELETE FROM creature_waypoints WHERE creatureid=%u",GetSQL_id());
}


/////////////
/// Quests

void Creature::AddQuest(QuestRelation *Q)
{
    m_quests->push_back(Q);
}

void Creature::DeleteQuest(QuestRelation *Q)
{
    list<QuestRelation *>::iterator it;
    for ( it = m_quests->begin(); it != m_quests->end(); ++it )
    {
        if (((*it)->type == Q->type) && ((*it)->qst == Q->qst ))
        {
            delete (*it);
            m_quests->erase(it);
            break;
        }
    }
}

Quest* Creature::FindQuest(uint32 quest_id, uint8 quest_relation)
{   
    list<QuestRelation *>::iterator it;
    for (it = m_quests->begin(); it != m_quests->end(); ++it)
    {
        QuestRelation *ptr = (*it);

        if ((ptr->qst->id == quest_id) && (ptr->type & quest_relation))
        {
            return ptr->qst;
        }
    }
    return NULL;
}

uint16 Creature::GetQuestRelation(uint32 quest_id)
{
    uint16 quest_relation = 0;
    list<QuestRelation *>::iterator it;

    for (it = m_quests->begin(); it != m_quests->end(); ++it)
    {
        if ((*it)->qst->id == quest_id)
        {
            quest_relation |= (*it)->type;
        }
    }
    return quest_relation;
}

uint32 Creature::NumOfQuests()
{
    return m_quests->size();
}

void Creature::_LoadQuests()
{
    sQuestMgr.LoadNPCQuests(this);
}

void Creature::setDeathState(DeathState s) 
{
    if(s == JUST_DIED) 
    {

        GetAIInterface()->SetUnitToFollow(NULL);
        m_deathState = CORPSE;
        
        sEventMgr.AddEvent(this, &Creature::OnRemoveCorpse, EVENT_CREATURE_REMOVE_CORPSE, 180000, 1);
        if(m_enslaveSpell)
            RemoveEnslave();

    }else m_deathState = s;
}

void Creature::AddToWorld()
{
    // force set faction
    if(m_faction == 0 || m_factionDBC == 0)
        _setFaction();

    if(creature_info == 0)
        creature_info = CreatureNameStorage.LookupEntry(GetEntry());

    if(creature_info == 0) return;
    
    if(m_faction == 0 || m_factionDBC == 0)
        return;

    Unit::AddToWorld();
}

bool Creature::CanAddToWorld()
{
    if(m_factionDBC == 0 || m_faction == 0)
        _setFaction();

    if(creature_info == 0 || m_faction == 0 || m_factionDBC == 0)
        return false;
    
    return true;
}

void Creature::RemoveFromWorld(bool addev)
{
    if(IsInWorld())
    {
        RemoveAllAuras();

        sEventMgr.RemoveEvents(this);
        if(addev)
        {
            //printf("DEBUG: removing creature respawnval: %d",proto->RespawnTime);
             // instanced creatures don't respawn
            if(proto && proto->RespawnTime > 0 && (GetMapId() == 530 || GetMapId() == 0 || GetMapId() == 1 )) // temp fix for instances...
                sEventMgr.AddEvent(this, &Creature::OnRespawn, EVENT_CREATURE_RESPAWN, proto->RespawnTime, 1);
            else
                SafeDelete();
        }
        Unit::RemoveFromWorld();
    }
    objmgr.SetCreatureBySqlId(GetSQL_id(), 0);
}

void Creature::EnslaveExpire()
{
    
    m_enslaveCount++;
    Player *caster = objmgr.GetPlayer(GetUInt64Value(UNIT_FIELD_CHARMEDBY));
    if(caster)
    {
        caster->SetUInt64Value(UNIT_FIELD_CHARM, 0);
        caster->SetUInt64Value(UNIT_FIELD_SUMMON, 0);
        WorldPacket data;
        data.Initialize(SMSG_PET_SPELLS);
        data << uint64(0);
        caster->GetSession()->SendPacket(&data);
    }
    SetUInt64Value(UNIT_FIELD_CHARMEDBY, 0);
    SetUInt64Value(UNIT_FIELD_SUMMONEDBY, 0);
    SetIsPet(false);

    m_walkSpeed = 2.5f;
    m_runSpeed = 6.0f;

    switch(GetCreatureName()->Type)
    {
    case DEMON:
        SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 90);
        break;
    default:
        SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 954);
        break;
    };
    _setFaction();

    GetAIInterface()->Init(((Unit *)this), AITYPE_AGRO, MOVEMENTTYPE_NONE);

    // Update InRangeSet
    UpdateOppFactionSet();
}

bool Creature::RemoveEnslave()
{
    return RemoveAura(m_enslaveSpell);
}

void Creature::AddInRangeObject(Object* pObj)
{
    Unit::AddInRangeObject(pObj);
}

void Creature::RemoveInRangeObject(Object* pObj)
{
    if(totemOwner == pObj)        // player gone out of range of the totem
    {
        // Expire next loop.
        event_ModifyTimeLeft(EVENT_TOTEM_EXPIRE, 1);
    }

    if(m_escorter == pObj)
    {
        // we lost our escorter, return to the spawn.
        m_aiInterface->StopMovement(10000);
        DestroyCustomWaypointMap();
        Despawn(1000, 1000);
    }

    Unit::RemoveInRangeObject(pObj);
}

void Creature::ClearInRangeSet()
{
    Unit::ClearInRangeSet();
}

void Creature::CalcResistance(uint32 type)
{
    int32 res = (BaseResistance[type] * (100 + BaseResistanceModPct[type])) / 100;
    if(res < 0) res = 0;
    res += FlatResistanceMod[type];
    if(res < 0) res = 0;
    res += (res * ResistanceModPct[type]) / 100;
    if(type==0)res+=GetUInt32Value(UNIT_FIELD_STAT1)*2;//fix armor from agi
    SetUInt32Value(UNIT_FIELD_RESISTANCES + type, res > 0 ? res : 0);
}

void Creature::CalcStat(uint32 type)
{
    int32 res=(BaseStats[type]*(100+StatModPct[type]))/100;
        
    res+=FlatStatMod[type];
    if(res<0)res=0;
        
    res+=(res*(TotalStatModPct[type]))/100;
    SetUInt32Value(UNIT_FIELD_STAT0+type,res>0?res:0);
}


void Creature::RegenerateHealth()
{
    uint32 cur=GetUInt32Value(UNIT_FIELD_HEALTH);
    uint32 mh=GetUInt32Value(UNIT_FIELD_MAXHEALTH);
    if(cur>=mh)return;
    
    //though creatures have their stats we use some wierd formula for amt
    float amt = 0.0f;

    if(PctRegenModifier == 0.0f)
        amt = getLevel()*2;
    else if(PctRegenModifier > 0)
        amt = (getLevel()*2)*(1+PctRegenModifier);
    else
        amt = (getLevel()*2)*(-1+PctRegenModifier);
        
    //Apply shit from conf file
    amt*=sWorld.getRate(RATE_HEALTH);
    
    if(amt<=1.0)//this fixes regen like 0.98
        cur++;
    else
        cur+=(uint32)amt;
    SetUInt32Value(UNIT_FIELD_HEALTH,(cur>=mh)?mh:cur);
}

void Creature::RegenerateMana()
{
    float amt;
    if (m_interruptRegen)
        return;
   
    uint32 cur=GetUInt32Value(UNIT_FIELD_POWER1);
    uint32 mm=GetUInt32Value(UNIT_FIELD_MAXPOWER1);
    if(cur>=mm)return;
    amt=(getLevel()+10)*PctPowerRegenModifier[POWER_TYPE_MANA];
    
    //Apply shit from conf file
    amt*=sWorld.getRate(RATE_POWER1);
    if(amt<=1.0)//this fixes regen like 0.98
        cur++;
    else
        cur+=(uint32)amt;
    SetUInt32Value(UNIT_FIELD_POWER1,(cur>=mm)?mm:cur);
}

void Creature::RegenerateFocus()
{
    if (m_interruptRegen)
        return;

    uint32 cur=GetUInt32Value(UNIT_FIELD_POWER3);
    uint32 mm=GetUInt32Value(UNIT_FIELD_MAXPOWER3);
    if(cur>=mm)return;
    float amt = 10.0 * PctPowerRegenModifier[POWER_TYPE_FOCUS];
    cur+=(uint32)amt;
    SetUInt32Value(UNIT_FIELD_POWER3,(cur>=mm)?mm:cur);
}

void Creature::CallScriptUpdate()
{
    ASSERT(_myScriptClass);
    if(!IsInWorld())
        return;

    _myScriptClass->AIUpdate();
}

void Creature::AddVendorItem(uint32 itemid, uint32 amount)
{
    CreatureItem ci;
    ci.amount = amount;
    ci.itemid = itemid;
    if(!m_SellItems)
    {
        m_SellItems = new vector<CreatureItem>;
        objmgr.SetVendorList(GetEntry(), m_SellItems);
    }
    m_SellItems->push_back(ci);
}

void Creature::TotemExpire()
{
    totemOwner->m_TotemSlots[totemSlot] = 0;
    totemSlot = -1;
    totemOwner = 0;

    RemoveFromWorld(false);
    SafeDelete();
}

void Creature::FormationLinkUp(uint32 SqlId)
{
    Creature * creature = objmgr.GetCreatureBySqlId(SqlId);
    if(creature != 0)
    {
        m_aiInterface->m_formationLinkTarget = creature;
        haslinkupevent = false;
        event_RemoveEvents(EVENT_CREATURE_FORMATION_LINKUP);
    }
}

void Creature::LoadAIAgents()
{
    /*std::stringstream ss;
    ss << "SELECT * FROM ai_agents where entryId=" << GetUInt32Value(OBJECT_FIELD_ENTRY);
    QueryResult *result = sDatabase.Query( ss.str().c_str() );

    if( !result )
        return;

    AI_Spell *sp;

    do
    {
        Field *fields = result->Fetch();

        sp = new AI_Spell;
        sp->entryId = fields[0].GetUInt32();
        sp->agent = fields[1].GetUInt16();
        sp->procChance = fields[3].GetUInt32();
        sp->spellId = fields[5].GetUInt32();
        sp->spellType = fields[6].GetUInt32();;
        sp->spelltargetType = fields[7].GetUInt32();
        sp->floatMisc1 = fields[9].GetFloat();
        sp->Misc2 = fields[10].GetUInt32();
        sp->minrange = GetMinRange(sSpellRange.LookupEntry(sSpellStore.LookupEntry(sp->spellId)->rangeIndex));
        sp->maxrange = GetMaxRange(sSpellRange.LookupEntry(sSpellStore.LookupEntry(sp->spellId)->rangeIndex));

        if(sp->agent == AGENT_RANGED)
        {
            GetAIInterface()->m_canRangedAttack = true;
        }
        else if(sp->agent == AGENT_FLEE)
        {
            GetAIInterface()->m_canFlee = true;
            if(sp->floatMisc1)
            {
                GetAIInterface()->m_FleeHealth = sp->floatMisc1;
            }
            else
            {
                GetAIInterface()->m_FleeHealth = 0.2f;
            }
            if(sp->Misc2)
            {
                GetAIInterface()->m_FleeDuration = sp->Misc2;
            }
            else
            {
                GetAIInterface()->m_FleeDuration = 10000;
            }
        }
        else if(sp->agent == AGENT_CALLFORHELP)
        {
            GetAIInterface()->m_canCallForHelp = true;
            if(sp->floatMisc1)
                GetAIInterface()->m_CallForHelpHealth = sp->floatMisc1;
            else
                GetAIInterface()->m_CallForHelpHealth = 0.2f;
        }
        else
        {
            GetAIInterface()->addSpellToList(sp);
        }
    } while( result->NextRow() );

    delete result;*/
}

WayPoint * Creature::CreateWaypointStruct()
{
    return new WayPoint();
}

bool Creature::Load(CreatureSpawn *spawn, uint32 mode, MapInfo *info)
{
    m_spawn = spawn;
    proto = CreatureProtoStorage.LookupEntry(spawn->entry);
    if(!proto)
        return false;
    creature_info = CreatureNameStorage.LookupEntry(spawn->entry);
    if(!creature_info)
        return false;
    
    spawnid = spawn->id;
    //Set fields
    SetUInt32Value(OBJECT_FIELD_ENTRY,proto->Id);
    SetFloatValue(OBJECT_FIELD_SCALE_X,proto->Scale);
    
    SetUInt32Value(UNIT_FIELD_HEALTH, (mode ? long2int32(proto->Health * 1.5)  : proto->Health));
    SetUInt32Value(UNIT_FIELD_BASE_HEALTH, (mode ? long2int32(proto->Health * 1.5)  : proto->Health));
    SetUInt32Value(UNIT_FIELD_MAXHEALTH, (mode ? long2int32(proto->Health * 1.5)  : proto->Health));

    SetUInt32Value(UNIT_FIELD_POWER1,proto->Mana);
    SetUInt32Value(UNIT_FIELD_MAXPOWER1,proto->Mana);
    SetUInt32Value(UNIT_FIELD_BASE_MANA,proto->Mana);
    
    SetUInt32Value(UNIT_FIELD_DISPLAYID,spawn->displayid);
    SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID,spawn->displayid);
    SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID,proto->MountedDisplayID);

    // Determine gender (for voices)
    if(spawn->displayid != creature_info->DisplayID)
        setGender(1);   // Female
    
    SetUInt32Value(UNIT_FIELD_LEVEL, (mode ? proto->Level + (info ? info->lvl_mod_a : 0) : proto->Level));
    for(uint32 i = 0; i < 7; ++i)
        SetUInt32Value(UNIT_FIELD_RESISTANCES+i,proto->Resistances[i]);

    SetUInt32Value(UNIT_FIELD_BASEATTACKTIME,proto->AttackTime);
    SetFloatValue(UNIT_FIELD_MINDAMAGE, (mode ? proto->MinDamage * 1.5  : proto->MinDamage));
    SetFloatValue(UNIT_FIELD_MAXDAMAGE, (mode ? proto->MaxDamage * 1.5  : proto->MaxDamage));

    SetUInt32Value(UNIT_FIELD_RANGEDATTACKTIME,proto->RangedAttackTime);
    SetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE,proto->RangedMinDamage);
    SetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE,proto->RangedMaxDamage);

    SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, proto->Item1SlotDisplay);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY_01, proto->Item2SlotDisplay);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY_02, proto->Item3SlotDisplay);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO, proto->Item1Info1);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO_01, proto->Item1Info2);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO_02, proto->Item2Info1);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO_03, proto->Item2Info2);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO_04, proto->Item3Info1);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO_05, proto->Item3Info2);

    SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, spawn->factionid);
    SetUInt32Value(UNIT_FIELD_FLAGS, spawn->flags);
    SetUInt32Value(UNIT_NPC_EMOTESTATE, spawn->emote_state);
    SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, proto->BoundingRadius);
    SetFloatValue(UNIT_FIELD_COMBATREACH, proto->CombatReach);
    original_emotestate = spawn->emote_state;
    // set position
    m_position.ChangeCoords( spawn->x, spawn->y, spawn->z, spawn->o );
    m_spawnLocation.ChangeCoords(spawn->x, spawn->y, spawn->z, spawn->o);
    m_aiInterface->setMoveType(spawn->movetype);    
    m_aiInterface->m_waypoints = objmgr.GetWayPointMap(spawn->id);

    m_faction = sFactionTmpStore.LookupEntry(spawn->factionid);
    
    if(m_faction)
    {
        m_factionDBC = sFactionStore.LookupEntry(m_faction->Faction);
    }
//SETUP NPC FLAGS
    SetUInt32Value(UNIT_NPC_FLAGS,proto->NPCFLags);

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR ) )
        m_SellItems = objmgr.GetVendorList(GetEntry());

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER ) )
        _LoadQuests();

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_TAXIVENDOR) )
        m_TaxiNode = sTaxiMgr.GetNearestTaxiNode( m_position.x, m_position.y, m_position.z, GetMapId() );

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP) && _gossipScript == 0 )
        SetGossipScript( sScriptMgr.GetGossipScript( GetEntry() ) );

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_TRAINER) )
        mTrainer = objmgr.GetTrainer(GetEntry());

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_AUCTIONEER ) )
        auctionHouse = sAuctionMgr.GetAuctionHouse(GetEntry());

//NPC FLAGS
     m_aiInterface->m_waypoints=objmgr.GetWayPointMap(spawn->id);

    //load resistances
    for(uint32 x=0;x<7;x++)
        BaseResistance[x]=GetUInt32Value(UNIT_FIELD_RESISTANCES+x);
    for(uint32 x=0;x<5;x++)
        BaseStats[x]=GetUInt32Value(UNIT_FIELD_STAT0+x);

    BaseDamage[0]=GetFloatValue(UNIT_FIELD_MINDAMAGE);
    BaseDamage[1]=GetFloatValue(UNIT_FIELD_MAXDAMAGE);
    BaseOffhandDamage[0]=GetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE);
    BaseOffhandDamage[1]=GetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE);
    BaseRangedDamage[0]=GetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE);
    BaseRangedDamage[1]=GetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE);

    SetFloatValue(UNIT_MOD_CAST_SPEED, 1.0f);   // better set this one
    SetUInt32Value(UNIT_FIELD_BYTES_0, spawn->bytes);
    SetUInt32Value(UNIT_FIELD_BYTES_2, spawn->bytes2);

////////////AI
    
    // kek
    for(list<AI_Spell*>::iterator itr = proto->spells.begin(); itr != proto->spells.end(); ++itr)
    {
        m_aiInterface->addSpellToList(*itr);
    }
    m_aiInterface->m_canCallForHelp = proto->m_canCallForHelp;
    m_aiInterface->m_CallForHelpHealth = proto->m_callForHelpHealth;
    m_aiInterface->m_canFlee = proto->m_canFlee;
    m_aiInterface->m_FleeHealth = proto->m_fleeHealth;
    m_aiInterface->m_FleeDuration = proto->m_fleeDuration;

    //these fields are always 0 in db
    GetAIInterface()->setMoveType(0);
    GetAIInterface()->setMoveRunFlag(0);
    
    // load formation data
    if(spawn->form)
    {
        m_aiInterface->m_formationLinkSqlId = spawn->form->fol;
        m_aiInterface->m_formationFollowDistance = spawn->form->dist;
        m_aiInterface->m_formationFollowAngle = spawn->form->ang;
        // add event
        sEventMgr.AddEvent(this, &Creature::FormationLinkUp, m_aiInterface->m_formationLinkSqlId,
            EVENT_CREATURE_FORMATION_LINKUP, 1000, 0);
        haslinkupevent = true;
    }
    else
    {
        m_aiInterface->m_formationLinkSqlId = 0;
        m_aiInterface->m_formationFollowDistance = 0;
        m_aiInterface->m_formationFollowAngle = 0;
    }

//////////////AI

    myFamily = sCreatureFamilyStore.LookupEntry(creature_info->Family);

    
// PLACE FOR DIRTY FIX BASTARDS
    // HACK! set call for help on civ health @ 100%
    if(creature_info->Civilian >= 1)
        m_aiInterface->m_CallForHelpHealth = 100;
 
 //HACK!
    if(m_uint32Values[UNIT_FIELD_DISPLAYID] == 17743 ||
        m_uint32Values[UNIT_FIELD_DISPLAYID] == 20242 ||
        m_uint32Values[UNIT_FIELD_DISPLAYID] == 15435 ||
        (creature_info->Family == UNIT_TYPE_MISC))
    {
        m_useAI = false;
    }

    /* more hacks! */
    if(proto->Mana != 0)
        SetPowerType(POWER_TYPE_MANA);
    else
        SetPowerType(0);

    has_combat_text = objmgr.HasMonsterSay(GetEntry(), MONSTER_SAY_EVENT_ENTER_COMBAT);
    has_waypoint_text = objmgr.HasMonsterSay(GetEntry(), MONSTER_SAY_EVENT_RANDOM_WAYPOINT);
    m_aiInterface->m_hasWaypointEvents = ScriptSystem->HasEventType(GetEntry(), CREATURE_EVENT_ON_REACH_WP);

    return true;
}


void Creature::Load(CreatureProto * proto_, float x, float y, float z)
{
    proto = proto_;

    creature_info = CreatureNameStorage.LookupEntry(proto->Id);
    if(!creature_info)
        return;

    //Set fields
    SetUInt32Value(OBJECT_FIELD_ENTRY,proto->Id);
    SetFloatValue(OBJECT_FIELD_SCALE_X,proto->Scale);

    SetUInt32Value(UNIT_FIELD_HEALTH, proto->Health);
    SetUInt32Value(UNIT_FIELD_BASE_HEALTH, proto->Health);
    SetUInt32Value(UNIT_FIELD_MAXHEALTH, proto->Health);

    SetUInt32Value(UNIT_FIELD_POWER1,proto->Mana);
    SetUInt32Value(UNIT_FIELD_MAXPOWER1,proto->Mana);
    SetUInt32Value(UNIT_FIELD_BASE_MANA,proto->Mana);

    SetUInt32Value(UNIT_FIELD_DISPLAYID,creature_info->DisplayID);
    SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID,creature_info->DisplayID);

    SetUInt32Value(UNIT_FIELD_LEVEL, proto->Level);
    for(uint32 i = 0; i < 7; ++i)
        SetUInt32Value(UNIT_FIELD_RESISTANCES+i,proto->Resistances[i]);

    SetUInt32Value(UNIT_FIELD_BASEATTACKTIME,proto->AttackTime);
    SetFloatValue(UNIT_FIELD_MINDAMAGE, proto->MinDamage);
    SetFloatValue(UNIT_FIELD_MAXDAMAGE, proto->MaxDamage);

    SetUInt32Value(UNIT_FIELD_RANGEDATTACKTIME,proto->RangedAttackTime);
    SetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE,proto->RangedMinDamage);
    SetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE,proto->RangedMaxDamage);

    SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, proto->Item1SlotDisplay);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY_01, proto->Item2SlotDisplay);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY_02, proto->Item3SlotDisplay);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO, proto->Item1Info1);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO_01, proto->Item1Info2);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO_02, proto->Item2Info1);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO_03, proto->Item2Info2);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO_04, proto->Item3Info1);
    SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO_05, proto->Item3Info2);

    SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, proto->Faction);
    SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, proto->BoundingRadius);
    SetFloatValue(UNIT_FIELD_COMBATREACH, proto->CombatReach);
    original_emotestate = 0;
    // set position

    m_position.ChangeCoords( x, y, z, 0 );
    m_spawnLocation.ChangeCoords(x, y, z, 0);

    m_faction = sFactionTmpStore.LookupEntry(proto->Faction);

    if(m_faction)
    {
        m_factionDBC = sFactionStore.LookupEntry(m_faction->Faction);
    }
    //SETUP NPC FLAGS
    SetUInt32Value(UNIT_NPC_FLAGS,proto->NPCFLags);

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VENDOR ) )
        m_SellItems = objmgr.GetVendorList(GetEntry());

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER ) )
        _LoadQuests();

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_TAXIVENDOR) )
        m_TaxiNode = sTaxiMgr.GetNearestTaxiNode( m_position.x, m_position.y, m_position.z, GetMapId() );

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP) && _gossipScript == 0 )
        SetGossipScript( sScriptMgr.GetGossipScript( GetEntry() ) );

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_TRAINER) )
        mTrainer = objmgr.GetTrainer(GetEntry());

    if ( HasFlag( UNIT_NPC_FLAGS, UNIT_NPC_FLAG_AUCTIONEER ) )
        auctionHouse = sAuctionMgr.GetAuctionHouse(GetEntry());

    //load resistances
    for(uint32 x=0;x<7;x++)
        BaseResistance[x]=GetUInt32Value(UNIT_FIELD_RESISTANCES+x);
    for(uint32 x=0;x<5;x++)
        BaseStats[x]=GetUInt32Value(UNIT_FIELD_STAT0+x);

    BaseDamage[0]=GetFloatValue(UNIT_FIELD_MINDAMAGE);
    BaseDamage[1]=GetFloatValue(UNIT_FIELD_MAXDAMAGE);
    BaseOffhandDamage[0]=GetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE);
    BaseOffhandDamage[1]=GetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE);
    BaseRangedDamage[0]=GetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE);
    BaseRangedDamage[1]=GetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE);

    SetFloatValue(UNIT_MOD_CAST_SPEED, 1.0f);   // better set this one

    ////////////AI

    // kek
    for(list<AI_Spell*>::iterator itr = proto->spells.begin(); itr != proto->spells.end(); ++itr)
    {
        m_aiInterface->addSpellToList(*itr);
    }
    m_aiInterface->m_canCallForHelp = proto->m_canCallForHelp;
    m_aiInterface->m_CallForHelpHealth = proto->m_callForHelpHealth;
    m_aiInterface->m_canFlee = proto->m_canFlee;
    m_aiInterface->m_FleeHealth = proto->m_fleeHealth;
    m_aiInterface->m_FleeDuration = proto->m_fleeDuration;

    //these fields are always 0 in db
    GetAIInterface()->setMoveType(0);
    GetAIInterface()->setMoveRunFlag(0);

    // load formation data
    m_aiInterface->m_formationLinkSqlId = 0;
    m_aiInterface->m_formationFollowDistance = 0;
    m_aiInterface->m_formationFollowAngle = 0;

    //////////////AI

    myFamily = sCreatureFamilyStore.LookupEntry(creature_info->Family);


    // PLACE FOR DIRTY FIX BASTARDS
    // HACK! set call for help on civ health @ 100%
    if(creature_info->Civilian >= 1)
        m_aiInterface->m_CallForHelpHealth = 100;

    //HACK!
    if(m_uint32Values[UNIT_FIELD_DISPLAYID] == 17743 ||
        m_uint32Values[UNIT_FIELD_DISPLAYID] == 20242 ||
        m_uint32Values[UNIT_FIELD_DISPLAYID] == 15435 ||
        (creature_info->Family == UNIT_TYPE_MISC))
    {
        m_useAI = false;
    }

    /* more hacks! */
    if(proto->Mana != 0)
        SetPowerType(POWER_TYPE_MANA);
    else
        SetPowerType(0);

    has_combat_text = objmgr.HasMonsterSay(GetEntry(), MONSTER_SAY_EVENT_ENTER_COMBAT);
    has_waypoint_text = objmgr.HasMonsterSay(GetEntry(), MONSTER_SAY_EVENT_RANDOM_WAYPOINT);
    m_aiInterface->m_hasWaypointEvents = ScriptSystem->HasEventType(GetEntry(), CREATURE_EVENT_ON_REACH_WP);
}

void Creature::OnPushToWorld()
{
    if(proto)
    {
        set<uint32>::iterator itr = proto->start_auras.begin();
        SpellEntry * sp;
        for(; itr != proto->start_auras.end(); ++itr)
        {
            sp = sSpellStore.LookupEntry((*itr));
            if(sp == 0) continue;

            CastSpell(this, sp, 0);
        }
    }
    LoadScript();
    Unit::OnPushToWorld();

    /* script */
    ScriptSystem->OnCreatureEvent(this, 0, CREATURE_EVENT_ON_SPAWN);

    if(_myScriptClass)
        _myScriptClass->OnLoad();

    objmgr.SetCreatureBySqlId(GetSQL_id(), this);

    if(IS_INSTANCE(m_mapMgr->GetMapId()))
        m_aiInterface->setOutOfCombatRange(0);        
}

// this is used for guardians. They are non respawnable creatures linked to a player
void Creature::SummonExpire()
{
    RemoveFromWorld(false);
    SafeDelete();//delete creature totaly.
}

void Creature::Despawn(uint32 delay, uint32 respawntime)
{
    if(delay)
    {
        sEventMgr.AddEvent(this, &Creature::Despawn, (uint32)0, respawntime, EVENT_CREATURE_RESPAWN, delay, 1);
        return;
    }

    RemoveFromWorld(false);
    m_position = m_spawnLocation;
    if(respawntime)
        sEventMgr.AddEvent(this, &Creature::OnRespawn, EVENT_CREATURE_RESPAWN, respawntime, 1);
}

void Creature::TriggerScriptEvent(void * func)
{
    ScriptSystem->OnCreatureEvent(this, (gmFunctionObject*)func);
}

void Creature::DestroyCustomWaypointMap()
{
    if(m_custom_waypoint_map)
    {
        for(WayPointMap::iterator itr = m_custom_waypoint_map->begin(); itr != m_custom_waypoint_map->end(); ++itr)
        {
            delete itr->second;
        }
        delete m_custom_waypoint_map;
        m_custom_waypoint_map = 0;
        m_aiInterface->SetWaypointMap(0);
    }
}
