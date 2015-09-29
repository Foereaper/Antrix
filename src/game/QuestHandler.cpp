/****************************************************************************
 *
 * General Packet Handler File
 *
 */

#include "StdAfx.h"
initialiseSingleton( QuestMgr );

void WorldSession::HandleQuestgiverStatusQueryOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Recieved CMSG_QUESTGIVER_STATUS_QUERY." );
    if(!_player->IsInWorld()) return;

    uint64 guid;
    WorldPacket data;

    recv_data >> guid;

    Creature *qst_giver = _player->GetMapMgr()->GetCreature(guid);

    if (!qst_giver)
    {
        sLog.outDebug("WORLD: Invalid questgiver GUID " I64FMT ".", guid);
        return;
    }

    if (!qst_giver->isQuestGiver())
    {
        sLog.outDebug("WORLD: Creature is not a questgiver.");
        return;
    }

    data.Initialize( SMSG_QUESTGIVER_STATUS );

    data << guid << sQuestMgr.CalcStatus(qst_giver, GetPlayer());
    SendPacket( &data );
}

void WorldSession::HandleQuestgiverHelloOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Recieved CMSG_QUESTGIVER_HELLO." );
    if(!_player->IsInWorld()) return;

    uint64 guid;

    recv_data >> guid;

    Creature *qst_giver = _player->GetMapMgr()->GetCreature(guid);

    if (!qst_giver)
    {
        sLog.outDebug("WORLD: Invalid questgiver GUID.");
        return;
    }

    if (!qst_giver->isQuestGiver())
    {
        sLog.outDebug("WORLD: Creature is not a questgiver.");
        return;
    }

    if(qst_giver->GetAIInterface()) // NPC Stops moving for 3 minutes
        qst_giver->GetAIInterface()->StopMovement(180000);

    //qst_giver->Emote(EMOTE_ONESHOT_TALK); // this doesnt work
    sQuestMgr.OnActivateQuestGiver(qst_giver, GetPlayer());
}

void WorldSession::HandleQuestGiverQueryQuestOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Recieved CMSG_QUESTGIVER_QUERY_QUEST." );
    if(!_player->IsInWorld()) return;

    WorldPacket data;
    uint64 guid;
    uint32 quest_id;
    uint32 status = 0;

    recv_data >> guid;
    recv_data >> quest_id;

    Object *qst_giver = NULL;

    bool bValid = false;
    Quest* qst = QuestStorage.LookupEntry(quest_id);
    
    if (!qst)
    {
        sLog.outDebug("WORLD: Invalid quest ID.");
        return;
    }

    if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_UNIT)
    {
        Creature *quest_giver = _player->GetMapMgr()->GetCreature(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = quest_giver->isQuestGiver();
        if(bValid)
            status = sQuestMgr.CalcQuestStatus(qst_giver, GetPlayer(), qst, quest_giver->GetQuestRelation(qst->id));
    } 
    else if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_GAMEOBJECT)
    {
        GameObject *quest_giver = _player->GetMapMgr()->GetGameObject(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = quest_giver->isQuestGiver();
        if(bValid)
            status = sQuestMgr.CalcQuestStatus(qst_giver, GetPlayer(), qst, quest_giver->GetQuestRelation(qst->id));
    } 
    else if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_ITEM)
    {
        Item *quest_giver = GetPlayer()->GetItemInterface()->GetItemByGUID(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = true;
        status = sQuestMgr.CalcQuestStatus(qst_giver, GetPlayer(), qst, 1);
    }
    
    if (!qst_giver)
    {
        sLog.outDebug("WORLD: Invalid questgiver GUID.");
        return;
    }

    if (!bValid)
    {
        sLog.outDebug("WORLD: Creature is not a questgiver.");
        return;
    }

    /*if (!qst_giver->FindQuest(quest_id, QUESTGIVER_QUEST_START | QUESTGIVER_QUEST_END))
    {
        sLog.outDebug("WORLD: QuestGiver doesn't have that quest.");
        return;
    }*/    // bleh.. not needed.. maybe for antihack later on would be a good idea though
    
    if ((status == QMGR_QUEST_AVAILABLE) || (status == QMGR_QUEST_REPEATABLE))
    {
        sQuestMgr.BuildQuestDetails(&data, qst,qst_giver,1);     // 0 because we want goodbye to function
        SendPacket(&data);
        sLog.outDebug( "WORLD: Sent SMSG_QUESTGIVER_QUEST_DETAILS." );
    }
    /*else if (status == QMGR_QUEST_FINISHED)
    {
        sQuestMgr.BuildOfferReward(&data, qst, qst_giver, 1);
        SendPacket(&data);
        sLog.outDebug( "WORLD: Sent SMSG_QUESTGIVER_OFFER_REWARD." );
    }*/
    else if (status == QMGR_QUEST_NOT_FINISHED || status == QMGR_QUEST_FINISHED)
    {
        sQuestMgr.BuildRequestItems(&data, qst, qst_giver, 1);
        SendPacket(&data);
        sLog.outDebug( "WORLD: Sent SMSG_QUESTGIVER_REQUEST_ITEMS." );
    }
}

