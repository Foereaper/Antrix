/****************************************************************************
 *
 * General Object Type File
 *
 */

/////////////////////////////////////////////////
//  Normal User Chat Commands
//

#include "StdAfx.h"


bool ChatHandler::ShowHelpForCommand(WorldSession *m_session, ChatCommand *table, const char* cmd)
{
	for(uint32 i = 0; table[i].Name != NULL; i++)
	{
		if(!hasStringAbbr(table[i].Name, cmd))
			continue;

		if(m_session->CanUseCommand(table[i].CommandGroup))
			continue;

		if(table[i].ChildCommands != NULL)
		{
			cmd = strtok(NULL, " ");
			if(cmd && ShowHelpForCommand(m_session, table[i].ChildCommands, cmd))
				return true;
		}

		if(table[i].Help == "")
		{
			SystemMessage(m_session, "There is no help for that command");
			return true;
		}

		SendMultilineMessage(m_session, table[i].Help.c_str());

		return true;
	}

	return false;
}

bool ChatHandler::HandleHelpCommand(const char* args, WorldSession *m_session)
{
//	ChatCommand *table = getCommandTable();
	WorldPacket data;

	if(!*args)
		return false;

	char* cmd = strtok((char*)args, " ");
	if(!cmd)
		return false;

	if(!ShowHelpForCommand(m_session, CommandTableStorage::getSingleton().Get(), cmd))
	{
		RedSystemMessage(m_session, "Sorry, no help was found for this command, or that command does not exist.");
	}

	return true;
}


bool ChatHandler::HandleCommandsCommand(const char* args, WorldSession *m_session)
{
	ChatCommand *table = CommandTableStorage::getSingleton().Get();
	WorldPacket data;

	std::string output;
	uint32 count = 0;

	output = "Available commands: \n\n";

	for(uint32 i = 0; table[i].Name != NULL; i++)
	{
		if(*args && !hasStringAbbr(table[i].Name, (char*)args))
			continue;

		if(!m_session->CanUseCommand(table[i].CommandGroup))
			continue;

		switch(table[i].CommandGroup)
		{
		case 'z':
			{
				output+="|cffff6060";
				output+=table[i].Name;
				output+="|r, ";
			}
			break;
		case 'm':
			{
				output+="|cff00ffff";
				output+=table[i].Name;
				output+=", ";
			}
			break;
		case 'c':
			{
				output += "|cff00ff00";
				output += table[i].Name;
				output += "|r, ";
			}break;
		default:
			{
				output+="|cff00ccff";
				output+=table[i].Name;
				output+="|r, ";
			}
			break;
		}

		count++;
		if(count == 5)  // 5 per line
		{
			output += "\n";
			count = 0;
		}
	}
	if(count)
		output += "\n";


		//FillSystemMessageData(&data, table[i].Name);
		//m_session->SendPacket(&data);
	//}

	SendMultilineMessage(m_session, output.c_str());

	return true;
}

bool ChatHandler::HandleStartCommand(const char* args, WorldSession *m_session)
{
	std::string race;
	uint32 raceid = 0;

	Player *m_plyr = getSelectedChar(m_session, false);

	if (m_plyr && args && strlen(args) < 2)
	{
		raceid = m_plyr->getRace();
		switch (raceid)
		{
		case 1:
			race = "human";
		break;
		case 2:
			race = "orc";
		break;
		case 3:
			race = "dwarf";
		break;
		case 4:
			race = "nightelf";
		break;
		case 5:
			race = "undead";
		break;
		case 6:
			race = "tauren";
		break;
		case 7:
			race = "gnome";
		break;
		case 8:
			race = "troll";
		break;
		case 10:
			race = "bloodelf";
		break;
		case 11:
			race = "draenei";
		break;
		default:
			return false;
		break;
		}
	}
	else if (m_plyr && args && strlen(args) > 2)
	{
		race = args;
		#ifdef WIN32
			
			transform(race.begin(), race.end(), race.begin(), tolower);
		#else
			race = "";
			for (uint32 i = 0; i < race.size(); i++)
			{
				race.push_back(tolower(args[i]));
			}
		#endif

		// Teleport to specific race
		if(race == "human")
			raceid = 1;
		else if(race == "orc")
			raceid = 2;
		else if(race == "dwarf")
			raceid = 3;
		else if(race == "nightelf")
			raceid = 4;
		else if(race == "undead")
			raceid = 5;
		else if(race == "tauren")
			raceid = 6;
		else if(race == "gnome")
			raceid = 7;
		else if(race == "troll")
			raceid = 8;
		else if(race == "bloodelf")
			raceid = 10;
		else if(race == "draenei")
			raceid = 11;
		else
		{
			RedSystemMessage(m_session, "Invalid start location! Valid locations are: human, dwarf, gnome, nightelf, draenei, orc, troll, tauren, undead, bloodelf");
			return true;
		}
	}
	else
	{
		return false;
	}

	// Try to find a class that works
	PlayerCreateInfo *info = NULL;
	for(uint32 i=1;i<11;i++)
	{
		 info = objmgr.GetPlayerCreateInfo(raceid, i);
		 if(info != NULL) break;
	}
	
	if(info == NULL)
	{
		RedSystemMessage(m_session, "Internal error: Could not find create info.");
		return false;
	}


	GreenSystemMessage(m_session, "Telporting %s to %s starting location.", m_plyr->GetName(), race.c_str());

	m_session->GetPlayer()->SafeTeleport(info->mapId, 0, LocationVector(info->positionX, info->positionY, info->positionZ));
	return true;
}


