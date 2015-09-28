/****************************************************************************
 *
 * General Packet Handler File
 *
 */

#include "StdAfx.h"

//////////////////////////////////////////////////////////////
/// This function handles CMSG_NAME_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleNameQueryOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE(recv_data, 8);
	WorldPacket data;
	uint64 guid;

	recv_data >> guid;

	PlayerInfo *pn = objmgr.GetPlayerInfo( guid );

	if(!pn)
		return;

	sLog.outDebug( "Recieved CMSG_NAME_QUERY for: %s", pn->name.c_str() );

	data.Initialize( SMSG_NAME_QUERY_RESPONSE );

	data << pn->guid;
	data << pn->name;
	
	data << uint8(0);	   // this probably is "different realm" or something flag.
	
	data << pn->race << pn->gender << pn->cl;

	SendPacket( &data );
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_QUERY_TIME:
//////////////////////////////////////////////////////////////
void WorldSession::HandleQueryTimeOpcode( WorldPacket & recv_data )
{
	uint32 t = time(NULL);
	OutPacket(SMSG_QUERY_TIME_RESPONSE, 4, &t);
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_CREATURE_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleCreatureQueryOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE(recv_data, 12);
	WorldPacket data(SMSG_CREATURE_QUERY_RESPONSE, 150);
	uint32 entry;
	uint64 guid;
	CreatureInfo *ci;

	recv_data >> entry;
	recv_data >> guid;

	if(entry == 300000)
	{
		data << (uint32)entry;
		data << "WayPoint";
		data << uint8(0) << uint8(0) << uint8(0);
		data << "Level is WayPoint ID";
		for(uint32 i = 0; i < 8;i++)
		{
			data << uint32(0);
		}
		data << uint8(0);  
	}
	else
	{
		ci = CreatureNameStorage.LookupEntry(entry);
		if(ci == NULL)
			return;
		sLog.outDetail("WORLD: CMSG_CREATURE_QUERY '%s'", ci->Name);

		data << (uint32)entry;
		data << ci->Name;
		data << uint8(0) << uint8(0) << uint8(0);
		data << ci->SubName;
		data << ci->Flags1;  
		data << ci->Type;
		data << ci->Family;
		data << ci->Rank;
		data << ci->Unknown1;
		data << ci->SpellDataID;
		data << ci->DisplayID;
		data << ci->unk2;
		data << ci->unk3;
		data << ci->Civilian;
		data << ci->Leader;
		
	}

	SendPacket( &data );
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_GAMEOBJECT_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleGameObjectQueryOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE(recv_data, 12);
	WorldPacket data(SMSG_GAMEOBJECT_QUERY_RESPONSE, 300);

	uint32 entryID;
	uint64 guid;
	GameObjectInfo *goinfo;

	recv_data >> entryID;
	recv_data >> guid;

	sLog.outDetail("WORLD: CMSG_GAMEOBJECT_QUERY '%u'", entryID);

	goinfo = GameObjectNameStorage.LookupEntry(entryID);
	if(goinfo == 0)
		return;

	data << entryID;
	data << goinfo->Type;
	data << goinfo->DisplayID;
	data << goinfo->Name;
	data << uint8(0) << uint8(0) << uint8(0) << uint8(0) << uint8(0) << uint8(0);   // new string in 1.12
	data << goinfo->SpellFocus;
	data << goinfo->sound1;
	data << goinfo->sound2;
	data << goinfo->sound3;
	data << goinfo->sound4;
	data << goinfo->sound5;
	data << goinfo->sound6;
	data << goinfo->sound7;
	data << goinfo->sound8;
	data << goinfo->sound9;
	data << goinfo->Unknown1;
	data << goinfo->Unknown2;
	data << goinfo->Unknown3;
	data << goinfo->Unknown4;
	data << goinfo->Unknown5;
	data << goinfo->Unknown6;
	data << goinfo->Unknown7;
	data << goinfo->Unknown8;
	data << goinfo->Unknown9;
	data << goinfo->Unknown10;
	data << goinfo->Unknown11;
	data << goinfo->Unknown12;
	data << goinfo->Unknown13;
	data << goinfo->Unknown14;

	SendPacket( &data );
}

//////////////////////////////////////////////////////////////
/// This function handles MSG_CORPSE_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleCorpseQueryOpcode(WorldPacket &recv_data)
{
	sLog.outDetail("WORLD: Received MSG_CORPSE_QUERY");

	Corpse *pCorpse;
	WorldPacket data(MSG_CORPSE_QUERY, 21);
	MapInfo *pMapinfo;

	pCorpse = objmgr.GetCorpseByOwner(GetPlayer()->GetGUIDLow());
	if(pCorpse)
	{
		pMapinfo = WorldMapInfoStorage.LookupEntry(pCorpse->GetMapId());
		if(pMapinfo)
		{
			if(pMapinfo->type == INSTANCE_NULL || pMapinfo->type == INSTANCE_PVP)
			{
				data << uint8(0x01); //show ?
				data << pCorpse->GetMapId(); // mapid (that tombstones shown on)
				data << pCorpse->GetPositionX();
				data << pCorpse->GetPositionY();
				data << pCorpse->GetPositionZ();
				data << pCorpse->GetMapId(); //instance mapid (needs to be same as mapid to be able to recover corpse)
				SendPacket(&data);
			}
			else
			{
				data << uint8(0x01); //show ?
				data << pMapinfo->repopmapid; // mapid (that tombstones shown on)
				data << pMapinfo->repopx;
				data << pMapinfo->repopy;
				data << pMapinfo->repopz;
				data << pCorpse->GetMapId(); //instance mapid (needs to be same as mapid to be able to recover corpse)
				SendPacket(&data);
			}
		}
		else
		{

			data.Initialize(MSG_CORPSE_QUERY);
			data << uint8(0x01); //show ?
			data << pCorpse->GetMapId(); // mapid (that tombstones shown on)
			data << pCorpse->GetPositionX();
			data << pCorpse->GetPositionY();
			data << pCorpse->GetPositionZ();
			data << pCorpse->GetMapId(); //instance mapid (needs to be same as mapid to be able to recover corpse)
			SendPacket(&data);

		}
	}
}

void WorldSession::HandlePageTextQueryOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE(recv_data, 4);
	uint32 pageid = 0;
	recv_data >> pageid;
	ItemPage * page = ItemPageStorage.LookupEntry(pageid);
	if(!page)
		return;

	WorldPacket data(SMSG_PAGE_TEXT_QUERY_RESPONSE, 1000);
	data << pageid;
	data << page->text;
	data << page->next_page;
	SendPacket(&data);
	/*ItemPage* page = NULL;
	while(pageid)
	{
		page = ItemPageStorage.LookupEntry(pageid);
		if(page == NULL) 
			break;
		data << pageid;
		data << page->text;
		data << page->next_page;
		pageid = page->next_page;
		SendPacket(&data);
	}*/
}
//////////////////////////////////////////////////////////////
/// This function handles CMSG_ITEM_NAME_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleItemNameQueryOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE(recv_data, 4);
	WorldPacket reply(SMSG_ITEM_NAME_QUERY_RESPONSE, 100);
	uint32 itemid;
	recv_data >> itemid;
	reply << itemid;
	ItemPrototype *proto=ItemPrototypeStorage.LookupEntry(itemid);
	if(!proto)
		reply << "Unknown Item";
	else
		reply << proto->Name1;
	SendPacket(&reply);	
}
