#include "Master.h"
#include "CConsole.h"
#include "../shared/CrashHandler.h"
#include "../game/StdAfx.h"
#include "../shared/antrix_getopt.h"

#ifdef WIN32
#define PLATFORM_TEXT "Win32"
#define BANNER "Antrix/Win32-2.1.2-%u :: World Server                        www.emupedia.com"
#else
#if UNIX_FLAVOUR == UNIX_FLAVOUR_LINUX
#define PLATFORM_TEXT "Linux"
#define BANNER "Antrix/Linux-2.1.2-%u :: World Server                        www.emupedia.com"
#elif UNIX_FLAVOUR == UNIX_FLAVOUR_BSD
#define PLATFORM_TEXT "FreeBSD"
#define BANNER "Antrix/FreeBSD-2.1.2-%u :: World Server                      www.emupedia.com"
#else
#define PLATFORM_TEXT "Unix"
#define BANNER "Antrix/Unix-2.1.2-%u :: World Server                         www.emupedia.com"
#endif
#include <sched.h>
#endif

#include "../shared/svn_revision.h"

#include "../game/WorldSession.h"
#include "LogonCommClient.h"

#include <signal.h>

createFileSingleton(Master);
std::string LogFileName;
bool bLogChat;
bool crashed = false;

volatile bool Master::m_stopEvent = false;

// Database defines.
SERVER_DECL Database* Database_Character;
SERVER_DECL Database* Database_World;

// mainserv defines
TextLogger * Crash_Log;
SessionLogWriter * GMCommand_Log;
SessionLogWriter * Anticheat_Log;

void Master::_OnSignal(int s)
{
	switch (s)
	{
#ifndef WIN32
	case SIGHUP:
		sWorld.Rehash(true);
		break;
#endif
	case SIGINT:
	case SIGTERM:
	case SIGABRT:
#ifdef _WIN32
	case SIGBREAK:
#endif
		Master::m_stopEvent = true;
		break;
	}

	signal(s, _OnSignal);
}

Master::Master()
{
	m_ShutdownTimer = 0;
	m_ShutdownEvent = false;
	m_restartEvent = false;
}

Master::~Master()
{
}

struct Addr
{
	unsigned short sa_family;
	/* sa_data */
	unsigned short Port;
	unsigned long IP; // inet_addr
	unsigned long unusedA;
	unsigned long unusedB;
};

#define DEF_VALUE_NOT_SET 0xDEADBEEF

