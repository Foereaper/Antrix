/****************************************************************************
 *
 * General Packet Handler File
 *
 */

#include "StdAfx.h"

void WorldSession::HandleRepopRequestOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Recvd CMSG_REPOP_REQUEST Message" );
      GetPlayer()->RepopRequestedPlayer();
}

void WorldSession::HandleAutostoreLootItemOpcode( WorldPacket & recv_data )
{
    if(!_player->IsInWorld()) return;
//    uint8 slot = 0;
    uint32 itemid = 0;
    uint32 amt = 1;
    uint8 lootSlot = 0;
    uint8 error = 0;
    SlotResult slotresult;

    Item *add;
    Loot *pLoot = NULL;

    if(_player->isCasting())
        _player->InterruptSpell();
    GameObject * pGO = NULL;
    Creature * pCreature = NULL;

    if(UINT32_LOPART(GUID_HIPART(GetPlayer()->GetLootGUID())) == HIGHGUID_UNIT)
    {
        pCreature = _player->GetMapMgr()->GetCreature((uint32)GetPlayer()->GetLootGUID());
        if (!pCreature)return;
        pLoot=&pCreature->loot;    
    }
    else if(UINT32_LOPART(GUID_HIPART(_player->GetLootGUID())) == HIGHGUID_GAMEOBJECT)
    {
        pGO = _player->GetMapMgr()->GetGameObject((uint32)GetPlayer()->GetLootGUID());
        if(!pGO)return;
        pLoot=&pGO->loot;
    }else if( (UINT32_LOPART(GUID_HIPART(_player->GetLootGUID())) == HIGHGUID_ITEM) )
    {
        Item *pItem = _player->GetItemInterface()->GetItemByGUID(_player->GetLootGUID());
        if(!pItem)
            return;
        pLoot = pItem->loot;
    }

    if(!pLoot) return;

    recv_data >> lootSlot;
    if (lootSlot >= pLoot->items.size())
    {
        sLog.outDebug("AutoLootItem: Player %s might be using a hack! (slot %d, size %d)",
                        GetPlayer()->GetName(), lootSlot, pLoot->items.size());
        return;
    }

    amt = pLoot->items.at(lootSlot).iItemsCount;

    if (!amt)//Test for party loot
    {  
        GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL,INV_ERR_ALREADY_LOOTED);
        return;
    } 
    itemid = pLoot->items.at(lootSlot).item.itemid;
    ItemPrototype* it = ItemPrototypeStorage.LookupEntry(itemid);

    if((error = _player->GetItemInterface()->CanReceiveItem(it, 1)))
    {
        _player->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, error);
        return;
    }

    if(pGO)
        CALL_GO_SCRIPT_EVENT(pGO, OnLootTaken)(_player, it);
    else if(pCreature)
        CALL_SCRIPT_EVENT(pCreature, OnLootTaken)(_player, it);

    add = GetPlayer()->GetItemInterface()->FindItemLessMax(itemid, amt, false);
    sHookInterface.OnLoot(_player, pCreature, 0, itemid);
    if (!add)
    {
        slotresult = GetPlayer()->GetItemInterface()->FindFreeInventorySlot(it);
        if(!slotresult.Result)
        {
            GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_INVENTORY_FULL);
            return;
        }
    
        sLog.outDebug("AutoLootItem MISC");
        Item *item = objmgr.CreateItem( itemid, GetPlayer());
       
        item->SetUInt32Value(ITEM_FIELD_STACK_COUNT,amt);
        uint32 rndprop=pLoot->items.at(lootSlot).iRandomProperty;
        if(rndprop)
            item->SetUInt32Value(ITEM_FIELD_RANDOM_PROPERTIES_ID,rndprop);
        item->ApplyRandomProperties();

        GetPlayer()->GetItemInterface()->SafeAddItem(item,slotresult.ContainerSlot, slotresult.Slot);
        
        if (it->Class == 12)        // Quest item
            sQuestMgr.OnPlayerItemPickup(GetPlayer(),item);
    }
    else 
    {    
        add->SetCount(add->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + amt);
        add->m_isDirty = true;
        if (it->Class == 12)        // Quest item
            sQuestMgr.OnPlayerItemPickup(GetPlayer(),add);
    }

    pLoot->items.at(lootSlot).iItemsCount=0;
    // this gets sent to all looters
    WorldPacket data(1);
    data.SetOpcode(SMSG_LOOT_REMOVED);
    data << lootSlot;
    Player * plr;
    for(LooterSet::iterator itr = pLoot->looters.begin(); itr != pLoot->looters.end(); ++itr)
    {
        if((plr = _player->GetMapMgr()->GetPlayer(*itr)))
            plr->GetSession()->SendPacket(&data);
    }

    WorldPacket idata;
    if(it->Class == ITEM_CLASS_QUEST)
    {
        uint32 pcount = _player->GetItemInterface()->GetItemCount(it->ItemId, true);
        BuildItemPushResult(&idata, _player->GetGUID(), ITEM_PUSH_TYPE_LOOT, amt, itemid, pLoot->items.at(lootSlot).iRandomProperty,0xFF,0,0xFFFFFFFF,pcount);
    }
    else BuildItemPushResult(&idata, _player->GetGUID(), ITEM_PUSH_TYPE_LOOT, amt, itemid, pLoot->items.at(lootSlot).iRandomProperty);

    if(_player->InGroup())
        _player->GetGroup()->SendPacketToAll(&idata);
    else
        SendPacket(&idata);
}

void WorldSession::HandleLootMoneyOpcode( WorldPacket & recv_data )
{
    if(!_player->IsInWorld()) return;
    Loot * pLoot = NULL;
    uint64 lootguid=GetPlayer()->GetLootGUID();
    if(!lootguid)
        return;   // duno why this happens

    if(_player->isCasting())
        _player->InterruptSpell();

    WorldPacket pkt;    
    Unit * pt = 0;

    if(UINT32_LOPART(GUID_HIPART(lootguid)) == HIGHGUID_UNIT)
    {
        Creature* pCreature = _player->GetMapMgr()->GetCreature(lootguid);
        if(!pCreature)return;
        pLoot=&pCreature->loot;
        pt = pCreature;
    }
    else if(UINT32_LOPART(GUID_HIPART(lootguid)) == HIGHGUID_GAMEOBJECT)
    {
        GameObject* pGO = _player->GetMapMgr()->GetGameObject(lootguid);
        if(!pGO)return;
        pLoot=&pGO->loot;
    }
    else if(UINT32_LOPART(GUID_HIPART(lootguid)) == HIGHGUID_CORPSE)
    {
        Corpse *pCorpse = objmgr.GetCorpse((uint32)lootguid);
        if(!pCorpse)return;
        pLoot=&pCorpse->loot;
    }
    else if(UINT32_LOPART(GUID_HIPART(lootguid)) == HIGHGUID_PLAYER)
    {
        Player * pPlayer = _player->GetMapMgr()->GetPlayer(lootguid);
        if(!pPlayer) return;
        pLoot = &pPlayer->loot;
        pPlayer->bShouldHaveLootableOnCorpse = false;
        pt = pPlayer;
    }
    else if( (UINT32_LOPART(GUID_HIPART(lootguid)) == HIGHGUID_ITEM) )
    {
        Item *pItem = _player->GetItemInterface()->GetItemByGUID(lootguid);
        if(!pItem)
            return;
        pLoot = pItem->loot;
    }

    if (!pLoot)
    {
        //bitch about cheating maybe?
        return;
    }

    uint32 money = pLoot->gold;

    pLoot->gold=0;
    WorldPacket data(1);
    data.SetOpcode(SMSG_LOOT_CLEAR_MONEY);
    // send to all looters
    Player * plr;
    for(LooterSet::iterator itr = pLoot->looters.begin(); itr != pLoot->looters.end(); ++itr)
    {
        if((plr = _player->GetMapMgr()->GetPlayer(*itr)))
            plr->GetSession()->SendPacket(&data);
    }

    if(!_player->InGroup())
    {
        if(money)
        {
            GetPlayer()->ModUInt32Value( PLAYER_FIELD_COINAGE , money);
            sHookInterface.OnLoot(_player, pt, money, 0);
        }
    }
    else
    {
        //this code is wrong mustbe party not raid!
        Group* party = _player->GetGroup();
        if(party)
        {
            /*uint32 share = money/party->MemberCount();*/
            vector<Player*> targets;
            targets.reserve(party->MemberCount());

            GroupMembersSet::iterator itr;
            SubGroup * sgrp;
            for(uint32 i = 0; i < party->GetSubGroupCount(); i++)
            {
                sgrp = party->GetSubGroup(i);
                for(itr = sgrp->GetGroupMembersBegin(); itr != sgrp->GetGroupMembersEnd(); ++itr)
                {
                    if((*itr)->GetZoneId() == _player->GetZoneId() && _player->GetInstanceID() == (*itr)->GetInstanceID())
                        targets.push_back((*itr));
                }
            }

            if(!targets.size())
                return;

            uint32 share = money / targets.size();

            pkt.SetOpcode(SMSG_LOOT_MONEY_NOTIFY);
            pkt << share;

            for(vector<Player*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                (*itr)->ModUInt32Value(PLAYER_FIELD_COINAGE, share);
                (*itr)->GetSession()->SendPacket(&pkt);
            }
        }
    }   
}

