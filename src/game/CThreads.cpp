// Class CThread - Base class for all threads in the
// server, and allows for easy management by ThreadMgr.

#include "Common.h"
#include "NameTables.h"
#include "CThreads.h"
#include "ThreadMgr.h"

/* Name tables */
NameTableEntry g_threadStates[] = {
	{ THREADSTATE_TERMINATE, "STATE_TERM" },
	{ THREADSTATE_PAUSED, "TSTATE_PAUSE" },
	{ THREADSTATE_SLEEPING, "STATE_SLEEP" },
	{ THREADSTATE_BUSY, "STATE_BUSY" },
	{ THREADSTATE_AWAITING, "STATE_AWAIT" },
	{ 0, NULL },
};

NameTableEntry g_threadTypes[] = {
	{ THREADTYPE_UNASSIGNED, "UNASSIGNED" },
	{ THREADTYPE_OBJECTUPDATER, "OBJECTUPDATER" },
	{ THREADTYPE_MAPMGR, "MAPMGR" },
	{ THREADTYPE_WORLDRUNNABLE, "WORLDRUNNABLE" },
	{ THREADTYPE_MAILDELIVERY, "MAILDELIVERY" },
	{ THREADTYPE_CONSOLEINTERFACE, "CONSOLE" },
	{ THREADTYPE_IRCBOT, "IRCBOT" },
	{ THREADTYPE_AUCTIONHOUSE, "AUCTIONHOUSE" },
	{ THREADTYPE_NETWORK, "NETWORK" },
	{ THREADTYPE_SESSIONUPDATER, "SESSIONUPDATER" },
	{ THREADTYPE_SOCKETUPDATER, "SOCKETUPDATER" },
	{ THREADTYPE_DATABASE, "DATABASEQUEUE" },
	{ THREADTYPE_IOCPWORKER, "IOCPWORKER" },
	{ THREADTYPE_IOCPLISTENER, "IOCPLISTENER" },
	{ 0, NULL },
};

CThread::CThread() : ThreadBase()
{
	ThreadState = THREADSTATE_AWAITING;
	ThreadType  = THREADTYPE_UNASSIGNED;
	ThreadId	= sThreadMgr.GenerateThreadId();
	start_time  = time(NULL);
	sThreadMgr.AddThread(this);
}

CThread::~CThread()
{
	if(ThreadType == THREADTYPE_CONSOLEINTERFACE || !delete_after_use)
		return; // we're deleted manually
	sThreadMgr.RemoveThread(this);
}

void CThread::run()
{

}

void CThread::manual_start()
{
	launch_thread(this);
}
