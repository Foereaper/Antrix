#include "StdAfx.h"

void Auction::DeleteFromDB()
{
	CharacterDatabase.WaitExecute("DELETE FROM auctions WHERE auctionId = %u", Id);
	CharacterDatabase.WaitExecute("DELETE FROM bids WHERE Id = %u", Id);
}

void Auction::SaveToDB(uint32 AuctionHouseId)
{
	CharacterDatabase.Execute("INSERT INTO auctions VALUES(%u, %u, " I64FMTD ", %u, %u, %u, %u, %u, %u)",
		Id, AuctionHouseId, pItem->GetGUID(), Owner, BuyoutPrice, ExpiryTime, HighestBidder, HighestBid,
		DepositAmount);
}

void Auction::UpdateInDB()
{
	CharacterDatabase.Execute("UPDATE auctions SET bidder = %u WHERE auctionId = %u", HighestBidder, Owner);
	CharacterDatabase.Execute("UPDATE auctions SET bid = %u WHERE auctionId = %u", HighestBid, Owner);
}

AuctionHouse::AuctionHouse(uint32 ID)
{
	dbc = sAuctionHouseStore.LookupEntry(ID);
	assert(dbc);

	cut_percent = float( float(dbc->fee) / 100.0f );
	deposit_percent = float( float(dbc->tax ) / 100.0f );
}

AuctionHouse::~AuctionHouse()
{
	UNORDERED_MAP<uint32, Auction*>::iterator itr = auctions.begin();
	for(; itr != auctions.end(); ++itr)
		delete itr->second;
}

void AuctionHouse::QueueDeletion(Auction * auct, uint32 Reason)
{
	if(auct->Deleted)
		return;

	auct->Deleted = true;
	auct->DeletedReason = Reason;
	removalLock.Acquire();
	removalList.push_back(auct);
	removalLock.Release();
}

void AuctionHouse::UpdateDeletionQueue()
{
	removalLock.Acquire();
	Auction * auct;

	list<Auction*>::iterator it = removalList.begin();
	for(; it != removalList.end(); ++it)
	{
		auct = *it;
		assert(auct->Deleted);
		RemoveAuction(auct);
	}

	removalList.clear();
	removalLock.Release();
}

void AuctionHouse::UpdateAuctions()
{
	auctionLock.AcquireReadLock();
	removalLock.Acquire();

	uint32 t = time(NULL);
	UNORDERED_MAP<uint32, Auction*>::iterator itr = auctions.begin();
	Auction * auct;
	for(; itr != auctions.end();)
	{
		auct = itr->second;
		++itr;

		if(t >= auct->ExpiryTime)
		{
			if(auct->HighestBidder == 0)
				auct->DeletedReason = AUCTION_REMOVE_EXPIRED;
			else
				auct->DeletedReason = AUCTION_REMOVE_WON;

			auct->Deleted = true;
			removalList.push_back(auct);
		}
	}

	removalLock.Release();
	auctionLock.ReleaseReadLock();
}

void AuctionHouse::AddAuction(Auction * auct)
{
	// add to the map
	auctionLock.AcquireWriteLock();
	auctions.insert( UNORDERED_MAP<uint32, Auction*>::value_type( auct->Id , auct ) );
	auctionLock.ReleaseWriteLock();

	// add the item
	itemLock.AcquireWriteLock();
	auctionedItems.insert( UNORDERED_MAP<uint64, Item*>::value_type( auct->pItem->GetGUID(), auct->pItem ) );
	itemLock.ReleaseWriteLock();

	sLog.outString("Auction House %u: Adding auction %u, expiry time %u.", dbc->id, auct->Id, auct->ExpiryTime);
}

Auction * AuctionHouse::GetAuction(uint32 Id)
{
	Auction * ret;
	UNORDERED_MAP<uint32, Auction*>::iterator itr;
	auctionLock.AcquireReadLock();
	itr = auctions.find(Id);
	ret = (itr == auctions.end()) ? 0 : itr->second;
	auctionLock.ReleaseReadLock();
	return ret;
}

