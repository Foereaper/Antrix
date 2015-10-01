#include "StdAfx.h"
#include <openssl/md5.h>
#include "../shared/AuthCodes.h"
#include "../shared/svn_revision.h"

#if PLATFORM == PLATFORM_WIN32
#define PLATFORM_TEXT "Win32"
#elif PLATFORM == PLATFORM_UNIX
#if UNIX_FLAVOUR == UNIX_FLAVOUR_LINUX
#define PLATFORM_TEXT "Linux"
#elif UNIX_FLAVOUR == UNIX_FLAVOUR_BSD
#define PLATFORM_TEXT "FreeBSD"
#else
#define PLATFORM_TEXT "Unknown"
#endif
#else
#define PLATFORM_TEXT "unknown"
#endif

#define SERVER_NAME "Antrix"
#ifdef _DEBUG
#define CONFIG "Debug"
#else
#define CONFIG "Release"
#endif

bool VerifyName(const char * name, size_t nlen)
{
    static char * bannedCharacters = "\t\v\b\f\a\n\r\\\"\'\? <>[](){}_=+-|/!@#$%^&*~`.,0123456789\0";
    char * p;
    for(size_t i = 0; i < nlen; ++i)
    {
        p = bannedCharacters;
        while(*p != 0 && name[i] != *p && name[i] != 0)
            ++p;

        if(*p != 0)
            return false;
    }
    return true;
}

void CapitalizeString(string& arg)
{
    if(arg.length() == 0) return;
    arg[0] = toupper(arg[0]);
    for(uint32 x = 1; x < arg.size(); ++x)
        arg[x] = tolower(arg[x]);
}

void WorldSession::HandleCharEnumOpcode( WorldPacket & recv_data )
{    
    uint32 start_time = getMSTime();

    // loading characters
    QueryResult* result = CharacterDatabase.Query("SELECT guid, level, race, class, gender, bytes, bytes2, guildid, name, positionX, positionY, positionZ, mapId, zoneId, banned, restState, deathstate, forced_rename_pending FROM characters WHERE acct=%u ORDER BY guid", GetAccountId());
    uint8 num = 0;
    
    // should be more than enough.. 200 bytes per char..
    WorldPacket data((result ? result->GetRowCount() * 200 : 1));    

    // parse m_characters and build a mighty packet of
    // characters to send to the client.
    data.SetOpcode(SMSG_CHAR_ENUM);

    data << num;
    SetSide(0);
    if( result )
    {
        Player *plr;
        uint64 guid;
        Field *fields;
        do
        {
            fields = result->Fetch();
            guid = fields[0].GetUInt32();
            
            plr = objmgr.GetPlayer(guid);
            if(plr)
            {
                // we already have that player in world... for some strange reason...
                continue;
            }

            plr = new Player(HIGHGUID_PLAYER, guid);
            ASSERT(plr);
            plr->SetSession(this);

            // added to catch an assertion failure at Player::LoadFromDB function.
            plr->LoadFromDB_Light( fields, guid );
            sLog.outDebug("Loaded char guid " I64FMTD " [%s] from account %d for enum build.",guid,plr->GetName(), GetAccountId());
            plr->BuildEnumData( &data );
            _side|=(plr->GetTeam()+1);

            plr->ok_to_remove = true;
            delete plr;

            num++;
        }
        while( result->NextRow() );

        delete result;
    }

    data.put<uint8>(0, num);

    sLog.outDetail("[Character Enum] Built in %u ms.", getMSTime() - start_time);
    SendPacket( &data );
}


