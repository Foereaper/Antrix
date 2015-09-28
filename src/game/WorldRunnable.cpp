/****************************************************************************
 *
 * General Object Type File
 *
 */

//
// WorldRunnable.cpp
//

#include "StdAfx.h"
#define WORLD_UPDATE_DELAY 50

WorldRunnable::WorldRunnable() : CThread()
{
	ThreadType = THREADTYPE_WORLDRUNNABLE;
}

void WorldRunnable::run()
{
	SetThreadName("WorldRunnable (non-instance/logon)");
	uint32 LastWorldUpdate=getMSTime();
	uint32 LastSessionsUpdate=getMSTime();

	THREAD_TRY_EXECUTION2

	while(ThreadState != THREADSTATE_TERMINATE)
	{
		// Provision for pausing this thread.
		if(ThreadState == THREADSTATE_PAUSED)
		{
			while(ThreadState == THREADSTATE_PAUSED)
			{
				Sleep(200);
			}
		}
		if(ThreadState == THREADSTATE_TERMINATE)
			break;

		ThreadState = THREADSTATE_BUSY;

		uint32 diff;
		//calce time passed
		uint32 now,execution_start;
		now=getMSTime();
		execution_start=now;

		if( now < LastWorldUpdate)//overrun
			diff=WORLD_UPDATE_DELAY;
		else
			diff=now-LastWorldUpdate;
		
		LastWorldUpdate=now;
		sWorld.Update( diff );
		
		now=getMSTime();
		
		if( now < LastSessionsUpdate)//overrun
			diff=WORLD_UPDATE_DELAY;
		else
			diff=now-LastSessionsUpdate;
		
		LastSessionsUpdate=now;
		sWorld.UpdateSessions( diff );
		
		now=getMSTime();
		//we have to wait now 
		
		if(execution_start > now)//overrun
			diff=WORLD_UPDATE_DELAY-now;
		else
			diff=now-execution_start;//time used for updating 
		if(ThreadState == THREADSTATE_TERMINATE)
			break;

		ThreadState = THREADSTATE_SLEEPING;

		/*This is execution time compensating system
			if execution took more than default delay 
			no need to make this sleep*/
		if(diff<WORLD_UPDATE_DELAY)
		Sleep(WORLD_UPDATE_DELAY-diff);
	}

	THREAD_HANDLE_CRASH2

}
