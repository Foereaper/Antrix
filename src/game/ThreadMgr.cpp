/****************************************************************************
 *
 * General Object Type File
 *
 */

// Class ThreadMgr - Pool that stores all threads
// and keeps track of them, watches for overloading,
// handles shutdown.

#include "StdAfx.h"

initialiseSingleton(ThreadMgr);

ThreadMgr::ThreadMgr()
{
	ThreadIdCounter = 0;
	m_SetBusy = false;
}

ThreadMgr::~ThreadMgr()
{

}

void ThreadMgr::Initialize()
{

}

void ThreadMgr::AddThread(CThread *thread)
{
	_mutex.Acquire();
	mThreads.insert(thread);
	_mutex.Release();
}

void ThreadMgr::RemoveThread(CThread *thread)
{
	// dont add/remove while searching a set. ;)
	_mutex.Acquire();
	mThreads.erase(thread);
	_mutex.Release();
}

#define SETTHREADCOUNT threadcount = mThreads.size()

void ThreadMgr::Shutdown()
{
	uint32 threadcount;
	uint32 timer = getMSTime() + 500;
	uint32 start = getMSTime();
	SETTHREADCOUNT;

	sLog.outString("*** ThreadMgr: Shutdown requested. Requesting termination from %u threads.", threadcount);

	for(ThreadSet::iterator itr = mThreads.begin(); itr != mThreads.end(); ++itr)
		(*itr)->SetThreadState(THREADSTATE_TERMINATE);

	SETTHREADCOUNT;
	sLog.outMenu("*** ThreadMgr: %u threads remaining.		", threadcount);

	while(mThreads.size())
	{
		SETTHREADCOUNT;
		if(getMSTime() > timer)
		{
			sLog.outMenu("\r*** ThreadMgr: %u threads remaining.	   ", threadcount);
			timer = getMSTime() + 1000;
		}
		Sleep(20);
	}

	sLog.outString("\n*** ThreadMgr: Shutdown completed in %u msec.", getMSTime() - start);


}

std::string ThreadMgr::ShowStatus()
{
	std::stringstream s;
	s << endl;
	s << "*** ThreadMgr: " << mThreads.size() << " threads active." << endl;
	s <<	"=============================================================================" << endl;
	s <<	"|  ID  |	  Type		|	 State	  |			Start Time		  |" << endl;
	s <<	"=============================================================================" << endl;
	for(ThreadSet::iterator itr = mThreads.begin(); itr != mThreads.end(); ++itr)
	{
		AppendThreadStatus((*itr), s);
		s << endl;
	}
	s <<	"=============================================================================" << endl;
	s << endl;
		
	return s.str();
}

void ThreadMgr::AppendThreadStatus(CThread* thread, std::stringstream &stream)
{
	char line[400];
	time_t stm = thread->GetStartTime();
	char tmp[40];
	strcpy(tmp, ctime(&stm));
	//strncpy(tmp, tmp, strlen(tmp)-2);
	tmp[strlen(tmp)-1] = 0;
	snprintf(line, 400, "| %4u | %16s | %14s | %30s |", thread->GetThreadId(),
		LookupName(thread->GetThreadType(), g_threadTypes),
		LookupName(thread->GetThreadState(), g_threadStates),
		tmp);

	stream.write(line, strlen(line));	
}

int ThreadMgr::GenerateThreadId()
{
	ThreadIdCounter++;
	return ThreadIdCounter;
}

#undef SETTHREADCOUNT

void ThreadMgr::PauseAllThreads()
{
	_mutex.Acquire();
	sLog.outString("*** ThreadMgr: Pausing %u threads.", mThreads.size());
	for(ThreadSet::iterator itr = mThreads.begin(); itr != mThreads.end(); ++itr)
		(*itr)->SetThreadState(THREADSTATE_PAUSED);

	// give them time to kick in
	Sleep(1000);
	_mutex.Release();
}

void ThreadMgr::ResumeAllThreads()
{
	_mutex.Acquire();
	sLog.outString("*** ThreadMgr: Resuming %u threads.", mThreads.size());
	for(ThreadSet::iterator itr = mThreads.begin(); itr != mThreads.end(); ++itr)
		if((*itr)->GetThreadState() == THREADSTATE_PAUSED)
			(*itr)->SetThreadState(THREADSTATE_PAUSED);

	// give them time to kick in
	Sleep(1000);
	_mutex.Release();
}

CThread* ThreadMgr::GetThreadByType(CThreadType type)
{
	_mutex.Acquire();
	for(ThreadSet::iterator itr = mThreads.begin(); itr != mThreads.end(); ++itr)
	{
		if((*itr)->GetThreadType() == type)
		{
			_mutex.Release();
			return (*itr);
		}
	}
	_mutex.Release();
	return NULL;
}
