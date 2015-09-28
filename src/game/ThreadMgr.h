/****************************************************************************
 *
 * General Object Type File
 *
 */

// Class ThreadMgr - Pool that stores all threads
// and keeps track of them, watches for overloading,
// handles shutdown.

#ifndef _MAPTHREADMGR_H
#define _MAPTHREADMGR_H

class CThread;
class MapMgr;

typedef std::set<CThread*> ThreadSet;

class SessionUpdaterThread;
class SocketUpdaterThread;

class ThreadMgr : public Singleton < ThreadMgr >
{
public:
	ThreadMgr();
	~ThreadMgr();

	void Initialize();
	void Shutdown();
	
	void OnMapMgrCreated(MapMgr *mapMgr);

	void AddThread(CThread *thread);
	void RemoveThread(CThread *thread);
	int GenerateThreadId();
	void GetThreadById(int id); // slow!
	CThread* GetThreadByType(CThreadType type);

	inline ThreadSet::iterator Begin() { return mThreads.begin(); }
	inline ThreadSet::iterator End() { return mThreads.end(); }

	inline void SetBusy(bool val) { m_SetBusy = val; }

	std::string ShowStatus();
	void AppendThreadStatus(CThread* thread, std::stringstream &stream);

	void PauseAllThreads();
	void ResumeAllThreads();

	inline uint32 GetThreadCount() { return mThreads.size(); }

private:
	ThreadSet mThreads;
	int ThreadIdCounter;
	bool m_SetBusy;
	Mutex _mutex;
};

#define sThreadMgr ThreadMgr::getSingleton( )
#endif