void WorldSession::HandleQuestgiverAcceptQuestOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Recieved CMSG_QUESTGIVER_ACCEPT_QUEST" );
    if(!_player->IsInWorld()) return;

    WorldPacket data;

    uint64 guid;
    uint32 quest_id;

    recv_data >> guid;
    recv_data >> quest_id;

    bool bValid = false;
    bool hasquest = true;
    Quest *qst = NULL;
    Object *qst_giver = NULL;

    if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_UNIT)
    {
        Creature *quest_giver = _player->GetMapMgr()->GetCreature(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = quest_giver->isQuestGiver();
        hasquest = quest_giver->HasQuest(quest_id, 1);
        if(bValid)
            qst = QuestStorage.LookupEntry(quest_id);
    } 
    else if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_GAMEOBJECT)
    {
        GameObject *quest_giver = _player->GetMapMgr()->GetGameObject(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = quest_giver->isQuestGiver();
        if(bValid)
            qst = QuestStorage.LookupEntry(quest_id);
    } 
    else if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_ITEM)
    {
        Item *quest_giver = GetPlayer()->GetItemInterface()->GetItemByGUID(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = true;
        qst = QuestStorage.LookupEntry(quest_id);
    }
    else if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_PLAYER)
    {
        Player *quest_giver = _player->GetMapMgr()->GetPlayer(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = true;
        qst = QuestStorage.LookupEntry(quest_id);
    }

    if (!qst_giver)
    {
        sLog.outDebug("WORLD: Invalid questgiver GUID.");
        return;
    }

    if (!bValid || qst == NULL)
    {
        sLog.outDebug("WORLD: Creature is not a questgiver.");
        return;
    }

    if(_player->GetQuestLogForEntry(qst->id))
        return;

    // Check the player hasn't already taken this quest, or
    // it isn't available.
    uint32 status = sQuestMgr.CalcStatus(qst_giver, _player);

    if((!sQuestMgr.IsQuestRepeatable(qst) && _player->HasFinishedQuest(qst->id)) || ( status != QMGR_QUEST_AVAILABLE && status != QMGR_QUEST_REPEATABLE )
        || !hasquest)
    {
        // We've got a hacker. Disconnect them.
        sCheatLog.writefromsession(this, "tried to accept incompatible quest %u from %u.", qst->id, qst_giver->GetEntry());
        //Disconnect();
        return;
    }

    int32 log_slot = GetPlayer()->GetOpenQuestSlot();

    if (log_slot == -1)
    {
        sQuestMgr.SendQuestLogFull(GetPlayer());
        return;
    }

    //FIXME
    /*if(Player Has Timed quest && qst->HasFlag(QUEST_FLAG_TIMED))
        sQuestMgr.SendQuestInvalid(INVALID_REASON_HAVE_TIMED_QUEST);*/

    if(qst->count_receiveitems || qst->srcitem)
    {
        uint32 slots_required = qst->count_receiveitems;
        if(qst->srcitem)
            slots_required += qst->srcitemcount ? qst->srcitemcount : 1;

        if(GetPlayer()->GetItemInterface()->CalculateFreeSlots(NULL) < slots_required)
        {
            GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_BAG_FULL);
            sQuestMgr.SendQuestFailed(FAILED_REASON_INV_FULL, GetPlayer());
            return;
        }
    }    
    
    if(qst_giver->GetTypeId() == TYPEID_UNIT && !ScriptSystem->OnQuestRequireEvent(qst, ((Creature*)qst_giver), _player, QUEST_EVENT_CAN_ACCEPT))
        return;

    QuestLogEntry *qle = new QuestLogEntry();
    qle->Init(qst, _player, log_slot);
    qle->UpdatePlayerFields();

    // If the quest should give any items on begin, give them the items.
    for(uint32 i = 0; i < 4; ++i)
    {
        if(qst->receive_items[i])
        {
            Item *item = objmgr.CreateItem( qst->receive_items[i], GetPlayer());
            if(!GetPlayer()->GetItemInterface()->AddItemToFreeSlot(item))
            {
                delete item;
            }
        }
    }

    if(qst->srcitem && qst->srcitem != qst->receive_items[0])
    {
        Item * item = objmgr.CreateItem( qst->srcitem, _player );
        if(item)
        {
            item->SetUInt32Value(ITEM_FIELD_STACK_COUNT, qst->srcitemcount ? qst->srcitemcount : 1);
            if(!_player->GetItemInterface()->AddItemToFreeSlot(item))
                delete item;
        }
    }

    // Timed quest handler.
    if(qst->time > 0)
    {
        //Start Quest Timer Event Here
        //sEventMgr.AddEvent(GetPlayer(), &Player::EventTimedQuestExpire, qst, qle, static_cast<uint32>(log_slot), EVENT_TIMED_QUEST_EXPIRE, qst->time * 1000, 1);
        uint32 qtime = static_cast<uint32>(time(NULL) + qst->time);
        GetPlayer()->SetUInt32Value(log_slot+2, qtime);
        GetPlayer()->timed_quest_slot = (log_slot - (PLAYER_QUEST_LOG_1_1) / 3);
    }

    if(qst->count_required_item || qst_giver->GetTypeId() == TYPEID_GAMEOBJECT)    // gameobject quests deactivate
        GetPlayer()->UpdateNearbyGameObjects();

    ScriptSystem->OnQuestEvent(qst, ((Creature*)qst_giver), _player, QUEST_EVENT_ON_ACCEPT);
    
    sLog.outDebug("WORLD: Added new QLE.");
    sHookInterface.OnQuestAccept(_player, qst);
}

