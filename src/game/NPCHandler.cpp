/****************************************************************************
 *
 * General Packet Handler File
 *
 */

#include "StdAfx.h"

trainertype trainer_types[TRAINER_TYPE_MAX] = 
{
{	"Warrior",			   0 },
{	"Paladin",			   0 },
{	"Rogue"  ,			   0 },
{	"Warlock",			   0 },
{	"Mage",				  0 },
{	"Shaman",				0 },
{	"Priest",				0 },
{	"Hunter",				0 },
{	"Druid",				 0 },
{	"Leatherwork",		   2 },
{	"Skinning",			  2 },
{	"Fishing",			   2 },
{	"First Aid",			 2 },
{	"Physician",			 2 },
{	"Engineer",			  2 },
{	"Weapon Master",		 0 },
};

//////////////////////////////////////////////////////////////
/// This function handles MSG_TABARDVENDOR_ACTIVATE:
//////////////////////////////////////////////////////////////
void WorldSession::HandleTabardVendorActivateOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
	uint64 guid;
	recv_data >> guid;
	Creature *pCreature = _player->GetMapMgr()->GetCreature(guid);
	if(!pCreature) return;

	SendTabardHelp(pCreature);
}

void WorldSession::SendTabardHelp(Creature* pCreature)
{
	if(!_player->IsInWorld()) return;
	WorldPacket data;
	data.Initialize( MSG_TABARDVENDOR_ACTIVATE );
	data << pCreature->GetGUID();
	SendPacket( &data );
}


//////////////////////////////////////////////////////////////
/// This function handles CMSG_BANKER_ACTIVATE:
//////////////////////////////////////////////////////////////
void WorldSession::HandleBankerActivateOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
	uint64 guid;
	recv_data >> guid;

	Creature *pCreature = _player->GetMapMgr()->GetCreature(guid);
	if(!pCreature) return;

	SendBankerList(pCreature);
}

void WorldSession::SendBankerList(Creature* pCreature)
{
	if(!_player->IsInWorld()) return;
	WorldPacket data;
	data.Initialize( SMSG_SHOW_BANK );
	data << pCreature->GetGUID();
	SendPacket( &data );
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_TRAINER_LIST
//////////////////////////////////////////////////////////////
//NOTE: we select prerequirements for spell that TEACHES you
//not by spell that you learn!
void WorldSession::HandleTrainerListOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
	// Inits, grab creature, check.
	uint64 guid;
	recv_data >> guid;
	Creature *train = GetPlayer()->GetMapMgr()->GetCreature(guid);
	if(!train) return;

	SendTrainerList(train);
}

void WorldSession::SendTrainerList(Creature* pCreature)
{
	Trainer * pTrainer = objmgr.GetTrainer(pCreature->GetEntry());
	if(pTrainer == 0) return;

	WorldPacket data(SMSG_TRAINER_LIST, 5000);
	
	data << pCreature->GetGUID();
	data << pTrainer->TrainerType;
	data << pTrainer->SpellCount;

	TrainerSpell * pSpell;
	uint32 Spacer = 0;
	uint32 * SpellCount = (uint32*)&data.contents()[12];
	uint8 Status;
	int32 RequiredLevel;

	for(uint32 i = 0; i < pTrainer->SpellCount; ++i)
	{
		// We need the info for the teaching spell ;)
		pSpell = pTrainer->SpellList[i];
		RequiredLevel = pSpell->RequiredLevel;

		if(pSpell->RequiredClass != -1)
		{
			// Check class
			if(!(_player->getClassMask() & pSpell->RequiredClass))
			{
				// Hide this spell.
				*SpellCount--;
				continue;
			}
		}

		//Dual Wield
		if(pSpell->SpellID == 674 || pSpell->SpellID == 29651)
		{
			switch(_player->getClass())
			{
			case WARRIOR:
			case HUNTER:
				RequiredLevel = 20;
				break;
			case ROGUE:
				RequiredLevel = 10;
				break;
			default:
				RequiredLevel = -1;
			}
		}

		Status = TrainerGetSpellStatus(pSpell);

		// HACKFIX: dont show already known spells
		if((Status == TRAINER_STATUS_ALREADY_HAVE && _player->getClass() == PALADIN) || RequiredLevel < 0)
		{
			*SpellCount--;
			continue;
		}

		data << pSpell->TeachingSpellID;
		data << Status;		
		data << pSpell->Cost;
		data << Spacer;
		data << pSpell->IsProfession;
		data << (uint8)pSpell->RequiredLevel;

		data << pSpell->RequiredSkillLine;
		data << pSpell->RequiredSkillLineValue;
		data << pSpell->RequiredSpell;

		data << Spacer << Spacer;
	}

	string Text = pTrainer->TalkMessage;
	data << Text;

	SendPacket(&data);
}