void AuctionHouse::RemoveAuction(Auction * auct)
{
	sLog.outString("Auction House %u: Removing auction %u because of reason %u.", dbc->id, auct->Id, auct->DeletedReason);

	char subject[100];
	char body[200];
	switch(auct->DeletedReason)
	{
	case AUCTION_REMOVE_EXPIRED:
		{
			// ItemEntry:0:3
			snprintf(subject, 100, "%u:0:3", (unsigned int)auct->pItem->GetEntry());

			// Auction expired, resend item, no money to owner.
			sMailSystem.SendAutomatedMessage(AUCTION, dbc->id, auct->Owner, subject, "", 0, 0, auct->pItem->GetGUID(), 62);
		}break;

	case AUCTION_REMOVE_WON:
		{
			// ItemEntry:0:1
			snprintf(subject, 100, "%u:0:1", (unsigned int)auct->pItem->GetEntry());

			// <owner player guid>:bid:buyout
			snprintf(body, 200, "%X:%u:%u", (unsigned int)auct->Owner, (unsigned int)auct->HighestBid, (unsigned int)auct->BuyoutPrice);

			// Auction won by highest bidder. He gets the item.
			sMailSystem.SendAutomatedMessage(AUCTION, dbc->id, auct->HighestBidder, subject, body, 0, 0, auct->pItem->GetGUID(), 62);

			// Send a mail to the owner with his cut of the price.
			uint32 auction_cut = FL2UINT(float(cut_percent * float(auct->HighestBid)));
			int32 amount = auct->HighestBid - auction_cut + auct->DepositAmount;
			if(amount < 0)
				amount = 0;

			// ItemEntry:0:2
			snprintf(subject, 100, "%u:0:2", (int)auct->pItem->GetEntry());

			// <hex player guid>:bid:0:deposit:cut
			if(auct->HighestBid == auct->BuyoutPrice)	   // Buyout
				snprintf(body, 200, "%X:%u:%u:%u:%u", (unsigned int)auct->HighestBidder, (unsigned int)auct->HighestBid, (unsigned int)auct->BuyoutPrice, (unsigned int)auct->DepositAmount, (unsigned int)auction_cut);
			else
				snprintf(body, 200, "%X:%u:0:%u:%u", (unsigned int)auct->HighestBidder, (unsigned int)auct->HighestBid, (unsigned int)auct->DepositAmount, (unsigned int)auction_cut);

			// send message away.
			sMailSystem.SendAutomatedMessage(AUCTION, dbc->id, auct->Owner, subject, body, amount, 0, 0, 62);
		}break;
	case AUCTION_REMOVE_CANCELLED:
		{
			snprintf(subject, 100, "%u:0:5", (unsigned int)auct->pItem->GetEntry());
			uint32 cut = uint32(float(cut_percent * auct->HighestBid));
			Player * plr = objmgr.GetPlayer(auct->Owner);
			if(cut && plr && plr->GetUInt32Value(PLAYER_FIELD_COINAGE) >= cut)
				plr->ModUInt32Value(PLAYER_FIELD_COINAGE, -((int32)cut));
			
			sMailSystem.SendAutomatedMessage(AUCTION, GetID(), auct->Owner, subject, "", 0, 0, auct->pItem->GetGUID(), 62);
			
			// return bidders money
			if(auct->HighestBidder)
			{
				sMailSystem.SendAutomatedMessage(AUCTION, GetID(), auct->HighestBidder, subject, "", auct->HighestBid, 
					0, 0, 62);
			}
			
		}break;
	}

	// Remove the auction from the hashmap.
	auctionLock.AcquireWriteLock();
	itemLock.AcquireWriteLock();
	
	auctions.erase(auct->Id);
	auctionedItems.erase(auct->pItem->GetGUID());

	auctionLock.ReleaseWriteLock();
	itemLock.ReleaseWriteLock();

	// Destroy the item from memory (it still remains in the db)
	delete auct->pItem;

	// Finally destroy the auction instance.
	auct->DeleteFromDB();
	delete auct;
}

void WorldSession::HandleAuctionListBidderItems( WorldPacket & recv_data )
{
	if(!_player->IsInWorld())
		return;

	uint64 guid;
	recv_data >> guid;

	Creature * pCreature = _player->GetMapMgr()->GetCreature(guid);
	if(!pCreature || !pCreature->auctionHouse)
		return;

	pCreature->auctionHouse->SendBidListPacket(_player, &recv_data);
}