void WorldSession::HandleLootOpcode( WorldPacket & recv_data )
{
    if(!_player->IsInWorld())
        return;

    uint64 guid;
    recv_data >> guid;

    if(_player->isCasting())
        _player->InterruptSpell();

    if(_player->InGroup() && !_player->m_bgInBattleground)
    {
        Group * party = _player->GetGroup();
        if(party)
        {
            if(party->GetMethod() == PARTY_LOOT_MASTER)
            {                
                WorldPacket data(SMSG_LOOT_MASTER_LIST, 330);  // wont be any larger
                data << (uint8)party->MemberCount();
                uint32 real_count = 0;
                SubGroup *s;
                GroupMembersSet::iterator itr;
                for(uint32 i = 0; i < party->GetSubGroupCount(); ++i)
                {
                    s = party->GetSubGroup(i);
                    for(itr = s->GetGroupMembersBegin(); itr != s->GetGroupMembersEnd(); ++itr)
                    {
                        if(_player->GetZoneId() == (*itr)->GetZoneId())
                        {
                            data << (*itr)->GetGUID();
                            ++real_count;
                        }
                    }
                }
                *(uint8*)&data.contents()[0] = real_count;

                party->SendPacketToAll(&data);
            }
/*            //this commented code is not used because it was never tested and finished !
            else if(party->GetMethod() == PARTY_LOOT_RR)
            {
                Creature *target=GetPlayer()->GetMapMgr()->GetCreature(guid); //maybe we should extend this to other object types too
                if(target)
                {
                    if(target->TaggerGuid==GetPlayer()->GetGUID())
                        GetPlayer()->SendLoot(guid,1);
                    else return;
                }
            }*/
        }    
    }
    GetPlayer()->SendLoot(guid,1);
}


void WorldSession::HandleLootReleaseOpcode( WorldPacket & recv_data )
{
    if(!_player->IsInWorld()) return;
    uint64 guid;

    recv_data >> guid;

    WorldPacket data(SMSG_LOOT_RELEASE_RESPONSE, 9);
    data << guid << uint8( 1 );
    SendPacket( &data );

    _player->SetLootGUID(0);
    _player->RemoveFlag(UNIT_FIELD_FLAGS, U_FIELD_ANIMATION_LOOTING);
    _player->m_currentLoot = 0;

    if(UINT32_LOPART(GUID_HIPART(guid)) == HIGHGUID_UNIT)
    {
        Creature* pCreature = _player->GetMapMgr()->GetCreature(guid);
        if(!pCreature)
            return;
        // remove from looter set
        pCreature->loot.looters.erase(_player->GetGUID());
        if(!pCreature->loot.gold)
        {            
            for(std::vector<__LootItem>::iterator i=pCreature->loot.items.begin();i!=pCreature->loot.items.end();i++)
            if(i->iItemsCount)
            {
                ItemPrototype *proto=ItemPrototypeStorage.LookupEntry(i->item.itemid);
                if(proto->Class != 12)
                return;
                if(_player->HasQuestForItem(i->item.itemid))
                return;
            }
            pCreature->BuildFieldUpdatePacket(_player, UNIT_DYNAMIC_FLAGS, 0);

            if(!pCreature->Skinned)
            {
                if(lootmgr.IsSkinnable(pCreature->GetEntry()))
                {
                    pCreature->BuildFieldUpdatePacket(_player, UNIT_FIELD_FLAGS, U_FIELD_FLAG_SKINNABLE);
                }
            }
        }
    }
    else if(UINT32_LOPART(GUID_HIPART(guid)) == HIGHGUID_GAMEOBJECT)
    {       
        GameObject* pGO = _player->GetMapMgr()->GetGameObject(guid);
        if(!pGO)
            return;
        pGO->loot.looters.erase(_player->GetGUID());
        //GO MUST DISAPPEAR AFTER LOOTING,
        //FIX ME: respawn time of GO must be added,15 minutes by default
        //if this is not fishing bobber despawn it
        if(pGO->GetUInt32Value(GAMEOBJECT_TYPE_ID)==GAMEOBJECT_TYPE_FISHINGNODE)
        {
            if(pGO->IsInWorld())
            {
                pGO->RemoveFromWorld();
            }
            delete pGO;
        }
        else
        {
            uint32 DespawnTime = 0;
            if(sQuestMgr.GetGameObjectLootQuest(pGO->GetEntry()))
                DespawnTime = 120000;       // 5 min for quest GO,
            else
            {
                DespawnTime = 900000;       // 15 for else
            }


            pGO->Despawn(DespawnTime);
        }
    }
    else if(UINT32_LOPART(GUID_HIPART(guid)) == HIGHGUID_CORPSE)
    {
        Corpse *pCorpse = objmgr.GetCorpse(guid);
        if(pCorpse) 
            pCorpse->SetUInt32Value(CORPSE_FIELD_DYNAMIC_FLAGS, 0);
    }
    else if(UINT32_LOPART(GUID_HIPART(guid)) == HIGHGUID_PLAYER)
    {
        Player *plr = objmgr.GetPlayer(guid);
        if(plr)
        {
            plr->bShouldHaveLootableOnCorpse = false;
            plr->RemoveFlag(UNIT_DYNAMIC_FLAGS, U_DYN_FLAG_LOOTABLE);
        }
    }
    else if(UINT32_LOPART(GUID_HIPART(guid)))
    {
        // suicide!
        _player->GetItemInterface()->SafeFullRemoveItemByGuid(guid);
    }
}