void WorldSession::HandleCharCreateOpcode( WorldPacket & recv_data )
{
    CHECK_PACKET_SIZE(recv_data, 10);
    std::string name;
    uint8 race, class_;

    recv_data >> name >> race >> class_;
    recv_data.rpos(0);

    if(!VerifyName(name.c_str(), name.length()))
    {
        OutPacket(SMSG_CHAR_CREATE, 1, "\x31");
        return;
    }

    if(objmgr.GetPlayerInfoByName(name) != 0)
    {
        OutPacket(SMSG_CHAR_CREATE, 1, "\x31");
        return;
    }

    if(!sHookInterface.OnNewCharacter(race, class_, this, name.c_str()))
    {
        OutPacket(SMSG_CHAR_CREATE, 1, "\x31");
        return;
    }

    // loading characters
    
    //checking number of chars is useless since client will not allow to create more than 10 chars
    //as the 'create' button will not appear (unless we want to decrease maximum number of characters)

    Player * pNewChar = objmgr.CreatePlayer();
    pNewChar->SetSession(this);
    if(!pNewChar->Create( recv_data ))
    {
        // failed.
        pNewChar->ok_to_remove = true;
        delete pNewChar;
        return;
    }

    //Same Faction limitation only applies to PVP and RPPVP realms :)
    uint32 realmType = sLogonCommHandler.GetRealmType();
    if(!HasGMPermissions() && (realmType==REALMTYPE_PVP||realmType==REALMTYPE_RPPVP))
    {
        if(
            ((pNewChar->GetTeam()== 0) && (_side&2))||
            ((pNewChar->GetTeam()== 1) && (_side&1))
            )
        {
            pNewChar->ok_to_remove = true;
            delete pNewChar;
            WorldPacket data;
            data.SetOpcode(SMSG_CHAR_CREATE);
            data << (uint8)ALL_CHARS_ON_PVP_REALM_MUST_AT_SAME_SIDE;
            SendPacket( &data );
            return;
        }
    }
    pNewChar->UnSetBanned();
    
    pNewChar->addSpell(22027);      // Remove Insignia


    if(pNewChar->getClass() == WARLOCK)
    {
        pNewChar->AddSummonSpell(416, 3110);        // imp fireball
        pNewChar->AddSummonSpell(417, 19505);
        pNewChar->AddSummonSpell(1860, 3716);
        pNewChar->AddSummonSpell(1863, 7814);
    }

    pNewChar->SaveToDB(true);    

    PlayerInfo *pn=new PlayerInfo ;
    pn->guid = pNewChar->GetGUID();
    pn->name = pNewChar->GetName();
    pn->cl = pNewChar->getClass();
    pn->race = pNewChar->getRace();
    pn->gender = pNewChar->getGender();
    pn->publicNote="";
    pn->officerNote="";
    
    pn->team = pNewChar->GetTeam ();
    objmgr.AddPlayerInfo(pn);

    pNewChar->ok_to_remove = true;
    delete  pNewChar;

    // CHAR_CREATE_SUCCESS
    OutPacket(SMSG_CHAR_CREATE, 1, "\x2E");

    sLogonCommHandler.UpdateAccountCount(GetAccountId(), 1);
}

/* FOR 1.10.1
SMSG_CHAR_CREATE Error Codes:
0x00 Success
0x01 Failure
0x02 Canceled
0x03 Disconnect from server
0x04 Failed to connect
0x05 Connected
0x06 Wrong client version
0x07 Connecting to server
0x08 Negotiating security
0x09 Negotiating security complete
0x0A Negotiating security failed
0x0B Authenticating
0x0C Authentication successful
0x0D Authentication failed
0x0E Login unavailable - Please contact Tech Support
0x0F Server is not valid
0x10 System unavailable 
0x11 System error
0x12 Billing system error
0x13 Account billing has expired
0x14 Wrong client version
0x15 Unknown account
0x16 Incorrect password
0x17 Session expired
0x18 Server Shutting Down
0x19 Already logged in
0x1A Invalid login server
0x1B Position in Queue: 0
0x1C This account has been banned
0x1D This character is still logged on
0x1E Your WoW subscription has expired
0x1F This session has timed out
0x20 This account has been temporarily suspended
0x21 Access to this account blocked by parental controls 
0x22 Retrieving realmlist
0x23 Realmlist retrieved
0x24 Unable to connect to realmlist server
0x25 Invalid realmlist
0x26 The game server is currently down
0x27 Creating account
0x28 Account created
0x29 Account creation failed
0x2A Retrieving character list
0x2B Character list retrieved
0x2C Error retrieving character list
0x2D Creating character
0x2E Character created
0x2F Error creating character
0x30 Character creation failed
0x31 That name is unavailable
0x32 Creation of that race/class is disabled
0x33 You cannot have both horde and alliance character at pvp realm
0x33 All characters on a PVP realm must be on the same team
0x34 You already have maximum number of characters
0x35 You already have maximum number of characters
0x36 The server is currently queued
0x37 Only players who have characters on this realm..
0x38 Creation of that race requires an account that has been upgraded to the approciate expansion
0x39 Deleting character
0x3A Character deleted
0x3B Char deletion failed
0x3c Entering world of warcraft
0x3D Login successful
0x3E World server is down
0x3F A character with that name already exists
0x40 No instance server available
0x41 Login failed
0x42 Login for that race/class is disabled
0x43 Character not found
0x44 Enter a name for your character
0x45 Names must be atleast 2 characters long
0x46 Names must be no more then 12 characters
0x47 Names can only contain letters
0x48 Names must contain only one language
0x49 That name contains profanity
0x4A That name is unavailable
0x4B You cannot use an apostrophe
0x4C You can only have one apostrophe
0x4D You cannot use the same letter three times consecutively
0x4E You cannit use space as the first or last character of your name
0x4F <Blank>
0x50 Invalid character name
0x51 <Blank>
All further codes give the number in dec.
*/

