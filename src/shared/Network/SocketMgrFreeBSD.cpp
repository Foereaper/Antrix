/*
 * Multiplatform Async Network Library
 * Copyright (c) 2007 Burlex
 *
 * SocketMgr - epoll manager for Linux.
 *
 */

#include "Network.h"
#ifdef CONFIG_USE_KQUEUE

initialiseSingleton(SocketMgr);
void SocketMgr::AddSocket(Socket * s)
{
    //printf("adding fd %u\n", s->GetFd());
    assert(fds[s->GetFd()] == 0);

    // add kevent
    struct kevent ev;
    int event_mask = (s->GetWriteBufferSize()) ? EVFILT_WRITE : EVFILT_READ;
    EV_SET(&ev, s->GetFd(), event_mask, EV_ADD/* | EV_ONESHOT*/, 0, 0, NULL);
    if(kevent(kq, &ev, 1, 0, 0, NULL) < 0)
    {
        printf("!! could not add kevent to kqueue.\n");
        return;
    }

    fds[s->GetFd()] = s;
}

void SocketMgr::RemoveSocket(Socket * s)
{
    //printf("remove fd: %u\n", s->GetFd());
    //assert(fds[s->GetFd()] == s);
    if(fds[s->GetFd()] != s)
        return;

    // remove kevent
    struct kevent ev;
    EV_SET(&ev, s->GetFd(), EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
    int i1 = kevent(kq, &ev, 1, 0, 0, NULL);
    EV_SET(&ev, s->GetFd(), EVFILT_READ, EV_DELETE, 0, 0, NULL);
    int i2 = kevent(kq, &ev, 1, 0, 0, NULL);

    /*printf("i1: %d, i2: %d\n", i1, i2);
    if(i1 < 0 || i2 < 0)
        printf("!! could not remove from kqueue!\n");*/
    
    fds[s->GetFd()] = 0;
}

void SocketMgr::CloseAll()
{
    for(uint32 i = 0; i < SOCKET_HOLDER_SIZE; ++i)
        if(fds[i] != NULL)
            fds[i]->Delete();
}

void SocketMgr::SpawnWorkerThreads()
{
    uint32 count = 1;
    for(uint32 i = 0; i < count; ++i)
        launch_thread(new SocketWorkerThread());
}

void SocketWorkerThread::run()
{
    //printf("Worker thread started.\n");
    int fd_count;
    Socket * ptr;
    int i;
    struct kevent ev;
    struct timespec ts;
    ts.tv_nsec = 0;
    ts.tv_sec = 5;

    SocketMgr * mgr = SocketMgr::getSingletonPtr();
    int kq = mgr->GetKq();

    while(true)
    {
        fd_count = kevent(kq, NULL, 0, &events[0], THREAD_EVENT_SIZE, &ts);
        //printf("event count: %u\n", i);
        for(i = 0; i < fd_count; ++i)
        {

            //printf("event flags: %d, filter %d\n", events[i].flags, events[i].filter);
            if(events[i].ident >= SOCKET_HOLDER_SIZE)
            {
                printf("kqueue: requested FD that is too high (%u). aborting.\n", events[i].ident);
                continue;
            }

            ptr = mgr->fds[events[i].ident];

            if(ptr == NULL)
            {
                printf("kqueue returned invalid fd (no pointer) of FD %u!!\n", events[i].ident);
                continue;
            }

            if(events[i].flags & EV_EOF)
            {
                //printf("higup\n");
                // Hangup, or error.
                ptr->Delete();
                continue;
            }

            if(events[i].filter == EVFILT_WRITE)
            {
                ptr->BurstBegin();          // Lock receive mutex
                ptr->WriteCallback();       // Perform actual send()
                if(ptr->GetWriteBufferSize() > 0)
                {
                    //printf("posting cuz of remaining data: %u\n", ptr->GetWriteBufferSize());
                    ptr->PostEvent(EVFILT_WRITE, true);   // Still remaining data.
                }
                else
                {
                    //printf("posting read event cuz of empty buffer.\n");
                    ptr->DecSendLock();
                    //ptr->PostEvent(EVFILT_READ, false);
                }
                ptr->BurstEnd();            // Unlock
            }

            if(events[i].filter == EVFILT_READ)
            {
                ptr->ReadCallback(0);               // Len is unknown at this point.
                /*if(!(events[i].flags & EVFILT_WRITE) && !ptr->HasSendLock())*/
                //ptr->PostEvent(EVFILT_READ, true);        // Remember we are oneshotting events, so we have to push another.
            }


        }       
    }
}

#endif
