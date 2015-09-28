/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef WOWSERVER_LOG_H
#define WOWSERVER_LOG_H

#include "Common.h"
#include "Singleton.h"
#include "TextLogger.h"

class WorldPacket;
class WorldSession;

#ifdef WIN32

#define TRED FOREGROUND_RED | FOREGROUND_INTENSITY
#define TGREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define TYELLOW FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
#define TNORMAL FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE
#define TWHITE TNORMAL | FOREGROUND_INTENSITY
#define TBLUE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY

#else

#define TRED 1
#define TGREEN 2
#define TYELLOW 3
#define TNORMAL 4
#define TWHITE 5
#define TBLUE 6

#endif

class SERVER_DECL oLog : public Singleton< oLog > {
public:
  void outString( const char * str, ... );
  void outError( const char * err, ... );
  void outBasic( const char * str, ... );
  void outDetail( const char * str, ... );
  void outDebug( const char * str, ... );
  void outMenu( const char * str, ... );

  void fLogText(const char *text);
  void SetLogging(bool enabled);
  
  void Init(int32 fileLogLevel, int32 screenLogLevel);
  void SetFileLoggingLevel(int32 level);
  void SetScreenLoggingLevel(int32 level);

  void outColor(uint32 colorcode, const char * str, ...);
  TextLogger * fileLogger;
  
#ifdef WIN32
  HANDLE stdout_handle, stderr_handle;
#endif
  int32 m_fileLogLevel;
  int32 m_screenLogLevel;
};

class SessionLogWriter : public TextLogger
{
public:
	SessionLogWriter(const char * filename, bool open) : TextLogger(filename, open) {}

	void write(const char* format, ...);
	void writefromsession(WorldSession* session, const char* format, ...);
};

extern SessionLogWriter * Anticheat_Log;
extern SessionLogWriter * GMCommand_Log;

#define sLog oLog::getSingleton()
#define sCheatLog (*Anticheat_Log)
#define sGMLog (*GMCommand_Log)

class WorldLog : public Singleton<WorldLog>
{
public:
	WorldLog();
	~WorldLog();

	void LogPacket(uint32 len, uint16 opcode, const uint8* data, uint8 direction);
	void Enable();
	void Disable();
private:
	Mutex mutex;
	bool bEnabled;
	TextLogger * log;
};

#define sWorldLog WorldLog::getSingleton()

#endif