void WorldSession::HandleCharDeleteOpcode( WorldPacket & recv_data )
{
    CHECK_PACKET_SIZE(recv_data, 8);
    uint8 fail = 0x3A;

    uint64 guid;
    recv_data >> guid;

    if(objmgr.GetPlayer(guid) != NULL)
    {
        // "Char deletion failed"
        fail = 0x3B;
    } else {

        Player* plr = new Player( HIGHGUID_PLAYER, GUID_LOPART(guid));
        ASSERT(plr);
        plr->SetSession(this);

        if(!plr->LoadFromDB( GUID_LOPART(guid)))
        {
            // Disconnect us
            sCheatLog.writefromsession(this, "Tried to delete non-existant player %u\n", guid);
            Disconnect();
            plr->ok_to_remove = true;
            delete plr;
            //sObjHolder.Delete<Player>(plr);
            return;
        }
        plr->DeleteFromDB();
        //if charter leader
        if(plr->m_charter)
            plr->m_charter->RemoveSignature(plr->GetGUID());
        
        Guild *pGuild = objmgr.GetGuild(plr->GetGuildId());
        if(pGuild)
        {
            pGuild->DeleteGuildMember(plr->GetGUID());
        }

        plr->ok_to_remove = true;
        delete plr;

        /* remove player info */
        objmgr.DeletePlayerInfo(guid);
    }

    OutPacket(SMSG_CHAR_DELETE, 1, &fail);
}

void WorldSession::HandleCharRenameOpcode(WorldPacket & recv_data)
{
    WorldPacket data(SMSG_CHAR_RENAME, recv_data.size() + 1);

    uint64 guid;
    string name;
    recv_data >> guid >> name;

    PlayerInfo * pi = objmgr.GetPlayerInfo(guid);
    if(pi == 0) return;

    QueryResult * result = CharacterDatabase.Query("SELECT forced_rename_pending FROM characters WHERE guid = %u AND acct = %u", 
        (uint32)guid, _accountId);
    if(result == 0) return;

    // Check name for rule violation.
    const char * szName=name.c_str();
    for(uint32 x=0;x<strlen(szName);x++)
    {
        if((int)szName[x]<65||((int)szName[x]>90&&(int)szName[x]<97)||(int)szName[x]>122)
        {
            data << uint8(0x31);
            data << guid << name;
            SendPacket(&data);
            return;
        }
    }

    // Check if name is in use.
    if(objmgr.GetPlayerInfoByName(name) != 0)
    {
        data << uint8(0x31);
        data << guid << name;
        SendPacket(&data);
        return;
    }

    // correct capitalization
    CapitalizeString(name);

    // If we're here, the name is okay.
    pi->name = name;
    CharacterDatabase.WaitExecute("UPDATE characters SET name = '%s' WHERE guid = %u", name.c_str(), (uint32)guid);
    CharacterDatabase.WaitExecute("UPDATE characters SET forced_rename_pending = 0 WHERE guid = %u", (uint32)guid);
    
    data << uint8(0) << guid << name;
    SendPacket(&data);
}


void WorldSession::HandlePlayerLoginOpcode( WorldPacket & recv_data )
{
    CHECK_PACKET_SIZE(recv_data, 8);
    uint64 playerGuid = 0;

    sLog.outDebug( "WORLD: Recvd Player Logon Message" );

    recv_data >> playerGuid; // this is the GUID selected by the player
    PlayerLogin((uint32)playerGuid, 0, 0);
}

