/****************************************************************************
 *
 * General Object Type File
 *
 */

#include "StdAfx.h"

initialiseSingleton( ObjectMgr );

#ifdef WIN32
#define ToLower(yourstring) transform (yourstring.begin(),yourstring.end(), yourstring.begin(), tolower);
#else
#define ToLower(str) for(unsigned int i=0;i<str.size();i++) tolower(str[i]);
#endif
#define ToUpper(yourstring) transform (yourstring.begin(),yourstring.end(), yourstring.begin(), towupper);

ObjectMgr::ObjectMgr()
{
	m_hiPetGuid = 0;
	m_hiContainerGuid = 0;
	m_hiItemGuid = 0;
	m_hiGroupId = 1;
	m_mailid = 0;
	m_hiPlayerGuid = 0;
	m_hiCorpseGuid = 0;
	m_transporters = 0;
}


ObjectMgr::~ObjectMgr()
{
	sLog.outString("	Removing Corpses from Object Holder");
	CorpseCollectorUnload();

	sLog.outString("	Deleting ItemSets...");
	for(ItemSetContentMap::iterator i = mItemSets.begin(); i != mItemSets.end(); ++i)
	{
		delete i->second;
	}
	mItemSets.clear();

	sLog.outString("	Deleting CreateInfo...");
	for( PlayerCreateInfoMap::iterator i = mPlayerCreateInfo.begin( ); i != mPlayerCreateInfo.end( ); ++ i ) {
		delete i->second;
	}
	mPlayerCreateInfo.clear( );

	sLog.outString("	Deleting Guilds...");
	for ( GuildMap::iterator i = mGuild.begin(); i != mGuild.end(); ++i ) {
		delete i->second;
	}

	sLog.outString("	Deleting Vendors...");
	for( VendorMap::iterator i = mVendors.begin( ); i != mVendors.end( ); ++ i ) 
	{
		delete i->second;
	}

	sLog.outString("	Deleting AI Threat Spells...");
	for( std::list<ThreatToSpellId*>::iterator i = threatToSpells.begin( ); i != threatToSpells.end( ); ++ i ) 
	{
		ThreatToSpellId *gc=(*i);
		delete gc;
	}


	sLog.outString("	Deleting Spell Override Map...");
	for(OverrideIdMap::iterator i = mOverrideIdMap.begin(); i != mOverrideIdMap.end(); ++i)
	{
		delete i->second;
	}

	for( TrainerMap::iterator i = mTrainers.begin( ); i != mTrainers.end( ); ++ i) {
		Trainer * t = i->second;
		delete [] t->TalkMessage;
		delete [] t->SpellList;
		delete t;
	}

	for(TrainerSpellMap::iterator i = mNormalSpells.begin(); i != mNormalSpells.end(); ++i)
	{
		vector<TrainerSpell*>::iterator itr = i->second.begin();
		for(; itr != i->second.end(); ++itr)
		{
			delete (*itr);
		}
		i->second.clear();
	}

	for(TrainerSpellMap::iterator i = mPetSpells.begin(); i != mPetSpells.end(); ++i)
	{
		vector<TrainerSpell*>::iterator itr = i->second.begin();
		for(; itr != i->second.end(); ++itr)
		{
			delete (*itr);
		}
		i->second.clear();
	}

	for( LevelInfoMap::iterator i = mLevelInfo.begin(); i != mLevelInfo.end(); ++i)
	{
		LevelMap * l = i->second;
		for(LevelMap::iterator i2 = l->begin(); i2 != l->end(); ++i2)
		{
			delete i2->second;
		}
		l->clear();
		delete l;
	}

	if(m_transporters)
	{
		for(uint32 i = 1; i <= this->TransportersCount; ++i)
		{
			if(m_transporters[i])
			{
				delete m_transporters[i];
				m_transporters[i] = 0;
			}
		}
		delete [] m_transporters;
	}

	/*BURSTORAGEREWRITEFIX*/
	/*sLog.outString("Deleting Prototypes/Waypoints/AISpells...");
	for(UNORDERED_MAP<uint32, CreatureProto*>::iterator itr = m_creatureproto.begin(); itr != m_creatureproto.end(); ++itr)
	{
		CreatureProto * p = itr->second;
		for(list<AI_Spell*>::iterator i = p->spells.begin(); i != p->spells.end(); ++i)
			delete (*i);
		delete p;
	}*/

	for(UNORDERED_MAP<uint32, WayPointMap*>::iterator i = m_waypoints.begin(); i != m_waypoints.end(); ++i)
	{
		for(WayPointMap::iterator i2 = i->second->begin(); i2 != i->second->end(); ++i2)
			delete i2->second;
		delete i->second;
	}

	for(UNORDERED_MAP<uint32, PlayerInfo*>::iterator itr = m_playersinfo.begin(); itr != m_playersinfo.end(); ++itr)
		delete itr->second;

	sLog.outString("Deleting npc_monstersay...");
	for(uint32 i = 0 ; i < NUM_MONSTER_SAY_EVENTS ; ++i)
	{
		NpcMonsterSay * p;
		for(MonsterSayMap::iterator itr = mMonsterSays[i].begin(); itr != mMonsterSays[i].end(); ++itr)
		{
			p = itr->second;
			for(uint32 j = 0; j < p->TextCount; ++j)
				free((char*)p->Texts[j]);
			delete [] p->Texts;
			free((char*)p->MonsterName);
			delete p;
		}

		mMonsterSays[i].clear();
	}

	sLog.outString("Deleting Charters...");
	for(UNORDERED_MAP<uint32, Charter*>::iterator itr =  m_charters.begin(); itr != m_charters.end(); ++itr)
	{
		delete itr->second;
	}

	sLog.outString("Deleting reputation tables...");
	for(UNORDERED_MAP<uint32, ReputationModifier*>::iterator itr = this->m_reputation_creature.begin(); itr != m_reputation_creature.end(); ++itr)
	{
		ReputationModifier * mod = itr->second;
		mod->mods.clear();
		delete mod;
	}
	for(UNORDERED_MAP<uint32, ReputationModifier*>::iterator itr = this->m_reputation_faction.begin(); itr != m_reputation_faction.end(); ++itr)
	{
		ReputationModifier * mod = itr->second;
		mod->mods.clear();
		delete mod;
	}
}

//
// Groups
//

Group * ObjectMgr::GetGroupByLeader(Player* pPlayer)
{
	GroupSet::const_iterator itr;
	for (itr = mGroupSet.begin(); itr != mGroupSet.end(); itr++)
	{
		if ((*itr)->GetLeader() == pPlayer)
		{
			return *itr;
		}
	}

	return NULL;
}

Group * ObjectMgr::GetGroupById(uint32 id)
{
	GroupSet::const_iterator itr;
	for (itr = mGroupSet.begin(); itr != mGroupSet.end(); itr++)
	{
		if ((*itr)->GetID() == id)
		{
			return *itr;
		}
	}

	return NULL;
}

//
// Player names
//
void ObjectMgr::DeletePlayerInfo( uint32 guid )
{
	UNORDERED_MAP<uint32,PlayerInfo*>::iterator i;
	playernamelock.AcquireWriteLock();
	i=m_playersinfo.find(guid);
	if(i!=m_playersinfo.end())
	{
		delete i->second;
		m_playersinfo.erase(i);
	}
	playernamelock.ReleaseWriteLock();
}

PlayerInfo *ObjectMgr::GetPlayerInfo( uint32 guid )
{
	UNORDERED_MAP<uint32,PlayerInfo*>::iterator i;
	PlayerInfo * rv;
	playernamelock.AcquireReadLock();
	i=m_playersinfo.find(guid);
	if(i!=m_playersinfo.end())
		rv = i->second;
	else
		rv = NULL;
	playernamelock.ReleaseReadLock();
	return rv;
}

void ObjectMgr::AddPlayerInfo(PlayerInfo *pn)
{
	playernamelock.AcquireWriteLock();
	m_playersinfo[pn->guid] =  pn ;
	playernamelock.ReleaseWriteLock();
}

void ObjectMgr::LoadSpellSkills()
{
	sLog.outString("  Loading Spell Skills...");
	uint32 i;
//	int total = sSkillStore.GetNumRows();

	for(i = 0; i < sSkillStore.GetNumRows(); i++)
	{
		skilllinespell *sp = sSkillStore.LookupEntry(i);
		if (sp)
		{
			mSpellSkills[sp->spell] = sp;
		}
	}
}

skilllinespell* ObjectMgr::GetSpellSkill(uint32 id)
{
	return mSpellSkills[id];
}

void ObjectMgr::LoadPlayersInfo()
{
	PlayerInfo * pn;
	QueryResult *result = CharacterDatabase.Query("SELECT guid,name,race,class,level,gender,zoneId,timestamp,publicNote,officerNote,guildRank,acct FROM characters");
	if(result)
	{
		do
		{
			Field *fields = result->Fetch();
			pn=new PlayerInfo;
			pn->guid = fields[0].GetUInt64();
			pn->name = fields[1].GetString();
			pn->race = fields[2].GetUInt8();
			pn->cl = fields[3].GetUInt8();
			pn->lastLevel = fields[4].GetUInt32();
			pn->gender = fields[5].GetUInt8();
			pn->lastZone=fields[6].GetUInt32();
			pn->lastOnline=fields[7].GetUInt32();
			pn->publicNote=fields[8].GetString();
			pn->officerNote= fields[9].GetString();
			pn->Rank=fields[10].GetUInt32();
			pn->acct = fields[11].GetUInt32();

			if(pn->race==RACE_HUMAN||pn->race==RACE_DWARF||pn->race==RACE_GNOME||pn->race==RACE_NIGHTELF||pn->race==RACE_DRAENEI)
				pn->team = 0;
			else 
				pn->team = 1;
		  
			//this is startup -> no need in lock -> don't use addplayerinfo
			 m_playersinfo[(uint32)pn->guid]=pn;
		} while( result->NextRow() );

		delete result;
	}
	LoadGuilds();
}

PlayerInfo* ObjectMgr::GetPlayerInfoByName(std::string &name)
{
	UNORDERED_MAP<uint32,PlayerInfo*>::const_iterator i;

	PlayerInfo * rv = 0;
	playernamelock.AcquireReadLock();
	for(i=m_playersinfo.begin();i!=m_playersinfo.end();i++)
		if(!stricmp(i->second->name.c_str(),name.c_str()))
		{
			rv = i->second;
			break;
		}
	playernamelock.ReleaseReadLock();
	return rv;
}