void WorldSession::HandleTrainerBuySpellOpcode(WorldPacket& recvPacket)
{
	if(!_player->IsInWorld()) return;
	uint64 Guid;
	uint32 TeachingSpellID;

	recvPacket >> Guid >> TeachingSpellID;
	Creature *pCreature = _player->GetMapMgr()->GetCreature(Guid);
	if(pCreature == 0) return;

	Trainer *pTrainer = objmgr.GetTrainer(pCreature->GetEntry());
	if(pTrainer == 0) return;

	// Find teaching spell index.
	uint32 i;
	for(i = 0; i < pTrainer->SpellCount; ++i)
	{
		if(pTrainer->SpellList[i]->TeachingSpellID == TeachingSpellID)
			break;
	}

	if(i == pTrainer->SpellCount) return;
	TrainerSpell *pSpell = pTrainer->SpellList[i];

	if(TrainerGetSpellStatus(pSpell) > 0) return;
	
	_player->ModUInt32Value(PLAYER_FIELD_COINAGE, -(int32)pSpell->Cost);
	if(pSpell->DeleteSpell)
	{
		// Remove old spell.
		_player->removeSpell(pSpell->DeleteSpell, true, true, pSpell->DeleteSpell);
	}

	// Cast teaching spell on player
	pCreature->CastSpell(_player, pSpell->TeachingSpellID, true);
}


uint8 WorldSession::TrainerGetSpellStatus(TrainerSpell* pSpell)
{
	// check player's lavel
	if(pSpell->RequiredLevel && _player->getLevel() < pSpell->RequiredLevel)
		return TRAINER_STATUS_NOT_LEARNABLE;

	// check if we need a skill line
	if(pSpell->RequiredSkillLine && !_player->HasSkillLine( pSpell->RequiredSkillLine ) )
		return TRAINER_STATUS_NOT_LEARNABLE;

	// check if we have the required value
	if(pSpell->RequiredSkillLineValue && pSpell->RequiredSkillLine &&
		_player->GetBaseSkillAmt( pSpell->RequiredSkillLine ) < pSpell->RequiredSkillLineValue )
		return TRAINER_STATUS_NOT_LEARNABLE;

	// check if we already have this spell
	if(_player->HasSpell( pSpell->SpellID ) || _player->HasDeletedSpell(pSpell->SpellID) )	// Check deleted here too.)
		return TRAINER_STATUS_ALREADY_HAVE;

	// check if we have a required spell
	if(pSpell->RequiredSpell && !_player->HasSpell( pSpell->RequiredSpell))
		return TRAINER_STATUS_NOT_LEARNABLE;

	// check if we have the $$$
	if(pSpell->Cost && _player->GetUInt32Value(PLAYER_FIELD_COINAGE) < pSpell->Cost)
		return TRAINER_STATUS_NOT_LEARNABLE;

	// see if we passed the profession limit
	if(pSpell->IsProfession && !_player->HasSkillLine(pSpell->RequiredSkillLine) && pSpell->TeachingLine && _player->GetUInt32Value(PLAYER_CHARACTER_POINTS2) == 0)
		return TRAINER_STATUS_NOT_LEARNABLE;

	return TRAINER_STATUS_LEARNABLE;
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_PETITION_SHOWLIST:
//////////////////////////////////////////////////////////////
void WorldSession::HandleCharterShowListOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
	uint64 guid;
	recv_data >> guid;

	Creature *pCreature = _player->GetMapMgr()->GetCreature(guid);
	if(!pCreature) return;

	SendCharterRequest(pCreature);
}