void WorldSession::HandleWhoOpcode( WorldPacket & recv_data )
{
    uint32 min_level;
    uint32 max_level;
    uint8  unk2;
    uint32 unk3;
    uint32 unk4;
    uint32 zone_count;
    uint32 * zones = 0;
    uint32 name_count;
    string * names = 0;
    string chatname;
    bool cname;
    uint32 i;

    recv_data >> min_level >> max_level;
    recv_data >> chatname >> unk2 >> unk3 >> unk4;
    recv_data >> zone_count;

    if(zone_count > 0 && zone_count < 10)
    {
        zones = new uint32[zone_count];
    
        for(i = 0; i < zone_count; ++i)
            recv_data >> zones[i];
    }
    else
    {
        zone_count = 0;
    }

    recv_data >> name_count;
    if(name_count > 0 && name_count < 10)
    {
        names = new string[name_count];

        for(i = 0; i < name_count; ++i)
            recv_data >> names[i];
    }
    else
    {
        name_count = 0;
    }

    if(chatname.length() > 0)
        cname = true;
    else
        cname = false;

    sLog.outDebug( "WORLD: Recvd CMSG_WHO Message with %u zones and %u names", zone_count, name_count );
    
    bool gm = false;
    uint32 team = _player->GetTeam();
    if(HasGMPermissions())
        gm = true;

    uint32 sent_count = 0;
    uint32 total_count = 0;

    UNORDERED_MAP<uint32, Player*>::const_iterator itr,iend;
    Player * plr;
    uint32 lvl;
    bool add;
    WorldPacket data;
    data.SetOpcode(SMSG_WHO);
    data << uint64(0);

    objmgr._playerslock.AcquireReadLock();
    iend=objmgr._players.end();
    itr=objmgr._players.begin();
    while(itr !=iend && sent_count < 50)
    {
        plr = itr->second;
        ++itr;

        if(!plr->GetSession() || !plr->IsInWorld())
            continue;

        // Team check
        if(!gm && plr->GetTeam() != team && !plr->GetSession()->HasGMPermissions())
            continue;

        ++total_count;

        // Add by default, if we don't have any checks
        add = true;

        // Chat name
        if(cname && chatname != *plr->GetNameString())
            continue;
        
        // Level check
        lvl = plr->m_uint32Values[UNIT_FIELD_LEVEL];
        if(min_level && max_level)
        {
            // skip players outside of level range
            if(lvl < min_level || lvl > max_level)
                continue;
        }

        // Zone id compare
        if(zone_count)
        {
            // people that fail the zone check don't get added
            add = false;
            for(i = 0; i < zone_count; ++i)
            {
                if(zones[i] == plr->GetZoneId())
                {
                    add = true;
                    break;
                }
            }
        }

        // skip players that fail zone check
        if(!add)
            continue;

        // name check
        if(name_count)
        {
            // people that fail name check don't get added
            add = false;
            for(i = 0; i < name_count; ++i)
            {
                if(!strnicmp(names[i].c_str(), plr->GetName(), names[i].length()))
                {
                    add = true;
                    break;
                }
            }
        }

        if(!add)
            continue;

        // if we're here, it means we've passed all testing
        // so add the names :)
        data << plr->GetName();
        if(plr->myGuild)
            data << plr->myGuild->GetGuildName();
        else
            data << uint8(0);       // Guild name

        data << plr->m_uint32Values[UNIT_FIELD_LEVEL];
        data << uint32(plr->getClass());
        data << uint32(plr->getRace());
        data << uint32(plr->GetZoneId());
        ++sent_count;
    }
    objmgr._playerslock.ReleaseReadLock();
    data.wpos(0);
    data << sent_count;
    data << sent_count;

    SendPacket(&data);

    // free up used memory
    if(zones)
        delete [] zones;
    if(names)
        delete [] names;
}

void WorldSession::HandleLogoutRequestOpcode( WorldPacket & recv_data )
{
    WorldPacket data(SMSG_LOGOUT_RESPONSE, 9);

    sLog.outDebug( "WORLD: Recvd CMSG_LOGOUT_REQUEST Message" );

    Player *pPlayer = GetPlayer();
    if(pPlayer)
    {
        if(pPlayer->m_isResting ||      // We are resting so log out instantly
            pPlayer->GetTaxiState() ||  // or we are on a taxi
            HasGMPermissions())           // or we are a gm
        {
            LogoutPlayer(true);
            return;
        }

        if(pPlayer->DuelingWith != NULL || pPlayer->isInCombat())
        {
            //can't quit still dueling or attacking
            data << uint32(0x1); //Filler
            data << uint8(0); //Logout accepted
            SendPacket( &data );
            return;
        }

        data << uint32(0); //Filler
        data << uint8(0); //Logout accepted
        SendPacket( &data );

        //stop player from moving
        pPlayer->SetMovement(MOVE_ROOT,1);

        // Set the "player locked" flag, to prevent movement
        pPlayer->SetFlag( UNIT_FIELD_FLAGS, U_FIELD_FLAG_LOCK_PLAYER );

        //make player sit
        pPlayer->SetStandState(STANDSTATE_SIT);
        SetLogoutTimer(20000);
    }
    /*
    > 0 = You can't Logout Now
    */
}

void WorldSession::HandlePlayerLogoutOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Recvd CMSG_PLAYER_LOGOUT Message" );
    if(!_logoutTime && !HasGMPermissions())
    {
        // send "You do not have permission to use this"
        SendNotification(NOTIFICATION_MESSAGE_NO_PERMISSION);
    } else {
        LogoutPlayer(true);
    }
}

void WorldSession::HandleLogoutCancelOpcode( WorldPacket & recv_data )
{

    sLog.outDebug( "WORLD: Recvd CMSG_LOGOUT_CANCEL Message" );

    Player *pPlayer = GetPlayer();
    if(!pPlayer)
        return;

    //Cancel logout Timer
    SetLogoutTimer(0);

    //tell client about cancel
    OutPacket(SMSG_LOGOUT_CANCEL_ACK);

    //unroot player
    pPlayer->SetMovement(MOVE_UNROOT,5);

    // Remove the "player locked" flag, to allow movement
    pPlayer->RemoveFlag( UNIT_FIELD_FLAGS, U_FIELD_FLAG_LOCK_PLAYER );

    //make player stand
    pPlayer->SetStandState(STANDSTATE_STAND);

    sLog.outDebug( "WORLD: sent SMSG_LOGOUT_CANCEL_ACK Message" );
}

void WorldSession::HandleZoneUpdateOpcode( WorldPacket & recv_data )
{
    uint32 newZone;
    WPAssert(GetPlayer());

    recv_data >> newZone;

    if (GetPlayer()->GetZoneId() == newZone)
        return;

    sWeatherMgr.SendWeather(GetPlayer());
    _player->ZoneUpdate(newZone);

    //clear buyback
    _player->GetItemInterface()->EmptyBuyBack();
}

void WorldSession::HandleSetTargetOpcode( WorldPacket & recv_data )
{
    uint64 guid ;
    recv_data >> guid;

    if( GetPlayer( ) != 0 ){
        GetPlayer( )->SetTarget(guid);
    }

    if(guid == 0 && _player->getAttackTarget())
        _player->setAttackTarget(0);
}

void WorldSession::HandleSetSelectionOpcode( WorldPacket & recv_data )
{
    uint64 guid;
    recv_data >> guid;

    if( GetPlayer( ) != 0 )
        GetPlayer( )->SetSelection(guid);
    else
        return;

    if(_player->m_comboPoints && _player->m_comboTarget != guid)
    { // if its a new Target set Combo Points Target to 0
        _player->ResetComboPoints();
    }

    _player->SetUInt64Value(UNIT_FIELD_TARGET, guid);
    if(guid == 0 && _player->getAttackTarget())
        _player->setAttackTarget(0);
}

