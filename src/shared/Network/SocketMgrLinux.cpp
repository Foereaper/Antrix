/*
 * Multiplatform Async Network Library
 * Copyright (c) 2007 Burlex
 *
 * SocketMgr - epoll manager for Linux.
 *
 */

#include "Network.h"
#ifdef CONFIG_USE_EPOLL

initialiseSingleton(SocketMgr);
void SocketMgr::AddSocket(Socket * s)
{
    assert(fds[s->GetFd()] == 0);

    // Add epoll event based on socket activity.
    struct epoll_event ev;
    memset(&ev, 0, sizeof(epoll_event));
    ev.events = (s->GetWriteBufferSize()) ? EPOLLOUT : EPOLLIN;
    ev.events |= EPOLLONESHOT;      // Only one event at a time.

    ev.data.fd = s->GetFd();
    
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, ev.data.fd, &ev))
    {
        printf("!! could not add to epoll set.\n");
        return;
    }

    fds[s->GetFd()] = s;
}

void SocketMgr::RemoveSocket(Socket * s)
{
    //assert(fds[s->GetFd()] == s);
    if(fds[s->GetFd()] != s)
        return;

    // Remove from epoll list.
    struct epoll_event ev;
    ev.data.fd = s->GetFd();
    ev.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP | EPOLLONESHOT;

    if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ev.data.fd, &ev))
        printf("!! could not remove from epoll set.\n");
    
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
    int fd_count;
    Socket * ptr;
    int i;
    struct epoll_event ev;
    SocketMgr * mgr = SocketMgr::getSingletonPtr();

    while(true)
    {
        fd_count = epoll_wait(mgr->epoll_fd, events, THREAD_EVENT_SIZE, 5000);
        for(i = 0; i < fd_count; ++i)
        {
            if(events[i].data.fd >= SOCKET_HOLDER_SIZE)
            {
                printf("epoll: requested FD that is too high (%u). aborting.\n", events[i].data.fd);
                continue;
            }

            ptr = mgr->fds[events[i].data.fd];

            if(ptr == NULL)
            {
                printf("epoll returned invalid fd (no pointer) of FD %u!!\n", events[i].data.fd);
                continue;
            }

            if(events[i].events & EPOLLHUP || events[i].events & EPOLLERR)
            {
                printf("higup\n");
                // Hangup, or error.
                ptr->Delete();
                continue;
            }

            if(events[i].events & EPOLLIN)
            {
                ptr->ReadCallback(0);               // Len is unknown at this point.
                if(!(events[i].events & EPOLLOUT) && !ptr->HasSendLock())
                    ptr->PostEvent(EPOLLIN);        // Remember we are oneshotting events, so we have to push another.
            }

            if(events[i].events & EPOLLOUT)
            {
                ptr->BurstBegin();          // Lock receive mutex
                ptr->WriteCallback();       // Perform actual send()
                if(ptr->GetWriteBufferSize() > 0)
                {
                    ptr->PostEvent(EPOLLOUT);   // Still remaining data.
                }
                else
                {
                    ptr->DecSendLock();
                    ptr->PostEvent(EPOLLIN);
                }
                ptr->BurstEnd();            // Unlock
            }
        }       
    }
}

#endif