bool Master::Run(int argc, char ** argv)
{
#ifdef WIN32
	char * config_file = "antrix.conf";
	char * realm_config_file = "realms.conf";
#else
	char * config_file = CONFDIR "/antrix.conf";
	char * realm_config_file = CONFDIR "/realms.conf";
#endif

	int file_log_level = DEF_VALUE_NOT_SET;
	int screen_log_level = DEF_VALUE_NOT_SET;
	int do_check_conf = 0;
	int do_version = 0;

	struct antrix_option longopts[] =
	{
		{ "checkconf",			antrix_no_argument,				&do_check_conf,			1		},
		{ "screenloglevel",		antrix_required_argument,		&screen_log_level,		1		},
		{ "fileloglevel",		antrix_required_argument,		&file_log_level,		1		},
		{ "version",			antrix_no_argument,				&do_version,			1		},
		{ "conf",				antrix_required_argument,		NULL,					'c'		},
		{ "realmconf",			antrix_required_argument,		NULL,					'r'		},
		{ 0, 0, 0, 0 }
	};

	char c;
	while ((c = antrix_getopt_long_only(argc, argv, ":f:", longopts, NULL)) != -1)
	{
		switch (c)
		{
		case 'c':
			config_file = new char[strlen(antrix_optarg)];
			strcpy(config_file, antrix_optarg);
			break;

		case 'r':
			realm_config_file = new char[strlen(antrix_optarg)];
			strcpy(realm_config_file, antrix_optarg);
			break;

		case 0:
			break;
		default:
			sLog.m_fileLogLevel = -1;
			sLog.m_screenLogLevel = 3;
			printf("Usage: %s [--checkconf] [--screenloglevel <level>] [--fileloglevel <level>] [--conf <filename>] [--realmconf <filename>] [--version]\n", argv[0]);
			return true;
		}
	}

	// Startup banner
	if(!do_version && !do_check_conf)
	{
		launch_thread(new TextLoggerThread);
		sLog.Init(-1, 3);
	}
	else
	{
		sLog.m_fileLogLevel = -1;
		sLog.m_screenLogLevel = 3;
	}

	sLog.outString("==============================================================================");
	sLog.outString(BANNER, g_getRevision());
	sLog.outString("");
	sLog.outString("Copyright (c) 2007 Antrix Team.");
	sLog.outString("==============================================================================");
	sLog.outString("");
	if(do_version)
		return true;

	if(do_check_conf)
	{
		printf("Checking config file: %s\n", config_file);
		if(Config.MainConfig.SetSource(config_file, true))
			printf("  Passed without errors.\n");
		else
			printf("  Encountered one or more errors.\n");

		printf("\nChecking config file: %s\n", realm_config_file);
		if(Config.RealmConfig.SetSource(realm_config_file, true))
			printf("  Passed without errors.\n");
		else
			printf("  Encountered one or more errors.\n");

		/* test for die variables */
		string die;
		if(Config.MainConfig.GetString("die", "msg", &die) || Config.MainConfig.GetString("die2", "msg", &die))
			printf("Die directive received: %s", die.c_str());

		return true;
	}

	sLog.outString("The key combination <Ctrl-C> will safely shut down the server at any time.");
	sLog.outString("");
	sLog.outString("Initializing File Loggers...");
	Crash_Log = new TextLogger(FormatOutputString("logs", "CrashLog", true).c_str(), false);
    
	sLog.outString("Initializing Random Number Generators...");
	uint32 seed = time(NULL);
	new MTRand(seed);
	srand(seed);

	sLog.outString("Starting Thread Manager...\n");
	new ThreadMgr;
	uint32 LoadingTime = getMSTime();

	sLog.outColor(TNORMAL, "Loading Config Files...\n");
	sLog.outColor(TYELLOW, "  >> %s :: ", config_file);
	if(Config.MainConfig.SetSource(config_file))
	{
		sLog.outColor(TGREEN, "ok!");
		sLog.outColor(TNORMAL, "\n");
	}
	else
	{
		sLog.outColor(TRED, "fail.");
		sLog.outColor(TNORMAL, "\n");
		return false;
	}

	/* test for die variables */
	string die;
	if(Config.MainConfig.GetString("die", "msg", &die) || Config.MainConfig.GetString("die2", "msg", &die))
	{
		printf("Die directive received: %s", die.c_str());
		return false;
	}	


	sLog.outColor(TYELLOW, "  >> %s :: ", realm_config_file);
	if(Config.RealmConfig.SetSource(realm_config_file))
	{
		sLog.outColor(TGREEN, "ok!");
		sLog.outColor(TNORMAL, "\n\n");
	}
	else
	{
		sLog.outColor(TRED, "fail.");
		sLog.outColor(TNORMAL, "\n\n");
		return false;
	}

	if(!_StartDB())
	{
		return false;
	}

	sLog.outString("");

	ScriptSystem = new ScriptEngine;
	ScriptSystem->Reload();

	new EventMgr;
	new World;

	// open cheat log file
	Anticheat_Log = new SessionLogWriter(FormatOutputString("logs", "cheaters", false).c_str(), false);
	GMCommand_Log = new SessionLogWriter(FormatOutputString("logs", "gmcommand", false).c_str(), false);

	/* load the config file */
	sWorld.Rehash(false);

	/* set new log levels */
	if(screen_log_level != (int)DEF_VALUE_NOT_SET)
		sLog.SetScreenLoggingLevel(screen_log_level);
	
	if(file_log_level != (int)DEF_VALUE_NOT_SET)
		sLog.SetFileLoggingLevel(file_log_level);

	string host = Config.MainConfig.GetStringDefault("Listen", "Host", DEFAULT_HOST);
	int wsport = Config.MainConfig.GetIntDefault("Listen", "WorldServerPort", DEFAULT_WORLDSERVER_PORT);

	new ScriptMgr;

	sWorld.SetInitialWorldSettings();
	sWorld.SetStartTime((uint32)time(NULL));
	
	_HookSignals();

	launch_thread(new CConsoleThread);

	uint32 realCurrTime, realPrevTime;
	realCurrTime = realPrevTime = getMSTime();

	// initialize thread system
	sThreadMgr.Initialize();
	
	// Socket loop!
	uint32 start;
	uint32 diff;
	uint32 last_time = now();
	uint32 etime;
	uint32 next_printout = getMSTime(), next_send = getMSTime();

	// Start Network Subsystem
	sLog.outString("Starting network subsystem...");
	new SocketMgr;
	new SocketGarbageCollector;
	sSocketMgr.SpawnWorkerThreads();

	sScriptMgr.LoadScripts();


	sLog.outString("Threading system initialized, currently %u threads are active.", sThreadMgr.GetThreadCount());	

	LoadingTime = getMSTime() - LoadingTime;
	sLog.outString ("\nServer is ready for connections. Startup time: %ums\n", LoadingTime );
 
	/* write pid file */
	FILE * fPid = fopen("antrix.pid", "w");
	if(fPid)
	{
		uint32 pid;
#ifdef WIN32
		pid = GetCurrentProcessId();
#else
		pid = getpid();
#endif
		fprintf(fPid, "%u", (unsigned int)pid);
		fclose(fPid);
	}
#ifndef CLUSTERING
	/* Connect to realmlist servers / logon servers */
	new LogonCommHandler();
	sLogonCommHandler.Startup();

	// Create listener
	ListenSocket<WorldSocket> * ls = new ListenSocket<WorldSocket>(host.c_str(), wsport);
    bool listnersockcreate = ls->IsOpen();
	while(!m_stopEvent && listnersockcreate)
#else
	new ClusterInterface;
	sClusterInterface.ConnectToRealmServer();
	while(!m_stopEvent)
#endif
	{
		start = now();
		diff = start - last_time;

#ifndef CLUSTERING
		sLogonCommHandler.UpdateSockets();
		ls->Update();
#else
		sClusterInterface.Update();
#endif
		sSocketGarbageCollector.Update();

		/* UPDATE */
		last_time = now();
		etime = last_time - start;
		if(m_ShutdownEvent)
		{
			if(getMSTime() >= next_printout)
			{
				if(m_ShutdownTimer > 60000.0f)
				{
					if(!((int)(m_ShutdownTimer)%60000))
						sLog.outString("Server shutdown in %i minutes.", (int)(m_ShutdownTimer / 60000.0f));
				}
				else
					sLog.outString("Server shutdown in %i seconds.", (int)(m_ShutdownTimer / 1000.0f));
					
				next_printout = getMSTime() + 500;
			}
			if(getMSTime() >= next_send)
			{
				// broadcast packet.
				WorldPacket data(20);
				data.SetOpcode(SMSG_SERVER_MESSAGE);
				data << uint32(SERVER_MSG_SHUTDOWN_TIME);
				int time = m_ShutdownTimer / 1000;
				if(time > 0)
				{
					int mins = 0, secs = 0;
					if(time > 60)
						mins = time / 60;
					if(mins)
						time -= (mins*60);
					secs = time;
					char str[20];
					snprintf(str, 20, "%02u:%02u", mins, secs);
					data << str;
					sWorld.SendGlobalMessage(&data, NULL);
				}
				next_send = getMSTime() + 1000;
			}
			if(diff >= m_ShutdownTimer)
				break;
			else
				m_ShutdownTimer -= diff;
		}
		
		Database_Character->CheckConnections();
		Database_World->CheckConnections();
		sWorld.UpdateQueuedSessions(diff);

		if(50 > etime)
			Sleep(50 - etime);

	}
	_UnhookSignals();

	CConsoleThread *thread = (CConsoleThread*)sThreadMgr.GetThreadByType(THREADTYPE_CONSOLEINTERFACE);
	ASSERT(thread);
	thread->SetThreadState(THREADSTATE_TERMINATE);
	// have to cleanup manually.
	sThreadMgr.RemoveThread(thread);

	sLog.outString("Killing all sockets and network subsystem.");
#ifndef CLUSTERING
	ls->Close();
	delete ls;
#endif
#ifdef WIN32
	sSocketMgr.ShutdownThreads();
#endif
	sSocketMgr.CloseAll();

	// begin server shutdown
	time_t st = time(NULL);
	sLog.outString("Server shutdown initiated at %s", ctime(&st));

	// send a query to wake it up if its inactive
	sLog.outString("Executing pending database queries and closing database thread...");
	// kill the database thread first so we don't lose any queries/data
	((MySQLDatabase*)Database_Character)->SetThreadState(THREADSTATE_TERMINATE);
	((MySQLDatabase*)Database_World)->SetThreadState(THREADSTATE_TERMINATE);

	CharacterDatabase.Execute("UPDATE characters SET online = 0");
	WorldDatabase.Execute("UPDATE characters SET online = 0");

	// wait for it to finish its work
	while(((MySQLDatabase*)Database_Character)->ThreadRunning || ((MySQLDatabase*)Database_World)->ThreadRunning)
	{
		Sleep(100);
	}
	sThreadMgr.RemoveThread(((MySQLDatabase*)Database_Character));
	sThreadMgr.RemoveThread(((MySQLDatabase*)Database_World));

	sLog.outString("All pending database operations cleared.\n");

	sWorld.SaveAllPlayers();
	sLog.outString("");

	delete LogonCommHandler::getSingletonPtr();

	sWorld.ShutdownClasses();
	sLog.outString("\nDeleting World...");
	delete World::getSingletonPtr();

	sLog.outString("Deleting Event Manager...");
	delete EventMgr::getSingletonPtr();

	sLog.outString("Terminating MySQL connections...\n");
	_StopDB();

	sLog.outString("Deleting Network Subsystem...");
	delete SocketMgr::getSingletonPtr();
	delete SocketGarbageCollector::getSingletonPtr();

	sLog.outString("Deleting Script Engine...");
	delete ScriptSystem;

	sLog.outString("\nServer shutdown completed successfully.\n");

	// close the logs
	TextLogger::Thread->Die();

#ifdef WIN32
	WSACleanup();

	// Terminate Entire Application
	//HANDLE pH = OpenProcess(PROCESS_TERMINATE, TRUE, GetCurrentProcessId());
	//TerminateProcess(pH, 0);
	//CloseHandle(pH);

#endif

	return true;
}