void WorldSession::HandleStandStateChangeOpcode( WorldPacket & recv_data )
{
    uint8 animstate;
    recv_data >> animstate;

    _player->SetStandState(animstate);
}

void WorldSession::HandleFriendListOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Received CMSG_FRIEND_LIST"  );

    sSocialMgr.SendFriendList( GetPlayer() );
    sSocialMgr.SendIgnoreList( GetPlayer() );
}

void WorldSession::HandleAddFriendOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Received CMSG_ADD_FRIEND"  );

    std::string friendName = "UNKNOWN";
    recv_data >> friendName;
    
    sSocialMgr.AddFriend( GetPlayer(), friendName );
}

void WorldSession::HandleDelFriendOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Received CMSG_DEL_FRIEND"  );

    uint64 FriendGuid;
    recv_data >> FriendGuid;

    sSocialMgr.DelFriend( GetPlayer(), FriendGuid );
}

void WorldSession::HandleAddIgnoreOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Received CMSG_ADD_IGNORE" );

    std::string ignoreName = "UNKNOWN";
    recv_data >> ignoreName;

    sSocialMgr.AddIgnore( GetPlayer(), ignoreName );
}

void WorldSession::HandleDelIgnoreOpcode( WorldPacket & recv_data )
{
    sLog.outDebug( "WORLD: Received CMSG_DEL_IGNORE" );

    uint64 IgnoreGuid;
    recv_data >> IgnoreGuid;

    sSocialMgr.DelIgnore( GetPlayer(), IgnoreGuid );
}

void WorldSession::HandleBugOpcode( WorldPacket & recv_data )
{
    uint32 suggestion, contentlen;
    std::string content;
    uint32 typelen;
    std::string type;

    recv_data >> suggestion >> contentlen >> content >> typelen >> type;

    if( suggestion == 0 )
        sLog.outDebug( "WORLD: Recieved CMSG_BUG [Bug Report]" );
    else
        sLog.outDebug( "WORLD: Recieved CMSG_BUG [Suggestion]" );

    sLog.outDebug( type.c_str( ) );
    sLog.outDebug( content.c_str( ) );
}

void WorldSession::HandleCorpseReclaimOpcode(WorldPacket &recv_data)
{
    if(_player->isAlive())
        return;

    sLog.outDetail("WORLD: Received CMSG_RECLAIM_CORPSE");

    uint64 guid;
    recv_data >> guid;
    // Check that we're reviving from a corpse, and that corpse is associated with us.
    Corpse * pCorpse = objmgr.GetCorpse(guid);
    if(pCorpse == 0) return;

    if(pCorpse == 0 ||
        pCorpse->GetUInt64Value(CORPSE_FIELD_OWNER) != _player->GetGUID() &&
        pCorpse->GetUInt32Value(CORPSE_FIELD_FLAGS) == 5)
    {
        WorldPacket data(SMSG_RESURRECT_FAILED, 4);
        data << uint32(1);  // this is a real guess!
        SendPacket(&data);

        return;
    }


    GetPlayer()->ResurrectPlayer();
    GetPlayer()->SetUInt32Value(UNIT_FIELD_HEALTH, GetPlayer()->GetUInt32Value(UNIT_FIELD_MAXHEALTH)/2 );
}

void WorldSession::HandleResurrectResponseOpcode(WorldPacket & recv_data)
{
    if(!_player->IsInWorld()) return;
    sLog.outDetail("WORLD: Received CMSG_RESURRECT_RESPONSE");

    if(GetPlayer()->isAlive())
        return;

    uint64 guid;
    uint8 status;
    recv_data >> guid;
    recv_data >> status;

    // need to check guid
    Player * pl = _player->GetMapMgr()->GetPlayer(guid);
    if(!pl)
        pl = objmgr.GetPlayer(guid);
        
    
    if(pl == 0 || status != 1)
    {
        _player->m_resurrectHealth = 0;
        _player->m_resurrectMana = 0;
        return;
    }

    _player->ResurrectPlayer();
    _player->SetMovement(MOVE_UNROOT, 1);
}

void WorldSession::HandleUpdateAccountData(WorldPacket &recv_data)
{
    sLog.outDetail("WORLD: Received CMSG_UPDATE_ACCOUNT_DATA");

    uint32 uiID;
    recv_data >> uiID;

    if(uiID > 8)
    {
        // Shit..
        sLog.outString("WARNING: Accountdata > 8 (%d) was requested to be updated by %s of account %d!", uiID, GetPlayer()->GetName(), this->GetAccountId());
        return;
    }

    uint32 uiDecompressedSize;
    recv_data >> uiDecompressedSize;
    uLongf uid = uiDecompressedSize;

    // client wants to 'erase' current entries
    if(uiDecompressedSize == 0)
    {
        SetAccountData(uiID, NULL, false,0);
        return;
    }

    uint32 RecievedPackedSize = recv_data.size() - 8;
    char* data = new char[uiDecompressedSize+1];

    if(uiDecompressedSize > RecievedPackedSize) // if packed is compressed
    {
        int32 ZlibResult;

        ZlibResult = uncompress((uint8*)data, &uid, recv_data.contents() + 8, RecievedPackedSize);
        
        switch (ZlibResult)
        {
        case Z_OK:                  //0 no error decompression is OK
            SetAccountData(uiID, data, false,uiDecompressedSize);
            sLog.outDetail("WORLD: Successfully decompressed account data %d for %s, and updated storage array.", uiID, GetPlayer()->GetName());
            break;
        
        case Z_ERRNO:               //-1
        case Z_STREAM_ERROR:        //-2
        case Z_DATA_ERROR:          //-3
        case Z_MEM_ERROR:           //-4
        case Z_BUF_ERROR:           //-5
        case Z_VERSION_ERROR:       //-6
        {
            delete [] data;     
            sLog.outString("WORLD WARNING: Decompression of account data %d for %s FAILED.", uiID, GetPlayer()->GetName());
            break;
        }

        default:
            delete [] data;     
            sLog.outString("WORLD WARNING: Decompression gave a unknown error: %x, of account data %d for %s FAILED.", ZlibResult, uiID, GetPlayer()->GetName());
            break;
        }
    }
    else
    {
        memcpy(data,recv_data.contents() + 8,uiDecompressedSize);
        SetAccountData(uiID, data, false,uiDecompressedSize);
    }
}

void WorldSession::HandleRequestAccountData(WorldPacket& recv_data)
{
    sLog.outDetail("WORLD: Received CMSG_REQUEST_ACCOUNT_DATA");

    uint32 id;
    recv_data >> id;
    
    if(id > 8)
    {
        // Shit..
        sLog.outString("WARNING: Accountdata > 8 (%d) was requested by %s of account %d!", id, GetPlayer()->GetName(), this->GetAccountId());
        return;
    }

    AccountDataEntry* res = GetAccountData(id);
        WorldPacket data ;
        data.SetOpcode(SMSG_UPDATE_ACCOUNT_DATA);
        data << id;
    // if red does not exists if ID == 7 and if there is no data send 0
    if (!res || !res->data) // if error, send a NOTHING packet
    {
        data << (uint32)0;
    }
    else
    {
        data << res->sz;
        uLongf destsize;
        if(res->sz>200)
        {
            data.resize( res->sz+800 );  // give us plenty of room to work with..
            
            if ( ( compress(const_cast<uint8*>(data.contents()) + (sizeof(uint32)*2), &destsize, (const uint8*)res->data, res->sz)) != Z_OK)
            {
                sLog.outError("Error while compressing ACCOUNT_DATA");
                return;
            }
            
            data.resize(destsize+8);
        }
        else 
            data.append(    res->data,res->sz);    
    }
        
    SendPacket(&data);    
}

