/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef __STDAFX_H
#define __STDAFX_H

#define _GAME
/*#define CLUSTERING*/

#include <cstring>
#include <cstdlib>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <fstream>
//#include <fstream>


#include "../shared/Common.h"
#include "../shared/MersenneTwister.h"
#include "../shared/WorldPacket.h"
#include "../shared/Log.h"
#include "../shared/NGLog.h"
#include "../shared/ByteBuffer.h"
#include "../shared/StackBuffer.h"
#include "../shared/Config/ConfigEnv.h"
#include "../shared/crc32.h"
#include "../shared/LocationVector.h"

#include <zlib.h>

#include "../shared/Database/DatabaseEnv.h"
#include "../shared/Database/DBCStores.h"
#include "../shared/Database/dbcfile.h"

#include <Network/Network.h>

#include "../shared/Auth/md5.h"
#include "../shared/Auth/BigNumber.h"
#include "../shared/Auth/Sha1.h"
#include "../shared/Auth/WowCrypt.h"
#include "../shared/CrashHandler.h"

#include "UpdateFields.h"
#include "UpdateMask.h"
#include "Opcodes.h"

#ifdef CLUSTERING
#include "../realmserver/WorkerOpcodes.h"
#endif

#include "../shared/CallBack.h"
#include "EventMgr.h"
#include "EventableObject.h"
#include "Object.h"
#include "LootMgr.h"
#include "Unit.h"

#include "AddonMgr.h"
#include "AIInterface.h"
#include "AreaTrigger.h"
#include "BattlegroundMgr.h"
#include "AlteracValley.h"
#include "ArathiBasin.h"
#include "Arenas.h"
#include "CellHandler.h"
#include "Chat.h"
#include "Corpse.h"
#include "Quest.h"
#include "QuestMgr.h"
#include "Creature.h"
#include "DynamicObject.h"
#include "GameObject.h"
#include "Group.h"
#include "Guild.h"
#include "HonorHandler.h"
#include "ItemPrototype.h"
#include "Item.h"
#include "Container.h"
#include "AuctionHouse.h"
#include "AuctionMgr.h"
#include "LfgMgr.h"
#include "MailSystem.h"
#include "Map.h"
#include "MapCell.h"
#include "TerrainMgr.h"
#include "MiscHandler.h"
#include "NPCHandler.h"
#include "Pet.h"
#include "WorldSocket.h"
#include "WorldSession.h"
#include "NameTables.h"
#include "MapMgr.h"
#include "MapScriptInterface.h"
#include "Player.h"
#include "faction.h"
#include "Professions.h"
#include "Skill.h"
#include "SocialMgr.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "TaxiMgr.h"
#include "TransporterHandler.h"
#include "WarsongGulch.h"
#include "WeatherMgr.h"
#include "World.h"
#include "ItemInterface.h"
#include "Stats.h"
#include "WorldCreator.h"
#include "InstanceSaveMgr.h"

#include "ObjectMgr.h"

#include "CThreads.h"
#include "ThreadMgr.h"
#include "ScriptMgr.h"

#include "Channel.h"
#include "ChannelMgr.h"

#include "LogonCommClient.h"
#include "LogonCommHandler.h"
#include "../antrix/MainServerDefines.h"
#include "WorldRunnable.h"

#include "scriptengine/ScriptEngine.h"
#include "scriptengine/ScriptFunctions.h"

#include "../shared/Storage.h"
#include "ObjectStorage.h"

#ifdef CLUSTERING
#include "WorkerServerClient.h"
#include "ClusterInterface.h"
#endif

#endif