bool WorldSession::PlayerLogin(uint32 playerGuid, uint32 forced_map_id, uint32 forced_instance_id)
{
    if(objmgr.GetPlayer(playerGuid) != NULL)
    {
        // A character with that name already exists 0x3E
        uint8 respons = CHAR_LOGIN_DUPLICATE_CHARACTER;
        OutPacket(SMSG_CHARACTER_LOGIN_FAILED, 1, &respons);
        return false;
    }

    Player* plr = new Player(HIGHGUID_PLAYER,playerGuid);
    ASSERT(plr);
    plr->SetSession(this);
    m_bIsWLevelSet = false;

    if(!plr->LoadFromDB(GUID_LOPART(playerGuid)))
    {
        // kick em.
        sCheatLog.writefromsession(this, "Tried to log in with invalid player guid %u.", playerGuid);
        Disconnect();
        plr->ok_to_remove = true;
        delete plr;
        return false;
    }

    SetPlayer(plr); 
    m_MoverWoWGuid.Init(plr->GetGUID());

    // copy to movement array
    movement_packet[0] = m_MoverWoWGuid.GetNewGuidMask();
    memcpy(&movement_packet[1], m_MoverWoWGuid.GetNewGuid(), m_MoverWoWGuid.GetNewGuidLen());

    StackWorldPacket<20> datab(SMSG_LOGIN_VERIFY_WORLD);
    datab << plr->GetMapId();
    datab << plr->GetPositionX()
        << plr->GetPositionY()  
        << plr->GetPositionZ()
        << plr->GetOrientation();

    SendPacket(&datab);

    plr->LoadPropertiesFromDB();
    plr->UpdateAttackSpeed();

    // Make sure our name exists (for premade system)
    PlayerInfo * info = objmgr.GetPlayerInfo(plr->GetGUID());
    if(info == 0)
    {
        info = new PlayerInfo;
        info->cl = plr->getClass();
        info->gender = plr->getGender();
        info->guid = plr->GetGUID();
        info->name = plr->GetName();
        info->lastLevel = plr->getLevel();
        info->lastOnline = time(NULL);
        info->lastZone = plr->GetZoneId();
        info->officerNote = "";
        info->publicNote = "";
        info->race = plr->getRace();
        info->Rank = plr->GetPVPRank();
        info->team = plr->GetTeam();
        objmgr.AddPlayerInfo(info);
    }

    // account data == UI config
    StackWorldPacket<128> data(SMSG_ACCOUNT_DATA_TIMES);

    for (int i = 0; i < 8; i++)
    {
        AccountDataEntry* acct_data = GetAccountData(i);

        if (!acct_data->data)
        {
            data << uint64(0) << uint64(0);                // Nothing.
            continue;
        }
        MD5_CTX ctx;
        MD5_Init(&ctx);

        MD5_Update(&ctx, acct_data->data, acct_data->sz);
        uint8 md5hash[MD5_DIGEST_LENGTH];
        MD5_Final(md5hash, &ctx);
        data.Write(md5hash, MD5_DIGEST_LENGTH);
    }
    SendPacket(&data);

    // Set TIME OF LOGIN
    CharacterDatabase.Execute (
        "UPDATE characters SET online = 1 WHERE guid = %u" , plr->GetGUIDLow());

    bool enter_world = true;
#ifndef CLUSTERING
    // Find our transporter and add us if we're on one.
    if(plr->m_TransporterGUID != 0)
    {
        Transporter * pTrans = objmgr.GetTransporter(plr->m_TransporterGUID);
        if(pTrans)
        {
            float c_tposx = pTrans->GetPositionX() + plr->m_TransporterX;
            float c_tposy = pTrans->GetPositionY() + plr->m_TransporterY;
            float c_tposz = pTrans->GetPositionZ() + plr->m_TransporterZ;
            if(plr->GetMapId() != pTrans->GetMapId())       // loaded wrong map
            {
                plr->SetMapId(pTrans->GetMapId());
                StackWorldPacket<20> dataw(SMSG_NEW_WORLD);
                dataw << pTrans->GetMapId() << c_tposx << c_tposy << c_tposz << plr->GetOrientation();
                SendPacket(&dataw);

                // shit is sent in worldport ack.
                enter_world = false;
            }

            plr->SetPosition(c_tposx, c_tposy, c_tposz, plr->GetOrientation(), false);
            plr->m_CurrentTransporter = pTrans;
            pTrans->AddPlayer(plr);
        }
    }
#endif

    sLog.outString("Player %s (%s %s %s), logged in.", plr->GetName(), plr->getGender() ? "Female" : "Male", 
        sCharRaceStore.LookupString(plr->myRace->name2), sCharClassStore.LookupString(plr->myClass->name));

#ifndef CLUSTERING
    // send extended message
    sWorld.BroadcastExtendedMessage(this, "[SM:PLRLOGIN:%u:%u]%s", plr->getRace(), plr->getClass(), plr->GetName());
    if(HasFlag(ACCOUNT_FLAG_XTEND_INFO))
    {
        // send gm list
        stringstream ssg;
        uint32 c = 0;
        for(set<WorldSession*>::iterator itr = sWorld.gmList.begin(); itr != sWorld.gmList.end(); ++itr)
        {
            if((*itr)->GetPlayer())
            {
                ssg << *(*itr)->GetPlayer()->GetNameString();
                ssg << ",";
                ++c;
            }
        }
        _player->BroadcastMessage("[SM:GMLIST:%s]", ssg.str().c_str());
    }

    if(HasGMPermissions())
    {
        sWorld.BroadcastExtendedMessage(this, "[SM:GMLOGIN]%s", plr->GetName());
    }

#endif

    if(plr->GetTeam() == 1)
        sWorld.HordePlayers++;
    else
        sWorld.AlliancePlayers++;

#ifndef CLUSTERING
    // send info
    sWorld.BroadcastExtendedMessage(0, "[SM:INFO:%u:%u]", sWorld.HordePlayers, sWorld.AlliancePlayers);
#endif

    if(plr->m_FirstLogin && !HasGMPermissions())
    {
        uint32 racecinematic = plr->myRace->cinematic_id;
        OutPacket(SMSG_TRIGGER_CINEMATIC, 4, &racecinematic);
    }

    sLog.outDetail( "WORLD: Created new player for existing players (%s)", plr->GetName() );

    // Login time, will be used for played time calc
    plr->m_playedtime[2] = (uint32)time(NULL);

    //Issue a message telling all guild members that this player has signed on
    if(plr->IsInGuild())
    {
        Guild *pGuild = objmgr.GetGuild( plr->GetGuildId() );
        if(pGuild)
        {
            WorldPacket data(50);
            data.Initialize(SMSG_GUILD_EVENT);
            data << uint8(GUILD_EVENT_MOTD);
            data << uint8(0x01);
            data << pGuild->GetGuildMotd();
            SendPacket(&data);

            data.Initialize(SMSG_GUILD_EVENT);
            data << uint8(GUILD_EVENT_HASCOMEONLINE);
            data << uint8(0x01);
            data << plr->GetName();
            data << plr->GetGUID();
            pGuild->SendMessageToGuild(0,&data,G_MSGTYPE_ALL);
        }
    }

    // Send online status to people having this char in friendlist
    sSocialMgr.LoggedIn( GetPlayer() );

    // Send MOTD
    _player->BroadcastMessage(sWorld.GetMotd());

    // Send revision (if enabled)
    if(sWorld.sendRevisionOnJoin)
    {
        uint32 rev = g_getRevision();
        if(!sWorld.SendStatsOnJoin) {
            _player->BroadcastMessage("Server: %s%s%s Core v2.1.2-%u-%s/%s|r %s %s", MSG_COLOR_LIGHTBLUE, 
                SERVER_NAME, MSG_COLOR_WHITE, rev, CONFIG, PLATFORM_TEXT, __DATE__, __TIME__);
        } else {
            _player->BroadcastMessage("Server Version: %s%s%s Core v2.1.2.%u-%s/%s|r %s\nOnline Players: %s%u |rPeak: %s%u|r Accepted Connections: %s%u", MSG_COLOR_LIGHTBLUE, 
                SERVER_NAME, MSG_COLOR_WHITE, rev, CONFIG, PLATFORM_TEXT, __DATE__, 
                MSG_COLOR_WHITE, sWorld.GetSessionCount(), MSG_COLOR_WHITE, sWorld.PeakSessionCount, MSG_COLOR_WHITE, sWorld.mAcceptedConnections);
        }
    }
    else
    {
        if(sWorld.SendStatsOnJoin) {
            _player->BroadcastMessage("This server has %u players currently online, with a peak of %u, and has accepted %u connections since its startup.", 
                sWorld.GetSessionCount(), sWorld.PeakSessionCount, sWorld.mAcceptedConnections );
        }
    }

    // Calculate rested experience if there is time between lastlogoff and now
    uint32 currenttime = (uint32)time(NULL);
    float timediff = currenttime - plr->m_timeLogoff;

    if(plr->m_timeLogoff > 0 && plr->GetUInt32Value(UNIT_FIELD_LEVEL) < plr->GetUInt32Value(PLAYER_FIELD_MAX_LEVEL))    // if timelogoff = 0 then it's the first login
    {
        if(plr->m_isResting) 
        {
            // We are resting at an inn, calculate XP and add it.
            uint32 RestXP = plr->CalculateRestXP((uint32)timediff);
            plr->AddRestXP(RestXP);
            sLog.outDebug("REST: Added %d of rest XP.", RestXP);
            plr->ApplyPlayerRestState(true);
        }
        else if(timediff > 0)
        {
            // We are resting in the wilderness at a slower rate.
            uint32 RestXP = plr->CalculateRestXP((uint32)timediff);
            RestXP >>= 2;        // divide by 4 because its at 1/4 of the rate
            plr->AddRestXP(RestXP);
        }
    }

#ifdef CLUSTERING
    plr->SetInstanceID(forced_instance_id);
    plr->SetMapId(forced_map_id);
#else
    sHookInterface.OnEnterWorld2(_player);
#endif

    if(enter_world)
    {
        plr->SendInitialLogonPackets();
        plr->AddToWorld();
    }

#ifndef CLUSTERING
    /*    if(sWorld.m_useIrc)
    sIRCBot.SendMessage("> %s from account %u entered world.", _player->GetName(), GetAccountId());*/

    if(_player->GetMapId() == 489 ||
        _player->GetMapId() == 529 /*|| _player->GetMapId() == 30*/)
    {
        uint32 battlegroundtype = sBattlegroundMgr.GetBattleGroundTypeByMapId(_player->GetMapId());
        Battleground *battleground = sBattlegroundMgr.GetBattlegroundByInstanceID(_player->GetInstanceID(),battlegroundtype);
        if(battleground == NULL)    // bad battleground
        {
            _player->SetInstanceID(_player->m_bgEntryPointInstance);
            _player->_Relocate(_player->m_bgEntryPointMap, LocationVector(_player->m_bgEntryPointX, _player->m_bgEntryPointY, _player->m_bgEntryPointZ, 
                _player->m_bgEntryPointO), true, true);
        } else {
            // we are ALREADY in battleground! no need to transport ;)
            battleground->AddPlayer(_player, false, true);
        }
    }
#endif

    sInstanceSavingManager.BuildSavedInstancesForPlayer(plr);
    objmgr.AddPlayer(_player);
    return true;
}

