/****************************************************************************
 *
 * General Object Type File
 *
 */

#include "../shared/Singleton.h"

extern bool mrunning;
class AuthSocket;
extern set<AuthSocket*> _authSockets;
extern Mutex _authSocketLock;

class LogonServer;
class LogonServer : public Singleton< LogonServer >
{
public:
	void CheckForDeadSockets();
	void Run(int argc, char ** argv);
	void Stop();
	uint32 max_build;
	uint32 min_build;
	uint8 sql_hash[20];

private:
	bool m_stopEvent;
};