void WorldSession::HandleSetActionButtonOpcode(WorldPacket& recv_data)
{
    sLog.outDebug( "WORLD: Recieved CMSG_SET_ACTION_BUTTON" ); 
    uint8 button, misc, type; 
    uint16 action; 
    recv_data >> button >> action >> misc >> type; 
    sLog.outDebug( "BUTTON: %u ACTION: %u TYPE: %u MISC: %u", button, action, type, misc ); 
    if(action==0)
    {
        sLog.outDebug( "MISC: Remove action from button %u", button ); 
        //remove the action button from the db
        GetPlayer()->setAction(button, 0, 0, 0);
    }
    else
    { 
        if(button >= 120)
            return;

        if(type == 64 || type == 65) 
        {
            sLog.outDebug( "MISC: Added Macro %u into button %u", action, button );
            GetPlayer()->setAction(button,action,misc,type);
        }
        else if(type == 128)
        {
            sLog.outDebug( "MISC: Added Item %u into button %u", action, button );
            GetPlayer()->setAction(button,action,misc,type);
        }
        else if(type == 0)
        {
            sLog.outDebug( "MISC: Added Spell %u into button %u", action, button );
            GetPlayer()->setAction(button,action,type,misc);
        } 
    }
}

void WorldSession::HandleSetWatchedFactionIndexOpcode(WorldPacket &recvPacket)
{
    uint32 factionid;
    recvPacket >> factionid;
    GetPlayer()->SetUInt32Value(PLAYER_FIELD_WATCHED_FACTION_INDEX, factionid);
}

void WorldSession::HandleTogglePVPOpcode(WorldPacket& recv_data)
{
    _player->PvPToggle();
}

void WorldSession::HandleAmmoSetOpcode(WorldPacket & recv_data)
{
    uint32 ammoId;
    recv_data >> ammoId;

    ItemPrototype * xproto=ItemPrototypeStorage.LookupEntry(ammoId);
    if(!xproto)
        return;

    if(xproto->Class != ITEM_CLASS_PROJECTILE || GetPlayer()->GetItemInterface()->GetItemCount(ammoId) == 0)
    {
        sCheatLog.writefromsession(GetPlayer()->GetSession(), "Definately cheating. tried to add %u as ammo.", ammoId);
        GetPlayer()->GetSession()->Disconnect();
        return;
    }

    _player->SetUInt32Value(PLAYER_AMMO_ID, ammoId);
    _player->CalcDamage();
}