void ObjectMgr::LoadPlayerCreateInfo()
{
	sLog.outString("  Loading Player Create Info...");
	QueryResult *result = WorldDatabase.Query( "SELECT * FROM playercreateinfo" );

	if( !result )
	{
		sLog.outString("  Query failed: SELECT * FROM playercreateinfo");
		return;
	}

	PlayerCreateInfo *pPlayerCreateInfo;

	do
	{
		Field *fields = result->Fetch();

		pPlayerCreateInfo = new PlayerCreateInfo;

		pPlayerCreateInfo->index = fields[0].GetUInt8();
		pPlayerCreateInfo->race = fields[1].GetUInt8();
		pPlayerCreateInfo->factiontemplate = fields[2].GetUInt32();
		pPlayerCreateInfo->class_ = fields[3].GetUInt8();
		pPlayerCreateInfo->mapId = fields[4].GetUInt32();
		pPlayerCreateInfo->zoneId = fields[5].GetUInt32();
		pPlayerCreateInfo->positionX = fields[6].GetFloat();
		pPlayerCreateInfo->positionY = fields[7].GetFloat();
		pPlayerCreateInfo->positionZ = fields[8].GetFloat();
		pPlayerCreateInfo->displayId = fields[9].GetUInt16();
		pPlayerCreateInfo->strength = fields[10].GetUInt8();
		pPlayerCreateInfo->ability = fields[11].GetUInt8();
		pPlayerCreateInfo->stamina = fields[12].GetUInt8();
		pPlayerCreateInfo->intellect = fields[13].GetUInt8();
		pPlayerCreateInfo->spirit = fields[14].GetUInt8();
		pPlayerCreateInfo->health = fields[15].GetUInt32();
		pPlayerCreateInfo->mana = fields[16].GetUInt32();
		pPlayerCreateInfo->rage = fields[17].GetUInt32();
		pPlayerCreateInfo->focus = fields[18].GetUInt32();
		pPlayerCreateInfo->energy = fields[19].GetUInt32();
		pPlayerCreateInfo->attackpower = fields[20].GetUInt32();
		pPlayerCreateInfo->mindmg = fields[21].GetFloat();
		pPlayerCreateInfo->maxdmg = fields[22].GetFloat();

		QueryResult *sk_sql = WorldDatabase.Query(
			"SELECT * FROM playercreateinfo_skills WHERE indexid=%u",pPlayerCreateInfo->index);

		if(sk_sql)
		{
			do 
			{
				Field *fields = sk_sql->Fetch();
				CreateInfo_SkillStruct tsk;
				tsk.skillid = fields[1].GetUInt32();
				tsk.currentval = fields[2].GetUInt32();
				tsk.maxval = fields[3].GetUInt32();
				pPlayerCreateInfo->skills.push_back(tsk);
			} while(sk_sql->NextRow());
			delete sk_sql;
		}
		QueryResult *sp_sql = WorldDatabase.Query(
			"SELECT * FROM playercreateinfo_spells WHERE indexid=%u",pPlayerCreateInfo->index);

		if(sp_sql)
		{
			do 
			{
				pPlayerCreateInfo->spell_list.push_back(sp_sql->Fetch()[1].GetUInt16());
			} while(sp_sql->NextRow());
			delete sp_sql;
		}
	  
		QueryResult *items_sql = WorldDatabase.Query(
			"SELECT * FROM playercreateinfo_items WHERE indexid=%u",pPlayerCreateInfo->index);
		
		if(items_sql)
		{
			do 
			{
				Field *fields = items_sql->Fetch();
				CreateInfo_ItemStruct itm;
				itm.protoid = fields[1].GetUInt32();
				itm.slot = fields[2].GetUInt8();
				itm.amount = fields[3].GetUInt32();
				pPlayerCreateInfo->items.push_back(itm);
			} while(items_sql->NextRow());
		   delete items_sql;
		}

		QueryResult *bars_sql = WorldDatabase.Query(
			"SELECT * FROM playercreateinfo_bars WHERE class=%u",pPlayerCreateInfo->class_ );

		if(bars_sql)
		{
			do 
			{
				Field *fields = bars_sql->Fetch();
				CreateInfo_ActionBarStruct bar;
				bar.button = fields[2].GetUInt32();
				bar.action = fields[3].GetUInt32();
				bar.type = fields[4].GetUInt32();
				bar.misc = fields[5].GetUInt32();
				pPlayerCreateInfo->actionbars.push_back(bar);
			} while(bars_sql->NextRow());			
			delete bars_sql;
		}
	
		mPlayerCreateInfo[pPlayerCreateInfo->index] = pPlayerCreateInfo;
	} while( result->NextRow() );

	delete result;

	GenerateLevelUpInfo();
}

// DK:LoadGuilds()
void ObjectMgr::LoadGuilds()
{
	QueryResult *result = CharacterDatabase.Query( "SELECT * FROM guilds" );
	QueryResult *result2;	
	QueryResult *result3;

	if(!result)
	{
		return;
	}

	Guild *pGuild;
	struct RankInfo rankList;

	do
	{
		Field *fields = result->Fetch();

		pGuild = new Guild;

		pGuild->SetGuildId( fields[0].GetUInt32() );
		pGuild->SetGuildName( fields[1].GetString() );
		pGuild->SetGuildLeaderGuid(fields[2].GetUInt64() );
		pGuild->SetGuildEmblemStyle( fields[3].GetUInt32() );
		pGuild->SetGuildEmblemColor(fields[4].GetUInt32() );
		pGuild->SetGuildBorderStyle( fields[5].GetUInt32() );
		pGuild->SetGuildBorderColor( fields[6].GetUInt32() );
		pGuild->SetGuildBackgroundColor( fields[7].GetUInt32() );
		pGuild->SetGuildInfo( fields[8].GetString() );
		pGuild->SetGuildMotd( fields[9].GetString() );

		result2 = CharacterDatabase.Query( "SELECT guid FROM characters WHERE guildId=%u",pGuild->GetGuildId());
		if(result2)
		{
			do
			{
				PlayerInfo *pi=objmgr.GetPlayerInfo(result2->Fetch()->GetUInt64());
				if(pi)
				pGuild->AddGuildMember( pi );
			}while( result2->NextRow() );
			delete result2;
		}

		result3 = CharacterDatabase.Query("SELECT * FROM guild_ranks WHERE guildId=%u ORDER BY rankId", pGuild->GetGuildId());
		if(result3)
		{ 
			do
			{
				Field *fields3 = result3->Fetch();

				rankList.name = fields3[2].GetString();
				rankList.rights = fields3[3].GetUInt32();

				pGuild->CreateRank(rankList.name, rankList.rights );
			}while( result3->NextRow() );
			delete result3;
		}
		pGuild->LoadGuildCreationDate();

		AddGuild(pGuild);

	}while( result->NextRow() );

	delete result;
}

Corpse* ObjectMgr::LoadCorpse(uint32 guid)
{
	Corpse *pCorpse;
	QueryResult *result = CharacterDatabase.Query("SELECT * FROM Corpses WHERE guid =%u ", guid );

	if( !result )
		return NULL;
	
	do
	{
		Field *fields = result->Fetch();
		pCorpse = new Corpse(HIGHGUID_CORPSE,fields[0].GetUInt32());
		pCorpse->SetPosition(fields[1].GetFloat(), fields[2].GetFloat(), fields[3].GetFloat(), fields[4].GetFloat());
		pCorpse->SetZoneId(fields[5].GetUInt32());
		pCorpse->SetMapId(fields[6].GetUInt32());
		pCorpse->LoadValues( fields[7].GetString());
		if(pCorpse->GetUInt32Value(CORPSE_FIELD_DISPLAY_ID) == 0)
		{
			delete pCorpse;
			continue;
		}

		pCorpse->SetLoadedFromDB(true);
		pCorpse->SetInstanceID(fields[8].GetUInt32());
		pCorpse->AddToWorld();
	 } while( result->NextRow() );

	delete result;

	return pCorpse;
}


//------------------------------------------------------
// Live corpse retreival.
// comments: I use the same tricky method to start from the last corpse instead of the first
//------------------------------------------------------
Corpse *ObjectMgr::GetCorpseByOwner(uint32 ownerguid)
{
	UNORDERED_MAP<uint32, Corpse*>::const_iterator itr;
	Corpse *rv = NULL;
	_corpseslock.Acquire();
	for (itr = m_corpses.begin();itr != m_corpses.end(); ++itr)
	{
		if(itr->second->GetUInt32Value(CORPSE_FIELD_OWNER) == ownerguid)
		{
			rv = itr->second;
			break;
		}
	}
	_corpseslock.Release();


	return rv;
}

void ObjectMgr::DelinkPlayerCorpses(Player *pOwner)
{
	//dupe protection agaisnt crashs
	Corpse * c;
	c=this->GetCorpseByOwner(pOwner->GetGUIDLow());
	if(!c)return;
	c->SetUInt64Value(CORPSE_FIELD_OWNER, 0);
	c->SetUInt32Value(CORPSE_FIELD_FLAGS, 5);
	c->SetCorpseState(CORPSE_STATE_BONES);
	c->DeleteFromDB();
	CorpseAddEventDespawn(c);
}

void ObjectMgr::LoadGMTickets()
{
	QueryResult *result = CharacterDatabase.Query( "SELECT * FROM gm_tickets" );

	GM_Ticket *ticket;
	if(result == 0)
		return;

	do
	{
		Field *fields = result->Fetch();

		ticket = new GM_Ticket;
		ticket->guid = fields[0].GetUInt32();
		ticket->name = fields[1].GetString();
		ticket->level = fields[2].GetUInt32();
		ticket->type = fields[3].GetUInt32();
		ticket->posX = fields[4].GetFloat();
		ticket->posY = fields[5].GetFloat();
		ticket->posZ = fields[6].GetFloat();
		ticket->message = fields[7].GetString();
		ticket->timestamp = fields[8].GetUInt32();

		AddGMTicket(ticket);

	} while( result->NextRow() );

	delete result;
}

void ObjectMgr::SaveGMTicket(uint64 guid)
{
	GM_Ticket* ticket = GetGMTicket(guid);
	if(!ticket)
	{
		return;
	}

	std::stringstream ss1;
	std::stringstream ss2;
	ss1 << "DELETE FROM gm_tickets WHERE guid = " << guid << ";";
	CharacterDatabase.Execute(ss1.str( ).c_str( ));

	ss2 << "INSERT INTO gm_tickets (guid, name, level, type, posX, posY, posZ, message, timestamp) VALUES(";
	ss2 << ticket->guid << ", '";
	ss2 << CharacterDatabase.EscapeString(ticket->name) << "', ";
	ss2 << ticket->level << ", ";
	ss2 << ticket->type << ", ";
	ss2 << ticket->posX << ", ";
	ss2 << ticket->posY << ", ";
	ss2 << ticket->posZ << ", '";
	ss2 << CharacterDatabase.EscapeString(ticket->message) << "', ";
	ss2 << ticket->timestamp << ");";
	CharacterDatabase.Execute(ss2.str( ).c_str( ));
}

void ObjectMgr::SetHighestGuids()
{
	QueryResult *result;

	result = CharacterDatabase.Query( "SELECT MAX(guid) FROM characters" );
	if( result )
	{
		m_hiPlayerGuid = result->Fetch()[0].GetUInt32();
		delete result;
	}

	result = CharacterDatabase.Query("SELECT MAX(guid) FROM playeritems WHERE guid <25769803776");
	if( result )
	{
		m_hiItemGuid = (uint32)result->Fetch()[0].GetUInt64();
		delete result;
	}

	result = CharacterDatabase.Query("SELECT MAX(guid) FROM playeritems WHERE guid >25769803776");
	if( result )
	{
		m_hiContainerGuid  = (uint32)result->Fetch()[0].GetUInt64();
		delete result;
	}

	result = CharacterDatabase.Query( "SELECT MAX(guid) FROM corpses" );
	if( result )
	{
		m_hiCorpseGuid = result->Fetch()[0].GetUInt32();
		delete result;
	}

	result = WorldDatabase.Query("SELECT MAX(id) FROM creature_spawns");
	if(result)
	{
		m_hiCreatureSpawnId = result->Fetch()[0].GetUInt32();
		delete result;
	}

	result = WorldDatabase.Query("SELECT MAX(id) FROM gameobject_spawns");
	if(result)
	{
		m_hiGameObjectSpawnId = result->Fetch()[0].GetUInt32();
		delete result;
	}
}


uint32 ObjectMgr::GenerateMailID()
{
	return m_mailid++;
}
uint32 ObjectMgr::GenerateLowGuid(uint32 guidhigh)
{
	ASSERT(guidhigh == HIGHGUID_ITEM || guidhigh == HIGHGUID_CONTAINER);

	uint32 ret;
	if(guidhigh == HIGHGUID_ITEM)
	{
		m_guidGenMutex.Acquire();
		ret = ++m_hiItemGuid;
		m_guidGenMutex.Release();
	}else
	{
		m_guidGenMutex.Acquire();
		ret = ++m_hiContainerGuid;
		m_guidGenMutex.Release();
	}
	return ret;
}

