/****************************************************************************
 *
 * TextLogger - Multithreaded Async File Logging Framework
 * Copyright (c) 2007 Burlex
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech ASA of Norway and appearing in the file
 * COPYING included in the packaging of this file.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "Common.h"
#include "TextLogger.h"

TextLoggerThread * TextLogger::Thread = 0;

void SetLowThreadPriority()
{
#ifdef WIN32
	::SetThreadPriority( ::GetCurrentThread(), THREAD_PRIORITY_LOWEST );
#else
	struct sched_param param;
	param.sched_priority = 0;
	pthread_setschedparam(pthread_self(), SCHED_OTHER, &param);
#endif
}
TextLogger::TextLogger(const char * filename, bool open)
{
	m_isOpen = false;
	m_writeLock = 0;
	m_filename = strnew(filename, false);
	m_file = 0;
	TextLogger::Thread->AddLogger(this);
	if(!open)
		return;

	m_file = fopen(filename, "a");
	if(m_file == 0)
	{
#ifdef WIN32
		CreateDirectory("logs", 0);
		m_file = fopen(filename, "a");
		if(!m_file)
			return;
#else
		return;
#endif
	}
	m_isOpen = true;
}

void TextLogger::Push(const char * str)
{
	queue.Push((char*)str);
	if(m_writeLock)		// data is pending already
		return;

#ifdef WIN32
	InterlockedIncrement(&m_writeLock);
#else
	m_writeLock++;
#endif
	TextLogger::Thread->AddPendingLogger(this);
}

void TextLogger::Update()
{
	char * str = queue.Pop();
	while(str)
	{
		if(m_file)
		{
			fputs(str, m_file);
			fflush(m_file);
		}
		delete [] str;
		str = queue.Pop();
	}
	m_writeLock = 0;
}

string FormatOutputString(const char * Prefix, const char * Description, bool useTimeStamp)
{

	char p[MAX_PATH];
	p[0] = 0;
	time_t t = time(NULL);
	tm * a = gmtime(&t);
	strcat(p, Prefix);
	strcat(p, "/");
	strcat(p, Description);
	if(useTimeStamp)
	{
		char ftime[100];
		snprintf(ftime, 100, "-%-4d-%02d-%02d %02d-%02d-%02d", a->tm_year+1900, a->tm_mon+1, a->tm_mday, a->tm_hour, a->tm_min, a->tm_sec);
		strcat(p, ftime);
	}

	strcat(p, ".log");
	return string(p);
}

void TextLoggerThread::run()
{
	// use the condition variable to wait until we have any data, hold
	// the thread in a suspended state until then so we don't waste time
	// switching to it
	TextLogger * l;
	SetLowThreadPriority();
	while(true)
	{
		m_condition.BeginSynchronized();
		m_active = false;
		m_condition.Wait();

		if(!m_running)
		{
			// we were told to die! muhahah! :)
			break;
		}

		// ooh! we got mail!
		l = updatePendingLoggers.Pop();
		while(l)
		{
			l->Update();
			l = updatePendingLoggers.Pop();
		}

		if(!m_running)
		{
			// we were told to die! muhahah! :)
			break;
		}

		// the end of another loop :> go back to sleep
		m_condition.EndSynchronized();
	}

	/* kill all the registered textloggers */
	for(set<TextLogger*>::iterator itr = loggers.begin(); itr != loggers.end(); ++itr)
		delete (*itr);

	// set will get cleared in destructor (happens at end of thread)
}