void Auction::AddToPacket(WorldPacket & data)
{
	data << Id;
	data << pItem->GetEntry();

	for (uint32 i = 0; i < 6; i++)
	{
		data << pItem->GetUInt32Value(ITEM_FIELD_ENCHANTMENT + (3 * i));   // Enchantment ID
		data << pItem->GetEnchantmentApplytime(i);						 // Unknown / maybe ApplyTime
		data << pItem->GetUInt32Value(ITEM_FIELD_SPELL_CHARGES + i);	   // Charges
	}

	data << pItem->GetUInt32Value(ITEM_FIELD_RANDOM_PROPERTIES_ID);		 // -ItemRandomSuffix / random property	 : If the value is negative its ItemRandomSuffix if its possitive its RandomItemProperty
	data << uint32(0);													  // when ItemRandomSuffix is used this is the modifier

	/******************** ItemRandomSuffix***************************
	* For what I have seen ItemRandomSuffix is like RandomItemProperty
	* The only difference is has is that it has a modifier.
	* That is the result of jewelcrafting, the effect is that the
	* enchantment is variable. That means that a enchantment can be +1 and 
	* with more Jem's +12 or so.
	* Decription for lookup: You get the enchantmentSuffixID and search the
	* DBC for the last 1 - 3 value's(depending on the enchantment).
	* That value is what I call EnchantmentValue. You guys might find a 
	* better name but for now its good enough. The formula to calculate
	* The ingame "GAIN" is:
	* (Modifier / 10000) * enchantmentvalue = EnchantmentGain;	
	*/
	
	data << pItem->GetUInt32Value(ITEM_FIELD_STACK_COUNT); // Amount
	data << uint32(0);				  // Unknown
	data << uint32(0);				  // Unknown
	data << uint64(Owner);			  // Owner guid
	data << HighestBid;				 // Current prize
	// hehe I know its evil, this creates a nice trough put of money
	data << uint32(50);				 // Next bid value modifier, like current bid + this value
	data << BuyoutPrice;				// Buyout
	data << uint32((ExpiryTime - time(NULL)) * 1000); // Time left
	data << uint64(HighestBidder);	  // Last bidder
	data << HighestBid;				 // The bid of the last bidder
}

void AuctionHouse::SendBidListPacket(Player * plr, WorldPacket * packet)
{
	uint32 count = 0;

	WorldPacket data(SMSG_AUCTION_BIDDER_LIST_RESULT, 1024);
	data << uint32(0);										  // Placeholder

	Auction * auct;
	auctionLock.AcquireReadLock();
	UNORDERED_MAP<uint32, Auction*>::iterator itr = auctions.begin();
	for(; itr != auctions.end(); ++itr)
	{
		auct = itr->second;
		if(auct->HighestBidder == plr->GetGUID())
		{
			if(auct->Deleted) continue;

			auct->AddToPacket(data);
			(*(uint32*)&data.contents()[0])++;
			++count;
		}			
	}
	data << count;
	auctionLock.ReleaseReadLock();
	plr->GetSession()->SendPacket(&data);
}

void AuctionHouse::SendOwnerListPacket(Player * plr, WorldPacket * packet)
{
	uint32 count = 0;

	WorldPacket data(SMSG_AUCTION_OWNER_LIST_RESULT, 1024);
	data << uint32(0);										  // Placeholder

	Auction * auct;
	auctionLock.AcquireReadLock();
	UNORDERED_MAP<uint32, Auction*>::iterator itr = auctions.begin();
	for(; itr != auctions.end(); ++itr)
	{
		auct = itr->second;
		if(auct->Owner == plr->GetGUID())
		{
			if(auct->Deleted) continue;

			auct->AddToPacket(data);
			(*(uint32*)&data.contents()[0])++;
			++count;
		}			
	}
	data << count;
	auctionLock.ReleaseReadLock();
	plr->GetSession()->SendPacket(&data);
}

void AuctionHouse::SendAuctionNotificationPacket(Player * plr, Auction * auct)
{
	WorldPacket data(SMSG_AUCTION_BIDDER_NOTIFICATION, 32);
	data << GetID(); 
	data << auct->Id;
	data << uint64(auct->HighestBidder);
	data << uint32(0);
	data << uint32(0);
	data << auct->pItem->GetEntry();
	data << uint32(0);
	
	plr->GetSession()->SendPacket(&data);
}

