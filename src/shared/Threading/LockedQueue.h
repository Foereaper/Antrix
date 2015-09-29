/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef _THREADING_LOCKED_QUEUE_H
#define _THREADING_LOCKED_QUEUE_H

#include "Mutex.h"
#include <deque>

template<class TYPE>
class LockedQueue
{
public:
    ~LockedQueue()
    {

    }

    inline void add(const TYPE& element)
    {
        mutex.Acquire();
        queue.push_back(element);
        mutex.Release();
    }

    inline TYPE next()
    {
        mutex.Acquire();
        assert(queue.size() > 0);
        TYPE t = queue.front();
        queue.pop_front();
        mutex.Release();
        return t;
    }

    inline uint32 size()
    {
        mutex.Acquire();
        uint32 c = queue.size();
        mutex.Release();
        return c;
    }

    inline TYPE get_first_element()
    {
        mutex.Acquire();
        TYPE t; 
        if(queue.size() == 0)
            t = reinterpret_cast<TYPE>(0);
        else
            t = queue.front();
        mutex.Release();
        return t;            
    }

    inline void pop()
    {
        mutex.Acquire();
        ASSERT(queue.size() > 0);
        queue.pop_front();
        mutex.Release();
    }

protected:
    std::deque<TYPE> queue;
    Mutex mutex;
};

#endif