bool Master::_StartDB()
{
	string hostname, username, password, database;
	int port = 0;
	int type = 1;
	//string lhostname, lusername, lpassword, ldatabase;
	//int lport = 0;
	//int ltype = 1;
	// Configure Main Database
	
	bool result = Config.MainConfig.GetString("WorldDatabase", "Username", &username);
	Config.MainConfig.GetString("WorldDatabase", "Password", &password);
	result = !result ? result : Config.MainConfig.GetString("WorldDatabase", "Hostname", &hostname);
	result = !result ? result : Config.MainConfig.GetString("WorldDatabase", "Name", &database);
	result = !result ? result : Config.MainConfig.GetInt("WorldDatabase", "Port", &port);
	result = !result ? result : Config.MainConfig.GetInt("WorldDatabase", "Type", &type);
	Database_World = Database::CreateDatabaseInterface();

	if(result == false)
	{
		sLog.outError("sql: One or more parameters were missing from WorldDatabase directive.");
		return false;
	}

	// Initialize it
	if(!WorldDatabase.Initialize(hostname.c_str(), (unsigned int)port, username.c_str(),
		password.c_str(), database.c_str(), Config.MainConfig.GetIntDefault("WorldDatabase", "ConnectionCount", 3),
		16384))
	{
		sLog.outError("sql: Main database initialization failed. Exiting.");
		return false;
	}


	result = Config.MainConfig.GetString("CharacterDatabase", "Username", &username);
	Config.MainConfig.GetString("CharacterDatabase", "Password", &password);
	result = !result ? result : Config.MainConfig.GetString("CharacterDatabase", "Hostname", &hostname);
	result = !result ? result : Config.MainConfig.GetString("CharacterDatabase", "Name", &database);
	result = !result ? result : Config.MainConfig.GetInt("CharacterDatabase", "Port", &port);
	result = !result ? result : Config.MainConfig.GetInt("CharacterDatabase", "Type", &type);
	Database_Character = Database::CreateDatabaseInterface();

	if(result == false)
	{
		sLog.outError("sql: One or more parameters were missing from Database directive.");
		return false;
	}

	// Initialize it
	if(!CharacterDatabase.Initialize(hostname.c_str(), (unsigned int)port, username.c_str(),
		password.c_str(), database.c_str(), Config.MainConfig.GetIntDefault("CharacterDatabase", "ConnectionCount", 3),
		16384))
	{
		sLog.outError("sql: Main database initialization failed. Exiting.");
		return false;
	}

	return true;
}