void WorldSession::HandleAuctionPlaceBid( WorldPacket & recv_data )
{
	if(!_player->IsInWorld())
		return;

	uint64 guid;
	recv_data >> guid;

	uint32 auction_id, price;
	recv_data >> auction_id >> price;

	Creature * pCreature = _player->GetMapMgr()->GetCreature(guid);
	if(!pCreature || !pCreature->auctionHouse)
		return;

	// Find Item
	AuctionHouse * ah = pCreature->auctionHouse;
	Auction * auct = ah->GetAuction(auction_id);
	if(auct == 0/* || auct->Owner == _player->GetGUID()*/)
		return;

	if(auct->HighestBid > price && price != auct->BuyoutPrice)
		return;

	if(_player->GetUInt32Value(PLAYER_FIELD_COINAGE) < price)
		return;

	_player->ModUInt32Value(PLAYER_FIELD_COINAGE, -((int32)price));
	if(auct->HighestBidder != 0)
	{
		// Return the money to the last highest bidder.
		char subject[100];
		snprintf(subject, 100, "%u:0:0", (int)auct->pItem->GetEntry());
		sMailSystem.SendAutomatedMessage(AUCTION, ah->GetID(), auct->HighestBidder, subject, "", auct->HighestBid,
			0, 0, 62);
	}

	if(auct->BuyoutPrice == price)
	{
		auct->HighestBidder = _player->GetGUID();
		auct->HighestBid = price;

		// we used buyout on the item.
		ah->QueueDeletion(auct, AUCTION_REMOVE_WON);

		// send response packet
		WorldPacket data(SMSG_AUCTION_COMMAND_RESULT, 12);
		data << auct->Id << uint32(AUCTION_BID) << uint32(0) << uint32(0);
		SendPacket(&data);
	}
	else
	{
		// update most recent bid
		auct->HighestBidder = _player->GetGUID();
		auct->HighestBid = price;
		auct->UpdateInDB();

		// send response packet
		WorldPacket data(SMSG_AUCTION_COMMAND_RESULT, 12);
		data << auct->Id << uint32(AUCTION_BID) << uint32(0);
		SendPacket(&data);
	}
}

void WorldSession::HandleCancelAuction( WorldPacket & recv_data)
{
	if(!_player->IsInWorld())
		return;

	uint64 guid;
	recv_data >> guid;

	uint32 auction_id;
	recv_data >> auction_id;

	Creature * pCreature = _player->GetMapMgr()->GetCreature(guid);
	if(!pCreature || !pCreature->auctionHouse)
		return;

	// Find Item
	Auction * auct = pCreature->auctionHouse->GetAuction(auction_id);
	if(auct == 0) return;

	pCreature->auctionHouse->QueueDeletion(auct, AUCTION_REMOVE_CANCELLED);

	// Send response packet.
	WorldPacket data(SMSG_AUCTION_COMMAND_RESULT, 8);
	data << auction_id << uint32(AUCTION_CANCEL) << uint32(0);
	SendPacket(&data);

	// Re-send the owner list.
	pCreature->auctionHouse->SendOwnerListPacket(_player, 0);
}

void WorldSession::HandleAuctionSellItem( WorldPacket & recv_data )
{
	if(!_player->IsInWorld())
		return;

	uint64 guid;
	uint64 item;
	uint32 bid,buyout,etime;
	recv_data >> guid;
	recv_data >> item;
	recv_data >> bid >> buyout >> etime;

	Creature * pCreature = _player->GetMapMgr()->GetCreature(guid);
	if(!pCreature || !pCreature->auctionHouse)
		return;

	// Find Item
	AuctionHouse * ah = pCreature->auctionHouse;
	Item * pItem = _player->GetItemInterface()->SafeRemoveAndRetreiveItemByGuid(item, false);
	if(!pItem)
		return;

	// Re-save item without its owner.
	pItem->RemoveFromWorld();
	pItem->SetOwner(0);
	pItem->SaveToDB(INVENTORY_SLOT_NOT_SET, 0);

	// Create auction structure.
	Auction * auct = new Auction;
	auct->BuyoutPrice = buyout;
	auct->ExpiryTime = time(NULL) + (etime * 60);
	auct->HighestBid = bid;
	auct->HighestBidder = 0;
	auct->Id = sAuctionMgr.GenerateAuctionId();
	auct->Owner = _player->GetGUID();
	auct->pItem = pItem;
	auct->Deleted = false;
	auct->DeletedReason = 0;
	
	// calculate deposit
	uint32 item_worth = pItem->GetProto()->SellPrice * pItem->GetUInt32Value(ITEM_FIELD_STACK_COUNT);
	auct->DepositAmount = FL2UINT(float(float(float(item_worth) * ah->deposit_percent) * float(float(etime) / 120.0f)));

	// Add to the auction house.
	ah->AddAuction(auct);
	auct->SaveToDB(ah->GetID());

	// Send result packet.
	WorldPacket data(SMSG_AUCTION_COMMAND_RESULT, 8);
	data << auct->Id;
	data << uint32(AUCTION_CREATE);
	data << uint32(0);
	SendPacket(&data);
}

void WorldSession::HandleAuctionListOwnerItems( WorldPacket & recv_data )
{
	if(!_player->IsInWorld())
		return;

	uint64 guid;
	recv_data >> guid;

	Creature * pCreature = _player->GetMapMgr()->GetCreature(guid);
	if(!pCreature || !pCreature->auctionHouse)
		return;

	pCreature->auctionHouse->SendOwnerListPacket(_player, &recv_data);
}