void ObjectMgr::ProcessGameobjectQuests()
{
	/*if(!mGameObjectNames.size())
		return;

	int total = mGameObjectNames.size();
	std::set<Quest*> tmp;
	for(UNORDERED_MAP<uint32, Quest*>::iterator itr = sQuestMgr.Begin(); itr != sQuestMgr.End(); ++itr)
	{
		Quest *qst = itr->second;
		if(qst->count_required_item > 0 || 
			qst->required_mobtype[0] == QUEST_MOB_TYPE_GAMEOBJECT ||
			qst->required_mobtype[1] == QUEST_MOB_TYPE_GAMEOBJECT ||
			qst->required_mobtype[2] == QUEST_MOB_TYPE_GAMEOBJECT ||
			qst->required_mobtype[3] == QUEST_MOB_TYPE_GAMEOBJECT )
		{
			tmp.insert(qst);
		}
	}
	std::vector<GameObjectInfo*> gos;
	gos.reserve(5000);
	for(GameObjectNameMap::iterator it0 = mGameObjectNames.begin(); it0 != mGameObjectNames.end(); ++it0)
	{
		GameObjectInfo *gon = it0->second;
		gos.push_back(it0->second);
	}

	int c = 0;
	total = gos.size();
	for(std::vector<GameObjectInfo*>::iterator it0 = gos.begin(); it0 != gos.end(); ++it0)
	{
		GameObjectInfo *gon = (*it0);

		map<uint32, std::set<uint32> >* golootlist = &(LootMgr::getSingleton().quest_loot_go);
		map<uint32, std::set<uint32> >::iterator it2 = golootlist->find(gon->ID);
		//// QUEST PARSING
		for(std::set<Quest*>::iterator itr = tmp.begin(); itr != tmp.end(); ++itr)
		{
			Quest *qst = *itr;
			int max = qst->count_required_mob;
			if(qst->count_required_item > max)
				max = qst->count_required_item;

			if(max > 0)
			{
				for(int i = 0; i < max; ++i)
				{
					if(qst->required_mob[i] > 0)
					{
						if(qst->required_mob[i] == gon->ID &&
						qst->required_mobtype[i] == QUEST_MOB_TYPE_GAMEOBJECT)
						{
							gon->goMap.insert( GameObjectGOMap::value_type( qst, qst->required_mobcount[i] ) );
							sDatabase.WaitExecute("INSERT INTO gameobject_quest_pickup_binding VALUES(%u, %u, %u)",
								gon->ID, qst->id, qst->required_mobcount[i]);
						}
					}
					if(qst->required_itemcount[i] > 0 && it2 != golootlist->end())
					{
						// check our loot template for this item
						for(std::set<uint32>::iterator it4 = it2->second.begin(); it4 != it2->second.end(); ++it4)
						{
							if((*it4) == qst->required_item[i])
							{
								//GOQuestItem it;
								//it.itemid = qst->required_item[i];
								//it.requiredcount = qst->required_itemcount[i];
								//gon->itemMap.insert( GameObjectItemMap::value_type( qst, it ) );
								//gon->itemMap[qst].insert(it);
								gon->itemMap[qst].insert( std::map<uint32, uint32>::value_type( qst->required_item[i], qst->required_itemcount[i]) );
								sDatabase.WaitExecute("INSERT INTO gameobject_quest_item_binding VALUES(%u, %u, %u, %u)",
									gon->ID, qst->id, qst->required_item[i], qst->required_itemcount[i]);
							}
						}
					}
				}
			}
		}
		c++;
		if(!(c % 150))
			SetProgressBar(c, total, "Binding");
	}
	ClearProgressBar();*/
	QueryResult * result  = WorldDatabase.Query("SELECT * FROM gameobject_quest_item_binding");
	QueryResult * result2 = WorldDatabase.Query("SELECT * FROM gameobject_quest_pickup_binding");

	GameObjectInfo * gon;
	Quest * qst;

	if(result)
	{
		do 
		{
			Field * fields = result->Fetch();
			gon = GameObjectNameStorage.LookupEntry(fields[0].GetUInt32());
			qst = QuestStorage.LookupEntry(fields[1].GetUInt32());
			if(gon && qst)
				gon->itemMap[qst].insert( make_pair( fields[2].GetUInt32(), fields[3].GetUInt32() ) );			

		} while(result->NextRow());
		delete result;
	}


	if(result2)
	{
		do 
		{
			Field * fields = result2->Fetch();
			gon = GameObjectNameStorage.LookupEntry(fields[0].GetUInt32());
			qst = QuestStorage.LookupEntry(fields[1].GetUInt32());
			if(gon && qst)
				gon->goMap.insert( make_pair( qst, fields[2].GetUInt32() ) );

		} while(result2->NextRow());
		delete result2;
	}

	result = WorldDatabase.Query("SELECT * FROM npc_gossip_textid");
	if(result)
	{
		uint32 entry, text;
		do 
		{
			entry = result->Fetch()[0].GetUInt32();
			text  = result->Fetch()[1].GetUInt32();

			mNpcToGossipText[entry] = text;

		} while(result->NextRow());
		delete result;
	}
}

Player* ObjectMgr::GetPlayer(const char* name, bool caseSensitive)
{
	Player * rv = NULL;
	UNORDERED_MAP<uint32, Player*>::const_iterator itr;
	_playerslock.AcquireReadLock();	

	if(!caseSensitive)
	{
		std::string strName = name;
		std::transform(strName.begin(),strName.end(),strName.begin(),towlower);
		for (itr = _players.begin(); itr != _players.end(); ++itr)
		{
			if(!stricmp(itr->second->GetNameString()->c_str(), strName.c_str()))
			{
				rv = itr->second;
				break;
			}
		}
	}
	else
	{
		for (itr = _players.begin(); itr != _players.end(); ++itr)
		{
			if(!strcmp(itr->second->GetName(), name))
			{
				rv = itr->second;
				break;
			}
		}
	}
		
	_playerslock.ReleaseReadLock();

	return rv;
}

Player* ObjectMgr::GetPlayer(uint32 guid)
{
	Player * rv;
	
	_playerslock.AcquireReadLock();	
	UNORDERED_MAP<uint32, Player*>::const_iterator itr = _players.find(guid);
	rv = (itr != _players.end()) ? itr->second : 0;
	_playerslock.ReleaseReadLock();

	return rv;
}

PlayerCreateInfo* ObjectMgr::GetPlayerCreateInfo(uint8 race, uint8 class_) const
{
	PlayerCreateInfoMap::const_iterator itr;
	for (itr = mPlayerCreateInfo.begin(); itr != mPlayerCreateInfo.end(); itr++)
	{
		if( (itr->second->race == race) && (itr->second->class_ == class_) )
			return itr->second;
	}
	return NULL;
}

void ObjectMgr::AddGuild(Guild *pGuild)
{
	ASSERT( pGuild );
	mGuild[pGuild->GetGuildId()] = pGuild;
}

uint32 ObjectMgr::GetTotalGuildCount()
{
	return mGuild.size();
}

bool ObjectMgr::RemoveGuild(uint32 guildId)
{
	GuildMap::iterator i = mGuild.find(guildId);
	if (i == mGuild.end())
	{
		return false;
	}

	i->second->RemoveFromDb();
	mGuild.erase(i);

	return true;
}

Guild* ObjectMgr::GetGuild(uint32 guildId)
{
	GuildMap::const_iterator itr = mGuild.find(guildId);
	if(itr == mGuild.end())
		return NULL;
	return itr->second;
}

Guild* ObjectMgr::GetGuildByLeaderGuid(uint64 leaderGuid)
{
	GuildMap::const_iterator itr;
	for (itr = mGuild.begin();itr != mGuild.end(); itr++)
	{
		if( itr->second->GetGuildLeaderGuid() == leaderGuid )
			return itr->second;
	}
	return NULL;
}

Guild* ObjectMgr::GetGuildByGuildName(std::string guildName)
{
	GuildMap::const_iterator itr;
	for (itr = mGuild.begin();itr != mGuild.end(); itr++)
	{
		if( itr->second->GetGuildName() == guildName )
			return itr->second;
	}
	return NULL;
}


void ObjectMgr::AddGMTicket(GM_Ticket *ticket)
{
	ASSERT( ticket );
	GM_TicketList.push_back(ticket);

	// save
	SaveGMTicket(ticket->guid);
}

//modified for vs2005 compatibility
void ObjectMgr::remGMTicket(uint64 guid)
{
	for(std::list<GM_Ticket*>::iterator i = GM_TicketList.begin(); i != GM_TicketList.end();)
	{
		if((*i)->guid == guid)
		{
			i = GM_TicketList.erase(i);
		}
		else
		{
			++i;
		}
	}

	// kill from db
	CharacterDatabase.Execute("DELETE FROM gm_tickets WHERE guid=%u", guid);
}

GM_Ticket* ObjectMgr::GetGMTicket(uint64 guid)
{
	for(std::list<GM_Ticket*>::iterator i = GM_TicketList.begin(); i != GM_TicketList.end(); i++)
	{
		if((*i)->guid == guid)
		{
			return (*i);
		}
	}
	return NULL;
}

void ObjectMgr::LoadVendors()
{
	sLog.outString("  Loading Vendors...");
	UNORDERED_MAP<uint32, std::vector<CreatureItem>*>::const_iterator itr;
	std::vector<CreatureItem> *items;
	CreatureItem itm;
  
	QueryResult *result = WorldDatabase.Query("SELECT * FROM vendors");
	if(result)
	{
		do
		{
			Field *fields = result->Fetch();

			itr = mVendors.find(fields[0].GetUInt32());
			if (itr == mVendors.end())
			{
				items = new std::vector<CreatureItem>;
				mVendors[fields[0].GetUInt32()] = items;
			}
			else
			{
				items = itr->second;
			}
			
			itm.itemid = fields[1].GetUInt32();
			itm.amount = fields[2].GetUInt32();
			items->push_back(itm);
		}
		while( result->NextRow() );

		delete result;
	}
}

std::vector<CreatureItem>* ObjectMgr::GetVendorList(uint32 entry)
{
	return mVendors[entry];
}

void ObjectMgr::LoadTotemSpells()
{
	sLog.outString("  Loading Totem Spells...");
	std::stringstream query;
	QueryResult *result = WorldDatabase.Query( "SELECT * FROM totemspells" );

	if(!result)
	{
		sLog.outString("Query failed: SELECT * FROM totemspells");
		return;
	}

	//TotemSpells *ts = NULL;
	SpellEntry * sp;
	uint32 spellid;

	do
	{
		Field *fields = result->Fetch();
		spellid = fields[1].GetUInt32();
		sp = sSpellStore.LookupEntry(spellid);
		if(!spellid || !sp) continue;

		m_totemSpells.insert( TotemSpellMap::value_type( fields[0].GetUInt32(), sp ));
	} while( result->NextRow() );

	delete result;
}

SpellEntry* ObjectMgr::GetTotemSpell(uint32 spellId)
{
	return m_totemSpells[spellId];
}

void ObjectMgr::LoadAIThreatToSpellId()
{
	QueryResult *result = WorldDatabase.Query( "SELECT * FROM ai_threattospellid" );

	if(!result)
	{
		sLog.outString("  Query failed: SELECT * FROM ai_threattospellid");
		return;
	}

	ThreatToSpellId *t2s = NULL;

	do
	{
		Field *fields = result->Fetch();

		t2s = new ThreatToSpellId;
		t2s->spellId = fields[0].GetUInt32();
		t2s->mod = atoi(fields[1].GetString());
		threatToSpells.push_back(t2s);

	} while( result->NextRow() );

	delete result;
}

int32 ObjectMgr::GetAIThreatToSpellId(uint32 spellId)
{
	for(std::list<ThreatToSpellId*>::iterator i = threatToSpells.begin(); i != threatToSpells.end(); i++)
	{
		if((*i)->spellId == spellId)
		{
			return (*i)->mod;
		}
	}
	return 0;
}

