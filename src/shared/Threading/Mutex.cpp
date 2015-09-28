#include "Common.h"
#include "Mutex.h"

#ifdef WIN32

/* Windows Critical Section Implementation */
Mutex::Mutex() { InitializeCriticalSection(&cs); }
Mutex::~Mutex() { DeleteCriticalSection(&cs); }

void Mutex::Acquire() { EnterCriticalSection(&cs); }
void Mutex::Release() { LeaveCriticalSection(&cs); }

bool Mutex::AttemptAcquire() { return TryEnterCriticalSection(&cs); }

#else

/* this is done slightly differently on bsd-variants */
#if defined(__FreeBSD__) ||  defined(__APPLE_CC__) || defined(__OpenBSD__)
#define recursive_mutex_flag PTHREAD_MUTEX_RECURSIVE
#else
#define recursive_mutex_flag PTHREAD_MUTEX_RECURSIVE_NP
#endif

/* Linux mutex implementation */
bool Mutex::attr_initalized = false;
pthread_mutexattr_t Mutex::attr;

Mutex::Mutex()
{
	if(!attr_initalized)
	{
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, recursive_mutex_flag);
		attr_initalized = true;
	}

	pthread_mutex_init(&mutex, &attr);
}

Mutex::~Mutex() { pthread_mutex_destroy(&mutex); }

void Mutex::Acquire() { pthread_mutex_lock(&mutex); }
void Mutex::Release() { pthread_mutex_unlock(&mutex); }
bool Mutex::AttemptAcquire() { return (pthread_mutex_trylock(&mutex) == 0); }


#endif
