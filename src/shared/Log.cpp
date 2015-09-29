/****************************************************************************
 *
 * General Object Type File
 *
 */

#include "Common.h"
#include "Config/ConfigEnv.h"
#include "Log.h"
#include "NGLog.h"
#include <stdarg.h>

createFileSingleton( oLog );
createFileSingleton(CLog);
initialiseSingleton( WorldLog );

time_t UNIXTIME;
#ifndef WIN32
static char* colorstrings[TBLUE+1] = {
"",
"\033[22;31m",
"\033[22;32m",
"\033[01;33m",
//"\033[22;37m",
"\033[0m",
"\033[01;37m",
"\033[22;34m",
};
#endif

void oLog::outString( const char * str, ... )
{
    if(m_fileLogLevel < 0 && m_screenLogLevel < 0)
        return;

    va_list ap;
    va_start(ap, str);
    
    if(m_fileLogLevel >= 0)
        fileLogger->AddLineSFormat(true, str, ap);

    if(m_screenLogLevel >= 0)
    {
        vprintf(str, ap);
        putc('\n', stdout);
    }

    va_end(ap);
}

void oLog::outError( const char * err, ... )
{
    if(m_fileLogLevel < 1 && m_screenLogLevel < 1)
        return;

    va_list ap;
    va_start(ap, err);

    if(m_fileLogLevel >= 1)
        fileLogger->AddLineSFormat(true, err, ap);

    if(m_screenLogLevel >= 1)
    {
#ifdef WIN32
        SetConsoleTextAttribute(stderr_handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
#else
        puts(colorstrings[TRED]);
#endif
        vfprintf(stderr, err, ap);
        putc('\n', stderr);
#ifdef WIN32
        SetConsoleTextAttribute(stderr_handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
#else
        puts(colorstrings[TNORMAL]);
#endif
    }

    va_end(ap);
}

void oLog::outBasic( const char * str, ... )
{
    if(m_fileLogLevel < 1 && m_screenLogLevel < 1)
        return;

    va_list ap;
    va_start(ap, str);

    if(m_fileLogLevel >= 1)
        fileLogger->AddLineSFormat(true, str, ap);

    if(m_screenLogLevel >= 1)
    {
        vprintf(str, ap);
        putc('\n', stdout);
    }

    va_end(ap);
}

void oLog::outDetail( const char * str, ... )
{
    if(m_fileLogLevel < 2 && m_screenLogLevel < 2)
        return;

    va_list ap;
    va_start(ap, str);

    if(m_fileLogLevel >= 2)
        fileLogger->AddLineSFormat(true, str, ap);

    if(m_screenLogLevel >= 2)
    {
        vprintf(str, ap);
        putc('\n', stdout);
    }

    va_end(ap);
}

void oLog::outDebug( const char * str, ... )
{
    if(m_fileLogLevel < 3 && m_screenLogLevel < 3)
        return;

    va_list ap;
    va_start(ap, str);

    if(m_fileLogLevel >= 3)
        fileLogger->AddLineSFormat(true, str, ap);

    if(m_screenLogLevel >= 3)
    {
        vprintf(str, ap);
        putc('\n', stdout);
    }

    va_end(ap);
}

void oLog::outMenu( const char * str, ... )
{
    va_list ap;
    va_start(ap, str);
    vprintf( str, ap );
    va_end(ap);
    fflush(stdout);
}

void oLog::Init(int32 fileLogLevel, int32 screenLogLevel)
{
    m_screenLogLevel = screenLogLevel;
    m_fileLogLevel = fileLogLevel;
    fileLogger = new TextLogger(FormatOutputString("logs", "ServerLog", true).c_str(), false);

    if(m_fileLogLevel >= 0)
        fileLogger->Open();

    // get error handle
#ifdef WIN32
    stderr_handle = GetStdHandle(STD_ERROR_HANDLE);
    stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

void oLog::SetScreenLoggingLevel(int32 level)
{
    m_screenLogLevel = level;
}

void oLog::SetFileLoggingLevel(int32 level)
{
    if(level < 0)
    {
        if(fileLogger->IsOpen())
            fileLogger->Close();
    }
    else
    {
        if(!fileLogger->IsOpen())
            fileLogger->Open();
    }
    m_fileLogLevel = level;
}

void SessionLogWriter::write(const char* format, ...)
{
    if(!IsOpen())
        return;

    va_list ap;
    va_start(ap, format);
    char out[32768];

    time_t t = time(NULL);
    tm* aTm = localtime(&t);
    sprintf(out, "[%-4d-%02d-%02d %02d:%02d:%02d] ",aTm->tm_year+1900,aTm->tm_mon+1,aTm->tm_mday,aTm->tm_hour,aTm->tm_min,aTm->tm_sec);
    int l = strlen(out);
    vsnprintf(&out[l], 32768 - l, format, ap);

    AddLine(out);
    va_end(ap);
}

WorldLog::WorldLog()
{
    log = new TextLogger(FormatOutputString("logs", "WorldLog", true).c_str(), false);
    bEnabled = false;

    if (Config.MainConfig.GetBoolDefault("LogLevel", "World", false))
    {
        sLog.outString("  Enabling packetlog output to \"world.log\"");
        Enable();
    } else {
        Disable();
    }
}

void WorldLog::Enable()
{
    if(bEnabled)
        return;

    bEnabled = true;
    log->Open();
}

void WorldLog::Disable()
{
    if(!bEnabled)
        return;

    bEnabled = false;
    log->Close();
}

WorldLog::~WorldLog()
{

}

void oLog::outColor(uint32 colorcode, const char * str, ...)
{
    if( !str ) return;
    va_list ap;
    va_start(ap, str);
#ifdef WIN32
    SetConsoleTextAttribute(stdout_handle, colorcode);
#else
    printf(colorstrings[colorcode]);
#endif
    vprintf( str, ap );
    fflush(stdout);
    va_end(ap);
}
