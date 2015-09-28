/*
 * Multiplatform Async Network Library
 * Copyright (c) 2007 Burlex
 *
 * SocketLinux.cpp - Linux-specific functions of Socket class are located here.
 *
 */

#include "Network.h"
#ifdef CONFIG_USE_EPOLL

void Socket::PostEvent(uint32 events)
{
    if(!IsConnected())
        return;

    assert(!(events & EPOLLOUT && !GetWriteBufferSize()));
    int epoll_fd = sSocketMgr.GetEpollFd();

    struct epoll_event ev;
    ev.data.fd = m_fd;
    ev.events = events | EPOLLONESHOT;

    // post actual event
    if(epoll_ctl(epoll_fd, EPOLL_CTL_MOD, ev.data.fd, &ev))
        printf("!! could not post epoll event: type %u, fd %u\n", (unsigned int)events, m_fd);   
}

void Socket::ReadCallback(uint32 len)
{
    // We have to lock here.
    m_readMutex.Acquire();

    int bytes = recv(m_fd, ((char*)m_readBuffer + m_readByteCount), m_readBufferSize - m_readByteCount, 0);
    if(bytes <= 0)
    {
        m_readMutex.Release();
        Disconnect();
        return;
    }    
    else if(bytes > 0)
    {
        m_readByteCount += bytes;
        // call virtual onread()
        OnRead();
    }

    m_readMutex.Release();
}

void Socket::WriteCallback()
{
    // We should already be locked at this point, so try to push everything out.
    int bytes_written = send(m_fd, (void*)m_writeBuffer, m_writeByteCount, 0);
    if(bytes_written < 0)
    {
        // error.
        Disconnect();
        return;
    }

    RemoveWriteBufferBytes(bytes_written, false);
}

void Socket::BurstPush()
{
    if(AcquireSendLock())
        PostEvent(EPOLLOUT);
}

#endif
