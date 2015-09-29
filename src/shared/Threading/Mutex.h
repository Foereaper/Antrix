/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef _THREADING_MUTEX_H
#define _THREADING_MUTEX_H

class SERVER_DECL Mutex
{
public:
    friend class Condition;

    /** Initializes a mutex class, with InitializeCriticalSection / pthread_mutex_init
     */
    Mutex();

    /** Deletes the associated critical section / mutex
     */
    ~Mutex();

    /** Acquires this mutex. If it cannot be acquired immediately, it will block.
     */
    void Acquire();

    /** Releases this mutex. No error checking performed
     */
    void Release();

    /** Attempts to acquire this mutex. If it cannot be acquired (held by another thread)
     * it will return false.
     * @return false if cannot be acquired, true if it was acquired.
     */
    bool AttemptAcquire();

protected:
#ifdef WIN32
    /** Critical section used for system calls
     */
    CRITICAL_SECTION cs;

#else
    /** Static mutex attribute
     */
    static bool attr_initalized;
    static pthread_mutexattr_t attr;

    /** pthread struct used in system calls
     */
    pthread_mutex_t mutex;
#endif
};

#endif

