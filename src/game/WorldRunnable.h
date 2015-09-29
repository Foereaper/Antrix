/****************************************************************************
 *
 * General Object Type File
 *
 */

//
// WorldRunnable.h
//

#ifndef __WORLDRUNNABLE_H
#define __WORLDRUNNABLE_H

#include "../game/CThreads.h"

class WorldRunnable : public CThread
{
public:
    WorldRunnable();
    void run();
};

#endif