void WorldSession::HandleQuestgiverCancelOpcode(WorldPacket& recvPacket)
{
    WorldPacket data;

    data.Initialize(SMSG_GOSSIP_COMPLETE);
    SendPacket(&data);

    sLog.outDebug("WORLD: Sent SMSG_GOSSIP_COMPLETE");
}

void WorldSession::HandleQuestlogRemoveQuestOpcode(WorldPacket& recvPacket)
{
    sLog.outDebug( "WORLD: Recieved CMSG_QUESTLOG_REMOVE_QUEST" );
    if(!_player->IsInWorld()) return;

    uint8 quest_slot;
    recvPacket >> quest_slot;
    if(quest_slot >= 25)
        return;

    QuestLogEntry *qEntry = GetPlayer()->GetQuestLogInSlot(quest_slot);
    if (!qEntry)
    {
        sLog.outDebug("WORLD: No quest in slot %d.", quest_slot);
        return;        
    }
    Quest *qPtr = qEntry->GetQuest();
    CALL_QUESTSCRIPT_EVENT(qEntry, OnQuestCancel)(GetPlayer());
    qEntry->Finish();

    // Remove all items given by the questgiver at the beginning
    for(uint32 i = 0; i < 4; ++i)
    {
        if(qPtr->receive_items[i])
            GetPlayer()->GetItemInterface()->RemoveItemAmt( qPtr->receive_items[i], 1 );
    }
    if(qPtr->time > 0)
    {
        GetPlayer()->timed_quest_slot = 0;
    }
    GetPlayer()->UpdateNearbyGameObjects();
}