void Master::_StopDB()
{
	CharacterDatabase.Shutdown();
	WorldDatabase.Shutdown();
    if (Database_World != NULL)
        delete Database_World;
    if (Database_Character != NULL)
        delete Database_Character;
    Database::CleanupLibs();
}

void Master::_HookSignals()
{
	signal(SIGINT, _OnSignal);
	signal(SIGTERM, _OnSignal);
	signal(SIGABRT, _OnSignal);
#ifdef _WIN32
	signal(SIGBREAK, _OnSignal);
#else
	signal(SIGHUP, _OnSignal);
#endif
}

void Master::_UnhookSignals()
{
	signal(SIGINT, 0);
	signal(SIGTERM, 0);
	signal(SIGABRT, 0);
#ifdef _WIN32
	signal(SIGBREAK, 0);
#else
	signal(SIGHUP, 0);
#endif

}

#ifdef WIN32

Mutex m_crashedMutex;

// Crash Handler
void OnCrash(bool Terminate)
{
	sLog.outString("Advanced crash handler initialized.");
	if(!m_crashedMutex.AttemptAcquire())
		TerminateThread(GetCurrentThread(), 0);

	try
	{
		if(World::getSingletonPtr() != 0 && ThreadMgr::getSingletonPtr() != 0)
		{
			sLog.outString("Waiting for all database queries to finish...");
			MySQLDatabase* dbThread = (MySQLDatabase*)sThreadMgr.GetThreadByType(THREADTYPE_DATABASE);
			if(dbThread != 0)
			{
				// end it
				MySQLDatabase * dbThread2 = (MySQLDatabase*)Database_World;
				dbThread = (MySQLDatabase*)Database_Character;
				dbThread->SetThreadState(THREADSTATE_TERMINATE);
				dbThread2->SetThreadState(THREADSTATE_TERMINATE);
				CharacterDatabase.Execute("UPDATE characters SET online = 0");
				WorldDatabase.Execute("UPDATE characters SET online = 0");
				// wait for it to finish its work
				while(dbThread->ThreadRunning || dbThread2->ThreadRunning)
				{
					Sleep(100);
				}
			}
			sLog.outString("All pending database operations cleared.\n");
			sWorld.SaveAllPlayers();
			sLog.outString("Data saved.");
		}
	}
	catch(...)
	{
		sLog.outString("Threw an exception while attempting to save all data.");
	}

	sLog.outString("Closing.");
	
	// beep
	//printf("\x7");
	
	// Terminate Entire Application
	if(Terminate)
	{
		HANDLE pH = OpenProcess(PROCESS_TERMINATE, TRUE, GetCurrentProcessId());
		TerminateProcess(pH, 1);
		CloseHandle(pH);
	}
}

#endif
