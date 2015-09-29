/****************************************************************************
 *
 * General Object Type File
 *
 */

//
// WorldSession.cpp
//

#include "StdAfx.h"

#define WORLDSOCKET_TIMEOUT		 80

bool MapSessionFilter::Process(WorldPacket* packet)
{
    OpcodeHandler const& opHandle = opcodeTable[packet->GetOpcode()];

    //let's check if our opcode can be really processed in Map::Update()
    if (opHandle.packetProcessing == PROCESS_INPLACE)
        return true;

    //we do not process thread-unsafe packets
    if (opHandle.packetProcessing == PROCESS_THREADUNSAFE)
        return false;

    Player* player = m_pSession->GetPlayer();
    if (!player)
        return false;

    //in Map::Update() we do not process packets where player is not in world!
    return player->IsInWorld();
}

//we should process ALL packets when player is not in world/logged in
//OR packet handler is not thread-safe!
bool WorldSessionFilter::Process(WorldPacket* packet)
{
    OpcodeHandler const& opHandle = opcodeTable[packet->GetOpcode()];
    //check if packet handler is supposed to be safe
    if (opHandle.packetProcessing == PROCESS_INPLACE)
        return true;

    //thread-unsafe packets should be processed in World::UpdateSessions()
    if (opHandle.packetProcessing == PROCESS_THREADUNSAFE)
        return true;

    //no player attached? -> our client! ^^
    Player* player = m_pSession->GetPlayer();
    if (!player)
        return true;

    //lets process all packets for non-in-the-world player
    return (player->IsInWorld() == false);
}

WorldSession::WorldSession(uint32 id, string Name, WorldSocket *sock) : _player(0), _socket(sock), _accountId(id), _accountName(Name),
_logoutTime(0), permissions(NULL), permissioncount(0), m_playerLogout(false), m_playerRecentlyLoggedOut(false), instanceId(0), packetThrottleTimeout(0), packetThrottleCount(0)
{
	memset(movement_packet, 0, sizeof(movement_packet));
	m_currMsTime = getMSTime();
	bDeleted = false;
	m_bIsWLevelSet = false;
	floodLines = 0;
	floodTime = World::UNIXTIME;

	for(uint32 x=0;x<8;x++)
		sAccountData[x].data=NULL;	
}

WorldSession::~WorldSession()
{
	deleteMutex.Acquire();

	if(HasFlag(ACCOUNT_FLAG_XTEND_INFO))
		sWorld.RemoveExtendedSession(this);

	if(HasGMPermissions())
		sWorld.gmList.erase(this);

	if(_player)
	{
		sLog.outError("warning: logged out player in worldsession destructor");
		LogoutPlayer(true);
	}

	if(permissions)
		delete [] permissions;

	WorldPacket *packet;

	while((packet = _recvQueue.Pop()))
		delete packet;

	while((packet = _throttledQueue.Pop()))
		delete packet;

	for(uint32 x=0;x<8;x++)
	{
		if(sAccountData[x].data)
			delete [] sAccountData[x].data;
	}

#ifndef CLUSTERING
	if(_socket)
		_socket->SetSession(0);
#endif

	deleteMutex.Release();
}