Item * ObjectMgr::CreateItem(uint32 entry,Player * owner)
{
	ItemPrototype * proto = ItemPrototypeStorage.LookupEntry(entry);
	if(proto == 0) return 0;

	if(proto->InventoryType == INVTYPE_BAG)
	{
		Container * pContainer = new Container(HIGHGUID_CONTAINER,GenerateLowGuid(HIGHGUID_CONTAINER));
		pContainer->Create( entry, owner);
		pContainer->SetUInt32Value(ITEM_FIELD_STACK_COUNT, 1);
		return pContainer;
	}
	else
	{
		Item * pItem = new Item(HIGHGUID_ITEM,GenerateLowGuid(HIGHGUID_ITEM));
		pItem->Create(entry, owner);
		pItem->SetUInt32Value(ITEM_FIELD_STACK_COUNT, 1);
		return pItem;
	}
}

Item * ObjectMgr::LoadItem(uint64 guid)
{
	QueryResult * result = CharacterDatabase.Query("SELECT * FROM playeritems WHERE guid =" I64FMTD, guid);
	Item * pReturn = 0;

	if(result)
	{
		ItemPrototype * pProto = ItemPrototypeStorage.LookupEntry(result->Fetch()[2].GetUInt32());
		if(pProto->InventoryType == INVTYPE_BAG)
		{
			Container * pContainer = new Container(HIGHGUID_CONTAINER,guid);
			pContainer->LoadFromDB(result->Fetch());
			pReturn = pContainer;
		}
		else
		{
			Item * pItem = new Item(HIGHGUID_ITEM,guid);
			pItem->LoadFromDB(result->Fetch(), 0, false);
			pReturn = pItem;
		}
		delete result;
	}
	
	return pReturn;
}

//------------------------------------------------------------
// Corpse Collector Loading
// comments:
//------------------------------------------------------------
void ObjectMgr::CorpseCollectorLoad()
{
	Corpse *pCorpse = NULL;
 
	QueryResult *result = CharacterDatabase.Query("SELECT * FROM corpses");

	if(result)
	{
		do
		{
		  Field *fields = result->Fetch();
		  pCorpse = new Corpse(HIGHGUID_CORPSE,fields[0].GetUInt32());
		  pCorpse->SetPosition(fields[1].GetFloat(), fields[2].GetFloat(), fields[3].GetFloat(), fields[4].GetFloat());
		  pCorpse->SetZoneId(fields[5].GetUInt32());
		  pCorpse->SetMapId(fields[6].GetUInt32());
		  pCorpse->LoadValues( fields[7].GetString());
		  pCorpse->SetInstanceID(fields[8].GetUInt32());
		  if(pCorpse->GetUInt32Value(CORPSE_FIELD_DISPLAY_ID) == 0)
		  {
			  delete pCorpse;
			  continue;
		  }

		  if(sWorldCreator.GetMap(pCorpse->GetMapId()) && sWorldCreator.GetMap(pCorpse->GetMapId())->InstanceExists(pCorpse->GetInstanceID()))
		  {
			  pCorpse->AddToWorld();
		  }else
			  delete pCorpse;
		} while( result->NextRow() );
		
		delete result;
	}
}

std::list<ItemPrototype*>* ObjectMgr::GetListForItemSet(uint32 setid)
{
	return mItemSets[setid];
}

void ObjectMgr::CorpseAddEventDespawn(Corpse *pCorpse)
{
	sEventMgr.AddEvent(pCorpse->GetMapMgr(), &MapMgr::EventCorpseDespawn, pCorpse->GetGUID(), EVENT_CORPSE_DESPAWN, 600000, 1);
}

void ObjectMgr::DespawnCorpse(uint64 Guid)
{
	Corpse * pCorpse = objmgr.GetCorpse(Guid);
	if(pCorpse == 0)	// Already Deleted
		return;
	
	pCorpse->Despawn();
	delete pCorpse;
}

void ObjectMgr::CorpseCollectorUnload()
{
	UNORDERED_MAP<uint32, Corpse*>::const_iterator itr;
	_corpseslock.Acquire();
	for (itr = m_corpses.begin(); itr != m_corpses.end();)
	{
		Corpse * c =itr->second;
		++itr;
		if(c->IsInWorld())
			c->RemoveFromWorld();
		delete c;
	}
	m_corpses.clear();
	_corpseslock.Release();
}

GossipMenu::GossipMenu(uint64 Creature_Guid, uint32 Text_Id) : TextId(Text_Id), CreatureGuid(Creature_Guid)
{

}

void GossipMenu::AddItem(uint16 Icon, const char* Text, int32 Id)
{
	GossipMenuItem Item;
	Item.Icon = Icon;
	Item.Text = Text;
	Item.Id = Menu.size();
	if(Id > 0)
		Item.IntId = Id;
	else
		Item.IntId = Item.Id;		

	Menu.push_back(Item);
}

void GossipMenu::AddItem(GossipMenuItem* GossipItem)
{
	Menu.push_back(*GossipItem);
}

void GossipMenu::BuildPacket(WorldPacket& Packet)
{
	Packet << CreatureGuid;
	Packet << TextId;
	Packet << uint32(Menu.size());

	for(std::vector<GossipMenuItem>::iterator iter = Menu.begin();
		iter != Menu.end(); ++iter)
	{
		Packet << iter->Id;
		Packet << iter->Icon;
		Packet << uint32(0);	// something new in tbc. maybe gold requirement or smth?
		Packet << iter->Text;
		Packet << uint8(0); // ?
	}
}

void GossipMenu::SendTo(Player* Plr)
{
	WorldPacket data(SMSG_GOSSIP_MESSAGE, Menu.size() * 50 + 12);
	BuildPacket(data);
	data << uint32(0);  // 0 quests obviously
	Plr->GetSession()->SendPacket(&data);
}

void ObjectMgr::CreateGossipMenuForPlayer(GossipMenu** Location, uint64 Guid, uint32 TextID, Player* Plr)
{
	GossipMenu *Menu = new GossipMenu(Guid, TextID);
	ASSERT(Menu);

	if(Plr->CurrentGossipMenu != NULL)
		delete Plr->CurrentGossipMenu;

	Plr->CurrentGossipMenu = Menu;
	*Location = Menu;
}

GossipMenuItem GossipMenu::GetItem(uint32 Id)
{
	if(Id >= Menu.size())
	{
		GossipMenuItem k;
		k.IntId = 1;
		return k;
	} else {
		return Menu[Id];
	}
}

uint32 ObjectMgr::GetGossipTextForNpc(uint32 ID)
{
	return mNpcToGossipText[ID];
}

