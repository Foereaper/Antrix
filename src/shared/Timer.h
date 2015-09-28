/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef WOW_TIMER_H
#define WOW_TIMER_H

#if PLATFORM == PLATFORM_WIN32
#   include <windows.h>
#   include <mmsystem.h>
#else
#   include <sys/timeb.h>
#endif

#if PLATFORM == PLATFORM_WINDOWS
inline uint32 getMSTime()
{
    return GetTickCount();
}
#else
inline uint32 getMSTime()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
#endif

class IntervalTimer
{
public:
	IntervalTimer() : _interval(0), _current(0) {}

	void Update(time_t diff) { _current += diff; if(_current<0) _current=0;}
	bool Passed() { return _current >= _interval; }
	void Reset() { if(_current >= _interval) _current = _current%_interval;  }
	
	void SetCurrent(time_t current) { _current = current; }
	void SetInterval(time_t interval) {
		_current = 0;
		_interval = interval; 
	}
	time_t GetInterval() const { return _interval; }
	time_t GetCurrent() const { return _current; }

private:
	time_t _interval;
	time_t _current;
};

#endif


