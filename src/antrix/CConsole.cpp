#include "CConsole.h"
#include "Log.h"
#include "Master.h"
#include "../game/StdAfx.h"
#include "../shared/svn_revision.h"


createFileSingleton(CConsole);
CConsole::~CConsole()
{
	if(running_link)
		*running_link = false;
	if(_thread)
		delete _thread;
}

void CConsoleThread::run()
{
	SetThreadName("Console Interpreter");
	CThread::run();
	sCConsole._thread = this;
	delete_after_use = false;
	size_t i = 0;
	char cmd[96];
    bool running = true;
	sCConsole.running_link = &running;	

	while (ThreadState != THREADSTATE_TERMINATE && running)
	{
		if(ThreadState == THREADSTATE_PAUSED)
		{
			while(ThreadState == THREADSTATE_PAUSED)
			{
				Sleep(200);
			}
		}
		
		// Make sure our buffer is clean to avoid Array bounds overflow
		memset(cmd,0,sizeof(cmd)); 
		// Read in single line from "stdin"
		fgets(cmd, 80, stdin);

		if(!running || ThreadState == THREADSTATE_TERMINATE)
			return;

		for( i = 0 ; i < 80 || cmd[i] != '\0' ; i++ )
		{
			if( cmd[i] =='\n' )
			{
				cmd[i]='\0';
				sCConsole.ProcessCmd(cmd);
				fflush(stdin);
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------
// Protected methods:
//------------------------------------------------------------------------------
// Process one command
void CConsole::ProcessCmd(char *cmd)
{
	typedef void (CConsole::*PTranslater)(char *str);
	struct SCmd
	{
		char *name;
		PTranslater tr;
	};

	SCmd cmds[] =
	{

		{ "?", &CConsole::TranslateHelp}, { "help", &CConsole::TranslateHelp},
		{ "ver", &CConsole::TranslateVersion}, { "version", &CConsole::TranslateVersion},
		{ "uptime", &CConsole::GetUptime},
		{ "threads", &CConsole::TranslateThreads},
		{ "cancelshutdown", &CConsole::CancelShutdown },
		{ "status", &CConsole::ObjectStats },
		{ "announce", &CConsole::Announce },
		{ "wannounce", &CConsole::WideAnnounce },
		{ "saveall", &CConsole::SaveallPlayers },
		{ "quit", &CConsole::TranslateQuit}, { "exit", &CConsole::TranslateQuit}, 
		{ "kick", &CConsole::Kick},
		{ "banaccount", &CConsole::BanAccount},
		{ "banip", &CConsole::IPBan},
		{ "playerinfo", &CConsole::PlayerInfo},
	};

	if(_thread->GetThreadState() == THREADSTATE_TERMINATE)
	{
		printf("Exit confirmed. \n");
		return;
	}
	char cmd2[80];
	strcpy(cmd2, cmd);
	for(size_t i = 0; i < strlen(cmd); ++i)
		cmd2[i] = tolower(cmd[i]);

	for (size_t i = 0; i < sizeof(cmds)/sizeof(SCmd); i++)
		if (strncmp(cmd2, cmds[i].name, strlen(cmds[i].name)) == 0)
		{
			(this->*(cmds[i].tr)) (cmd + strlen(cmds[i].name) +1);
			return;
		}

		printf("Console: Unknown console command (use \"help\" for help).\n");
}

void CConsole::CancelShutdown(char *str)
{
	printf("Shutdown aborted.\n");
	WorldPacket data(20);
	data.SetOpcode(SMSG_SERVER_MESSAGE);
	data << uint32(SERVER_MSG_SHUTDOWN_CANCELLED);
	sWorld.SendGlobalMessage(&data);
	sMaster.m_ShutdownEvent = false;
	sMaster.m_ShutdownTimer = 0;
}

void CConsole::GetUptime(char *str)
{
	uint32 count = objmgr._players.size();

	sLog.outString("Console: Server has been running for %s There are currently %d online players.",
		sWorld.GetUptimeString().c_str(), count);
}

//------------------------------------------------------------------------------
// ver[sion]
void CConsole::TranslateVersion(char *str)
{
	ProcessVersion();
}
void CConsole::ProcessVersion()
{
    sLog.outString("Console: Server %s, Rev: %d", _FULLVERSION, g_getRevision());
}
//------------------------------------------------------------------------------
// quit | exit
void CConsole::TranslateQuit(char *str)
{
	int delay = str != NULL ? atoi(str) : 5000;
	if(!delay)
		delay = 5000;
	else
		delay *= 1000;

	ProcessQuit(delay);
}
void CConsole::ProcessQuit(int delay)
{
	sMaster.m_ShutdownTimer = delay;
	sMaster.m_ShutdownEvent = true;
}
//------------------------------------------------------------------------------
// help | ?
void CConsole::TranslateHelp(char *str)
{
	ProcessHelp(NULL);
}
void CConsole::ProcessHelp(char *command)
{
	if (command == NULL)
	{
		sLog.outString("Console:--------help--------");
		sLog.outString("   help, ?: print this text");
		sLog.outString("   uptime: print uptime of the server");
		sLog.outString("   version, ver: print version");
		sLog.outString("   cancelshutdown: cancels the shutdown of the server");
		sLog.outString("   announce: announces a msg to the server.");
		sLog.outString("   wannounce: announces a widescreen msg to the server");
		sLog.outString("   saveall: saves all players");
		sLog.outString("   kick: kicks a player with a reason");
		sLog.outString("   banaccount: bans an account");
		sLog.outString("   banip: bans an ip");
		sLog.outString("   playerinfo: gets info on an online player");
		sLog.outString("   quit, exit: close program");
	}
}
//------------------------------------------------------------------------------

CConsoleThread::CConsoleThread() : CThread()
{
	ThreadType = THREADTYPE_CONSOLEINTERFACE;
	delete_after_use = false;
}

void CConsole::TranslateThreads(char* str)
{
	std::string threads = sThreadMgr.ShowStatus();
	printf(threads.c_str());
}

CConsoleThread::~CConsoleThread()
{

}

void CConsole::ObjectStats(char *str)
{
	printf("\n");
	printf("Loaded object information:\n");
	printf("\n");
}

void CConsole::Announce(char* str)
{
	if(!str)
		return;

	char msg[500];
	snprintf(msg, 500, "%sConsole:%s%s", "|cff00ccff", "|r", str);
	sWorld.SendWorldText(msg, 0);
}

void CConsole::BanAccount(char* str)
{
	sLogonCommHandler.LogonDatabaseSQLExecute("UPDATE accounts SET banned = 1 WHERE login = '%s'", str);
	sLog.outString("User %s banned!", str);
	sLogonCommHandler.LogonDatabaseReloadAccounts();
}

void CConsole::IPBan(char* str)
{
	sLogonCommHandler.LogonDatabaseSQLExecute("INSERT INTO ipbans (ip, time) VALUES ('%s', '0')", str);
	sLog.outString("IP %s banned!", str);
	sLogonCommHandler.LogonDatabaseReloadAccounts();
}

void CConsole::PlayerInfo(char* str)
{
	char player[100];
	if(sscanf(str, "%s", player) != 1)
		return;

	Player * _plr = objmgr.GetPlayer(player, false);
	if(!_plr)
	{
		sLog.outString("Cannot find online player %s", str);
		return;
	}
	
	if(!_plr) return;
	if(!_plr->GetSession())
	{
		sLog.outString("ERROR: this player hasn't got any session !");
		return;
	}

	WorldSession* sess = _plr->GetSession();

		static const char* _classes[12] =
	{"None","Warrior", "Paladin", "Hunter", "Rogue", "Priest", "None", "Shaman", "Mage", "Warlock", "None", "Druid"};
	static const char* _races[12] =
	{"None","Human","Orc","Dwarf","Night Elf","Undead","Tauren","Gnome","Troll","None","Blood Elf","Draenei"};


	sLog.outColor(TGREEN, "Name: ");
	sLog.outColor(TNORMAL, "%s\n", _plr->GetName());
	sLog.outColor(TGREEN, "Account: ");
	sLog.outColor(TNORMAL, "%s\n", sess->GetAccountName().c_str());
	sLog.outColor(TGREEN, "Level: ");
	sLog.outColor(TNORMAL, "%d\n",  _plr->getLevel());
	sLog.outColor(TGREEN, "Race: ");
	sLog.outColor(TNORMAL, "%s\n", _races[_plr->getRace()]);
	sLog.outColor(TGREEN, "Class: ");
	sLog.outColor(TNORMAL, "%s\n", _classes[_plr->getClass()]);
	sLog.outColor(TGREEN, "Map: ");
	sLog.outColor(TNORMAL, "%d\n",  _plr->GetMapId());
	sLog.outColor(TGREEN, "Banned: ");
	sLog.outColor(TNORMAL, "%s\n",  (_plr->IsBanned() ? "Yes" : "No"));
}

void CConsole::Kick(char* str)
{
	char player[100];
	char reason[256];
	if(sscanf(str, "%s %s", player, reason) != 2)
		return;

	Player * _plr = objmgr.GetPlayer(player, false);
	if(!_plr)
	{
		sLog.outColor(TRED, "Unable to find player %s\n", player);
		return;
	}

	_plr->BroadcastMessage("|cff00ccffYou have been kicked for |cffff0000%s", reason);
	_plr->Kick(6000);


	
}

void CConsole::WideAnnounce(char *str)
{
	if(!str)
		return;

	char msg[500];
	snprintf(msg, 500, "%sConsole:%s%s", "|cff00ccff", "|r", str);
	sWorld.SendWorldText(msg, 0);
	sWorld.SendWorldWideScreenText(msg, 0);
}

void CConsole::SaveallPlayers(char *str)
{
    UNORDERED_MAP<uint32, Player*>::const_iterator itr;
	uint32 stime = now();
	uint32 count = 0;
	objmgr._playerslock.AcquireReadLock();
	for (itr = objmgr._players.begin(); itr != objmgr._players.end(); itr++)
	{
		if(itr->second->GetSession())
		{
			itr->second->SaveToDB(false);
			count++;
		}
	}
	objmgr._playerslock.ReleaseReadLock();
	char msg[100];
	snprintf(msg, 100, "Saved all %d online players in %d msec.", (unsigned int)count, (unsigned int)((uint32)now() - stime));
	sWorld.SendWorldText(msg);
	sWorld.SendWorldWideScreenText(msg);
}
