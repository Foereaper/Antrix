#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "Config/ConfigEnv.h"
#include "Log.h"
#include "Master.h"
//#include <vld.h>
//#include <vldapi.h>

#ifdef WIN32
#include "../shared/CrashHandler.h"
#endif

#ifndef WIN32
#include <sys/resource.h>
#endif

uint8 loglevel = DEFAULT_LOG_LEVEL;
int main(int argc, char ** argv)
{
#ifndef WIN32
	rlimit rl;
	if (getrlimit(RLIMIT_CORE, &rl) == -1)
		printf("getrlimit failed. This could be problem.\n");
	else
	{
		rl.rlim_cur = rl.rlim_max;
		if (setrlimit(RLIMIT_CORE, &rl) == -1)
			printf("setrlimit failed. Server may not save core.dump files.\n");
	}
#endif

	//VLDEnable();
	SetThreadName("Main Thread");

#ifdef WIN32
	// Activate Crash Handler
	StartCrashHandler();

	/*THREAD_TRY_EXECUTION
	{*/
#endif
		if(!sMaster.Run(argc, argv))
		{
			sLog.outString("\nStartup failed for some reason. Please review the error messages above and hit any key to exit.");
		} else {
			sLog.outString("Server exited without failure. Hit any key to close this window.");
		}
#ifdef WIN32
	/*}
	THREAD_HANDLE_CRASH;*/
#endif

	exit(0);
}