void WorldSession::HandleQuestQueryOpcode( WorldPacket & recv_data )
{
    if(!_player->IsInWorld()) return;
    sLog.outDebug( "WORLD: Recieved CMSG_QUEST_QUERY" );

    uint32 quest_id;

    recv_data >> quest_id;

    Quest *qst = QuestStorage.LookupEntry(quest_id);

    if (!qst)
    {
        sLog.outDebug("WORLD: Invalid quest ID.");
        return;
    }

    WorldPacket *pkt = BuildQuestQueryResponse(qst);
    SendPacket(pkt);
    delete pkt;

    sLog.outDebug( "WORLD: Sent SMSG_QUEST_QUERY_RESPONSE." );
}

void WorldSession::HandleQuestgiverRequestRewardOpcode( WorldPacket & recv_data )
{
    if(!_player->IsInWorld()) return;
    sLog.outDebug( "WORLD: Recieved CMSG_QUESTGIVER_COMPLETE_QUEST." );

    WorldPacket data;
    uint64 guid;
    uint32 quest_id;

    recv_data >> guid;
    recv_data >> quest_id;

    bool bValid = false;
    Quest *qst = NULL;
    Object *qst_giver = NULL;
    uint32 status = 0;

    if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_UNIT)
    {
        Creature *quest_giver = _player->GetMapMgr()->GetCreature(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = quest_giver->isQuestGiver();
        if(bValid)
        {
            qst = quest_giver->FindQuest(quest_id, QUESTGIVER_QUEST_END);
            if(!qst)
                qst = quest_giver->FindQuest(quest_id, QUESTGIVER_QUEST_START);

            /*if(!qst) 
                qst = QuestStorage.LookupEntry(quest_id);*/
            if(!qst)
            {
                sLog.outError("WARNING: Cannot complete quest, as it doesnt exist.");
                return;
            }
            status = sQuestMgr.CalcQuestStatus(qst_giver, GetPlayer(), qst, quest_giver->GetQuestRelation(qst->id));
        }
    } 
    else if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_GAMEOBJECT)
    {
        GameObject *quest_giver = _player->GetMapMgr()->GetGameObject(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return; // oops..
        bValid = quest_giver->isQuestGiver();
        if(bValid)
        {
            qst = quest_giver->FindQuest(quest_id, QUESTGIVER_QUEST_END);
            /*if(!qst) sQuestMgr.FindQuest(quest_id);*/
            if(!qst)
            {
                sLog.outError("WARNING: Cannot complete quest, as it doesnt exist.");
                return;
            }
            status = sQuestMgr.CalcQuestStatus(qst_giver, GetPlayer(), qst, quest_giver->GetQuestRelation(qst->id));
        }
    }

    if (!qst_giver)
    {
        sLog.outDebug("WORLD: Invalid questgiver GUID.");
        return;
    }

    if (!bValid || qst == NULL)
    {
        sLog.outDebug("WORLD: Creature is not a questgiver.");
        return;
    }

    if (status == QMGR_QUEST_FINISHED)
    {
        sQuestMgr.BuildOfferReward(&data, qst, qst_giver, 1);
        SendPacket(&data);
        sLog.outDebug( "WORLD: Sent SMSG_QUESTGIVER_REQUEST_ITEMS." );
    }

    // if we got here it means we're cheating
}