void ObjectMgr::GenerateTrainerSpells()
{
	std::map<uint32, TrainerSpellOverride> OMap;
	
	QueryResult * result = WorldDatabase.Query("SELECT * FROM trainerspelloverride");
	if(result != 0)
	{
//		uint32 mx = result->GetRowCount(), c = 0;
		do 
		{
			Field * f = result->Fetch();
			TrainerSpellOverride ov;
			ov.Cost = f[1].GetUInt32();
			ov.RequiredSpell = f[2].GetUInt32();
			ov.DeleteSpell = f[3].GetUInt32();
			ov.RequiredSkill = f[4].GetUInt32();
			ov.RequiredSkillValue = f[5].GetUInt32();
			ov.RequiredLevel = f[6].GetUInt32();
			ov.RequiredClass = f[7].GetUInt32();

			OMap[f[0].GetUInt32()] = ov;
		} while(result->NextRow());
		delete result;
	}
	std::vector<uint32> itemSpell;

	// Lets take item spell learn list so we can remove recipe from trainers
	result = WorldDatabase.Query("SELECT spellid_1,spellid_2,spellid_3,spellid_4,spellid_5 FROM items");
	if(result != 0)
	{
		do 
		{
			Field * f = result->Fetch();
			uint32 s1,s2,s3,s4,s5;
			if((s1 = f[0].GetUInt32()) != 0)
			{
				SpellEntry *sp = sSpellStore.LookupEntry(s1);
				for(int i = 0; i < 3; i++)
				{
					if(sp->Effect[i] == SPELL_EFFECT_LEARN_SPELL
						|| sp->Effect[i] == SPELL_EFFECT_LEARN_PET_SPELL)
						itemSpell.push_back(sp->EffectTriggerSpell[i]);
				}
			}
			if((s2 = f[1].GetUInt32()) != 0)
			{
				SpellEntry *sp = sSpellStore.LookupEntry(s2);
				for(int i = 0; i < 3; i++)
				{
					if(sp->Effect[i] == SPELL_EFFECT_LEARN_SPELL
						|| sp->Effect[i] == SPELL_EFFECT_LEARN_PET_SPELL)
						itemSpell.push_back(sp->EffectTriggerSpell[i]);
				}
			}
			if((s3 = f[2].GetUInt32()) != 0)
			{
				SpellEntry *sp = sSpellStore.LookupEntry(s3);
				for(int i = 0; i < 3; i++)
				{
					if(sp->Effect[i] == SPELL_EFFECT_LEARN_SPELL
						|| sp->Effect[i] == SPELL_EFFECT_LEARN_PET_SPELL)
						itemSpell.push_back(sp->EffectTriggerSpell[i]);
				}
			}
			if((s4 = f[3].GetUInt32()) != 0)
			{
				SpellEntry *sp = sSpellStore.LookupEntry(s4);
				for(int i = 0; i < 3; i++)
				{
					if(sp->Effect[i] == SPELL_EFFECT_LEARN_SPELL
						|| sp->Effect[i] == SPELL_EFFECT_LEARN_PET_SPELL)
						itemSpell.push_back(sp->EffectTriggerSpell[i]);
				}
			}
			if((s5 = f[4].GetUInt32()) != 0)
			{
				SpellEntry *sp = sSpellStore.LookupEntry(s5);
				for(int i = 0; i < 3; i++)
				{
					if(sp->Effect[i] == SPELL_EFFECT_LEARN_SPELL
						|| sp->Effect[i] == SPELL_EFFECT_LEARN_PET_SPELL)
						itemSpell.push_back(sp->EffectTriggerSpell[i]);
				}
			}
		} while(result->NextRow());
		delete result;
	}

	// Convert ranks into our temp map.

	// i _hate_ string indexes :p
	map<string, map<uint32, uint32>* > SpellRankMap;
	map<uint32, uint32> SpellRanks;
	map<string, map<uint32, uint32>* >::iterator it1;
	map<uint32, uint32>::iterator it2;
	map<uint32, uint32> TeachingSpellMap;

	uint32 mx = sSpellStore.GetNumRows();
	for(uint32 i = 0; i < mx; ++i)
	{
		// Get Spell
		SpellEntry *Sp = static_cast<FastIndexedDataStore<SpellEntry>*>(SpellStore::getSingletonPtr())->LookupRow(i);
		if(Sp != NULL)
		{
			// Skip learning spells ;)
			// Skip any spells that are obselete
			if(Sp->SpellVisual == 222)
				continue;

			uint32 j;
			bool check = false;
			for(j = 0; j < 3; j++)
			{
				if(check)
					break;
				check = false;
				if(Sp->Effect[j] == SPELL_EFFECT_LEARN_SPELL ||
					Sp->Effect[j] == SPELL_EFFECT_LEARN_PET_SPELL)
				{
					// BANNED SPELLS CUZ THEY'RE FUCKED.. GG BLIZZARD
					if(Sp->Id == 21085 || Sp->Id == 1872)
						continue;

//					const char* SpellName = sSpellStore.LookupString(Sp->Name);
//					const char* RankName = sSpellStore.LookupString(Sp->Rank);
					if(!(TeachingSpellMap.find(Sp->EffectTriggerSpell[j]) == TeachingSpellMap.end()))
					{
						//printf("Duplicate training spell %s %s\n", SpellName, RankName);
					} else {
						for(std::vector<uint32>::iterator itr = itemSpell.begin(); itr != itemSpell.end(); ++itr)
						{
							if((*itr) == Sp->Id)
							{
								check = true;
								break;
							}
						}
						if(check)
							continue;
						TeachingSpellMap.insert( map<uint32, uint32>::value_type( Sp->EffectTriggerSpell[j], Sp->Id ) );
					}
					break;
				}
			}

			if(j != 3)
				continue;

			// Get our row name
			if(!Sp->Rank)
				continue;

			const char* SpellName = sSpellStore.LookupString(Sp->Name);
			const char* RankName = sSpellStore.LookupString(Sp->Rank);

			// Skip old spells
			if(SpellName[0] == 'z' && SpellName[1] == 'z' &&
				SpellName[2] == 'O' && SpellName[3] == 'L' &&
				SpellName[4] == 'D')
			{
				continue;
			}

			if(m_disabled_trainer_spells.find(Sp->Id) != m_disabled_trainer_spells.end())
				continue;

			// Convert rank name into a number
			int32 RankNumber = -1;

			if(sscanf(RankName, "Rank %d", (int*)&RankNumber) != 1)  // Not a ranked spell
				continue;

			SpellRanks[Sp->Id] = RankNumber;

			// Insert into our map if we don't have one
			string Sp_Name = SpellName;
			it1 = SpellRankMap.find(Sp_Name);
			map<uint32, uint32> *mapPtr;
			if(it1 == SpellRankMap.end())
			{
				mapPtr = new map<uint32, uint32>;
				SpellRankMap.insert( map<string, map<uint32, uint32>* >::value_type( Sp_Name, mapPtr ) );
				it1 = SpellRankMap.find(Sp_Name);
				ASSERT(it1 != SpellRankMap.end());
			} else {
				mapPtr = it1->second;
			}

			if(!(mapPtr->find(RankNumber) == mapPtr->end()))
			{

				uint32 o = mapPtr->find(RankNumber)->second;
				SpellEntry *p = sSpellStore.LookupEntry(o);
//				const char* SpellName2 = sSpellStore.LookupString(p->Name);
//				const char* RankName2 = sSpellStore.LookupString(p->Rank);

				// For enchants, override the aura spell with casting spell.
				if(Sp->Effect[0] == 54 ||
					Sp->Effect[1] == 54 ||
					Sp->Effect[2] == 54)
				{
					if(p->Effect[0] != 54 && p->Effect[1] != 54 && p->Effect[2] != 54)
						mapPtr->find(RankNumber)->second = Sp->Id;
				}
			} else {
				mapPtr->insert( map<uint32, uint32>::value_type( (uint32)RankNumber, Sp->Id ) );
			}
		}
	}

	skilllinespell *sp;
	SpellEntry * spell;
	TrainerSpellMap * destmap;

	mx = sSkillStore.GetNumRows();

	for(uint32 i = 0; i < mx; ++i)
	{
		sp = sSkillStore.LookupEntry(i);

		// Check if we're a learning spell :)
		spell = sSpellStore.LookupEntry(sp->spell);
		
		skilllineentry *skill = sSkillLineStore.LookupEntry(sp->skilline);
		ASSERT(skill);

		for(uint32 j = 0; j < 3; j++)
		{
			destmap = NULL;
			uint32 TeachingSpellId = TeachingSpellMap[sp->spell];
			
			const char* SpellName = sSpellStore.LookupString(spell->Name);
			const char* RankName = sSpellStore.LookupString(spell->Rank);

			if(!TeachingSpellId)
			{
				continue;
			}

			SpellEntry * TeachingSpell = sSpellStore.LookupEntry(TeachingSpellId);
			if(TeachingSpell->Effect[j] == SPELL_EFFECT_LEARN_SPELL)
				destmap = &mNormalSpells;
			else
				destmap = &mPetSpells;

			if(destmap == NULL)
				continue;

			// Create our trainer spell.
			uint32 SpellID = TeachingSpell->EffectTriggerSpell[j];

			// TODO: Check for quest reward spells, and shit like that.

			TrainerSpell * TS = new TrainerSpell;
			TS->pSpell = spell;
			TS->pTrainingSpell = TeachingSpell;
			TS->SpellID = SpellID;
			TS->TeachingSpellID = TeachingSpellId;
			TS->DeleteSpell = 0;
			TS->RequiredSpell = 0;
			TS->TeachingLine = 0;
			TS->IsProfession = 0;
			TS->RequiredClass = -1;

			// Find out our spell rank.
			string Sp_Name = SpellName;
			it1 = SpellRankMap.find(Sp_Name);
			if(it1 != SpellRankMap.end())
			{
				// We're a ranked spell.
				uint32 SpellRank = SpellRanks[SpellID];
				// Grab any ranks lower than ours
				if(SpellRank > 1)
				{
					vector<uint32> lowerspells;
					lowerspells.reserve(15);

					// Assign required spells
					uint32 crank = SpellRank - 1;
					if(crank > 0)
					{
						it2 = it1->second->find(crank);
						if((it2 != it1->second->end()))
						{
							uint32 rspell = it2->second;
							ASSERT(rspell);
							TS->RequiredSpell = rspell;

							uint32 flags = spell->SpellFamilyName;
							if(flags == 0x4 || flags == 0x10 || flags == 0x8 || flags == 0xA)
								TS->DeleteSpell = rspell;
						}
					}
				}
			}

			// Profession checks.. la di da...
			TS->RequiredSkillLine = 0;
			TS->RequiredSkillLineValue = 0;
			
			TS->RequiredLevel = spell->spellLevel;
			TS->Cost = sWorld.mPrices[spell->spellLevel];

			if(skill->type == SKILL_TYPE_PROFESSION)
			{
				// Check if we're a profession learner. If we are, we need to have the previous
				// rank. If we're a profession spell, we need to have an amount

				uint32 l;
				for(l = 0; l < 3; ++l)
				{
					if(TeachingSpell->Effect[l] == SPELL_EFFECT_SKILL_STEP)		// Rank
					{
						break;
					}
				}
				if(l == 3)
				{
					//TS->RequiredSkillLineValue = 1;
					//TS->RequiredSkillLineValue = sp->minrank ? sp->minrank : 1;
					if(sp->green)
						TS->RequiredSkillLineValue = (sp->green >= 30) ? (sp->green - 30) : sp->green;
					else
						TS->RequiredSkillLineValue = 1;
					TS->RequiredSkillLine = skill->id;
				}
				else
				{
					//Here handles general profession learns
					TS->TeachingLine = skill->id;
					uint32 rval = 0;
					// hack hack hack!
					if(!stricmp(RankName, "Journeyman"))
						rval = 75;
					else if(!stricmp(RankName, "Expert"))
						rval = 150;
					else if(!stricmp(RankName, "Artisan"))
						rval = 225;
					else if(!stricmp(RankName, "Master"))
						rval = 300;
					else
						TS->IsProfession = 1;

					if(rval != 0)
					{
						TS->RequiredSkillLine = skill->id;
						TS->RequiredSkillLineValue = rval;
					}
				}
			}
			if(skill->type == SKILL_TYPE_SECONDARY)
			{
				uint32 rval = 0;
				//Riding skills again
				if(strstr(SpellName, "Riding") || strstr(SpellName, "Piloting")
					|| strstr(SpellName, "Horsemanship"))
				{					
					if(!stricmp(RankName, "Apprentice"))
					{
						TS->Cost = 900000;
						TS->RequiredLevel = 40;
					}
					else if(!stricmp(RankName, "Journeyman"))
					{
						rval = 75;
						TS->Cost = 6000000;
						TS->RequiredLevel = 60;
					}
					else if(!stricmp(RankName, "Expert"))
					{
						rval = 150;
						TS->Cost = 8000000;
						TS->RequiredLevel = 70;
					}
					else if(!stricmp(RankName, "Artisan"))
					{
						rval = 225;
						TS->Cost = 50000000;
						TS->RequiredLevel = 70;
					}
					//No Master for now but if we have later
					else if(!stricmp(RankName, "Master"))
					{
						rval = 300;
						TS->RequiredLevel = 70;
						TS->Cost = 90000000;
					}
					else//No old shit
					{
						delete TS;
						break;
					}
				}

				if(rval != 0)
				{
					TS->RequiredSkillLine = skill->id;
					TS->RequiredSkillLineValue = rval;
				}
			}
			std::map<uint32, TrainerSpellOverride>::iterator oitr = OMap.find(TS->TeachingSpellID);
			if(oitr == OMap.end()) oitr = OMap.find(TS->SpellID);
			if(oitr != OMap.end())
			{
				TrainerSpellOverride * ov = &oitr->second;
				TS->Cost = ov->Cost ? ov->Cost : TS->Cost;
				TS->RequiredClass = ov->RequiredClass ? ov->RequiredClass : TS->RequiredClass;
				TS->RequiredSpell = ov->RequiredSpell ? ov->RequiredSpell : TS->RequiredSpell;
				TS->RequiredSkillLine = ov->RequiredSkill ? ov->RequiredSkill : TS->RequiredSkillLine;
				TS->RequiredSkillLineValue = ov->RequiredSkillValue ? ov->RequiredSkillValue : TS->RequiredSkillLineValue;
				TS->DeleteSpell = ov->DeleteSpell ? ov->DeleteSpell : TS->DeleteSpell;
				TS->RequiredLevel = ov->RequiredLevel ? ov->RequiredLevel : TS->RequiredLevel;
				TS->RequiredClass = ov->RequiredClass ? ov->RequiredClass : TS->RequiredClass;
			} 

			if(skill->type == SKILL_TYPE_PROFESSION || skill->type == SKILL_TYPE_SECONDARY)
			{
				if(skill->type == SKILL_TYPE_SECONDARY)
				{
					if(skill->id == 185 || skill->id == 129 || skill->id == 356)
					{
						if(sp->next == 0 && TS->RequiredSkillLineValue <= 1)
						{
							delete TS;
							continue;
						}
					}
				}
				else
				{
					if(TS->IsProfession != 1 && TS->RequiredSkillLineValue <= 1)
					{
						delete TS;
						continue;
					}
				}
			}

			if(m_disabled_trainer_spells.find( TS->pSpell->Id ) != m_disabled_trainer_spells.end() ||
				m_disabled_trainer_spells.find( TS->pTrainingSpell->Id ) != m_disabled_trainer_spells.end())
			{
				delete TS;
				continue;
			}

			TrainerSpellMap::iterator iter = destmap->find(sp->skilline);
			if(iter == destmap->end())
			{
				vector<TrainerSpell*> v;
				v.push_back(TS);
				destmap->insert( TrainerSpellMap::value_type( sp->skilline, v ) );
				//const char* skillname = sSkillLineStore.LookupString(skill->Name);
				/*printf("Skill line: %s created for %s.\n", skillname,
					( destmap == &mNormalSpells ? "NORMAL" : "PET"));*/
			} else {
				iter->second.push_back(TS);
			}
		}
	}
	// Cleanup
	for(it1 = SpellRankMap.begin(); it1 != SpellRankMap.end(); ++it1)
	{
		it1->second->clear();
		delete it1->second;
	}
	SpellRankMap.clear();
}

