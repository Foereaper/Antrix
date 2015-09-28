/****************************************************************************
 *
 * General Object Type File
 *
 */

#include "LogonStdAfx.h"
#include "LogonConsole.h"
#include "Log.h"

initialiseSingleton(LogonConsole);

void LogonConsoleThread::run()
{
	new LogonConsole;

	SetThreadName("Console Interpreter");
	sLogonConsole._thread = this;
	sLogonConsole.running = true;
	int i = 0;
	char cmd[96];
	

	while (sLogonConsole.running)
	{
		
		// Make sure our buffer is clean to avoid Array bounds overflow
		memset(cmd,0,sizeof(cmd)); 
		// Read in single line from "stdin"
		fgets(cmd, 80, stdin);
		if(!sLogonConsole.running)
			break;

		for( i = 0 ; i < 80 || cmd[i] != '\0' ; i++ )
		{
			if( cmd[i] =='\n' )
			{
				cmd[i]='\0';
				sLogonConsole.ProcessCmd(cmd);
				fflush(stdin);
				break;
			}
		}
	}

	delete LogonConsole::getSingletonPtr();

}

//------------------------------------------------------------------------------
// Protected methods:
//------------------------------------------------------------------------------
// Process one command
void LogonConsole::ProcessCmd(char *cmd)
{
	typedef void (LogonConsole::*PTranslater)(char *str);
	struct SCmd
	{
		char *name;
		PTranslater tr;
	};

	SCmd cmds[] =
	{

		{"?", &LogonConsole::TranslateHelp}, {"help", &LogonConsole::TranslateHelp},
		{ "reload", &LogonConsole::ReloadAccts},
		{"quit", &LogonConsole::TranslateQuit}, {"exit", &LogonConsole::TranslateQuit}, 
	};

	char cmd2[80];
	strcpy(cmd2, cmd);
	for(size_t i = 0; i < strlen(cmd); ++i)
		cmd2[i] = tolower(cmd[i]);

	for (size_t i = 0; i < sizeof(cmds)/sizeof(SCmd); i++)
		if (strncmp(cmd2, cmds[i].name, strlen(cmds[i].name)) == 0)
		{
			(this->*(cmds[i].tr)) (cmd + strlen(cmds[i].name));
			return;
		}

		printf("Console:Unknown console command (use \"help\" for help).\n");
}

void LogonConsole::ReloadAccts(char *str)
{
AccountMgr::getSingleton().ReloadAccounts(false);
IPBanner::getSingleton().Reload();
}

// quit | exit
void LogonConsole::TranslateQuit(char *str)
{
	int delay = str != NULL ? atoi(str) : 5000;
	if(!delay)
		delay = 5000;
	else
		delay *= 1000;

	ProcessQuit(delay);
}
void LogonConsole::ProcessQuit(int delay)
{
	mrunning = false;
}
//------------------------------------------------------------------------------
// help | ?
void LogonConsole::TranslateHelp(char *str)
{
	ProcessHelp(NULL);
}
void LogonConsole::ProcessHelp(char *command)
{
	if (command == NULL)
	{
		sLog.outString("Console:--------help--------");
		sLog.outString("   help, ?: print this text");
		sLog.outString("   reload: reloads accounts");
		sLog.outString("   quit, exit: close program");
	}
}
//------------------------------------------------------------------------------

LogonConsoleThread::LogonConsoleThread()
{

}

LogonConsoleThread::~LogonConsoleThread()
{

}