#define OPEN_CHEST 11437 
void WorldSession::HandleGameObjectUse(WorldPacket & recv_data)
{
    if(!_player->IsInWorld()) return;
    uint64 guid;
    recv_data >> guid;
    SpellCastTargets targets;
    Spell *spell;
    SpellEntry *spellInfo;
    sLog.outDebug("WORLD: CMSG_GAMEOBJ_USE: [GUID %d]", guid);   

    GameObject *obj = _player->GetMapMgr()->GetGameObject(guid);
    if (!obj) return;
    GameObjectInfo *goinfo= obj->GetInfo();
//    if (!goinfo) return;

    Player *plyr = GetPlayer();
   
    CALL_GO_SCRIPT_EVENT(obj, OnActivate)(_player);
    ScriptSystem->OnGameObjectEvent(obj, _player, GAMEOBJECT_EVENT_ON_USE);

    uint32 type = obj->GetUInt32Value(GAMEOBJECT_TYPE_ID);
    switch (type)
    {
        case GAMEOBJECT_TYPE_CHAIR:
        {
            WorldPacket data(MSG_MOVE_HEARTBEAT, 66);
            data << plyr->GetNewGUID();
            data << uint64(0);
            data << obj->GetPositionX() << obj->GetPositionY() << obj->GetPositionZ() << obj->GetOrientation();
            plyr->SendMessageToSet(&data, true);
            plyr->SetStandState(STANDSTATE_SIT_MEDIUM_CHAIR);
        }break;
    case GAMEOBJECT_TYPE_CHEST://cast da spell
        {
            spellInfo = sSpellStore.LookupEntry( OPEN_CHEST );
            spell = new Spell(plyr, spellInfo, true, NULL);
            _player->m_currentSpell = spell;
            targets.m_unitTarget = obj->GetGUID();
            spell->prepare(&targets); 
        }break;
    case GAMEOBJECT_TYPE_FISHINGNODE:
        {
            obj->UseFishingNode(plyr);
        }break;
    case GAMEOBJECT_TYPE_DOOR:
        {
            // door
            if((obj->GetUInt32Value(GAMEOBJECT_STATE) == 1) && (obj->GetUInt32Value(GAMEOBJECT_FLAGS) == 33))
                obj->EventCloseDoor();
            else
            {
                obj->SetUInt32Value(GAMEOBJECT_FLAGS, 33);
                obj->SetUInt32Value(GAMEOBJECT_STATE, 0);
                sEventMgr.AddEvent(obj,&GameObject::EventCloseDoor,EVENT_GAMEOBJECT_DOOR_CLOSE,20000,1);
            }
        }break;
    case GAMEOBJECT_TYPE_FLAGSTAND:
        {
            // battleground/warsong gulch flag
            // CAPTURE!
            if(plyr->GetCurrentBattleground() != NULL)
            {
                // Send "capture" message to battleground
                plyr->GetCurrentBattleground()->HandleBattlegroundEvent(plyr, obj, BGEVENT_WSG_CAPTURE_FLAG);
            }
        }break;
    case GAMEOBJECT_TYPE_FLAGDROP:
        {
            // Dropped flag
            if(plyr->GetCurrentBattleground() != NULL)
            {            
                // Send "capture" message to battleground
                plyr->GetCurrentBattleground()->HandleBattlegroundEvent(plyr, obj, BGEVENT_WSG_PICKUP_FLAG);
            }
        }break;
    case GAMEOBJECT_TYPE_QUESTGIVER:
        {
            // Questgiver
            if(obj->HasQuests())
            {
                sQuestMgr.OnActivateQuestGiver(obj, plyr);
            }
        }break;
    case GAMEOBJECT_TYPE_SPELLCASTER:
        {
            SpellEntry *info = sSpellStore.LookupEntry(goinfo->SpellFocus);
            if(!info)
                break;
            Spell * spell = new Spell(plyr, info, false, NULL);
            //spell->SpellByOther = true;
            SpellCastTargets targets;
            targets.m_unitTarget = plyr->GetGUID();
            spell->prepare(&targets);
            if(!--obj->charges)
                obj->ExpireAndDelete();
        }break;
    case GAMEOBJECT_TYPE_RITUAL: 
        {
            // store the members in the ritual, cast sacrifice spell, and summon.
            uint32 i = 0;
            if(!obj->m_ritualmembers || !obj->m_ritualspell || !obj->m_ritualcaster /*|| !obj->m_ritualtarget*/)
                return;

            for(i=0;i<goinfo->SpellFocus;i++)
            {
                if(!obj->m_ritualmembers[i])
                {
                    obj->m_ritualmembers[i] = plyr->GetGUIDLow();
                    plyr->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, obj->GetGUID());
                    plyr->SetUInt32Value(UNIT_CHANNEL_SPELL, obj->m_ritualspell);
                    break;
                }else if(obj->m_ritualmembers[i] == plyr->GetGUIDLow()) 
                {
                    // we're deselecting :(
                    obj->m_ritualmembers[i] = 0;
                    plyr->SetUInt32Value(UNIT_CHANNEL_SPELL, 0);
                    plyr->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, 0);
                    return;
                }
            }

            if(i == goinfo->SpellFocus - 1)
            {
                obj->m_ritualspell = 0;
                Player * plr;
                for(i=0;i<goinfo->SpellFocus;i++)
                {
                    plr = _player->GetMapMgr()->GetPlayer(obj->m_ritualmembers[i]);
                    if(plr)
                    {
                        plr->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, 0);
                        plr->SetUInt32Value(UNIT_CHANNEL_SPELL, 0);
                    }
                }
                
                SpellEntry *info = NULL;                
                if(goinfo->ID == 36727) // summon portal
                {
                    if(!obj->m_ritualtarget)
                        return;
                    info = sSpellStore.LookupEntry(goinfo->sound1);
                    if(!info)
                        break;
                    Player * target = _player->GetMapMgr()->GetPlayer(obj->m_ritualtarget);
                    if(!target)
                        return;

                    spell = new Spell(obj,info,true,NULL);
                    SpellCastTargets targets;
                    targets.m_unitTarget = target->GetGUID();
                    spell->prepare(&targets);
                }
                else if(goinfo->ID == 177193) // doom portal
                {
                    Player *psacrifice = NULL;
                    Spell * spell = NULL;
                    
                    // kill the sacrifice player
                    psacrifice = _player->GetMapMgr()->GetPlayer(obj->m_ritualmembers[(int)(rand()%(goinfo->SpellFocus-1))]);
                    Player * pCaster = obj->GetMapMgr()->GetPlayer(obj->m_ritualcaster);
                    if(!psacrifice || !pCaster)
                        return;

                    info = sSpellStore.LookupEntry(goinfo->sound4);
                    if(!info)
                        break;
                    spell = new Spell(psacrifice, info, true, NULL);
                    targets.m_unitTarget = psacrifice->GetGUID();
                    spell->prepare(&targets);
                    
                    // summons demon           
                    info = sSpellStore.LookupEntry(goinfo->sound1);
                    spell = new Spell(pCaster, info, true, NULL);
                    SpellCastTargets targets;
                    targets.m_unitTarget = pCaster->GetGUID();
                    spell->prepare(&targets);                    
                }
                else if(goinfo->ID == 179944)            // Summoning portal for meeting stones
                {
                    Player * plr = _player->GetMapMgr()->GetPlayer(obj->m_ritualtarget);
                    if(!plr)
                        return;

                    Player * pleader = _player->GetMapMgr()->GetPlayer(obj->m_ritualcaster);
                    if(!pleader)
                        return;

                    info = sSpellStore.LookupEntry(goinfo->sound1);
                    Spell * spell = new Spell(pleader, info, true, 0);
                    SpellCastTargets targets(plr->GetGUID());
                    spell->prepare(&targets);

                    /* expire the gameobject */
                    obj->ExpireAndDelete();
                }
            }
        }break;
    case GAMEOBJECT_TYPE_GOOBER:
        {
            //Quest related mostly
        }
    case GAMEOBJECT_TYPE_CAMERA://eye of azora
        {
            WorldPacket pkt(SMSG_TRIGGER_CINEMATIC,4);
            pkt << (uint32)1;//i ve found only on such item,id =1
            SendPacket(&pkt);
        }break;
    case GAMEOBJECT_TYPE_MEETINGSTONE:    // Meeting Stone
        {
            /* Use selection */
            Player * pPlayer = _player->GetMapMgr()->GetPlayer((uint32)_player->GetSelection());
            if(!pPlayer || _player->m_Group != pPlayer->m_Group || !_player->m_Group)
                return;

            GameObjectInfo * info = GameObjectNameStorage.LookupEntry(179944);
            if(!info)
                return;

            /* Create the summoning portal */
            GameObject * pGo = _player->GetMapMgr()->CreateGameObject();
            pGo->CreateFromProto(179944, _player->GetMapId(), _player->GetPositionX(), _player->GetPositionY(), _player->GetPositionZ(), 0);
            pGo->m_ritualcaster = _player->GetGUIDLow();
            pGo->m_ritualtarget = pPlayer->GetGUIDLow();
            pGo->m_ritualspell = 18540;    // meh
            pGo->PushToWorld(_player->GetMapMgr());

            /* member one: the (w00t) caster */
            pGo->m_ritualmembers[0] = _player->GetGUIDLow();
            _player->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, pGo->GetGUID());
            _player->SetUInt32Value(UNIT_CHANNEL_SPELL, pGo->m_ritualspell);
            
            /* expire after 2mins*/
            sEventMgr.AddEvent(pGo, &GameObject::_Expire, EVENT_GAMEOBJECT_EXPIRE, 120000, 1);
        }break;
    }   
}

void WorldSession::HandleTutorialFlag( WorldPacket & recv_data )
{
    uint32 iFlag;
    recv_data >> iFlag;

    uint32 wInt = (iFlag / 32);
    uint32 rInt = (iFlag % 32);

    uint32 tutflag = GetPlayer()->GetTutorialInt( wInt );
    tutflag |= (1 << rInt);
    GetPlayer()->SetTutorialInt( wInt, tutflag );

    sLog.outDebug("Received Tutorial Flag Set {%u}.", iFlag);
}

void WorldSession::HandleTutorialClear( WorldPacket & recv_data )
{
    for ( uint32 iI = 0; iI < 8; iI++)
        GetPlayer()->SetTutorialInt( iI, 0xFFFFFFFF );
}

void WorldSession::HandleTutorialReset( WorldPacket & recv_data )
{
    for ( uint32 iI = 0; iI < 8; iI++)
        GetPlayer()->SetTutorialInt( iI, 0x00000000 );
}

void WorldSession::HandleSetSheathedOpcode( WorldPacket & recv_data )
{
    uint32 active;
    recv_data >> active;
    _player->SetByte(UNIT_FIELD_BYTES_2,0,active); 
}

void WorldSession::HandlePlayedTimeOpcode( WorldPacket & recv_data )
{
    uint32 playedt = (uint32)time(NULL) - _player->m_playedtime[2];
    if(playedt)
    {
        _player->m_playedtime[0] += playedt;
        _player->m_playedtime[1] += playedt;
        _player->m_playedtime[2] += playedt;
    }

    WorldPacket data(SMSG_PLAYED_TIME, 8);
    data << (uint32)_player->m_playedtime[1];
    data << (uint32)_player->m_playedtime[0];
    SendPacket(&data);
}

void WorldSession::HandleSetActionBarTogglesOpcode(WorldPacket &recvPacket)
{
    uint8 cActionBarId;
    recvPacket >> cActionBarId;
    sLog.outDebug("Recieved CMSG_SET_ACTIONBAR_TOGGLES for actionbar id %d.", cActionBarId);
   
    GetPlayer()->SetByte(PLAYER_FIELD_BYTES,2, cActionBarId);
}