int WorldSession::Update(uint32 InstanceID, PacketFilter& updater)
{
    m_currMsTime = getMSTime();
    WorldPacket* packet = nullptr;

	if(InstanceID != instanceId)
	{
		// We're being updated by the wrong thread.
		// "Remove us!" - 2
		return 2;
	}

	// Socket disconnection.
	if(!_socket)
	{
		// Check if the player is in the process of being moved. We can't delete him
		// if we are.
		if(_player && _player->m_beingPushed)
		{
			// Abort..
			return 0;
		}

		bDeleted = true;
		LogoutPlayer(true);
		// 1 - Delete session completely.
		return 1;
	}

	while ((packet = _recvQueue.Pop()))
	{
        OpcodeHandler const& opcodeHandler = opcodeTable[packet->GetOpcode()];
		if (packet->GetOpcode() >= NUM_MSG_TYPES)
			sLog.outDebug("Opcode 0x%.4X is non-existent.", packet->GetOpcode());
        else
        {
            try
            {
                switch (opcodeHandler.status)
                {
                    case STATUS_LOGGEDIN:
                        if (_player->IsInWorld())
                            (this->*opcodeHandler.handler)(*packet);
                        break;
                    case STATUS_LOGGEDIN_OR_RECENTLY_LOGGEDOUT:
                        if (!_player && !m_playerRecentlyLoggedOut && !m_playerLogout)
                            sLog.outDebug("Player has not logged in and not recently logged out");
                        else
                            (this->*opcodeHandler.handler)(*packet);
                    break;
                    case STATUS_TRANSFER:
                        if (_player && !_player->IsInWorld())
                            (this->*opcodeHandler.handler)(*packet);
                        break;
                    case STATUS_AUTHED:
                        if (packet->GetOpcode() != CMSG_CHAR_ENUM)
                            m_playerRecentlyLoggedOut = false;

                        (this->*opcodeHandler.handler)(*packet);
                        break;
                case STATUS_NEVER:
                case STATUS_UNHANDLED:
                    sLog.outDebug("WorldSession::Update: received not allowed (or handled) opcode (0x%.4X)", packet->GetOpcode());
                    break;
                default:
                    break;
                }
            }
            catch (...) {} // @TODO Add ByteBufferException and log the error(s)
        }

		delete packet;

		if(InstanceID != instanceId)
		{
			// If we hit this -> means a packet has changed our map.
			return 2;
		}
	}

	if(InstanceID != instanceId)
	{
		// If we hit this -> means a packet has changed our map.
		return 2;
	}

	if( _logoutTime && (m_currMsTime >= _logoutTime) && instanceId == InstanceID)
	{
		// Check if the player is in the process of being moved. We can't delete him
		// if we are.
		if(_player && _player->m_beingPushed)
		{
			// Abort..
			return 0;
		}

		LogoutPlayer(true);
	}

	if(m_lastPing + WORLDSOCKET_TIMEOUT < (uint32)time(NULL))
	{
		// Check if the player is in the process of being moved. We can't delete him
		// if we are.
		if(_player && _player->m_beingPushed)
		{
			// Abort..
			return 0;
		}

		// ping timeout!
		Disconnect();
		bDeleted = true;
		LogoutPlayer(true);

		// 1 - Complete deletion
		return 1;
	}

	// 0 - OK!
	/*UpdateThrottledPackets();*/
	return 0;
}


void WorldSession::LogoutPlayer(bool Save)
{
    m_playerLogout = true;

	if (_player)
	{
		if(_player->m_currentLoot && _player->IsInWorld())
		{
			Object * obj = _player->GetMapMgr()->_GetObject(_player->m_currentLoot);
			if(obj)
			{
				switch(obj->GetTypeId())
				{
				case TYPEID_UNIT:
					((Creature*)obj)->loot.looters.erase(_player->GetGUID());
					break;
				case TYPEID_GAMEOBJECT:
					((GameObject*)obj)->loot.looters.erase(_player->GetGUID());
					break;
				}
			}
		}

		if(_player->m_CurrentTransporter)
			_player->m_CurrentTransporter->RemovePlayer(_player);
		
	  

		// cancel current spell
		if(_player->m_currentSpell)
			_player->m_currentSpell->cancel();

		sSocialMgr.LoggedOut(_player);

		// messages
		if(HasGMPermissions())
		{
			sWorld.BroadcastExtendedMessage(this, "[SM:GMLOGOUT]%s", _player->GetName());
		}

		if(_player->GetTeam() == 1)
			sWorld.HordePlayers--;
		else
			sWorld.AlliancePlayers--;

		// send info
		sWorld.BroadcastExtendedMessage(0, "[SM:INFO:%u:%u]", sWorld.HordePlayers, sWorld.AlliancePlayers);

		//Duel Cancel on Leave
		if(_player->DuelingWith != NULL)
			_player->EndDuel(DUEL_WINNER_RETREAT);

		// wipe our attacker list and target list
		_player->clearAttackers(true);

		//Issue a message telling all guild members that this player signed off
		if(_player->IsInGuild())
		{
			Guild *pGuild = objmgr.GetGuild( _player->GetGuildId() );
			if(pGuild)
			{
				//Update Offline info
				pGuild->GuildMemberLogoff(_player);
				WorldPacket data(SMSG_GUILD_EVENT, 11+strlen(_player->GetName()));
				data << uint8(GUILD_EVENT_HASGONEOFFLINE);
				data << uint8(0x01);
				data << _player->GetName();
				data << _player->GetGUID();
				pGuild->SendMessageToGuild(0,&data,G_MSGTYPE_ALL);
			}
		}

		_player->GetItemInterface()->EmptyBuyBack();
		
		
		// Remove from BG
		if(_player->GetCurrentBattleground() != NULL)
		{
			_player->GetCurrentBattleground()->RemovePlayer(_player, false, false, false);
		}
		
		// Remove ourself from a group
		if (_player->InGroup())
		{
			Group *group = _player->GetGroup();
			if(group)
				group->RemovePlayer(_player);
		}
		
		for(int i=0;i<3;++i)
		{
			if(_player->LfgDungeonId[i] != 0)
				sLfgMgr.RemoveFromLfgQueue(_player,_player->LfgDungeonId[i]);	   
		}
		
		// Save HP/Mana
		_player->load_health = _player->GetUInt32Value(UNIT_FIELD_HEALTH);
		_player->load_mana = _player->GetUInt32Value(UNIT_FIELD_POWER1);
		
		objmgr.RemovePlayer(_player);		
		_player->ok_to_remove = true;

		if(_player->GetSummon() != NULL)
			_player->GetSummon()->Remove(false, true, false);

   //	 _player->SaveAuras();
		if(Save)
			_player->SaveToDB(false);
		
		_player->RemoveAllAuras();
		  if(_player->IsInWorld())
			_player->RemoveFromWorld();
		
	  
		// Remove the "player locked" flag, to allow movement on next login
		if ( GetPlayer( )->GetUInt32Value(UNIT_FIELD_FLAGS) & U_FIELD_FLAG_LOCK_PLAYER )
			GetPlayer( )->RemoveFlag( UNIT_FIELD_FLAGS, U_FIELD_FLAG_LOCK_PLAYER );

		// Save Honor Points
		_player->SaveHonorFields();

		// Update any dirty account_data fields.
		/*bool dirty=false;
		std::stringstream ss;
		ss << "UPDATE accounts SET ";
		for(uint32 ui=0;ui<8;ui++)
		{
			if(sAccountData[ui].bIsDirty)
			{
				if(dirty)
					ss <<",";
				ss << "uiconfig"<< ui <<"=\"";
				if(sAccountData[ui].data)
					ss.write(sAccountData[ui].data,sAccountData[ui].sz);
				ss << "\"";
				dirty=true;
			}
		}			
		if(dirty)
		{
			ss	<<" WHERE acct="<< _accountId <<";";
			sLogonDatabase.Execute(ss.str().c_str());
		}*/

		delete _player;
		_player = NULL;

		OutPacket(SMSG_LOGOUT_COMPLETE, 0, NULL);
		sLog.outDebug( "SESSION: Sent SMSG_LOGOUT_COMPLETE Message" );
	}

    m_playerLogout = false;
    m_playerRecentlyLoggedOut = true;

	SetLogoutTimer(0);
}