void WorldSession::HandleQuestgiverCompleteQuestOpcode( WorldPacket & recvPacket )
{
    if(!_player->IsInWorld()) return;
    sLog.outDebug( "WORLD: Recieved CMSG_QUESTGIVER_COMPLETE_QUEST." );

    WorldPacket data;
    uint64 guid;
    uint32 quest_id;

    recvPacket >> guid;
    recvPacket >> quest_id;

    bool bValid = false;
    Quest *qst = NULL;
    Object *qst_giver = NULL;
    uint32 status = 0;

    if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_UNIT)
    {
        Creature *quest_giver = _player->GetMapMgr()->GetCreature(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = quest_giver->isQuestGiver();
        if(bValid)
        {
            qst = quest_giver->FindQuest(quest_id, QUESTGIVER_QUEST_START);
            /*if(!qst) 
                sQuestMgr.FindQuest(quest_id);*/
            if(!qst)
            {
                sLog.outError("WARNING: Cannot complete quest, as it doesnt exist.");
                return;
            }
            status = sQuestMgr.CalcQuestStatus(qst_giver, GetPlayer(), qst, quest_giver->GetQuestRelation(qst->id));
        }
    } 
    else if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_GAMEOBJECT)
    {
        GameObject *quest_giver = _player->GetMapMgr()->GetGameObject(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return; // oops..
        bValid = quest_giver->isQuestGiver();
        if(bValid)
        {
            qst = quest_giver->FindQuest(quest_id, QUESTGIVER_QUEST_START);
            /*if(!qst) sQuestMgr.FindQuest(quest_id);*/
            if(!qst)
            {
                sLog.outError("WARNING: Cannot complete quest, as it doesnt exist.");
                return;
            }
            status = sQuestMgr.CalcQuestStatus(qst_giver, GetPlayer(), qst, quest_giver->GetQuestRelation(qst->id));
        }
    }

    if (!qst_giver)
    {
        sLog.outDebug("WORLD: Invalid questgiver GUID.");
        return;
    }

    if (!bValid || qst == NULL)
    {
        sLog.outDebug("WORLD: Creature is not a questgiver.");
        return;
    }

    if (status == QMGR_QUEST_NOT_FINISHED)
    {
        sQuestMgr.BuildRequestItems(&data, qst, qst_giver, 1);
        SendPacket(&data);
        sLog.outDebug( "WORLD: Sent SMSG_QUESTGIVER_REQUEST_ITEMS." );
    }
}

void WorldSession::HandleQuestgiverChooseRewardOpcode(WorldPacket& recvPacket)
{
    if(!_player->IsInWorld()) return;
    sLog.outDebug( "WORLD: Recieved CMSG_QUESTGIVER_CHOOSE_REWARD." );

    WorldPacket data;
    uint64 guid;
    uint32 quest_id;
    uint32 reward_slot;

    recvPacket >> guid;
    recvPacket >> quest_id;
    recvPacket >> reward_slot;

    bool bValid = false;
    Quest *qst = NULL;
    Object *qst_giver = NULL;

    if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_UNIT)
    {
        Creature *quest_giver = _player->GetMapMgr()->GetCreature(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = quest_giver->isQuestGiver();
        if(bValid)
            qst = QuestStorage.LookupEntry(quest_id);
    } 
    else if(UINT32_LOPART(GUID_HIPART(guid))==HIGHGUID_GAMEOBJECT)
    {
        GameObject *quest_giver = _player->GetMapMgr()->GetGameObject(guid);
        if(quest_giver)
            qst_giver = (Object*)quest_giver;
        else
            return;
        bValid = quest_giver->isQuestGiver();
        if(bValid)
            qst = QuestStorage.LookupEntry(quest_id);
    }

    if (!qst_giver)
    {
        sLog.outDebug("WORLD: Invalid questgiver GUID.");
        return;
    }

    if (!bValid || qst == NULL)
    {
        sLog.outDebug("WORLD: Creature is not a questgiver.");
        return;
    }

    //FIXME: Some Quest givers talk in the end of the quest.
    //   qst_giver->SendChatMessage(CHAT_MSG_MONSTER_SAY,LANG_UNIVERSAL,qst->GetQuestEndMessage().c_str());
    QuestLogEntry *qle = _player->GetQuestLogForEntry(quest_id);

    if (!qle)
    {
        sLog.outDebug("WORLD: QuestLogEntry not found.");
        return;
    }

    if (!qle->CanBeFinished())
    {
        sLog.outDebug("WORLD: Quest not finished.");
        return;
    }

    // remove icon
    if(qst_giver->GetTypeId() == TYPEID_UNIT)
    {
        qst_giver->BuildFieldUpdatePacket(GetPlayer(), UNIT_DYNAMIC_FLAGS, qst_giver->GetUInt32Value(UNIT_DYNAMIC_FLAGS));
    }

    //check for room in inventory for all items
    if(!sQuestMgr.CanStoreReward(GetPlayer(),qst,reward_slot))
    {
        GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_INVENTORY_FULL);
        return;
    }

    
    sQuestMgr.OnQuestFinished(GetPlayer(), qst, qst_giver, reward_slot);
    //if(qst_giver->GetTypeId() == TYPEID_UNIT) qst->LUA_SendEvent(((Creature*)qst_giver),GetPlayer(),ON_QUEST_COMPLETEQUEST);

    if(qst->next_quest_id)
    {
        data.Initialize(CMSG_QUESTGIVER_QUERY_QUEST);
        data << guid;
        data << qst->next_quest_id;
        HandleQuestGiverQueryQuestOpcode(data);
    }
    if(qst->time > 0)
    {
        GetPlayer()->timed_quest_slot = 0;
    }
}

