/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef FQUEUE_H
#define FQUEUE_H

#include "Condition.h"
#include "Mutex.h"
 
template<class T> 
class FQueue 
{
public:
    inline FQueue() : cond(&lock) {first=last=NULL;size=0;}
    volatile unsigned int size;

    uint32 get_size()
    {
        uint32 ret;
        cond.BeginSynchronized();
        ret = size;
        cond.EndSynchronized();
        return ret;
    }

    void push(T &item)
    {
        h*p=new h;
        p->value=item;
        p->pNext=NULL;
        
        //lock.Acquire();
        cond.BeginSynchronized();
        if(last)//have some items
        {
            last->pNext=p;
            last=p;
            size++;
        }
        else//first item
        {
            last=first=p;
            size=1;
            cond.Signal();
        }
        //lock.Release();
        cond.EndSynchronized();
    }

    T pop()
    {
        //lock.Acquire();
        cond.BeginSynchronized();
        if(size==0)
        cond.Wait();

        h*tmp=first;

        if(--size)//more than 1 item
        {
            first=(h*)first->pNext;
        }
        else//last item
        {
            first=last=NULL;
        }
        //lock.Release();
        cond.EndSynchronized();

        T returnVal = tmp->value;
        delete tmp;
        
        return returnVal;
    }    
    
private:
    struct h
    {
        T value;
        void *pNext;
    };

    h*first;
    h*last;
    
    Mutex lock;
    Condition cond;

};

#endif 


