/****************************************************************************
 *
 * General Packet Handler File
 *
 */

#include "StdAfx.h"

void WorldSession::HandlePetAction(WorldPacket & recv_data)
{
    if(!_player->IsInWorld()) return;

    WorldPacket data;
    uint64 petGuid = 0;
    uint16 misc = 0;
    uint16 action = 0;

    uint64 targetguid = 0;
    recv_data >> petGuid >> misc >> action;
    //recv_data.hexlike();

    //printf("Pet_Action: 0x%.4X 0x%.4X\n", misc, action);

    if(UINT32_LOPART(GUID_HIPART(petGuid)) == HIGHGUID_UNIT)
    {
        Creature *pCharm = GetPlayer()->GetMapMgr()->GetCreature(petGuid);
        if(!pCharm) 
            return;

        // must be a mind controled creature..
        if(action == PET_ACTION_ACTION)
        {
            recv_data >> targetguid;
            switch(misc)
            {
            case PET_ACTION_ATTACK:
                {
                    if(!sEventMgr.HasEvent(_player, EVENT_PLAYER_CHARM_ATTACK))
                    {
                        uint32 timer = pCharm->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME);
                        if(!timer) timer = 2000;

                        sEventMgr.AddEvent(_player, &Player::_EventCharmAttack, EVENT_PLAYER_CHARM_ATTACK, timer, 0);
                        _player->_EventCharmAttack();
                    }
                }break;
            }
        }
        return;
    }
    Pet *pPet = _player->GetMapMgr()->GetPet(petGuid);
    if(!pPet)
        return;

    Unit *pTarget = NULL;

    if(action == PET_ACTION_SPELL || action == PET_ACTION_SPELL_1 || action == PET_ACTION_SPELL_2 || (action == PET_ACTION_ACTION && misc == PET_ACTION_ATTACK )) // >> target
    {
        recv_data >> targetguid;
        pTarget = _player->GetMapMgr()->GetUnit(targetguid);
        if(!pTarget) pTarget = pPet;    // target self
    }

    switch(action)
    {
    case PET_ACTION_ACTION:
        {
            pPet->SetPetAction(misc);       // set current action
            switch(misc)
            {
            case PET_ACTION_ATTACK:
                {
                    // make sure the target is attackable
                    if(pTarget == pPet || !isAttackable(pPet, pTarget))
                    {
                        WorldPacket data(SMSG_SPELL_FAILURE, 20);
                        data << _player->GetNewGUID() << uint32(0) << uint8(SPELL_FAILED_BAD_TARGETS);
                        SendPacket(&data);
                        return;
                    }

                    // Clear the threat
                    pPet->GetAIInterface()->WipeTargetList();
                    pPet->GetAIInterface()->WipeHateList();

                    // Attack target with melee if the owner if we dont have spells - other wise cast. All done by AIInterface.
                    if(pPet->GetAIInterface()->getUnitToFollow() == NULL)
                        pPet->GetAIInterface()->SetUnitToFollow(_player);

                    // EVENT_PET_ATTACK
                    pPet->GetAIInterface()->SetAIState(STATE_ATTACKING);
                    pPet->GetAIInterface()->AttackReaction(pTarget, 1, 0);
                }break;
            case PET_ACTION_FOLLOW:
                {
                    // Clear the threat
                    pPet->GetAIInterface()->WipeTargetList();
                    pPet->GetAIInterface()->WipeHateList();

                    // Follow the owner... run to him...
                    pPet->GetAIInterface()->SetUnitToFollow(_player);
                    pPet->GetAIInterface()->HandleEvent(EVENT_FOLLOWOWNER, pPet, 0);
                }break;
            case PET_ACTION_STAY:
                {
                    // Clear the threat
                    pPet->GetAIInterface()->WipeTargetList();
                    pPet->GetAIInterface()->WipeHateList();

                    // Stop following the owner, and sit.
                    pPet->GetAIInterface()->SetUnitToFollow(NULL);
                }break;
            case PET_ACTION_DISMISS:
                {
                    // Bye byte...
                    pPet->Dismiss();
                }break;
            }
        }break;

    case PET_ACTION_SPELL_2:
    case PET_ACTION_SPELL_1:
    case PET_ACTION_SPELL:
        {
            // misc == spellid
            SpellEntry *entry = sSpellStore.LookupEntry(misc);
            if(!entry) 
                return;

            AI_Spell * sp = pPet->GetAISpellForSpellId(entry->Id);
            if(sp)
            {
                // Check the cooldown
                if(pPet->GetAIInterface()->GetSpellCooldown(sp->spell->Id) > 0)
                {
                    //SendNotification("That spell is still cooling down.");
                    WorldPacket data(SMSG_SPELL_FAILURE, 20);
                    data << pPet->GetNewGUID();
                    data << sp->spell->Id;
                    data << uint8(SPELL_FAILED_NOT_READY);
                    SendPacket(&data);
                }
                else
                {
                    if(sp->spellType != STYPE_BUFF)
                    {
                        // make sure the target is attackable
                        if(pTarget == pPet || !isAttackable(pPet, pTarget))
                        {
                            WorldPacket data(SMSG_SPELL_FAILURE, 20);
                            data << _player->GetNewGUID() << sp->spell->Id << uint8(SPELL_FAILED_BAD_TARGETS);
                            SendPacket(&data);
                            return;
                        }
                    }

                    // Clear the threat
                    pPet->GetAIInterface()->WipeTargetList();
                    pPet->GetAIInterface()->WipeHateList();

                    pPet->GetAIInterface()->AttackReaction(pTarget, 1, 0);
                    pPet->GetAIInterface()->SetNextSpell(sp);
                }
            }

            /*// cast spell
            SpellCastTargets targets;
            
            //HACK HACK HACK
            switch (misc)
            {
                case 7812:
                case 19438:
                case 19440:
                case 19441:
                case 19442:
                case 19443:
                    targets.m_unitTarget = pPet->GetGUID(); // dono maybe it should be NULL;
                    break;
                default:
                    targets.m_unitTarget = (pTarget ? pTarget->GetGUID() : pPet->GetGUID());
                    break;
            }
                        
            targets.m_targetMask = 0x2; // unit

            pPet->GetAIInterface()->CastSpell(pPet, entry, targets);*/
        }break;
    case PET_ACTION_STATE:
        {
            pPet->SetPetState(misc);
        }break;
    default:
        {
            printf("WARNING: Unknown pet action received. Action = %.4X, Misc = %.4X\n", action, misc);
        }break;
    }

    /* Send pet action sound - WHEE THEY TALK */
    WorldPacket actionp(SMSG_PET_ACTION_SOUND, 12);
    actionp << pPet->GetGUID() << uint32(1);
    SendPacket(&actionp);
}