bool ChatHandler::HandleRenameCommand(const char * args, WorldSession * m_session)
{
    // prevent buffer overflow
    if(strlen(args) > 100)
        return false;

    char name1[100];
    char name2[100];

    if(sscanf(args, "%s %s", name1, name2) != 2)
        return false;

    if(VerifyName(name2, strlen(name2)) == false)
    {
        RedSystemMessage(m_session, "That name is invalid or contains invalid characters.");
        return true;
    }

    string new_name = name2;
    string oldn = name1;//some crazy func, dunno who invented that shit...
    PlayerInfo * pi = objmgr.GetPlayerInfoByName(oldn);
    if(pi == 0)
    {
        RedSystemMessage(m_session, "Player not found with this name.");
        return true;
    }

    pi->name = new_name;

    // look in world for him
    Player * plr = objmgr.GetPlayer(pi->guid);
    if(plr != 0)
    {
        plr->SetName(new_name);
        BlueSystemMessageToPlr(plr, "%s changed your name to '%s'.", m_session->GetPlayer()->GetName(), new_name.c_str());
        plr->SaveToDB(false);
    }
    else
    {
        CharacterDatabase.WaitExecute("UPDATE characters SET name = '%s' WHERE guid = %u", CharacterDatabase.EscapeString(new_name).c_str(), (uint32)pi->guid);
    }

    GreenSystemMessage(m_session, "Changed name of '%s' to '%s'.", name1, name2);
    return true;
}