void AuctionHouse::SendAuctionList(Player * plr, WorldPacket * packet)
{
	uint32 start_index, current_index = 0;
	uint32 counted_items = 0;
	std::string auctionString;
	uint8 levelRange1, levelRange2, usableCheck;
	int32 inventory_type, itemclass, itemsubclass, rarityCheck;

	*packet >> start_index;
	*packet >> auctionString;
	*packet >> levelRange1 >> levelRange2;
	*packet >> inventory_type >> itemclass >> itemsubclass;
	*packet >> rarityCheck >> usableCheck;

	// convert auction string to lowercase for faster parsing.
	if(auctionString.length() > 0)
	{
		for(uint32 j = 0; j < auctionString.length(); ++j)
			auctionString[j] = tolower(auctionString[j]);
	}

	WorldPacket data(SMSG_AUCTION_LIST_RESULT, 7000);
	data << uint32(0);

	auctionLock.AcquireReadLock();
	UNORDERED_MAP<uint32, Auction*>::iterator itr = auctions.begin();
	ItemPrototype * proto;
	for(; itr != auctions.end(); ++itr)
	{
		if(itr->second->Deleted) continue;
		proto = itr->second->pItem->GetProto();

		// Page system.
		current_index++;
		if(start_index && current_index < start_index) continue;
		++counted_items;
		if(counted_items > 50)
			continue;

		// Check the auction for parameters

		// inventory type
		if(inventory_type != -1 && inventory_type != (int32)proto->InventoryType)
			continue;

		// class
		if(itemclass != -1 && itemclass != (int32)proto->Class)
			continue;

		// subclass
		if(itemsubclass != -1 && itemsubclass != (int32)proto->SubClass)
			continue;

		// this is going to hurt. - name
		if(auctionString.length() > 0 && !FindXinYString(auctionString, proto->lowercase_name))
			continue;

		// rarity
		if(rarityCheck != -1 && rarityCheck != (int32)proto->Quality)
			continue;

		// level range check - lower boundary
		if(levelRange1 && proto->ItemLevel < levelRange1)
			continue;

		// level range check - high boundary
		if(levelRange2 && proto->ItemLevel > levelRange2)
			continue;

		// usable check - this will hurt too :(
		if(usableCheck)
		{
			// allowed class
			if(proto->AllowableClass && !(plr->getClassMask() & proto->AllowableClass))
				continue;

			if(proto->RequiredLevel && proto->RequiredLevel > plr->getLevel())
				continue;

			if(proto->AllowableRace && !(plr->getRaceMask() & proto->AllowableRace))
				continue;

			if(proto->Class == 4 && proto->SubClass && !(plr->GetArmorProficiency()&(((uint32)(1))<<proto->SubClass)))
				continue;
			
			if(proto->Class == 2 && proto->SubClass && !(plr->GetWeaponProficiency()&(((uint32)(1))<<proto->SubClass)))
				continue;
		}

		// all checks passed -> add to packet.
		itr->second->AddToPacket(data);
		(*(uint32*)&data.contents()[0])++;
	}
	
	// total count
	data << uint32(start_index + counted_items);

	auctionLock.ReleaseReadLock();
	plr->GetSession()->SendPacket(&data);
}

void WorldSession::HandleAuctionListItems( WorldPacket & recv_data )
{
	uint64 guid;
	recv_data >> guid;

	Creature * pCreature = _player->GetMapMgr()->GetCreature(guid);
	if(!pCreature || !pCreature->auctionHouse)
		return;

	pCreature->auctionHouse->SendAuctionList(_player, &recv_data);
}

void AuctionHouse::LoadAuctions()
{
	QueryResult *result = CharacterDatabase.Query("SELECT * FROM auctions WHERE auctionhouse =%u", GetID());

	if( !result )
		return;

	Auction * auct;
	Field * fields;
	do
	{
		fields = result->Fetch();
		auct = new Auction;
		auct->Id = fields++->GetUInt32();
		fields++;
		
		Item * pItem = objmgr.LoadItem(fields++->GetUInt64());
		if(!pItem)
		{
			delete auct;
			continue;
		}
		auct->pItem = pItem;
		auct->Owner = fields++->GetUInt32();
		auct->BuyoutPrice = fields++->GetUInt32();
		auct->ExpiryTime = fields++->GetUInt32();
		auct->HighestBidder = fields++->GetUInt32();
		auct->HighestBid = fields++->GetUInt32();
		auct->DepositAmount = fields++->GetUInt32();
		auct->DeletedReason = 0;
		auct->Deleted = false;

		auctions.insert( UNORDERED_MAP<uint32, Auction*>::value_type( auct->Id, auct ) );
	} while (result->NextRow());
	delete result;
}