void ObjectMgr::LoadTrainers()
{
	sLog.outString("  Loading Trainers...");
	LoadDisabledSpells();
	GenerateTrainerSpells();
	QueryResult * result = WorldDatabase.Query("SELECT * FROM trainers");
	if(!result) return;

//	uint32 mx = result->GetRowCount();
//	uint32 c = 0;
	uint32 entry, maxlevel, class_;
	uint32 skilllines[20];
	skilllineentry *skill;
	do 
	{
		Field * fields = result->Fetch();
		entry = fields[0].GetUInt32();
		
		Trainer * tr = new Trainer;
		tr->TrainerType = 0;
		
		for(uint32 i = 0; i < 20; ++i)
		{
			skilllines[i] = fields[1+i].GetUInt32();
			skill = sSkillLineStore.LookupEntry(skilllines[i]);
			if(!skill)
			{
				skilllines[i] = 0;
				continue;
			}
			if(skill->type == SKILL_TYPE_PROFESSION ||
				skill->type == SKILL_TYPE_SECONDARY)
			{
				tr->TrainerType = 2;
			}
		}
		maxlevel = fields[21].GetUInt32();
		class_ = fields[22].GetUInt32();

		vector<TrainerSpell*> tmp;
		tmp.reserve(400);
		for(uint32 i = 0; i < 20; ++i)
		{
			if(skilllines[i] != 0)
			{
				//TODO: Check for pet trainer!
				TrainerSpellMap::iterator iter = mNormalSpells.find(skilllines[i]);
				if(iter == mNormalSpells.end())
				{
					// Not found.
					//printf("WARNING: No spells found under skill line %u\n", skilllines[i]);
					continue;
				}

				for(vector<TrainerSpell*>::iterator it = iter->second.begin();
					it != iter->second.end(); ++it)
				{
					if((*it)->pSpell->spellLevel <= maxlevel || maxlevel == 60)	// 60 trainers have all?
					{
						skill = sSkillLineStore.LookupEntry(skilllines[i]);
						if(skill->type == SKILL_TYPE_PROFESSION || skill->type == SKILL_TYPE_SECONDARY)
						{
							if(skill->type == SKILL_TYPE_SECONDARY)
							{
								if(skill->id == 185 || skill->id == 129 || skill->id == 356)
								{
									bool add = AddTrainerSpell(entry, (*it)->pSpell);
									if(add)
										tmp.push_back((*it));
								}
								else
								{
									tmp.push_back((*it));
								}
							}
							else
							{
								bool add = AddTrainerSpell(entry, (*it)->pSpell);
								if(add)
									tmp.push_back((*it));
							}
						}
						else
							tmp.push_back((*it));
					}						
				}
			}
		}
		tr->SpellCount = tmp.size();
		tr->SpellList = new TrainerSpell*[tmp.size()];

		uint32 j = 0;
		for(vector<TrainerSpell*>::iterator it = tmp.begin();
			it != tmp.end(); ++it, j++)
		{
			tr->SpellList[j] = (*it);
		}
		
		const char * temp = fields[23].GetString();
		tr->TalkMessage = new char[strlen(temp)+1];
		strcpy(tr->TalkMessage, temp);
		tr->TalkMessage[strlen(temp)] = 0;

		tr->RequiredClass = class_;
		//assert(mTrainers.find(entry) == mTrainers.end());
		if(mTrainers.find(entry) != mTrainers.end())
		{
			delete [] tr->TalkMessage;
			delete [] tr->SpellList;
			delete tr;
			continue;
		}
		mTrainers.insert( TrainerMap::value_type( entry, tr ) );
		
	} while(result->NextRow());
	delete result;
}

bool ObjectMgr::AddTrainerSpell(uint32 entry, SpellEntry *pSpell)
{
	CreatureInfo *ci = CreatureNameStorage.LookupEntry(entry);
	if(ci)
	{
		const char* RankName = sSpellStore.LookupString(pSpell->Rank);
		if(strstr(ci->SubName,"Journeyman"))
		{
			if(!stricmp(RankName, "Journeyman"))
				return true;
			else if(!stricmp(RankName, "Expert"))
				return false;
			else if(!stricmp(RankName, "Artisan"))
				return false;
			else if(!stricmp(RankName, "Master"))
				return false;
			else
				return true;
		}
		else if(strstr(ci->SubName,"Expert"))
		{
			if(!stricmp(RankName, "Journeyman"))
				return true;
			else if(!stricmp(RankName, "Expert"))
				return true;
			else if(!stricmp(RankName, "Artisan"))
				return false;
			else if(!stricmp(RankName, "Master"))
				return false;
			else
				return true;
		}
		else if(strstr(ci->SubName,"Artisan"))
		{
			if(!stricmp(RankName, "Journeyman"))
				return true;
			else if(!stricmp(RankName, "Expert"))
				return true;
			else if(!stricmp(RankName, "Artisan"))
				return true;
			else if(!stricmp(RankName, "Master"))
				return false;
			else
				return true;
		}
		else
			return true;
	}
	else
		return false;
}

Trainer* ObjectMgr::GetTrainer(uint32 Entry)
{
	TrainerMap::iterator iter = mTrainers.find(Entry);
	if(iter == mTrainers.end())
		return NULL;

	return iter->second;
}

void ObjectMgr::GenerateLevelUpInfo()
{
	// Generate levelup information for each class.
	PlayerCreateInfo * PCI;
	for(uint32 Class = WARRIOR; Class <= DRUID; ++Class)
	{
		// These are empty.
		if(Class == 10 || Class == 6)
			continue;

		// Search for a playercreateinfo.
		for(uint32 Race = RACE_HUMAN; Race <= RACE_DRAENEI; ++Race )
		{
			PCI = GetPlayerCreateInfo(Race, Class);

			if(PCI == 0)
				continue;   // Class not valid for this race.

			// Generate each level's information
			uint32 MaxLevel = sWorld.Expansion1LevelCap + 1;
			LevelInfo* lvl=0, lastlvl;
			lastlvl.HP = PCI->health;
			lastlvl.Mana = PCI->mana;
			lastlvl.Stat[0] = PCI->strength;
			lastlvl.Stat[1] = PCI->ability;
			lastlvl.Stat[2] = PCI->stamina;
			lastlvl.Stat[3] = PCI->intellect;
			lastlvl.Stat[4] = PCI->spirit;
			lastlvl.XPToNextLevel = 400;
			LevelMap * lMap = new LevelMap;

			// Create first level.
			lvl = new LevelInfo;
			*lvl = lastlvl;

			// Insert into map
			lMap->insert( LevelMap::value_type( 1, lvl ) );

			uint32 val;
			for(uint32 Level = 2; Level < MaxLevel; ++Level)
			{
				lvl = new LevelInfo;

				// Calculate Stats
				for(uint32 s = 0; s < 5; ++s)
				{
					val = GainStat(Level, Class, s);
					lvl->Stat[s] = lastlvl.Stat[s] + val;
				}

				// Calculate HP/Mana
				uint32 TotalHealthGain = 0;
				uint32 TotalManaGain = 0;

				switch(Class)
				{
				case WARRIOR:
					if(Level<13)TotalHealthGain+=19;
					else if(Level <36) TotalHealthGain+=Level+6;
//					else if(Level >60) TotalHealthGain+=Level+100;
					else if(Level >60) TotalHealthGain+=Level+206;
					else TotalHealthGain+=2*Level-30;
					break;
				case HUNTER:
					if(Level<13)TotalHealthGain+=17;
//					else if(Level >60) TotalHealthGain+=Level+45;
					else if(Level >60) TotalHealthGain+=Level+161;
					else TotalHealthGain+=Level+4;

					if(Level<11)TotalManaGain+=29;
					else if(Level<27)TotalManaGain+=Level+18;
//					else if(Level>60)TotalManaGain+=Level+20;
					else if(Level>60)TotalManaGain+=Level+150;
					else TotalManaGain+=45;
					break;
				case ROGUE:
					if(Level <15)TotalHealthGain+=17;
//					else if(Level >60) TotalHealthGain+=Level+110;
					else if(Level >60) TotalHealthGain+=Level+191;
					else TotalHealthGain+=Level+2;
					break;
				case DRUID:
					if(Level < 17)TotalHealthGain+=17;
//					else if(Level >60) TotalHealthGain+=Level+55;
					else if(Level >60) TotalHealthGain+=Level+176;
					else TotalHealthGain+=Level;

					if(Level < 26)TotalManaGain+=Level+20;
//					else if(Level>60)TotalManaGain+=Level+25;
					else if(Level>60)TotalManaGain+=Level+150;
					else TotalManaGain+=45;
					break;
				case MAGE:
					if(Level < 23)TotalHealthGain+=15;
//					else if(Level >60) TotalHealthGain+=Level+40;
					else if(Level >60) TotalHealthGain+=Level+190;
					else TotalHealthGain+=Level-8;

					if(Level <28)TotalManaGain+=Level+23;
//					else if(Level>60)TotalManaGain+=Level+26;
					else if(Level>60)TotalManaGain+=Level+115;
					else TotalManaGain+=51;
					break;
				case SHAMAN:
					if(Level <16)TotalHealthGain+=17;
//					else if(Level >60) TotalHealthGain+=Level+75;
					else if(Level >60) TotalHealthGain+=Level+157;
					else TotalHealthGain+=Level+1;

					if(Level<22)TotalManaGain+=Level+19;
//					else if(Level>60)TotalManaGain+=Level+70;
					else if(Level>60)TotalManaGain+=Level+175;
					else TotalManaGain+=49;
					break;
				case WARLOCK:
					if(Level <17)TotalHealthGain+=17;
//					else if(Level >60) TotalHealthGain+=Level+50;
					else if(Level >60) TotalHealthGain+=Level+192;
					else TotalHealthGain+=Level-2;

					if(Level< 30)TotalManaGain+=Level+21;
//					else if(Level>60)TotalManaGain+=Level+25;
					else if(Level>60)TotalManaGain+=Level+121;
					else TotalManaGain+=51;
					break;
				case PALADIN:
					if(Level < 14)TotalHealthGain+=18;
//					else if(Level >60) TotalHealthGain+=Level+55;
					else if(Level >60) TotalHealthGain+=Level+167;
					else TotalHealthGain+=Level+4;

					if(Level<30)TotalManaGain+=Level+17;
//					else if(Level>60)TotalManaGain+=Level+100;
					else if(Level>60)TotalManaGain+=Level+131;
					else TotalManaGain+=42;
					break;
				case PRIEST:
					if(Level <21)TotalHealthGain+=15;
//					else if(Level >60) TotalHealthGain+=Level+40;
					else if(Level >60) TotalHealthGain+=Level+157;
					else TotalHealthGain+=Level-6;

					if(Level <22)TotalManaGain+=Level+22;
					else if(Level <32)TotalManaGain+=Level+37;
//					else if(Level>60)TotalManaGain+=Level+35;
					else if(Level>60)TotalManaGain+=Level+207;
					else TotalManaGain+=54;
					break;
				}

				// Apply HP/Mana
				lvl->HP = lastlvl.HP + TotalHealthGain;
				lvl->Mana = lastlvl.Mana + TotalManaGain;

				// Calculate next level XP
				uint32 nextLvlXP = 0;
				if( Level > 0 && Level <= 30 )
				{
					nextLvlXP = ((int)((((double)(8 * Level * ((Level * 5) + 45)))/100)+0.5))*100;
				}
				else if( Level == 31 )
				{
					nextLvlXP = ((int)((((double)(((8 * Level) + 3) * ((Level * 5) + 45)))/100)+0.5))*100;
				}
				else if( Level == 32 )
				{
					nextLvlXP = ((int)((((double)(((8 * Level) + 6) * ((Level * 5) + 45)))/100)+0.5))*100;
				}
				else
				{
					nextLvlXP = ((int)((((double)(((8 * Level) + ((Level - 30) * 5)) * ((Level * 5) + 45)))/100)+0.5))*100;
				}

				lvl->XPToNextLevel = nextLvlXP;
				lastlvl = *lvl;
				lastlvl.HP = lastlvl.HP;

				// Apply to map.
				lMap->insert( LevelMap::value_type( Level, lvl ) );
			}

			// Now that our level map is full, let's create the class/race pair
			pair<uint32, uint32> p;
			p.first = Race;
			p.second = Class;

			// Insert back into the main map.
			mLevelInfo.insert( LevelInfoMap::value_type( p, lMap ) );
		}
	}
}