void WorldSession::SendCharterRequest(Creature* pCreature)
{
	if(!_player->IsInWorld()) return;
	WorldPacket data;
	data.Initialize( SMSG_PETITION_SHOWLIST );
	data << pCreature->GetGUID();
	data << uint8(1);		   // BOOL SHOW_COST = 1
	data << uint32(1);		  // unknown
	data << uint16(0x16E7);	 // ItemId of the guild charter
	data << float(0.62890625);  // strange floating point
	data << uint16(0);		  // unknown
//	data << uint32(0x3F21);	 // unknown

	data << uint32(1000);	   // charter prise
	data << uint32(0);		  // unknown, maybe charter type
	data << uint32(9);		  // amount of unique players needed to sign the charter
	SendPacket( &data );
}

//////////////////////////////////////////////////////////////
/// This function handles MSG_AUCTION_HELLO:
//////////////////////////////////////////////////////////////
void WorldSession::HandleAuctionHelloOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
	uint64 guid;
	recv_data >> guid;
	Creature* auctioneer = _player->GetMapMgr()->GetCreature(guid);
	if(!auctioneer)
		return;

	SendAuctionList(auctioneer);
}

void WorldSession::SendAuctionList(Creature* auctioneer)
{
	AuctionHouse* AH = sAuctionMgr.GetAuctionHouse(auctioneer->GetEntry());
	if(!AH)
	{
		sChatHandler.BlueSystemMessage(this, "Report to devs: Unbound auction house npc %u.", auctioneer->GetEntry());
		return;
	}

	WorldPacket data(MSG_AUCTION_HELLO, 12);
	data << auctioneer->GetGUID();
	data << uint32(AH->GetID());

	SendPacket( &data );
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_GOSSIP_HELLO:
//////////////////////////////////////////////////////////////
void WorldSession::HandleGossipHelloOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
	uint64 guid;
	list<QuestRelation *>::iterator it;
	std::set<uint32> ql;

	recv_data >> guid;
	Creature *qst_giver = _player->GetMapMgr()->GetCreature(guid);
	if(!qst_giver) 
		return;

	//stop when talked to for 3 min
	if(qst_giver->GetAIInterface())
		qst_giver->GetAIInterface()->StopMovement(180000);

	// reputation
	_player->Reputation_OnTalk(qst_giver->m_factionDBC);

	sLog.outDebug( "WORLD: Recieved CMSG_GOSSIP_HELLO from %u",GUID_LOPART(guid) );

	/* script */
	ScriptSystem->OnCreatureEvent(qst_giver, _player, CREATURE_EVENT_ON_GOSSIP_TALK);

	GossipScript * Script = qst_giver->GetGossipScript();
	if(!Script)
		return;

	if (qst_giver->isQuestGiver() && qst_giver->HasQuests())
	{
		WorldPacket data;
		data.SetOpcode(SMSG_GOSSIP_MESSAGE);
		Script->GossipHello(qst_giver, _player, false);
		if(!_player->CurrentGossipMenu)
			return;

		_player->CurrentGossipMenu->BuildPacket(data);
		uint32 count=0;//sQuestMgr.ActiveQuestsCount(qst_giver, GetPlayer());
		uint32 pos=data.wpos();
		data << uint32(count);
		for (it = qst_giver->QuestsBegin(); it != qst_giver->QuestsEnd(); ++it)
		{
			uint32 status = sQuestMgr.CalcQuestStatus(qst_giver, GetPlayer(), *it);
			if (status >= QMGR_QUEST_NOT_FINISHED)
			{
				if (!ql.count((*it)->qst->id) )
				{	
					ql.insert((*it)->qst->id);
					count++;
					data << (*it)->qst->id;
					data << status;//sQuestMgr.CalcQuestStatus(qst_giver, GetPlayer(), *it);
					data << uint32(0);
					data << (*it)->qst->title;
				}
			}
		}
		data.wpos(pos);
		data << count;
		SendPacket(&data);
		sLog.outDebug( "WORLD: Sent SMSG_GOSSIP_MESSAGE" );
	}
	else
	{
		Script->GossipHello(qst_giver, _player, true);
	}
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_GOSSIP_SELECT_OPTION:
//////////////////////////////////////////////////////////////
void WorldSession::HandleGossipSelectOptionOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
	WorldPacket data;
	uint32 option;
	uint64 guid;

	recv_data >> guid >> option;

	sLog.outDetail("WORLD: CMSG_GOSSIP_SELECT_OPTION Option %i Guid %.8X", option, guid );
	Creature *qst_giver = _player->GetMapMgr()->GetCreature(guid);
	if(!qst_giver)
		return;

	GossipScript * Script = qst_giver->GetGossipScript();
	if(!Script)
		return;

	uint32 IntId = 1;
	if(_player->CurrentGossipMenu)
	{
		GossipMenuItem item = _player->CurrentGossipMenu->GetItem(option);
		IntId = item.IntId;
	}

	Script->GossipSelectOption(qst_giver, _player, option, IntId);
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_SPIRIT_HEALER_ACTIVATE:
//////////////////////////////////////////////////////////////
void WorldSession::HandleSpiritHealerActivateOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld() ||!_player->isDead()) return;
	GetPlayer( )->DeathDurabilityLoss(0.25);
	GetPlayer( )->ResurrectPlayer();

	Aura *aur = GetPlayer()->FindAura(15007);

	if(aur) // If the player already have the aura, just extend it.
	{
		GetPlayer()->SetAurDuration(15007,aur->GetDuration());
	}
	else // else add him one, that fucker, he think he will get away!?
	{
		SpellEntry *spellInfo = sSpellStore.LookupEntry( 15007 );//resurrectin sickness
		SpellCastTargets targets;
		targets.m_unitTarget = GetPlayer()->GetGUID();
		Spell*sp=new Spell(_player,spellInfo,true,NULL);
		sp->prepare(&targets);
	}

	GetPlayer( )->SetUInt32Value(UNIT_FIELD_HEALTH, GetPlayer()->GetUInt32Value(UNIT_FIELD_MAXHEALTH)/2);
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_NPC_TEXT_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleNpcTextQueryOpcode( WorldPacket & recv_data )
{
	WorldPacket data;
	uint32 textID;
	uint64 targetGuid;
	GossipText *pGossip;

	recv_data >> textID;
	sLog.outDetail("WORLD: CMSG_NPC_TEXT_QUERY ID '%u'", textID );

	recv_data >> targetGuid;
	GetPlayer()->SetUInt64Value(UNIT_FIELD_TARGET, targetGuid);

	pGossip = NpcTextStorage.LookupEntry(textID);

	data.Initialize( SMSG_NPC_TEXT_UPDATE );
	data << textID;
	
	if(pGossip)
	{
		data << float(1.0f);		// Unknown
		for(uint32 i=0;i<8;i++)
		{
			if(pGossip->Texts[i].Text[0][0])
				data << pGossip->Texts[i].Text[1];
			else
				data << pGossip->Texts[i].Text[0];
			if(pGossip->Texts[i].Text[1][1])
				data << pGossip->Texts[i].Text[0];
			else
				data << pGossip->Texts[i].Text[1];
			data << pGossip->Texts[i].Lang;
			data << uint32(0x00);		// Was prob.. but if you set it to 0 emotes work ;)
			for(uint32 e=0;e<6;e++)
				data << uint32(pGossip->Texts[i].Emote[e]);

			if(i!=7) data << uint32(0x00);	// dont append to last
		}
	} 
	else 
	{
		data << float(1.0f);		// unknown
		data << "Hey there, $N. How can I help you?";
		data << "Hey there, $N. How can I help you?";
		data << uint32(0x00);	// ?
		data << uint32(0x00);	// ?
		for(uint32 e=0;e<6;e++)
			data << uint32(0x00);

		for(int i=0;i<7;i++)
		{
			data << uint32(0x00);
			data << uint8(0x00) << uint8(0x00);
			data << uint32(0x00);	// ?
			data << uint32(0x00);	// ?
			for(uint32 e=0;e<6;e++)
				data << uint32(0x00);	// emote 1
		}
	}

	SendPacket(&data);
	return;
}