void WorldSession::HandlePushQuestToPartyOpcode(WorldPacket &recv_data)
{
    if(!_player->IsInWorld()) return;
    uint32 questid;
    recv_data >> questid;

    sLog.outDetail( "WORLD: Received CMSG_PUSHQUESTTOPARTY quest = %u", questid );

    Quest *pQuest = QuestStorage.LookupEntry(questid);
    if(pQuest)
    {
        Group *pGroup = _player->GetGroup();
        if(pGroup)
        {
            uint32 pguid = _player->GetGUID();
            SubGroup * sgr = _player->GetGroup() ?
                _player->GetGroup()->GetSubGroup(_player->GetSubGroup()) : 0;

            if(sgr)
            {
                GroupMembersSet::iterator itr;
                for(itr = sgr->GetGroupMembersBegin(); itr != sgr->GetGroupMembersEnd(); ++itr)
                {
                    Player *pPlayer = (*itr);
                    if(pPlayer->GetGUID() !=  pguid)
                    {
                        WorldPacket data( MSG_QUEST_PUSH_RESULT, 13 );
                        data << pPlayer->GetGUID();
                        data << uint32(QUEST_SHARE_MSG_SHARING_QUEST);
                        data << uint8(0);
                        _player->GetSession()->SendPacket(&data);

                        uint32 response = 0;
                        if(_player->GetDistance2dSq(pPlayer) > 100)
                        {
                            response = QUEST_SHARE_MSG_TOO_FAR;
                            continue;
                        }
                        QuestLogEntry *qst = pPlayer->GetQuestLogForEntry(questid);
                        if(qst)
                        {
                            response = QUEST_SHARE_MSG_HAVE_QUEST;
                            continue;
                        }
                        if(sQuestMgr.PlayerMeetsReqs(pPlayer, pQuest) != QMGR_QUEST_AVAILABLE)
                        {
                            response = QUEST_SHARE_MSG_CANT_TAKE_QUEST;
                            continue;
                        }
                        if(pPlayer->HasFinishedQuest(questid))
                        {
                            response = QUEST_SHARE_MSG_FINISH_QUEST;
                            continue;
                        }
                        if(pPlayer->GetOpenQuestSlot() == -1)
                        {
                            response = QUEST_SHARE_MSG_LOG_FULL;
                            continue;
                        }
                        //Anything more?
                        if(pPlayer->DuelingWith)
                        {
                            response = QUEST_SHARE_MSG_BUSY;
                            continue;
                        }
                        if(response > 0)
                            sQuestMgr.SendPushToPartyResponse(_player, pPlayer, response);

                        data.clear();
                        sQuestMgr.BuildQuestDetails(&data, pQuest, pPlayer, 1);
                        pPlayer->GetSession()->SendPacket(&data);
                        pPlayer->SetQuestSharer(pguid);
                    }
                }
            }
        }
    }
}

void WorldSession::HandleQuestPushResult(WorldPacket& recvPacket)
{
    if(!_player->IsInWorld()) return;
    uint64 guid;
    uint8 msg;
    recvPacket >> guid >> msg;

    sLog.outDetail( "WORLD: Received MSG_QUEST_PUSH_RESULT " );

    if(GetPlayer()->GetQuestSharer())
    {
        Player *pPlayer = objmgr.GetPlayer(GetPlayer()->GetQuestSharer());
        if(pPlayer)
        {
            WorldPacket data(MSG_QUEST_PUSH_RESULT, 13);
            data << guid;
            data << uint32(msg);
            data << uint8(0);
            pPlayer->GetSession()->SendPacket(&data);
            GetPlayer()->SetQuestSharer(0);
        }
    }
}
