/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef __LOGONCONSOLE_H
#define __LOGONCONSOLE_H

#include "Common.h"
#include "../game/CThreads.h"

class LogonConsoleThread : public ThreadBase
{
public:
	LogonConsoleThread();
	~LogonConsoleThread();
	void run();
};

class LogonConsole :  public Singleton < LogonConsole >
{
	friend class LogonConsoleThread;

public:						// Public methods:
	void kill() { running = false; };

protected:					// Protected methods:
	LogonConsoleThread *_thread;

	// Process one command
	void ProcessCmd(char *cmd);

	// quit | exit
	void TranslateQuit(char *str);
	void ProcessQuit(int delay);
	void CancelShutdown(char *str);

	// help | ?
	void TranslateHelp(char *str);
	void ProcessHelp(char *command);

	void ReloadAccts(char *str);
	bool running;
};

#define sLogonConsole LogonConsole::getSingleton()

#endif