void WorldSession::HandlePetInfo(WorldPacket & recv_data)
{
    //nothing
    sLog.outDebug("HandlePetInfo is called");
}

void WorldSession::HandlePetNameQuery(WorldPacket & recv_data)
{
    if(!_player->IsInWorld()) return;
    uint32 petNumber = 0;
    uint64 petGuid = 0;

    recv_data >> petNumber >> petGuid;
    Pet *pPet = _player->GetMapMgr()->GetPet(petGuid);
    if(!pPet) return;

    WorldPacket data;
    data.SetOpcode(SMSG_PET_NAME_QUERY_RESPONSE);
    data << (uint32)pPet->GetGUIDLow();
    data << pPet->GetName();
    data << pPet->GetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP);        // stops packet flood
    SendPacket(&data);
}

void WorldSession::HandleStablePet(WorldPacket & recv_data)
{
    if(!_player->IsInWorld()) return;
    WorldPacket data;
    data.SetOpcode(SMSG_STABLE_RESULT);
    data << uint8(0x8);  // success
    SendPacket(&data);

    // remove pet from world and association with player
    Pet *pPet = _player->GetSummon();
    if(!pPet || pPet->GetUInt32Value(UNIT_CREATED_BY_SPELL) != 0) return;

    pPet->Remove(false, true, true);    // no safedelete needed
}

void WorldSession::HandleUnstablePet(WorldPacket & recv_data)
{
    if(!_player->IsInWorld()) return;
    WorldPacket data;
    uint64 npcguid = 0;
    uint32 petnumber = 0;

    recv_data >> npcguid >> petnumber;
    PlayerPet *pet = _player->GetPlayerPet(petnumber);
    if(!pet)
    {
        sLog.outError("PET SYSTEM: Player " I64FMT " tried to unstable non-existant pet %d", _player->GetGUID(), petnumber);
        return;
    }

    // much easier? :P
    _player->SpawnPet(petnumber);

    data.SetOpcode(SMSG_STABLE_RESULT);
    data << uint8(0x9); // success?
    SendPacket(&data);
}