void WorldSession::BuildItemPushResult(WorldPacket *data, uint64 guid, uint32 type, uint32 count, uint32 itemid, uint32 randomprop, uint8 unk, uint32 unk2, uint32 unk3, uint32 count_have)
{
    ItemPrototype *proto = ItemPrototypeStorage.LookupEntry(itemid);
    if(!proto) return;

    data->Initialize(SMSG_ITEM_PUSH_RESULT);
    *data << guid;
    *data << type << unk2;
    *data << uint32(1);      // show msg
    *data << unk;
    *data << unk3;
    *data << itemid;
	//not sure if random property. 
	//For quest items also sent at loot list but it's changing in time.
	//in SMSG_ITEM_PUSH_RESULT packet it's used as sent in first occurance of lootlist packet
    *data << randomprop; 
    *data << proto->Quality;
    *data << count;
    *data << count_have;
}

void WorldSession::SendBuyFailed(uint64 guid, uint32 itemid, uint8 error)
{
	WorldPacket data(13);
	data.SetOpcode(SMSG_BUY_FAILED);
	data << guid << itemid << error;
	_socket->SendPacket(&data);
}

void WorldSession::SendSellItem(uint64 vendorguid, uint64 itemid, uint8 error)
{
	WorldPacket data(17);
	data.SetOpcode(SMSG_SELL_ITEM);
	data << vendorguid << itemid << error;
	_socket->SendPacket(&data);
}

void WorldSession::LoadSecurity(std::string securitystring)
{
	std::list<char> tmp;
	bool hasa = false;
	for(uint32 i = 0; i < securitystring.length(); ++i)
	{
		char c = securitystring.at(i);
		c = towlower(c);
		if(c == '4' || c == '3')
			c = 'a';	// for the lazy people

		if(c == 'a')
		{
			// all permissions
			tmp.push_back('a');
			hasa = true;
		}
		else if(!hasa && (c == '0') && i == 0)
			break;
		else if(!hasa || (hasa && (c == 'z')))
		{
			tmp.push_back(c);
		}
	}

	permissions = new char[tmp.size()+1];
	memset(permissions, 0, tmp.size()+1);
	permissioncount = tmp.size();
	int k = 0;
	for(std::list<char>::iterator itr = tmp.begin(); itr != tmp.end(); ++itr)
		permissions[k++] = (*itr);
	
	if(permissions[tmp.size()] != 0)
		permissions[tmp.size()] = 0;

	sLog.outDebug("Loaded permissions for %u. (%u) : [%s]", this->GetAccountId(), permissioncount, securitystring.c_str());
}

