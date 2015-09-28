#ifndef __CConsole_H
#define __CConsole_H

#include "Common.h"
#include "../game/CThreads.h"

class CConsoleThread : public CThread
{
public:
	CConsoleThread();
	~CConsoleThread();
	void run();
};

class CConsole :  public Singleton < CConsole >
{
	friend class CConsoleThread;

public:						// Public methods:
	bool * running_link;
	~CConsole();
protected:					// Protected methods:
	CConsoleThread *_thread;

	// Process one command
	void ProcessCmd(char *cmd);

	// ver[sion]
	void TranslateVersion(char *str);
	void ProcessVersion();

	// quit | exit
	void TranslateQuit(char *str);
	void ProcessQuit(int delay);
	void CancelShutdown(char *str);

	// help | ?
	void TranslateHelp(char *str);
	void ProcessHelp(char *command);


	void TranslateThreads(char* str);
	void ObjectStats(char *str);

	// getuptime
	void GetUptime(char *str);

	void WideAnnounce(char *str);
	void Announce(char* str);
	void SaveallPlayers(char *str);
	void Kick(char *str);
	void IPBan(char *str);
	void BanAccount(char *str);
	void PlayerInfo(char *str);
};

#define sCConsole CConsole::getSingleton()

#endif