void WorldSession::HandleStabledPetList(WorldPacket & recv_data)
{
    if(!_player->IsInWorld()) return;
    WorldPacket data;
    data.SetOpcode(MSG_LIST_STABLED_PETS);

    uint64 npcguid = 0;
    recv_data >> npcguid;
    data << npcguid;

    data << uint8(_player->m_Pets.size());
    data << uint8(_player->m_StableSlotCount);

    for(std::map<uint32, PlayerPet*>::iterator itr = _player->m_Pets.begin(); itr != _player->m_Pets.end(); ++itr)
    {
        data << uint32(itr->first); // pet no
        data << uint32(itr->second->entry); // entryid
        data << uint32(itr->second->level); // level
        data << itr->second->name;          // name
        data << uint32(itr->second->loyalty);
        if(itr->second->active && _player->GetSummon() != NULL)
            data << uint8(STABLE_STATE_ACTIVE);
        else
            data << uint8(STABLE_STATE_PASSIVE);
    }

    SendPacket(&data);
}

void WorldSession::HandleBuyStableSlot(WorldPacket &recv_data)
{
    if(!_player->IsInWorld()) return;
    uint8 scount = _player->GetStableSlotCount();
    int32 cost = (scount == 0) ? -500 : -50000;
    if(cost > (int32)_player->GetUInt32Value(PLAYER_FIELD_COINAGE))
        return;

    _player->ModUInt32Value(PLAYER_FIELD_COINAGE, -cost);
    
    WorldPacket data;
    data.SetOpcode(SMSG_STABLE_RESULT);
    data << uint8(0x0A);
    SendPacket(&data);
    if(_player->GetStableSlotCount() > 2)
        _player->m_StableSlotCount = 2;
    else
        _player->m_StableSlotCount++;
}


void WorldSession::HandlePetSetActionOpcode(WorldPacket& recv_data)
{
    if(!_player->IsInWorld()) return;
    uint32 unk1;
    uint32 unk2;
    uint32 slot;
    uint16 spell;
    uint16 state;
    recv_data >> unk1 >> unk2 >> slot >> spell >> state;
    if(!_player->GetSummon())
        return;

    Pet * pet = _player->GetSummon();
    pet->ActionBar[slot] = spell;
    pet->SetSpellState(spell, state);
    /*if(state == 0x8100 &&       // no autocast
        spell == pet->GetAIInterface()->GetDefaultSpell()->spell->Id)
    {
        // removing autocast
        pet->GetAIInterface()->SetDefaultSpell(0);
    }

    if(state == 0xC100)         // adding autocast
    {
        AI_Spell * sp = pet->GetAISpellForSpellId(spell);
        if(sp)
            pet->GetAIInterface()->SetDefaultSpell(sp);
    }*/
    AI_Spell * sp = pet->GetAISpellForSpellId(spell);
    if(!sp) return;

    if(state == 0x8100)
    {
        if(sp->procChance == 100)
            sp->procChance = 0;

        pet->GetAIInterface()->disable_melee = false;
    }
    else if(state == 0xC100)
    {
        if(sp->procChance != 100)
            sp->procChance = 100;
        
        pet->GetAIInterface()->disable_melee = true;
    }
}

void WorldSession::HandlePetRename(WorldPacket & recv_data)
{
    if(!_player->IsInWorld()) return;
    uint64 guid;
    string name;
    recv_data >> guid >> name;

    if(!_player->GetSummon() || _player->GetSummon()->GetGUID() != guid)
    {
        sChatHandler.SystemMessage(this, "That pet is not your current pet, or you do not have a pet.");
        return;
    }

    Pet * pet = _player->GetSummon();
    pet->Rename(name);

    // Disable pet rename.
    pet->SetUInt32Value(UNIT_FIELD_BYTES_2, 1 | (0x28 << 8) | (0x2 << 16));
}

void WorldSession::HandlePetAbandon(WorldPacket & recv_data)
{
    if(!_player->IsInWorld()) return;
    Pet * pet = _player->GetSummon();
    if(!pet) return;

    pet->Dismiss(false);
}