LevelInfo* ObjectMgr::GetLevelInfo(uint32 Race, uint32 Class, uint32 Level)
{
	// Iterate levelinfo map until we find the right class+race.
	LevelInfoMap::iterator itr = mLevelInfo.begin();
	for(; itr != mLevelInfo.end(); ++itr)
	{
		if(itr->first.first == Race &&
			itr->first.second == Class)
		{
			// We got a match.
			// Let's check that our level is valid first.
			if(Level > sWorld.Expansion1LevelCap) // too far.
				Level = sWorld.Expansion1LevelCap;

			// Pull the level information from the second map.
			LevelMap::iterator it2 = itr->second->find(Level);
			ASSERT(it2 != itr->second->end());

			return it2->second;
		}
	}

	return NULL;
}

void ObjectMgr::LoadDefaultPetSpells()
{
	QueryResult * result = WorldDatabase.Query("SELECT * FROM petdefaultspells");
	if(result)
	{
		do 
		{
			Field * f = result->Fetch();
			uint32 Entry = f[0].GetUInt32();
			uint32 spell = f[1].GetUInt32();
			SpellEntry * sp = sSpellStore.LookupEntry(spell);

			if(spell && Entry && sp)
			{
				PetDefaultSpellMap::iterator itr = mDefaultPetSpells.find(Entry);
				if(itr != mDefaultPetSpells.end())
					itr->second.insert(sp);
				else
				{
					set<SpellEntry*> s;
					s.insert(sp);
					mDefaultPetSpells[Entry] = s;
				}
			}
		} while(result->NextRow());

		delete result;
	}
}

set<SpellEntry*>* ObjectMgr::GetDefaultPetSpells(uint32 Entry)
{
	PetDefaultSpellMap::iterator itr = mDefaultPetSpells.find(Entry);
	if(itr == mDefaultPetSpells.end())
		return 0;

	return &(itr->second);
}

void ObjectMgr::LoadPetSpellCooldowns()
{
	DBCFile dbc;
	dbc.open("DBC/CreatureSpellData.dbc");
	uint32 SpellId;
	uint32 Cooldown;
	for(uint32 i = 0; i < dbc.getRecordCount(); ++i)
	{
		for(uint32 j = 0; j < 3; ++j)
		{
			SpellId = dbc.getRecord(i).getUInt(1 + j);
			Cooldown = dbc.getRecord(i).getUInt(5 + j);
			Cooldown *= 10;
			if(SpellId)
			{
				PetSpellCooldownMap::iterator itr = mPetSpellCooldowns.find(SpellId);
				if(itr == mPetSpellCooldowns.end())
				{
					mPetSpellCooldowns.insert( make_pair(SpellId, Cooldown) );
				}
				else
				{
					uint32 SP2 = mPetSpellCooldowns[SpellId];
					ASSERT(Cooldown == SP2);
				}
			}
		}
	}
}

uint32 ObjectMgr::GetPetSpellCooldown(uint32 SpellId)
{
	PetSpellCooldownMap::iterator itr = mPetSpellCooldowns.find(SpellId);
	if(itr != mPetSpellCooldowns.end())
		return itr->second;
	return 0;
}

void ObjectMgr::LoadSpellFixes()
{
	// Loads data from stored 1.12 dbc to fix spells that have had spell data removed in 2.0.
	sLog.outString("  Loading Spell Fixes...");
	QueryResult * result = WorldDatabase.Query("SELECT * FROM spells112");
	if(result == 0) return;

//	uint32 count = result->GetRowCount();
//	uint32 counter = 0;
	uint32 fixed_count = 0;
	uint32 proc_chance;
	do 
	{
		Field * fields = result->Fetch();
		uint32 entry = fields[0].GetUInt32();
		SpellEntry * sp = sSpellStore.LookupEntry(entry);
		if(sp == 0) continue;

		// FIX SPELL GROUP RELATIONS
		{
			uint32 sgr[3];
			sgr[0] = fields[103].GetUInt32();
			sgr[1] = fields[104].GetUInt32();
			sgr[2] = fields[105].GetUInt32();
			proc_chance = fields[25].GetUInt32();

			for(uint32 i = 0; i < 3; ++i)
			{
				if(sgr[i] && sp->EffectSpellGroupRelation[i] == 0)
				{
					//string name = fields[120].GetString();
					//printf("%s[%u] %u->%u\n", name.c_str(),i, sp->EffectSpellGroupRelation[i], sgr[i]);
					sp->EffectSpellGroupRelation[i] = sgr[i];
					++fixed_count;
				}
			}

			sp->procChance = min(proc_chance, sp->procChance);			
		}

		// FIX OTHER STUFF.. we'll find out..

	} while(result->NextRow());
	delete result;
}

void ObjectMgr::LoadSpellOverride()
{
	sLog.outString("  Loading Spell Override...");
//	int i = 0;
	std::stringstream query;
	QueryResult *result = WorldDatabase.Query( "SELECT DISTINCT overrideId FROM spelloverride" );

	if(!result)
	{
		sLog.outString("Query failed: SELECT distinct overrideId FROM spelloverride");
		return;
	}

//	int num = 0;
//	uint32 total =(uint32) result->GetRowCount();
	SpellEntry * sp;
	uint32 spellid;

	do
	{
		Field *fields = result->Fetch();
		query.rdbuf()->str("");
		query << "SELECT spellId FROM spelloverride WHERE overrideId = ";
		query << fields[0].GetUInt32();
		QueryResult *resultIn = WorldDatabase.Query(query.str().c_str());
		std::list<SpellEntry*>* list = new std::list<SpellEntry*>;
		if(resultIn)
		{
			do
			{
				Field *fieldsIn = resultIn->Fetch();
				spellid = fieldsIn[0].GetUInt32();
				sp = sSpellStore.LookupEntry(spellid);
				if(!spellid || !sp) 
					continue;
				list->push_back(sp);
			}while(resultIn->NextRow());
		}
		delete resultIn;
		if(list->size() == 0)
			delete list;
		else
			mOverrideIdMap.insert( OverrideIdMap::value_type( fields[0].GetUInt32(), list ));
	} while( result->NextRow() );
	delete result;
}

void ObjectMgr::SetVendorList(uint32 Entry, std::vector<CreatureItem>* list_)
{
	mVendors[Entry] = list_;
}

Creature * ObjectMgr::GetCreatureBySqlId(uint32 Sql_Id)
{
	CreatureSqlIdMapMutex.Acquire();
	Creature * c;
	CreatureSqlIdMap::iterator itr = mCreatureSqlIds.find(Sql_Id);
	c = (itr == mCreatureSqlIds.end()) ? 0 : itr->second;
	CreatureSqlIdMapMutex.Release();
	return c;
}

void ObjectMgr::SetCreatureBySqlId(uint32 Sql_Id, Creature * pCreature)
{
	CreatureSqlIdMapMutex.Acquire();

	if(pCreature != 0)
		mCreatureSqlIds[Sql_Id] = pCreature;
	else
	{
		CreatureSqlIdMap::iterator itr = mCreatureSqlIds.find(Sql_Id);
		if(itr != mCreatureSqlIds.end())
			mCreatureSqlIds.erase(itr);
	}
	CreatureSqlIdMapMutex.Release();
}

void ObjectMgr::LoadCreatureWaypoints()
{
	QueryResult *result = WorldDatabase.Query("SELECT * FROM creature_waypoints");
	if(!result)return;

	do
	{
		Field *fields = result->Fetch();
		WayPoint* wp = new WayPoint;
		wp->id = fields[1].GetUInt32();
		wp->x = fields[2].GetFloat();
		wp->y = fields[3].GetFloat();
		wp->z = fields[4].GetFloat();
		wp->waittime = fields[5].GetUInt32();
		wp->flags = fields[6].GetUInt32();
		wp->forwardemoteoneshot = fields[7].GetBool();
		wp->forwardemoteid = fields[8].GetUInt32();
		wp->backwardemoteoneshot = fields[9].GetBool();
		wp->backwardemoteid = fields[10].GetUInt32();
		wp->forwardskinid = fields[11].GetUInt32();
		wp->backwardskinid = fields[12].GetUInt32();

		UNORDERED_MAP<uint32,WayPointMap*>::const_iterator i;
		uint32 spawnid=fields[0].GetUInt32();
		i=m_waypoints.find(spawnid);
		if(i==m_waypoints.end())
		{
			WayPointMap* m=new WayPointMap;
			(*m)[wp->id]=wp;
			m_waypoints[spawnid]=m;		
		}else
			(*(i->second))[wp->id]=wp;
	}while( result->NextRow() );

	delete result;
}

WayPointMap*ObjectMgr::GetWayPointMap(uint32 spawnid)
{
	UNORDERED_MAP<uint32,WayPointMap*>::const_iterator i;
	i=m_waypoints.find(spawnid);
	if(i!=m_waypoints.end())
	{
		WayPointMap * m=i->second;
		// we don't wanna erase from the map, becuase some are used more
		// than once (for instances)

		//m_waypoints.erase(i);
		return m;
	}
	else return NULL;
}

Pet * ObjectMgr::CreatePet()
{
	uint32 guid;
	m_petlock.Acquire();
	guid =++m_hiPetGuid;
	m_petlock.Release();
	return new Pet(HIGHGUID_PET,guid);
}

Player * ObjectMgr::CreatePlayer()
{
	uint32 guid;
	m_playerguidlock.Acquire();
	guid =++m_hiPlayerGuid;
	m_playerguidlock.Release();
	return new Player(HIGHGUID_PLAYER,guid);
}

void ObjectMgr::AddPlayer(Player * p)//add it to global storage
{
	_playerslock.AcquireWriteLock();
	_players[p->GetGUIDLow()] = p;
	_playerslock.ReleaseWriteLock();
}

void ObjectMgr::RemovePlayer(Player * p)
{
	_playerslock.AcquireWriteLock();
	_players.erase(p->GetGUIDLow());
	_playerslock.ReleaseWriteLock();

}

Corpse * ObjectMgr::CreateCorpse()
{
	uint32 guid;
	m_corpseguidlock.Acquire();
	guid =++m_hiCorpseGuid;
	m_corpseguidlock.Release();
	return new Corpse(HIGHGUID_CORPSE,guid);
}

void ObjectMgr::AddCorpse(Corpse * p)//add it to global storage
{
	_corpseslock.Acquire();
	m_corpses[p->GetGUIDLow()]=p;
	_corpseslock.Release();
}

void ObjectMgr::RemoveCorpse(Corpse * p)
{
	_corpseslock.Acquire();
	m_corpses.erase(p->GetGUIDLow());
	_corpseslock.Release();
}

Corpse * ObjectMgr::GetCorpse(uint32 corpseguid)
{
	Corpse * rv;
	_corpseslock.Acquire();
	UNORDERED_MAP<uint32, Corpse*>::const_iterator itr = m_corpses.find(corpseguid);
	rv = (itr != m_corpses.end()) ? itr->second : 0;
	_corpseslock.Release();
	return rv;
}

Transporter * ObjectMgr::GetTransporter(uint32 guid)
{
	if(guid > TransportersCount)
		return 0;

	return m_transporters[guid];
}

Transporter * ObjectMgr::GetTransporterByEntry(uint32 entry)
{
	for(uint32 i = 1; i <= TransportersCount; ++i)
		if(m_transporters[i] && m_transporters[i]->GetEntry() == entry)
			return m_transporters[i];
	
	return 0;
}

void ObjectMgr::LoadGuildCharters()
{
	m_hiCharterId = 0;
	QueryResult * result = CharacterDatabase.Query("SELECT * FROM charters");
	if(!result) return;
	do 
	{
		Charter * c = new Charter(result->Fetch());
		m_charters[c->GetID()] = c;
		if(c->GetID() > m_hiCharterId)
			m_hiCharterId = c->GetID();
	} while(result->NextRow());
	delete result;
}

