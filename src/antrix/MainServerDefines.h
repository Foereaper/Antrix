#ifndef _MAINSERVER_DEFINES_H
#define _MAINSERVER_DEFINES_H

#include "../shared/TextLogger.h"

class Database;

SERVER_DECL extern Database* Database_Character;
SERVER_DECL extern Database* Database_World;
extern TextLogger * Crash_Log;

#define WorldDatabase (*Database_World)
#define CharacterDatabase (*Database_Character)

#endif
