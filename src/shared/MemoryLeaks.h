/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef WOWSERVER_MEMORY_H
#define WOWSERVER_MEMORY_H

#include "Common.h"
#include "Singleton.h"

#if COMPILER == COMPILER_MICROSOFT
#  define _CRTDBG_MAP_ALLOC
#  include <stdlib.h>
#  include <crtdbg.h>
#endif

struct MemoryManager : public Singleton < MemoryManager > {
    MemoryManager();
};

#endif