Charter * ObjectMgr::GetCharter(uint32 CharterId)
{
	Charter * rv;
	UNORDERED_MAP<uint32,Charter*>::iterator itr;
	m_charterLock.AcquireReadLock();
	itr = m_charters.find(CharterId);
	rv = (itr == m_charters.end()) ? 0 : itr->second;
	m_charterLock.ReleaseReadLock();
	return rv;
}

Charter * ObjectMgr::CreateCharter(uint32 LeaderGuid)
{
	m_charterLock.AcquireWriteLock();
	Charter * c = new Charter(++m_hiCharterId, LeaderGuid);
	m_charters[c->GetID()] = c;
	c->LeaderGuid = LeaderGuid;
	m_charterLock.ReleaseWriteLock();
	return c;
}

Charter::Charter(Field * fields)
{
	uint32 f = 0;
	CharterId = fields[f++].GetUInt32();
	LeaderGuid = fields[f++].GetUInt32();
	GuildName = fields[f++].GetString();
	ItemGuid = fields[f++].GetUInt64();
	SignatureCount = 0;

	for(uint32 i = 0; i < 9; ++i)
	{
		Signatures[i] = fields[f++].GetUInt32();
		if(Signatures[i])
			++SignatureCount;
	}
}

void Charter::AddSignature(uint32 PlayerGuid)
{
	if(SignatureCount >= 9)
		return;

	SignatureCount++;
	uint32 i;
	for(i = 0; i < 9; ++i)
	{
		if(Signatures[i] == 0)
		{
			Signatures[i] = PlayerGuid;
			break;
		}
	}

	assert(i != 9);
}

void Charter::RemoveSignature(uint32 PlayerGuid)
{
	for(uint32 i = 0; i < 9; ++i)
	{
		if(Signatures[i] == PlayerGuid)
		{
			Signatures[i] = 0;
			SignatureCount--;
			SaveToDB();
			break;
		}
	}
}


void Charter::Destroy()
{
	//meh remove from objmgr
	objmgr.RemoveCharter(this);
	// Kill the players with this (in db/offline)
	CharacterDatabase.Execute("UPDATE characters SET charterId = 0 WHERE charterId = %u", CharterId);
	CharacterDatabase.Execute("DELETE FROM charters WHERE charterId = %u", CharterId);
	Player * p;
	for(uint32 i = 0; i < 9; ++i)
	{
		if(!Signatures[i])
			continue;
		p =  objmgr.GetPlayer(Signatures[i]) ;
		if(p)
			p->m_charter = 0;
	}

	// click, click, boom!
	delete this;
}

void Charter::SaveToDB()
{
	CharacterDatabase.Execute(
		"REPLACE INTO charters VALUES(%u,%u,'%s'," I64FMTD ",%u,%u,%u,%u,%u,%u,%u,%u,%u)",
		CharterId,LeaderGuid,GuildName.c_str(),ItemGuid,Signatures[0],Signatures[1],
		Signatures[2],Signatures[3],Signatures[4],Signatures[5],
		Signatures[6],Signatures[7],Signatures[8]);

}

Charter * ObjectMgr::GetCharterByItemGuid(uint64 guid)
{
	Charter * rv = 0;
	m_charterLock.AcquireReadLock();
	UNORDERED_MAP<uint32, Charter*>::iterator itr = m_charters.begin();
	for(; itr != m_charters.end(); ++itr)
	{
		if(itr->second->ItemGuid == guid)
		{
			rv = itr->second;
			break;
		}
	}
	m_charterLock.ReleaseReadLock();
	return rv;
}


Charter * ObjectMgr::GetCharterByName(string &charter_name)
{
	Charter * rv = 0;
	m_charterLock.AcquireReadLock();
	UNORDERED_MAP<uint32, Charter*>::iterator itr = m_charters.begin();
	for(; itr != m_charters.end(); ++itr)
	{
		if(itr->second->GuildName == charter_name)
		{
			rv = itr->second;
			break;
		}
	}

	m_charterLock.ReleaseReadLock();
	return rv;
}

void ObjectMgr::RemoveCharter(Charter * c)
{
	m_charterLock.AcquireWriteLock();
	m_charters.erase(c->CharterId);
	m_charterLock.ReleaseWriteLock();
}

void ObjectMgr::LoadReputationModifierTable(const char * tablename, UNORDERED_MAP<uint32, ReputationModifier*> * dmap)
{
	QueryResult * result = WorldDatabase.Query("SELECT * FROM %s", tablename);
	UNORDERED_MAP<uint32, ReputationModifier*>::iterator itr;
	ReputationModifier * modifier;
	ReputationMod mod;

	if(result)
	{
		do 
		{
			mod.faction[0] = result->Fetch()[1].GetUInt32();
			mod.faction[1] = result->Fetch()[2].GetUInt32();
			mod.value = result->Fetch()[3].GetInt32();
			mod.replimit = result->Fetch()[4].GetUInt32();

			itr = dmap->find(result->Fetch()[0].GetUInt32());
			if(itr == dmap->end())
			{
				modifier = new ReputationModifier;
				modifier->entry = result->Fetch()[0].GetUInt32();
				modifier->mods.push_back(mod);
				dmap->insert( UNORDERED_MAP<uint32, ReputationModifier*>::value_type( result->Fetch()[0].GetUInt32(), modifier ) );
			}
			else
			{
				itr->second->mods.push_back(mod);
			}
		} while(result->NextRow());
		delete result;
	}
}

void ObjectMgr::LoadReputationModifiers()
{
	LoadReputationModifierTable("reputation_creature_onkill", &m_reputation_creature);
	LoadReputationModifierTable("reputation_faction_onkill", &m_reputation_faction);
	LoadInstanceReputationModifiers();
}

ReputationModifier * ObjectMgr::GetReputationModifier(uint32 entry_id, uint32 faction_id)
{
	// first, try fetching from the creature table (by faction is a fallback)
	UNORDERED_MAP<uint32, ReputationModifier*>::iterator itr = m_reputation_creature.find(entry_id);
	if(itr != m_reputation_creature.end())
		return itr->second;

	// fetch from the faction table
	itr = m_reputation_faction.find(faction_id);
	if(itr != m_reputation_faction.end())
		return itr->second;

	// no data. fallback to default -5 value.
	return 0;
}

void ObjectMgr::LoadMonsterSay()
{
	QueryResult * result = WorldDatabase.Query("SELECT * FROM npc_monstersay");
	if(!result) return;

	uint32 Entry, Event;
	Field * fields = result->Fetch();
	do 
	{
		Entry = fields[0].GetUInt32();
		Event = fields[1].GetUInt32();

		if(Event >= NUM_MONSTER_SAY_EVENTS)
			continue;

		NpcMonsterSay * ms = new NpcMonsterSay;
		ms->Chance = fields[2].GetFloat();
		ms->Language = fields[3].GetUInt32();
		ms->Type = fields[4].GetUInt32();
		ms->MonsterName = fields[5].GetString() ? strdup(fields[5].GetString()) : "None";

		char * texts[5];
		char * text;
		uint32 textcount = 0;

		for(uint32 i = 0; i < 5; ++i)
		{
			text = (char*)fields[6+i].GetString();
			if(!text) continue;

			texts[textcount++] = strdup(fields[6+i].GetString());

			// check for ;
			if(texts[textcount-1][strlen(texts[textcount-1])-1] == ';')
				texts[textcount-1][strlen(texts[textcount-1])-1] = 0;
		}

		if(!textcount)
		{
			delete ms;
			continue;
		}

		ms->Texts = new const char*[textcount];
		memcpy(ms->Texts, texts, sizeof(char*) * textcount);
		ms->TextCount = textcount;

		mMonsterSays[Event].insert( make_pair( Entry, ms ) );

	} while(result->NextRow());
	delete result;
}

void ObjectMgr::HandleMonsterSayEvent(Creature * pCreature, MONSTER_SAY_EVENTS Event)
{
	MonsterSayMap::iterator itr = mMonsterSays[Event].find(pCreature->GetEntry());
	if(itr == mMonsterSays[Event].end())
		return;

	NpcMonsterSay * ms = itr->second;
	if(Rand(ms->Chance))
	{
		// chance successful.
		int choice = (ms->TextCount == 1) ? 0 : sRand.randInt(ms->TextCount - 1);
		const char * text = ms->Texts[choice];
		pCreature->SendChatMessage(ms->Type, ms->Language, text);
	}
}

bool ObjectMgr::HasMonsterSay(uint32 Entry, MONSTER_SAY_EVENTS Event)
{
	MonsterSayMap::iterator itr = mMonsterSays[Event].find(Entry);
	if(itr == mMonsterSays[Event].end())
		return false;

	return true;
}

void ObjectMgr::LoadInstanceReputationModifiers()
{
	QueryResult * result = WorldDatabase.Query("SELECT * FROM reputation_instance_onkill");
	if(!result) return;

	do 
	{
		Field * fields = result->Fetch();
		InstanceReputationMod mod;
		mod.mapid = fields[0].GetUInt32();
		mod.mob_rep_reward = fields[1].GetInt32();
		mod.mob_rep_limit = fields[2].GetUInt32();
		mod.boss_rep_reward = fields[3].GetInt32();
		mod.boss_rep_limit = fields[4].GetUInt32();
		mod.faction[0] = fields[5].GetUInt32();
		mod.faction[1] = fields[6].GetUInt32();

		UNORDERED_MAP<uint32, InstanceReputationModifier*>::iterator itr = m_reputation_instance.find(mod.mapid);
		if(itr == m_reputation_instance.end())
		{
			InstanceReputationModifier * m = new InstanceReputationModifier;
			m->mapid = mod.mapid;
			m->mods.push_back(mod);
			m_reputation_instance.insert( make_pair( m->mapid, m ) );
		}
		else
			itr->second->mods.push_back(mod);

	} while(result->NextRow());
	delete result;
}

bool ObjectMgr::HandleInstanceReputationModifiers(Player * pPlayer, Unit * pVictim)
{
	uint32 team = pPlayer->GetTeam();
	bool is_boss;
	if(pVictim->GetTypeId() != TYPEID_UNIT)
		return false;

	UNORDERED_MAP<uint32, InstanceReputationModifier*>::iterator itr = m_reputation_instance.find(pVictim->GetMapId());
	if(itr == m_reputation_instance.end())
		return false;

	is_boss = ((Creature*)pVictim)->GetCreatureName() ? ((Creature*)pVictim)->GetCreatureName()->Rank : 0;
	if(!is_boss && ((Creature*)pVictim)->proto && ((Creature*)pVictim)->proto->boss)
		is_boss = 1;

	// Apply the bonuses as normal.
	int32 replimit;
	int32 value;

	for(vector<InstanceReputationMod>::iterator i = itr->second->mods.begin(); i !=  itr->second->mods.end(); ++i)
	{
		if(!(*i).faction[team])
			continue;

		if(is_boss)
		{
			value = i->boss_rep_reward;
			replimit = i->boss_rep_limit;
		}
		else
		{
			value = i->mob_rep_reward;
			replimit = i->mob_rep_reward;
		}

		if(!value || (replimit && pPlayer->GetStanding(i->faction[team]) >= replimit))
			continue;

		//value *= sWorld.getRate(RATE_KILLREPUTATION);
		value = int32(float(value) * sWorld.getRate(RATE_KILLREPUTATION));
		pPlayer->ModStanding(i->faction[team], value);
	}

	return true;
}

void ObjectMgr::LoadDisabledSpells()
{
	QueryResult * result = WorldDatabase.Query("SELECT * FROM spell_disable");
	if(result)
	{
		do 
		{
			m_disabled_spells.insert( result->Fetch()[0].GetUInt32() );
		} while(result->NextRow());
		delete result;
	}

	result = WorldDatabase.Query("SELECT * FROM spell_disable_trainers");
	if(result)
	{
		do 
		{
			m_disabled_trainer_spells.insert( result->Fetch()[0].GetUInt32() );
		} while(result->NextRow());
		delete result;
	}
}
