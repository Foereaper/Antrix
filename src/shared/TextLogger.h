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

#ifndef TEXT_LOGGER_H
#define TEXT_LOGGER_H

#include <set>
#include <string>
using namespace std;

#include "Threading/Condition.h"

/** dummy lock to use a non-locked queue.
 */
class DummyLock
{
public:
	inline void Acquire() { }
	inline void Release() { }
};

/** linked-list style queue
 */
template<class T, class LOCK>
class FastQueue
{
	struct node
	{
		T element;
		node * next;
	};

	node * last;
	node * first;
	LOCK m_lock;

public:

	FastQueue()
	{
		last = 0;
		first = 0;
	}

	~FastQueue()
	{
		Clear();
	}

	void Clear()
	{
		// clear any elements
		while(last != 0)
			Pop();
	}

	void Push(T elem)
	{
		m_lock.Acquire();
		node * n = new node;
		if(last)
			last->next = n;
		else
			first = n;

		last = n;
		n->next = 0;
		n->element = elem;
		m_lock.Release();
	}

	T Pop()
	{
		m_lock.Acquire();
		if(first == 0)
		{
			m_lock.Release();
			return reinterpret_cast<T>(0);
		}
        
		T ret = first->element;
		node * td = first;
		first = td->next;
		if(!first)
			last = 0;

		delete td;
		m_lock.Release();
		return ret;
	}

	inline bool HasItems()
	{
		bool ret;
		m_lock.Acquire();
		ret = (first != 0);
		m_lock.Release();
		return ret;
	}
};

inline char * strnew(const char * str, bool addnewline = true)
{
	int len = strlen(str);
	if(!addnewline)
	{
		char * n = new char[len + 1];
		memcpy(n, str, len + 1);
		return n;
	}
	else
	{
		char * n = new char[len + 2];
		memcpy(n, str, len);
		n[len] = '\n';
		n[len+1] = '\0';
		return n;
	}
}

inline char * strfnew(const char * format, va_list ap, bool timestamp = false, bool addnewline = true)
{
	char line[32768];
	int len;
	if(timestamp)
	{
		time_t cu = time(NULL);
		struct tm * a = localtime(&cu);
		sprintf(line, "[%02d:%02d:%02d] ", a->tm_hour, a->tm_min, a->tm_sec);
		int l2 = strlen(line);
		vsnprintf(&line[l2], 32768-l2, format, ap);
	}
	else
        vsnprintf(line, 32768, format, ap);

	len = strlen(line);

	if(!addnewline)
	{
		char * n = new char[len + 1];
		memcpy(n, line, len + 1);
		return n;
	}
	else
	{
		char * n = new char[len + 2];
		memcpy(n, line, len);
		n[len] = '\n';
		n[len+1] = '\0';
		return n;
	}
}

class TextLoggerThread;

class TextLogger
{
	FastQueue<char*, Mutex> queue;
	FILE * m_file;
	bool m_isOpen;
	const char * m_filename;
	volatile long m_writeLock;
public:

	static TextLoggerThread * Thread;

	TextLogger(const char * filename, bool open);
	void Open()
	{
		if(m_isOpen)
			return;

		m_file = fopen(m_filename, "a");
		if(m_file != 0)
			m_isOpen = true;
	}

	~TextLogger()
	{
		// flush any data to the file
		Update();

		// close the file
		m_isOpen = false;
		if(m_file)
			fclose(m_file);
		delete [] m_filename;
	}

	void AddLine(const char * text)
	{
		if(!m_isOpen)
			Open();

		// duplicate the buffer and push it
		Push(strnew(text));
	}

	void AddLineFormat(const char * format, ...)
	{
		if(!m_isOpen)
			Open();

		// duplicate the formatted text and push it
		va_list ap;
		va_start(ap, format);
		Push(strfnew(format, ap));
		va_end(ap);
	}

	void AddLineSFormat(bool timestamp, const char * format, va_list ap)
	{
		if(!m_isOpen)
			Open();

		// duplicate the formatted text and push it
		Push(strfnew(format, ap, timestamp));
	}

	void Add(const char * text)
	{
		if(!m_isOpen)
			Open();

		// duplicate the buffer and push it
		Push(strnew(text, false));
	}

	void AddFormat(const char * format, ...)
	{
		if(!m_isOpen)
			Open();

		// duplicate the formatted text and push it
		va_list ap;
		va_start(ap, format);
		Push(strfnew(format, ap, false, false));
		va_end(ap);
	}

	void AddSFormat(bool timestamp, const char * format, va_list ap)
	{
		if(!m_isOpen)
			Open();

		// duplicate the formatted text and push it
		Push(strfnew(format, ap, timestamp, false));
	}

	void Push(const char * str);
	void Update();

	inline bool IsOpen() { return m_isOpen; }
	void Close()
	{
		if(!m_isOpen)
			return;

		Update();
		if(m_isOpen)
		{
			m_isOpen = false;
			fclose(m_file);
			m_file = 0;
		}
	}

};

class TextLoggerThread : public ThreadBase
{
	bool m_running;
	bool m_active;
	set<TextLogger*> loggers;
	FastQueue<TextLogger*, DummyLock> updatePendingLoggers;
	Mutex m_lock;
	Mutex m_condLock;
	Condition m_condition;
public:
	TextLoggerThread() : m_condition(&m_condLock)
	{
		m_running = true;
		m_active = false;
		TextLogger::Thread = this;
	}

	void AddLogger(TextLogger * ptr)
	{
		m_lock.Acquire();
		loggers.insert(ptr);
		m_lock.Release();
	}

	void AddPendingLogger(TextLogger * ptr)
	{
		m_condition.BeginSynchronized();
		updatePendingLoggers.Push(ptr);
		if(!m_active)
		{
			// this is our first item. signal the other thread to wake up. :)
			m_condition.Signal();
			m_active = true;
		}
		m_condition.EndSynchronized();
	}

	void Die()
	{
		m_running = false;
		m_condition.BeginSynchronized();
		if(!updatePendingLoggers.HasItems())
		{
			// we have no pending data to be written.
			// signal the thread to wake up, otherwise its gonna be waiting indefinitely.
			m_condition.Signal();
		}
		m_condition.EndSynchronized();
	}

	void run();
};


std::string FormatOutputString(const char * Prefix, const char * Description, bool useTimeStamp);
void SetLowThreadPriority();

#endif
