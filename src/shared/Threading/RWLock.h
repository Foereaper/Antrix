/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef RWLOCK_H
#define RWLOCK_H

#include "Condition.h"
#include "Mutex.h"

class RWLock
{
public: 
  
	inline void AcquireReadLock()
	{
		//_lock.Acquire();
		_cond.BeginSynchronized();
		_readers++;
		//_lock.Release();
		_cond.EndSynchronized();
	}
	
	inline void ReleaseReadLock()
	{
		//_lock.Acquire();
		_cond.BeginSynchronized();
		if(!(--_readers))
			if(_writers)
				_cond.Signal();
		//_lock.Release();
		_cond.EndSynchronized();
	}

	inline void AcquireWriteLock()
	{
		//_lock.Acquire();
		_cond.BeginSynchronized();
		_writers++;
		if(_readers)
			_cond.Wait();
	}

	inline void ReleaseWriteLock()
	{
		if(--_writers)
			_cond.Signal();
		//_lock.Release();
		_cond.EndSynchronized();
	}
	inline RWLock() : _cond(&_lock) {_readers=0;_writers=0;}
  
	private:
		Mutex _lock;
		Condition _cond;
		volatile unsigned int _readers;
		volatile unsigned int _writers;
   
}; 

#endif