// Handlers for acknowledgement opcodes (removes some 'unknown opcode' flood from the logs)
void WorldSession::HandleAcknowledgementOpcodes( WorldPacket & recv_data )
{
   /* uint16 opcode = recv_data.GetOpcode();
    std::stringstream ss;
    ss << "Received ";
    switch( opcode )
    {
    case CMSG_MOVE_FEATHER_FALL_ACK:            ss << "Move_Feather_Fall"; break;
    case CMSG_MOVE_WATER_WALK_ACK:              ss << "Move_Water_Walk"; break;
    case CMSG_MOVE_KNOCK_BACK_ACK:              ss << "Move_Knock_Back"; break;
    case CMSG_MOVE_HOVER_ACK:                   ss << "Move_Hover"; break;
    case CMSG_FORCE_WALK_SPEED_CHANGE_ACK:      ss << "Force_Walk_Speed_Change"; break;
    case CMSG_FORCE_SWIM_SPEED_CHANGE_ACK:      ss << "Force_Swim_Speed_Change"; break;
    case CMSG_FORCE_SWIM_BACK_SPEED_CHANGE_ACK: ss << "Force_Swim_Back_Speed_Change"; break;
    case CMSG_FORCE_TURN_RATE_CHANGE_ACK:       ss << "Force_Turn_Rate_Change"; break;
    case CMSG_FORCE_RUN_SPEED_CHANGE_ACK:       ss << "Force_Run_Speed_Change"; break;
    case CMSG_FORCE_RUN_BACK_SPEED_CHANGE_ACK:  ss << "Force_Run_Back_Speed_Change"; break;
    case CMSG_FORCE_MOVE_ROOT_ACK:              ss << "Force_Move_Root"; break;
    case CMSG_FORCE_MOVE_UNROOT_ACK:            ss << "Force_Move_Unroot"; break;
    default:                                    ss << "Unknown"; break;
    }
    ss << " Acknowledgement. PktSize: " << recv_data.size();
    sLog.outDebug( ss.str().c_str() );*/

    /*uint16 opcode = recv_data.GetOpcode();
    if (opcode == CMSG_FORCE_RUN_SPEED_CHANGE_ACK)
    {
 
        uint64 GUID;
        uint32 Flags, unk0, unk1, d_time;
        float X, Y, Z, O, speed;
        
        recv_data >> GUID;
        recv_data >> unk0 >> Flags;
        if (Flags & (0x2000 | 0x6000))             //0x2000 == jumping  0x6000 == Falling
        {
            uint32 unk2, unk3, unk4, unk5;
            float OldSpeed;

            recv_data >> d_time;
            recv_data >> X >> Y >> Z >> O;
            recv_data >> unk2 >> unk3;                          //no idea, maybe unk2 = flags2
            recv_data >> unk4 >> unk5;                          //no idea
            recv_data >> OldSpeed >> speed;
        }
        else                                                    //single check
        {
            recv_data >> d_time;
            recv_data >> X >> Y >> Z >> O;
            recv_data >> unk1 >> speed;
        }
        
        // if its not good kick player???
        if (_player->GetPlayerSpeed() != speed)
        {
            sLog.outError("SpeedChange player:%s is NOT correct, its set to: %f he seems to be cheating",_player->GetName(), speed);
        }
    }*/

}

void WorldSession::HandleSelfResurrectOpcode(WorldPacket& recv_data)
{
    uint32 self_res_spell = _player->GetUInt32Value(PLAYER_SELF_RES_SPELL);
    if(self_res_spell)
    {
        SpellEntry * sp=sSpellStore.LookupEntry(self_res_spell);
        Spell *s=new Spell(_player,sp,true,NULL);
        SpellCastTargets tgt;
        tgt.m_unitTarget=_player->GetGUID();
        s->prepare(&tgt);    
    }
}

void WorldSession::HandleRandomRollOpcode(WorldPacket &recv_data)
{
    uint32 min, max;
    recv_data >> min >> max;

    sLog.outDetail("WORLD: Received MSG_RANDOM_ROLL: %u-%u", min, max);

    WorldPacket data(20);
    data.SetOpcode(MSG_RANDOM_ROLL);
    data << min << max;

    uint32 roll;

    // generate number
    roll = min + int( ((max-min)+1) * rand() / (RAND_MAX + 1.0) );
    
    // append to packet, and guid
    data << roll << _player->GetGUID();

    // send to set
    if(_player->InGroup())
        _player->GetGroup()->SendPacketToAll(&data);
    else
        GetPlayer()->SendMessageToSet(&data, true, true);
}

void WorldSession::HandleLootMasterGiveOpcode(WorldPacket& recv_data)
{
    if(!_player->IsInWorld()) return;
//    uint8 slot = 0;
    uint32 itemid = 0;
    uint32 amt = 1;
    uint8 error = 0;
    SlotResult slotresult;

    Creature *pCreature = NULL;
    Loot *pLoot = NULL;
    /* struct:
    {CLIENT} Packet: (0x02A3) CMSG_LOOT_MASTER_GIVE PacketSize = 17
    |------------------------------------------------|----------------|
    |00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |0123456789ABCDEF|
    |------------------------------------------------|----------------|
    |39 23 05 00 81 02 27 F0 01 7B FC 02 00 00 00 00 |9#....'..{......|
    |00                                              |.               |
    -------------------------------------------------------------------

        uint64 creatureguid
        uint8  slotid
        uint64 target_playerguid

    */
    uint64 creatureguid, target_playerguid;
    uint8 slotid;
    recv_data >> creatureguid >> slotid >> target_playerguid;

    Player *player = _player->GetMapMgr()->GetPlayer(target_playerguid);
    if(!player)
        return;

    // cheaterz!
    if(_player->GetLootGUID() != creatureguid)
        return;

    //now its time to give the loot to the target player
    if(UINT32_LOPART(GUID_HIPART(GetPlayer()->GetLootGUID())) == HIGHGUID_UNIT)
    {
        pCreature = _player->GetMapMgr()->GetCreature((creatureguid));
        if (!pCreature)return;
        pLoot=&pCreature->loot;    
    }

    if(!pLoot) return;

    if (slotid >= pLoot->items.size())
    {
        sLog.outDebug("AutoLootItem: Player %s might be using a hack! (slot %d, size %d)",
                        GetPlayer()->GetName(), slotid, pLoot->items.size());
        return;
    }

    amt = pLoot->items.at(slotid).iItemsCount;

    if (!amt)//Test for party loot
    {  
        GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL,INV_ERR_ALREADY_LOOTED);
        return;
    } 
    itemid = pLoot->items.at(slotid).item.itemid;
    ItemPrototype* it = ItemPrototypeStorage.LookupEntry(itemid);

    if((error = player->GetItemInterface()->CanReceiveItem(it, 1)))
    {
        _player->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, error);
        return;
    }

    if(pCreature)
        CALL_SCRIPT_EVENT(pCreature, OnLootTaken)(player, it);
    
    
    slotresult = player->GetItemInterface()->FindFreeInventorySlot(it);
    if(!slotresult.Result)
    {
        GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_INVENTORY_FULL);
        return;
    }

    Item *item = objmgr.CreateItem( itemid, player);
    
    item->SetUInt32Value(ITEM_FIELD_STACK_COUNT,amt);
    uint32 rndprop=pLoot->items.at(slotid).iRandomProperty;
    if(rndprop)
        item->SetUInt32Value(ITEM_FIELD_RANDOM_PROPERTIES_ID,rndprop);
    item->ApplyRandomProperties();

    player->GetItemInterface()->SafeAddItem(item,slotresult.ContainerSlot, slotresult.Slot);
    
    if (it->Class == 12)        // Quest item
        sQuestMgr.OnPlayerItemPickup(player,item);

    pLoot->items.at(slotid).iItemsCount=0;

    // this gets sent to all looters
    WorldPacket data(1);
    data.SetOpcode(SMSG_LOOT_REMOVED);
    data << slotid;
    Player * plr;
    for(LooterSet::iterator itr = pLoot->looters.begin(); itr != pLoot->looters.end(); ++itr)
    {
        if((plr = _player->GetMapMgr()->GetPlayer(*itr)))
            plr->GetSession()->SendPacket(&data);
    }

    WorldPacket idata;
    if(it->Class == ITEM_CLASS_QUEST)
    {
        uint32 pcount = player->GetItemInterface()->GetItemCount(it->ItemId, true);
        BuildItemPushResult(&idata, GetPlayer()->GetGUID(), ITEM_PUSH_TYPE_LOOT, amt, itemid, pLoot->items.at(slotid).iRandomProperty,0xFF,0,0xFFFFFFFF,pcount);
    }
    else BuildItemPushResult(&idata, player->GetGUID(), ITEM_PUSH_TYPE_LOOT, amt, itemid, pLoot->items.at(slotid).iRandomProperty);

    if(_player->InGroup())
        _player->GetGroup()->SendPacketToAll(&idata);
    else
        SendPacket(&idata);
}