bool ChatHandler::HandleInfoCommand(const char* args, WorldSession *m_session)
{
	WorldPacket data;

	
	uint32 clientsNum = sWorld.GetSessionCount();

	int gm = 0;
	int count = 0;
	int avg = 0;
	UNORDERED_MAP<uint32, Player*>::const_iterator itr;
	objmgr._playerslock.AcquireReadLock();
	for (itr = objmgr._players.begin(); itr != objmgr._players.end(); itr++)
	{
		if(itr->second->GetSession())
		{
			count++;
			avg += itr->second->GetSession()->GetLatency();
			if(itr->second->GetSession()->GetPermissionCount())
				gm++;
		}			
	}
	objmgr._playerslock.ReleaseReadLock();
	GreenSystemMessage(m_session, "Server Uptime: |r%s", sWorld.GetUptimeString().c_str());
	GreenSystemMessage(m_session, "Current Players: |r%d (%d GMs, %d queued)", clientsNum, gm,  0);
	GreenSystemMessage(m_session, "Thread Count: |r%u", sThreadMgr.GetThreadCount());
	GreenSystemMessage(m_session, "Average Latency: |r%.3fms", (float)((float)avg / (float)count));
	GreenSystemMessage(m_session, "SQL Query Cache Size (World): |r%u queries delayed", ((MySQLDatabase*)Database_World)->GetQueueSize());
	GreenSystemMessage(m_session, "SQL Query Cache Size (Character): |r%u queries delayed", ((MySQLDatabase*)Database_Character)->GetQueueSize());

	return true;
}


bool ChatHandler::HandleNYICommand(const char* args, WorldSession *m_session)
{
	RedSystemMessage(m_session, "Not yet implemented.");
	return true;
}

bool ChatHandler::HandleDismountCommand(const char* args, WorldSession *m_session)
{
	Unit *m_target = NULL;
	Player *m_plyr = getSelectedChar(m_session, false);
	if(m_plyr)
		m_target = m_plyr;
	else
	{
		Creature *m_crt = getSelectedCreature(m_session, false);
		if(m_crt)
			m_target = m_crt;
	}

	if(!m_target)
	{
		RedSystemMessage(m_session, "No target found.");
		return true;
	}

	if(m_target->GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID) == 0)
	{
		RedSystemMessage(m_session, "Target is not mounted.");
		return true;
	}

	m_target->SetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID , 0);
	if(m_target->HasFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_MOUNT_SIT)) m_target->RemoveFlag( UNIT_FIELD_FLAGS , U_FIELD_FLAG_MOUNT_SIT );

	BlueSystemMessage(m_session, "Now unmounted.");
	return true;
}


bool ChatHandler::HandleSaveCommand(const char* args, WorldSession *m_session)
{
	WorldPacket data;
	if(m_session->GetPlayer()->m_nextSave < 300000 || m_session->CanUseCommand('s')) //5min out of 10 left so 5 min since last save
	{
		m_session->GetPlayer()->SaveToDB(false);
		GreenSystemMessage(m_session, "Player saved to DB");
	}
	else
	{
		RedSystemMessage(m_session, "You can only save once every 5 minutes.");
	}
	m_session->SendPacket( &data );
	return true;
}


bool ChatHandler::HandleGMListCommand(const char* args, WorldSession *m_session)
{
	WorldPacket data;
	bool first = true;

	UNORDERED_MAP<uint32, Player*>::const_iterator itr;
	objmgr._playerslock.AcquireReadLock();
	for (itr = objmgr._players.begin(); itr != objmgr._players.end(); itr++)
	{
		if(itr->second->GetSession()->GetPermissionCount())
		{
			if(first)
				GreenSystemMessage(m_session, "There are following active GMs on this server:");

			SystemMessage(m_session, "%s [%s]", itr->second->GetName(), itr->second->GetSession()->GetPermissions());

			first = false;
		}
	}
	objmgr._playerslock.ReleaseReadLock();

	if(first)
		SystemMessage(m_session, "There are no GMs currently logged in on this server.");

	return true;
}