void WorldSession::SetSecurity(std::string securitystring)
{
	delete [] permissions;
	LoadSecurity(securitystring);

	// update db
	CharacterDatabase.Execute("UPDATE accounts SET gm=\"%s\" WHERE acct=%u", CharacterDatabase.EscapeString(string(permissions)).c_str(), _accountId);
}

bool WorldSession::CanUseCommand(char cmdstr)
{
	if(permissioncount == 0)
		return false;
	if(cmdstr == 0)
		return true;
	if(permissions[0] == 'a' && cmdstr != 'z')   // all
		return true;

	for(int i = 0; i < permissioncount; ++i)
		if(permissions[i] == cmdstr)
			return true;

	return false;
}

void WorldSession::SendNotification(const char *message, ...)
{
	if( !message ) return;
	va_list ap;
	va_start(ap, message);
	char msg1[1024];
	vsnprintf(msg1,1024, message,ap);
	WorldPacket data(SMSG_NOTIFICATION, strlen(msg1) + 1);
	data << msg1;
	SendPacket(&data);
}

void WorldSession::Handle_NULL(WorldPacket& recvPacket)
{
	// Unhandled Opcode
}

void WorldSession::Handle_EarlyProccess(WorldPacket& recvPacket)
{
    // Received Opcode
}

void WorldSession::Handle_ServerSide(WorldPacket& recvPacket)
{
    // Received Server side Opcode
}

void WorldSession::Handle_Deprecated(WorldPacket& recvPacket)
{
    // Receive deprecated Opcode
}

void WorldSession::CHECK_PACKET_SIZE(WorldPacket& data, uint32 size)
{
	if(data.size() < size && size)
	{
		// write to file
		sCheatLog.writefromsession(this, "kicked for invalid packet (opcode %u), size %u less than %u", data.GetOpcode(), data.size(), size);
		
		// disconnect
		Disconnect();
	}
}

void SessionLogWriter::writefromsession(WorldSession* session, const char* format, ...)
{
	if(!IsOpen())
		return;

	va_list ap;
	va_start(ap, format);
	char out[32768];

	time_t t = time(NULL);
	tm* aTm = localtime(&t);
	snprintf(out, 32768, "[%-4d-%02d-%02d %02d:%02d:%02d] ",aTm->tm_year+1900,aTm->tm_mon+1,aTm->tm_mday,aTm->tm_hour,aTm->tm_min,aTm->tm_sec);
	int l = strlen(out);

	snprintf(&out[l], 32768 - l, "Account %u [%s], IP %s, Player %s :: ", (unsigned int)session->GetAccountId(), session->GetAccountName().c_str(),
		session->GetSocket() ? session->GetSocket()->GetRemoteIP().c_str() : "NOIP", 
		session->GetPlayer() ? session->GetPlayer()->GetName() : "nologin");

	l = strlen(out);
	vsnprintf(&out[l], 32768 - l, format, ap);

	AddLine(out);
	va_end(ap);
}

bool WorldSession::SendThrottledPacket(WorldPacket * packet, bool allocated)
{
	if(World::UNIXTIME < packetThrottleTimeout)
	{
		if(allocated)
			_throttledQueue.Push(packet);
		else
			_throttledQueue.Push(new WorldPacket(*packet));

		return false;
	}

	if(++packetThrottleCount > 15)
	{
		// 2 second delay between throttles
		packetThrottleTimeout = World::UNIXTIME + 3;
	}

	SendPacket(packet);
	return true;
}

void WorldSession::UpdateThrottledPackets()
{
	if(packetThrottleTimeout)
	{
		if(World::UNIXTIME < packetThrottleTimeout)
			return;
		else
		{
			packetThrottleCount = 0;
			packetThrottleTimeout = 0;
		}
	}

	WorldPacket * pck;
	while((pck = _throttledQueue.Pop()))
	{
		SendPacket(pck);
		delete pck;
	}
}

#ifdef CLUSTERING
void WorldSession::HandlePingOpcode(WorldPacket& recvPacket)
{
	uint32 pong;
	recvPacket >> pong;
	WorldPacket data(SMSG_PONG, 4);
	data << pong;
	SendPacket(&data);
}

#endif