void WorldSession::HandleBinderActivateOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) return;
	uint64 guid;
	recv_data >> guid;

	Creature *pC = _player->GetMapMgr()->GetCreature(guid);
	if(!pC) return;

	SendInnkeeperBind(pC);
}

void WorldSession::SendInnkeeperBind(Creature* pCreature)
{
	if(!_player->IsInWorld()) return;
	WorldPacket data;

	if(!_player->bHasBindDialogOpen)
	{
		data.Initialize(SMSG_GOSSIP_COMPLETE);
		SendPacket(&data);

		data.Initialize(SMSG_BINDER_CONFIRM);
		data << pCreature->GetGUID() << _player->GetZoneId();
		SendPacket(&data);

		_player->bHasBindDialogOpen = true;
		return;
	}

	// Add a hearthstone if they don't have one
	if(!_player->GetItemInterface()->GetItemCount(6948, true))
	{
		// We don't have a hearthstone. Add one.
		if(_player->GetItemInterface()->CalculateFreeSlots(NULL) > 0)
		{
			/*data.Initialize(SMSG_ITEM_PUSH_RESULT);
			data.Initialize( SMSG_ITEM_PUSH_RESULT );
			data << GetPlayer()->GetGUID();
			data << uint32(0x01) << uint32(0x00) << uint32(0x01) << uint8(0xFF);
			data << uint32(6948) << uint64(0);
			SendPacket(&data);*/
			BuildItemPushResult(&data, _player->GetGUID(), ITEM_PUSH_TYPE_RECEIVE, 1, 6948, 0);
			SendPacket(&data);

			Item *item = objmgr.CreateItem( 6948, _player);

			_player->GetItemInterface()->AddItemToFreeSlot(item);					
		}
	}

	_player->bHasBindDialogOpen = false;

	_player->SetBindPoint(_player->GetPositionX(),_player->GetPositionY(),_player->GetPositionZ(),_player->GetMapId(),_player->GetZoneId());

	data.Initialize(SMSG_BINDPOINTUPDATE);
	data << _player->GetBindPositionX() << _player->GetBindPositionY() << _player->GetBindPositionZ() << _player->GetBindMapId() << _player->GetBindZoneId();
	SendPacket( &data );

	data.Initialize(SMSG_PLAYERBOUND);
	data << pCreature->GetGUID() << _player->GetBindZoneId();
	SendPacket(&data);

	data.Initialize(SMSG_GOSSIP_COMPLETE);
	SendPacket(&data);

#define BIND_SPELL_ID 3286
	data.Initialize( SMSG_SPELL_START );
	data << pCreature->GetNewGUID();
	data << pCreature->GetNewGUID();
	data << uint32(BIND_SPELL_ID);
	data << uint16(0);
	data << uint32(0);
	data << uint16(2);
	data << _player->GetGUID();
	_player->SendMessageToSet(&data, true);

	data.Initialize( SMSG_SPELL_GO );
	data << pCreature->GetNewGUID();
	data << pCreature->GetNewGUID();
	data << uint32(BIND_SPELL_ID);  // spellID
	data << uint8(0) << uint8(1);   // flags
	data << uint8(1);			   // amount of targets
	data << _player->GetGUID();
	data << uint8(0);
	data << uint16(2);
	data << _player->GetGUID();
	_player->SendMessageToSet( &data, true );
}

void WorldSession::SendSpiritHealerRequest(Creature* pCreature)
{
	WorldPacket data(SMSG_SPIRIT_HEALER_CONFIRM, 8);
	data << pCreature->GetGUID();
	SendPacket(&data);
}