void WorldSession::HandleLootRollOpcode(WorldPacket& recv_data)
{
    if(!_player->IsInWorld()) return;
    /* struct:
        
        {CLIENT} Packet: (0x02A0) CMSG_LOOT_ROLL PacketSize = 13
        |------------------------------------------------|----------------|
        |00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |0123456789ABCDEF|
        |------------------------------------------------|----------------|
        |11 4D 0B 00 BD 06 01 F0 00 00 00 00 02          |.M...........   |
        -------------------------------------------------------------------

        uint64 creatureguid
        uint21 slotid
        uint8  choice

    */
    uint64 creatureguid;
    uint32 slotid;
    uint8 choice;
    recv_data >> creatureguid >> slotid >> choice;

    Creature *pCreature = _player->GetMapMgr()->GetCreature(creatureguid);
    if(!pCreature)
    {
        return;
    }

    LootRoll *li = NULL;
    if(slotid >= pCreature->loot.items.size() || pCreature->loot.items.size()==0)
    {
        return;
    } else {
        li = pCreature->loot.items[slotid].roll;
    }

    if(!li)
        return;

    li->PlayerRolled(_player, choice);
}

void WorldSession::HandleOpenItemOpcode(WorldPacket &recv_data)
{
    if(!_player->IsInWorld()) return;
    CHECK_PACKET_SIZE(recv_data, 2);
    int8 slot, containerslot;
    recv_data >> containerslot >> slot;

    Item *pItem = _player->GetItemInterface()->GetInventoryItem(containerslot, slot);
    if(!pItem)
        return;

    Lock *lock = sLockStore.LookupEntry( pItem->GetProto()->LockId );
    
    uint32 removeLockItems[5] = {0,0,0,0,0};
    
    if(lock) // locked item
    {
        for(int i=0;i<5;i++)
        {
            if(lock->locktype[i] == 1 && lock->lockmisc[i] > 0)
            {
                int8 slot = _player->GetItemInterface()->GetInventorySlotById(lock->lockmisc[i]);
                if(slot != ITEM_NO_SLOT_AVAILABLE && slot >= INVENTORY_SLOT_ITEM_START && slot < INVENTORY_SLOT_ITEM_END)
                {
                    removeLockItems[i] = lock->lockmisc[i];
                }
                else
                {
                    _player->GetItemInterface()->BuildInventoryChangeError(pItem,NULL,INV_ERR_ITEM_LOCKED);
                    return;
                }
            }
            else if(lock->locktype[i] == 2 && pItem->locked)
            {
                _player->GetItemInterface()->BuildInventoryChangeError(pItem,NULL,INV_ERR_ITEM_LOCKED);
                return;
            }
        }
        for(int i=0;i<5;i++)
            if(removeLockItems[i])
                _player->GetItemInterface()->RemoveItemAmt(removeLockItems[i],1);
    }

    // fill loot
    _player->SetLootGUID(pItem->GetGUID());
    if(!pItem->loot)
    {
        pItem->loot = new Loot;
        lootmgr.FillItemLoot(pItem->loot, pItem->GetEntry());
    }
    _player->SendLoot(pItem->GetGUID(), 5);
}


void WorldSession::HandleCompleteCinematic(WorldPacket &recv_data)
{
    // when a Cinematic is started the player is going to sit down, when its finished its standing up.
    _player->SetStandState(STANDSTATE_STAND);
};

void WorldSession::HandleResetInstanceOpcode(WorldPacket& recv_data)
{
    sInstanceSavingManager.ResetSavedInstancesForPlayer(_player);
}

void EncodeHex(const char* source, char* dest, uint32 size)
{
    char temp[5];
    for(uint32 i = 0; i < size; ++i)
    {
        snprintf(temp, 5, "%02X", source[i]);
        strcat(dest, temp);
    }
}

void DecodeHex(const char* source, char* dest, uint32 size)
{
    char temp;
    char* acc = const_cast<char*>(source);
    for(uint32 i = 0; i < size; ++i)
    {
        sscanf("%02X", &temp);
        acc = ((char*)&source[2]);
        strcat(dest, &temp);
    }
}

void WorldSession::HandleToggleCloakOpcode(WorldPacket &recv_data)
{
    //////////////////////////
    //    PLAYER_FLAGS                                       = 3104 / 0x00C20 / 0000000000000000000110000100000
    //                                                                                             ^ 
    // This bit, on = toggled OFF, off = toggled ON.. :S

    //uint32 SetBit = 0 | (1 << 11);

    if(_player->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_NOCLOAK))
        _player->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_NOCLOAK);
    else
        _player->SetFlag(PLAYER_FLAGS, PLAYER_FLAG_NOCLOAK);
}

void WorldSession::HandleToggleHelmOpcode(WorldPacket &recv_data)
{
    //////////////////////////
    //    PLAYER_FLAGS                                       = 3104 / 0x00C20 / 0000000000000000000110000100000
    //                                                                                              ^ 
    // This bit, on = toggled OFF, off = toggled ON.. :S

    //uint32 SetBit = 0 | (1 << 10);

    if(_player->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_NOHELM))
        _player->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_NOHELM);
    else
        _player->SetFlag(PLAYER_FLAGS, PLAYER_FLAG_NOHELM);
}

void WorldSession::HandleDungeonDifficultyOpcode(WorldPacket& recv_data)
{
    uint32 data;
    recv_data >> data;

    _player->iInstanceType = data;
    sInstanceSavingManager.ResetSavedInstancesForPlayer(_player);
}

void WorldSession::HandleSummonResponseOpcode(WorldPacket & recv_data)
{
    if(!_player->m_summoner)
    {
        SendNotification(NOTIFICATION_MESSAGE_NO_PERMISSION);
        return;
    }

    _player->SafeTeleport(_player->m_summonMapId, _player->m_summonInstanceId, 
        _player->m_summonPos);

    _player->m_summoner = _player->m_summonInstanceId = _player->m_summonMapId = 0;
}

void WorldSession::HandleDismountOpcode(WorldPacket& recv_data)
{
    sLog.outDebug( "WORLD: Received CMSG_DISMOUNT"  );

    if( !_player->IsInWorld() )
        return;

    if( _player->m_MountSpellId )
        _player->RemoveAura( _player->m_MountSpellId );
}

