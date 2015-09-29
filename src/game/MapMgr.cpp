/****************************************************************************
 *
 * General Object Type File
 *
 */

//
// MapMgr.cpp
//

#include "StdAfx.h"
#define MAP_MGR_UPDATE_PERIOD 100

MapMgr::MapMgr(Map *map, uint32 mapId, uint32 instanceid) : CellHandler<MapCell>(map), _mapId(mapId), eventHolder(instanceid)
{
	ThreadType = THREADTYPE_MAPMGR;
	_shutdown = false;
	m_instanceID = instanceid;
	m_UpdateDistance = sWorld.GetUpdateDistance();
	pMapInfo = WorldMapInfoStorage.LookupEntry(mapId);
    iInstanceMode = 0;
	reset_pending = false;
	DeletionPending = false;

	// Create script interface
	ScriptInterface = new MapScriptInterface(*this);
	CreationTime = time(NULL);
	ExpiryTime = 0;
	RaidExpireTime = 0;
	if(pMapInfo && pMapInfo->type == INSTANCE_RAID || pMapInfo && pMapInfo->type == INSTANCE_MULTIMODE)
	{
		if(!pMapInfo->cooldown)
			pMapInfo->cooldown = 604800;

		RaidExpireTime = (CreationTime + (pMapInfo ? pMapInfo->cooldown : 604800));
	}
	m_iCreator = 0;
	m_GroupSignatureId = 0;

	// Set up storage arrays
	m_CreatureArraySize = map->CreatureSpawnCount;
	m_GOArraySize = map->GameObjectSpawnCount;

	//m_CreatureStorage = new Creature*[m_CreatureArraySize];
	m_CreatureStorage = (Creature**)malloc(sizeof(Creature*) * m_CreatureArraySize);
	memset(m_CreatureStorage,0,sizeof(Creature*)*m_CreatureArraySize);

	//m_GOStorage = new GameObject*[m_GOArraySize];
	m_GOStorage = (GameObject**)malloc(sizeof(GameObject*) * m_GOArraySize);
	memset(m_GOStorage,0,sizeof(GameObject*)*m_GOArraySize);
	m_GOHighGuid = m_CreatureHighGuid = 0;
	m_DynamicObjectHighGuid=0; 
	// dont allow it to delete us when the thread exits :)
	delete_after_use = false;
	lastUnitUpdate = getMSTime();
	lastGameobjectUpdate = getMSTime();
	m_battleground = 0;

	m_holder = &eventHolder;
	m_event_Instanceid = eventHolder.GetInstanceID();
	thread_is_alive = true;
	delete_pending = false;
}


MapMgr::~MapMgr()
{
	if(thread_is_alive && !_shutdown)
	{
		sLog.outString("possible crash! instance deletion while thread is alive! oh noes!");
		Crash_Log->AddLine("possible crash! instance deletion while thread is alive! oh noes!");
#ifdef WIN32
		CStackWalker ws;
		ws.ShowCallstack();
#endif
	}
	_shutdown=true;
	sEventMgr.RemoveEvents(this);
	delete ScriptInterface;
	
	// Remove objects
	sLog.outString("	Emptying all cells of objects...");
	if(_cells)
	{
		for (uint32 i = 0; i < _sizeX; i++)
		{
			for (uint32 j = 0; j < _sizeY; j++)
			{
				if(_cells[i][j] != 0)
					_cells[i][j]->RemoveObjects();
			}
		}
	}

	sLog.outString("	Instance %d deleted (MapId: %u)" , m_instanceID, _mapId);
	sLog.outString("	Instance closed successfully.");

	free(m_GOStorage);
	free(m_CreatureStorage);
}


void MapMgr::PushObject(Object *obj)
{
#ifdef WIN32
	if(GetCurrentThreadId()!=threadid && !_shutdown)
	{
		printf("Push object of mapmgr is accessed from external thread!!!\n");
		Crash_Log->AddLine("Push object of mapmgr is accessed from external thread!!!");
		CStackWalker sw;
		sw.ShowCallstack();
	}
#endif
	/////////////
	// Assertions
	/////////////
	ASSERT(obj);
	
	// That object types are not map objects. TODO: add AI groups here?
	if(obj->GetTypeId() == TYPEID_ITEM || obj->GetTypeId() == TYPEID_CONTAINER)
	{
		// mark object as updatable and exit
		return;
	}
	
	
	obj->ClearInRangeSet();
	ASSERT(obj->GetMapId() == _mapId);
	if(!(obj->GetPositionX() < _maxX && obj->GetPositionX() > _minX) || 
	   !(obj->GetPositionY() < _maxY && obj->GetPositionY() > _minY))
	{
		obj->SetPosition(0, 0, 0, 0, false);
	}

	ASSERT(obj->GetPositionY() < _maxY && obj->GetPositionY() > _minY);
	ASSERT(_cells);

	///////////////////////
	// Get cell coordinates
	///////////////////////

	uint32 x = GetPosX(obj->GetPositionX());
	uint32 y = GetPosY(obj->GetPositionY());

	if(x >= _sizeX || y >= _sizeY)
	{
		obj->SetMapMgr(0);
		return;		
	}

	MapCell *objCell = GetCell(x,y);
	if (!objCell)
	{
		objCell = Create(x,y);
		objCell->Init(x, y, _mapId, this);
	}

	uint32 endX = x < _sizeX ? x + 1 : _sizeX;
	uint32 endY = y < _sizeY ? y + 1 : _sizeY;
	uint32 startX = x > 0 ? x - 1 : 0;
	uint32 startY = y > 0 ? y - 1 : 0;
	uint32 posX, posY;
	MapCell *cell;
	MapCell::ObjectSet::iterator iter;

	ByteBuffer * buf = 0;
	uint32 count;
	Player *plObj;

	if(obj->GetTypeId() == TYPEID_PLAYER)
		plObj = ((Player*)obj);
	else
		plObj = NULL;

	//////////////////////
	// Build in-range data
	//////////////////////

	for (posX = startX; posX <= endX; posX++ )
	{
		for (posY = startY; posY <= endY; posY++ )
		{
			cell = GetCell(posX, posY);
			if (cell)
			{
				UpdateInRangeSet(obj, plObj, cell, &buf);
			}
		}
	}

	if(plObj)
	{
		sLog.outDetail("Creating player " I64FMT " for himself.", obj->GetGUID());
		ByteBuffer pbuf(10000);
		count = plObj->BuildCreateUpdateBlockForPlayer(&pbuf, plObj);
		plObj->PushUpdateData(&pbuf, count);
	}

	//Add to the cell's object list
	objCell->AddObject(obj);

	obj->SetMapCell(objCell);
	 //Add to the mapmanager's object list
	if(plObj)
	{
	   m_PlayerStorage[plObj->GetGUIDLow()] = plObj;
	   UpdateCellActivity(x, y, 2);
	}
	else
	switch(UINT32_LOPART(obj->GetGUIDHigh()))
	{
		case HIGHGUID_UNIT:
			///ASSERT(obj->GetGUIDLow() <= m_CreatureHighGuid);
			m_CreatureStorage[obj->GetGUIDLow()] = (Creature*)obj;
			break;

		case HIGHGUID_PET:
			m_PetStorage[obj->GetGUIDLow()] = (Pet*)obj;
			break;

		case HIGHGUID_DYNAMICOBJECT:
			m_DynamicObjectStorage[obj->GetGUIDLow()] = (DynamicObject*)obj;
			break;

		case HIGHGUID_GAMEOBJECT:
			m_GOStorage[obj->GetGUIDLow()] = (GameObject*)obj;
			break;
	}

	// Handle activation of that object.
	if(objCell->IsActive() && obj->CanActivate())
		obj->Activate(this);

	// Add the session to our set if it is a player.
	if(plObj)
	{
		Sessions.insert(plObj->GetSession());

		// Change the instance ID, this will cause it to be removed from the world thread (return value 1)
		plObj->GetSession()->SetInstance(GetInstanceID());
	}

	if(buf)
		delete buf;

	if(plObj && InactiveMoveTime)
		InactiveMoveTime = 0;
}


void MapMgr::RemoveObject(Object *obj)
{
#ifdef WIN32
	if(GetCurrentThreadId()!=threadid && !_shutdown)
	{
		printf("Remove object of mapmgr is accessed from external thread!!!\n");
		Crash_Log->AddLine("Remove object of mapmgr is accessed from external thread!!!\n");
		CStackWalker sw;
		sw.ShowCallstack();
		sLog.outString("");
	}
#endif
	/////////////
	// Assertions
	/////////////

	ASSERT(obj);
	ASSERT(obj->GetMapId() == _mapId);
	ASSERT(obj->GetPositionX() > _minX && obj->GetPositionX() < _maxX);
	ASSERT(obj->GetPositionY() > _minY && obj->GetPositionY() < _maxY);
	ASSERT(_cells);

	if(obj->Active)
		obj->Deactivate(this);

	_updates.erase(obj);
	obj->ClearUpdateMask();
	Player * plObj = (obj->GetTypeId() == TYPEID_PLAYER) ? ((Player*)obj) : 0;

	///////////////////////////////////////
	// Remove object from all needed places
	///////////////////////////////////////
 
	switch(UINT32_LOPART(obj->GetGUIDHigh()))
	{
		case HIGHGUID_UNIT:
			ASSERT(obj->GetGUIDLow() <= m_CreatureHighGuid);
			m_CreatureStorage[obj->GetGUIDLow()] = 0;
			  break;

		case HIGHGUID_PET:
			m_PetStorage.erase(obj->GetGUIDLow());
			break;

		case HIGHGUID_DYNAMICOBJECT:
			m_DynamicObjectStorage.erase(obj->GetGUIDLow());
			break;

		case HIGHGUID_GAMEOBJECT:
			ASSERT(obj->GetGUIDLow() <= m_GOHighGuid);
			m_GOStorage[obj->GetGUIDLow()] = 0;
			break;
	}

	// That object types are not map objects. TODO: add AI groups here?
	if(obj->GetTypeId() == TYPEID_ITEM || obj->GetTypeId() == TYPEID_CONTAINER)
	{
		return;
	}


	if(!obj->GetMapCell())
	{
		/* set the map cell correctly */
		obj->SetMapCell(this->GetCellByCoords(obj->GetPositionX(), obj->GetPositionY()));
	}
	ASSERT(obj->GetMapCell());

	// Remove object from cell
	obj->GetMapCell()->RemoveObject(obj);

	// Unset object's cell
	obj->SetMapCell(NULL);

	// Clear any updates pending
	if(obj->GetTypeId() == TYPEID_PLAYER)
	{
		_processQueue.erase(((Player*)obj));
		((Player*)obj)->ClearAllPendingUpdates();
	}
	
	// Remove object from all objects 'seeing' him

	for (Object::InRangeSet::iterator iter = obj->GetInRangeSetBegin();
		iter != obj->GetInRangeSetEnd(); ++iter)
	{
		if((*iter)->GetTypeId() == TYPEID_PLAYER)
			if (((Player*)(*iter))->IsVisible(obj) && static_cast<Player*>(*iter)->m_TransporterGUID != obj->GetGUID())
				((Player*)*iter)->PushOutOfRange(obj->GetNewGUID());

		(*iter)->RemoveInRangeObject(obj);
	}
	
	// Clear object's in-range set
	obj->ClearInRangeSet();

	// If it's a player - update his nearby cells
	if(!_shutdown && obj->GetTypeId() == TYPEID_PLAYER)
	{
		// get x/y
		uint32 x = GetPosX(obj->GetPositionX());
		uint32 y = GetPosY(obj->GetPositionY());
		UpdateCellActivity(x, y, 2);
		m_PlayerStorage.erase(((Player*)obj)->GetGUIDLow());
	}

	// Remove the session from our set if it is a player.
	if(plObj)
	{
		// Setting an instance ID here will trigger the session to be removed
		// by MapMgr::run(). :)
		plObj->GetSession()->SetInstance(0);

		// Add it to the global session set.
		// Don't "re-add" to session if it is being deleted.
		if(!plObj->GetSession()->bDeleted)
			sWorld.AddGlobalSession(plObj->GetSession());
	}

	if(!HasPlayers() && !InactiveMoveTime && RaidExpireTime)
		InactiveMoveTime = time(NULL) + (10 * 60);	   // 10 mins -> move to inactive
}

void MapMgr::ChangeObjectLocation(Object *obj)
{
#ifdef WIN32
	if(GetCurrentThreadId()!=threadid)
	{
		sLog.outString("Change object location of mapmgr is accessed from external thread!!!");
		Crash_Log->AddLine("Change object location of mapmgr is accessed from external thread!!!");
		CStackWalker sw;
		sw.ShowCallstack();
		sLog.outString("");
	}
#endif
	// Items and containers are of no interest for us
	if(obj->GetTypeId() == TYPEID_ITEM || obj->GetTypeId() == TYPEID_CONTAINER)
	{
		return;
	}

	Player *plObj, *plObj2;
	ByteBuffer * buf = 0;

	if(obj->GetTypeId() == TYPEID_PLAYER) {
		plObj = ((Player*)obj);
	} else {
		plObj = NULL;
	}

	Object* curObj;
	float fRange;

	///////////////////////////////////////
	// Update in-range data for old objects
	///////////////////////////////////////

	for (Object::InRangeSet::iterator iter = obj->GetInRangeSetBegin();
		iter != obj->GetInRangeSetEnd();)
	{
		curObj = *iter;
		iter++;
		if(curObj->IsPlayer() && obj->IsPlayer() && plObj->m_TransporterGUID && plObj->m_TransporterGUID == ((Player*)curObj)->m_TransporterGUID)
			fRange = 0.0f;			 // unlimited distance for people on same boat
		else if((UINT32_LOPART(curObj->GetGUIDHigh()) == HIGHGUID_TRANSPORTER || UINT32_LOPART(obj->GetGUIDHigh()) == HIGHGUID_TRANSPORTER))
			fRange = 0.0f;			  // unlimited distance for transporters (only up to 2 cells +/- anyway.)
		else
			fRange = m_UpdateDistance;	  // normal distance

		if (curObj->GetDistance2dSq(obj) > fRange && fRange > 0)
		{
			if( plObj )
			{
				if (plObj->IsVisible(curObj))
				{
					plObj->PushOutOfRange(curObj->GetNewGUID());
					plObj->RemoveVisibleObject(curObj);
				}
			}

			if( curObj->IsPlayer() )
			{
				plObj2 = ((Player*)curObj);
				if (plObj2->IsVisible(obj))
				{
					plObj2->PushOutOfRange(obj->GetNewGUID());
					plObj2->RemoveVisibleObject(obj);
				}
			}

			obj->RemoveInRangeObject(curObj);
			curObj->RemoveInRangeObject(obj);
		}
	}
	
	///////////////////////////
	// Get new cell coordinates
	///////////////////////////

	uint32 cellX = GetPosX(obj->GetPositionX());
	uint32 cellY = GetPosY(obj->GetPositionY());

	if(cellX >= _sizeX || cellY >= _sizeY)
	{
		return;
	}

	MapCell *objCell = GetCell(cellX, cellY);
	if (!objCell)
	{
		objCell = Create(cellX,cellY);
		objCell->Init(cellX, cellY, _mapId, this);
	}

	// If object moved cell
	if (objCell != obj->GetMapCell())
	{
		// THIS IS A HACK!
		// Current code, if a creature on a long waypoint path moves from an active
		// cell into an inactive one, it will disable itself and will never return.
		// This is to prevent cpu leaks. I will think of a better solution very soon :P

		if(!objCell->IsActive() && !plObj && obj->Active)
			obj->Deactivate(this);

		if(obj->GetMapCell())
			obj->GetMapCell()->RemoveObject(obj);
	
		objCell->AddObject(obj);
		obj->SetMapCell(objCell);

		// if player we need to update cell activity
		// radius = 2 is used in order to update both
		// old and new cells
		if(obj->GetTypeId() == TYPEID_PLAYER)
		{
			// have to unlock/lock here to avoid a deadlock situation.
			UpdateCellActivity(cellX, cellY, 2);
		}
	}


	//////////////////////////////////////
	// Update in-range set for new objects
	//////////////////////////////////////

	uint32 endX = cellX < _sizeX ? cellX + 1 : _sizeX;
	uint32 endY = cellY < _sizeY ? cellY + 1 : _sizeY;
	uint32 startX = cellX > 0 ? cellX - 1 : 0;
	uint32 startY = cellY > 0 ? cellY - 1 : 0;
	uint32 posX, posY;
	MapCell *cell;
	MapCell::ObjectSet::iterator iter;

	for (posX = startX; posX <= endX; ++posX )
	{
		for (posY = startY; posY <= endY; ++posY )
		{
			cell = GetCell(posX, posY);
			if (cell)
			   UpdateInRangeSet(obj, plObj, cell, &buf);
		}
	}

	if(buf)
		delete buf;
}

void MapMgr::UpdateInRangeSet(Object *obj, Player *plObj, MapCell* cell, ByteBuffer ** buf)
{
#define CHECK_BUF if(!*buf) *buf = new ByteBuffer(2500)

	Object *curObj;
	Player *plObj2;
	int count;
	ObjectSet::iterator iter = cell->Begin();
	float fRange;
	bool cansee, isvisible;

	while(iter != cell->End())
	{
		curObj = *iter;
		++iter;
		if(curObj->IsPlayer() && obj->IsPlayer() && plObj && plObj->m_TransporterGUID && plObj->m_TransporterGUID == ((Player*)curObj)->m_TransporterGUID)
			fRange = 0.0f;			 // unlimited distance for people on same boat
		else if((UINT32_LOPART(curObj->GetGUIDHigh()) == HIGHGUID_TRANSPORTER || UINT32_LOPART(obj->GetGUIDHigh()) == HIGHGUID_TRANSPORTER))
			fRange = 0.0f;			  // unlimited distance for transporters (only up to 2 cells +/- anyway.)
		else
			fRange = m_UpdateDistance;	  // normal distance

		if ( curObj != obj &&
			((curObj)->GetDistance2dSq(obj) <= fRange || fRange == 0.0f) )
		{
			if(!obj->IsInRangeSet(curObj))
			{
				// Object in range, add to set
				curObj->AddInRangeObject(obj);
				obj->AddInRangeObject(curObj);

				if(curObj->IsPlayer())
				{
					plObj2 = ((Player*)curObj);

					if (plObj2->CanSee(obj) && !plObj2->IsVisible(obj))
					{
						CHECK_BUF;
						count = obj->BuildCreateUpdateBlockForPlayer(*buf, plObj2);
						plObj2->PushUpdateData(*buf, count);
						plObj2->AddVisibleObject(obj);
						(*buf)->clear();
					}
				}

				if(plObj)
				{
					if (plObj->CanSee(curObj) && !plObj->IsVisible(curObj))
					{
						CHECK_BUF;
						count = curObj->BuildCreateUpdateBlockForPlayer(*buf, plObj);
						plObj->PushUpdateData(*buf, count);
						plObj->AddVisibleObject(curObj);
						(*buf)->clear();
					}
				}
			}
			else
			{
				// Check visiblility
				if(curObj->IsPlayer())
				{
					plObj2 = ((Player*)curObj);
					cansee = plObj2->CanSee(obj);
					isvisible = plObj2->IsVisible(obj);
					if(!cansee && isvisible)
					{
						plObj2->PushOutOfRange(obj->GetNewGUID());
						plObj2->RemoveVisibleObject(obj);
					}
					else if(cansee && !isvisible)
					{
						CHECK_BUF;
						count = obj->BuildCreateUpdateBlockForPlayer(*buf, plObj2);
						plObj2->PushUpdateData(*buf, count);
						plObj2->AddVisibleObject(obj);
						(*buf)->clear();
					}
				}

				if(plObj)
				{
					cansee = plObj->CanSee(curObj);
					isvisible = plObj->CanSee(curObj);
					if(!cansee && isvisible)
					{
						plObj->PushOutOfRange(curObj->GetNewGUID());
						plObj->RemoveVisibleObject(curObj);
					}
					else if(cansee && !isvisible)
					{
						CHECK_BUF;
						count = curObj->BuildCreateUpdateBlockForPlayer(*buf, plObj);
						plObj->PushUpdateData(*buf, count);
						plObj->AddVisibleObject(curObj);
						(*buf)->clear();
					}
				}
			}
		}
	}
}

void MapMgr::_UpdateObjects()
{
	if(this->pMapInfo && pMapInfo->type != INSTANCE_NULL)
	{
		if(HasPlayers() && reset_pending)
		{
			reset_pending = false;
			ExpiryTime = 0;
		}
		else if(!HasPlayers() && !reset_pending)
		{
			reset_pending = true;
			ExpiryTime = time(NULL) + 600;
		}
	}

	if(!_updates.size() && !_processQueue.size())
		return;

	Object *pObj;
	Player *pOwner;
	//std::set<Object*>::iterator it_start, it_end, itr;
	std::set<Player*>::iterator it_start, it_end, itr;
	Player * lplr;
	ByteBuffer update(2500);
	uint32 count = 0;
	
	UpdateQueue::iterator iter = _updates.begin();
	PUpdateQueue::iterator it, eit;

	for(; iter != _updates.end();)
	{
		pObj = *iter;
		++iter;
		if(!pObj) continue;

		if(pObj->GetTypeId() == TYPEID_ITEM || pObj->GetTypeId() == TYPEID_CONTAINER)
		{
			// our update is only sent to the owner here.
			pOwner = static_cast<Item*>(pObj)->GetOwner();
			if(pOwner != NULL)
			{
				count = static_cast<Item*>(pObj)->BuildValuesUpdateBlockForPlayer(&update, pOwner);
				// send update to owner
				pOwner->PushUpdateData(&update, count);
				update.clear();
			}
		} else {
			if(pObj->IsInWorld())
			{
				// players have to receive their own updates ;)
				if(pObj->GetTypeId() == TYPEID_PLAYER)
				{
					// need to be different! ;)
					count = pObj->BuildValuesUpdateBlockForPlayer(&update, static_cast<Player*>(pObj));
					((Player*)pObj)->PushUpdateData(&update, count);
					update.clear();
				}

				if(pObj->IsUnit() && pObj->HasUpdateField(UNIT_FIELD_HEALTH))
					((Unit*)pObj)->EventHealthChangeSinceLastUpdate();
				// build the update
				count = pObj->BuildValuesUpdateBlockForPlayer(&update, NULL);

				it_start = pObj->GetInRangePlayerSetBegin();
				it_end = pObj->GetInRangePlayerSetEnd();
				for(itr = it_start; itr != it_end;)
				{
					lplr = *itr;
					++itr;
					// Make sure that the target player can see us.
					if(lplr->GetTypeId() == TYPEID_PLAYER && lplr->IsVisible(pObj))
						lplr->PushUpdateData(&update, count);
				}

				update.clear();
			}
		}
		pObj->ClearUpdateMask();
	}
	_updates.clear();
	
	// generate pending a9packets and send to clients.
	Player *plyr;
	for(it = _processQueue.begin(); it != _processQueue.end();)
	{
		plyr = *it;
		eit = it;
		++it;
		_processQueue.erase(eit);
		if(plyr->GetMapMgr() == this)
			plyr->ProcessPendingUpdates();
	}
}

void MapMgr::UpdateCellActivity(uint32 x, uint32 y, int radius)
{
	Instance_Map_InstanceId_Holder * pInstance =  sInstanceSavingManager.GetInstance(GetMapId(), GetInstanceID());
	CellSpawns * sp;
	uint32 endX = x + radius < _sizeX ? x + radius : _sizeX;
	uint32 endY = y + radius < _sizeY ? y + radius : _sizeY;
	uint32 startX = x - radius > 0 ? x - radius : 0;
	uint32 startY = y - radius > 0 ? y - radius : 0;
	uint32 posX, posY;

	MapCell *objCell;

	for (posX = startX; posX <= endX; posX++ )
	{
		for (posY = startY; posY <= endY; posY++ )
		{
			objCell = GetCell(posX, posY);

			if (!objCell)
			{
				if (_CellActive(posX, posY))
				{
					objCell = Create(posX, posY);
					objCell->Init(posX, posY, _mapId, this);

					sLog.outDetail("Cell [%d,%d] on map %d (instance %d) is now active.", 
						posX, posY, this->_mapId, m_instanceID);
					objCell->SetActivity(true);
					_map->GetTerrainMgr()->CellGoneActive(posX, posY);

					ASSERT(!objCell->IsLoaded());

					sLog.outDetail("Loading objects for Cell [%d][%d] on map %d (instance %d)...", 
						posX, posY, this->_mapId, m_instanceID);

					sp = _map->GetSpawnsList(posX, posY);
					if(sp) objCell->LoadObjects(sp, pInstance);
				}
			}
			else
			{
				//Cell is now active
				if (_CellActive(posX, posY) && !objCell->IsActive())
				{
					sLog.outDetail("Cell [%d,%d] on map %d (instance %d) is now active.", 
						posX, posY, this->_mapId, m_instanceID);
					_map->GetTerrainMgr()->CellGoneActive(posX, posY);
					objCell->SetActivity(true);

					if (!objCell->IsLoaded())
					{
						sLog.outDetail("Loading objects for Cell [%d][%d] on map %d (instance %d)...", 
							posX, posY, this->_mapId, m_instanceID);
						sp = _map->GetSpawnsList(posX, posY);
						if(sp) objCell->LoadObjects(sp, pInstance);
					}
				}
				//Cell is no longer active
				else if (!_CellActive(posX, posY) && objCell->IsActive())
				{
					sLog.outDetail("Cell [%d,%d] on map %d (instance %d) is now idle.", 
						posX, posY, this->_mapId, m_instanceID);
					_map->GetTerrainMgr()->CellGoneIdle(posX, posY);
					objCell->SetActivity(false);
				}
			}
		}
	}

}

bool MapMgr::_CellActive(uint32 x, uint32 y)
{
	uint32 endX = x < _sizeX ? x + 1 : _sizeX;
	uint32 endY = y < _sizeY ? y + 1 : _sizeY;
	uint32 startX = x > 0 ? x - 1 : 0;
	uint32 startY = y > 0 ? y - 1 : 0;
	uint32 posX, posY;

	MapCell *objCell;

	for (posX = startX; posX <= endX; posX++ )
	{
		for (posY = startY; posY <= endY; posY++ )
		{
			objCell = GetCell(posX, posY);

			if (objCell)
			{
				if (objCell->HasPlayers())
				{
					return true;
				}
			}
		}
	}

	return false;
}

void MapMgr::ObjectUpdated(Object *obj)
{
#ifdef WIN32
	if(GetCurrentThreadId() != threadid && !_shutdown)
	{
		Crash_Log->AddLine("ObjectUpdated accessed from external thread!!!");
		sLog.outString("ObjectUpdated accessed from external thread!!!");
		CStackWalker sw;
		sw.ShowCallstack();
	}
#endif
	// set our fields to dirty
	_updates.insert(obj);
}

void MapMgr::PushToProcessed(Player* plr)
{
	_processQueue.insert(plr);
}


void MapMgr::ChangeFarsightLocation(Player *plr, Creature *farsight)
{
	if(farsight == 0)
	{
		// We're clearing.
		for(ObjectSet::iterator itr = plr->m_visibleFarsightObjects.begin(); itr != plr->m_visibleFarsightObjects.end();
			++itr)
		{
			if(!plr->IsVisible((*itr)) && plr->CanSee((*itr)))
			{
				// Send destroy
				plr->PushOutOfRange((*itr)->GetNewGUID());
			}
		}
		plr->m_visibleFarsightObjects.clear();
	}
	else
	{
		uint32 cellX = GetPosX(farsight->GetPositionX());
		uint32 cellY = GetPosY(farsight->GetPositionY());
		uint32 endX = cellX < _sizeX ? cellX + 1 : _sizeX;
		uint32 endY = cellY < _sizeY ? cellY + 1 : _sizeY;
		uint32 startX = cellX > 0 ? cellX - 1 : 0;
		uint32 startY = cellY > 0 ? cellY - 1 : 0;
		uint32 posX, posY;
		MapCell *cell;
		Object *obj;
		MapCell::ObjectSet::iterator iter, iend;
		uint32 count;
		for (posX = startX; posX <= endX; ++posX )
		{
			for (posY = startY; posY <= endY; ++posY )
			{
				cell = GetCell(posX, posY);
				if (cell)
				{
					iter = cell->Begin();
					iend = cell->End();
					for(; iter != iend; ++iter)
					{
						obj = (*iter);
						if(!plr->IsVisible(obj) && plr->CanSee(obj) && farsight->GetDistance2dSq(obj) <= m_UpdateDistance)
						{
							ByteBuffer buf;
							count = obj->BuildCreateUpdateBlockForPlayer(&buf, plr);
							plr->PushUpdateData(&buf, count);
							plr->m_visibleFarsightObjects.insert(obj);
						}
					}
					
				}
			}
		}
	}
}

void MapMgr::LoadAllCells()
{
#ifdef WIN32
	HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadid);
	SuspendThread(hThread);
	DWORD tid = threadid;
	threadid = GetCurrentThreadId();
#endif

	MapCell * pCell;
	char msg[50];
	snprintf(msg,50, "Preload: Map%u", (unsigned int)_mapId);
	//uint32 count = _sizeX * _sizeY;
	//uint32 c = 0;
	CellSpawns * sp;

	for(uint32 x = 0; x < _sizeX; ++x)
	{
		for(uint32 y = 0; y < _sizeY; ++y)
		{
			pCell = _cells[x][y];
			sp = _map->GetSpawnsList(x, y);
			if(sp)
			{
				if(!pCell)
				{
					pCell = Create(x, y);
					pCell->Init(x, y, _mapId, this);
				}
				pCell->LoadObjects(sp, 0);
			}
			/*if(pCell == 0)
			{
				pCell = Create(x, y);
				pCell->Init(x, y, _mapId, this);
				sp = _map->GetSpawnsList(x, y);
				if(sp) pCell->LoadObjects(sp, 0);
			}
			else if(pCell->IsLoaded() == false)
			{
				sp = _map->GetSpawnsList(x, y);
				if(sp) pCell->LoadObjects(sp, 0);
			}*/
		}
	}
#ifdef WIN32
	threadid = tid;
	ResumeThread(hThread);
	CloseHandle(hThread);
#endif
}


/* new stuff
*/

void MapMgr::run()
{
	THREAD_TRY_EXECUTION2
		Do();
	THREAD_HANDLE_CRASH2
}

void MapMgr::Do()
{
#ifdef WIN32
	threadid=GetCurrentThreadId();
#endif
	ThreadState =THREADSTATE_BUSY;
	SetThreadName("Map mgr - M%u|I%u",this->_mapId ,this->m_instanceID);
	ObjectSet::iterator i;
	uint32 last_exec=getMSTime();

	// always declare local variables outside of the loop!
	// otherwise theres a lot of sub esp; going on.

	uint32 exec_time, exec_start;
	time_t t = 0;
	while((ThreadState != THREADSTATE_TERMINATE) && !_shutdown)
	{
		t = time(NULL);
		exec_start=getMSTime();
		//first push to world new objects
		m_objectinsertlock.Acquire();//<<<<<<<<<<<<<<<<
		if(m_objectinsertpool.size())
		{
			for(i=m_objectinsertpool.begin();i!=m_objectinsertpool.end();i++)
			{
				//PushObject(*i);
				(*i)->PushToWorld(this);
			}
			m_objectinsertpool.clear();
		}
		m_objectinsertlock.Release();//>>>>>>>>>>>>>>>>
		//-------------------------------------------------------
				
		//Now update sessions of this map + objects
		_PerformObjectDuties();

		last_exec=getMSTime();
		exec_time=last_exec-exec_start;
		if(exec_time<MAP_MGR_UPDATE_PERIOD)
			Sleep(MAP_MGR_UPDATE_PERIOD-exec_time);

		////////////////////////////////////
		// Instance Soft Reset Handler
		///////////
		if(ExpiryTime && t >= ExpiryTime)
		{
            if(GetMapInfo() && GetMapInfo()->type == INSTANCE_RAID || GetMapInfo() && GetMapInfo()->type == INSTANCE_MULTIMODE && iInstanceMode == MODE_HEROIC)
			{
				if(HasPlayers())
				{
					ExpiryTime = 0;
					DeletionPending = false;
					reset_pending = false;
				}
				else
				{
					DeletionPending = true;
					sInstanceSavingManager.CreateInactiveInstance(this);
					break;
				}

			}
			else
			{
				DeletionPending = true;
				if(HasPlayers())
				{
					ExpiryTime = 0;
					DeletionPending = false;
					reset_pending = false;
				}
				else
					break;
			}
		}
		if(RaidExpireTime && t >= RaidExpireTime)
		{
			 DeletionPending = true;
			 if(HasPlayers())
			 {
				 TeleportPlayers();
			 }
			 break;
		}
	}

	sThreadMgr.RemoveThread(this);

	if(delete_pending)
	{
		thread_is_alive = false;
		GetBaseMap()->DestroyMapMgrInstance(GetInstanceID());
		return;
	}

	///////////////////////////////
	// Instance Soft Reset
	/////////////
	// make sure this executes in the correct context. otherwise,
	// with per-thread heap management we're gonna have issues.

	if(m_battleground)
	{
		uint32 ID = m_battleground->GetID();
		thread_is_alive = false;
		sBattlegroundMgr.RemoveBattleground(ID);
		sWorldCreator.DestroyBattlegroundInstance(GetMapId(), GetInstanceID());
		return;
	}
	
	// variable 't' never been initialized
	if(RaidExpireTime && t >= RaidExpireTime)
	{
		sInstanceSavingManager.RemoveSavedInstance(GetMapId(),GetInstanceID(),true);
		thread_is_alive = false;
		sWorldCreator.InstanceHardReset(this);
	}
	else
	{
		if(ExpiryTime && t >= ExpiryTime)
		{
			thread_is_alive = false;
			sWorldCreator.InstanceSoftReset(this);
		}

	}
}

void MapMgr::AddObject(Object *obj)
{
	m_objectinsertlock.Acquire();//<<<<<<<<<<<<
	m_objectinsertpool.insert(obj);
	m_objectinsertlock.Release();//>>>>>>>>>>>>
}


Unit* MapMgr::GetUnit(const uint64 & guid)
{
	switch (((uint32*)&guid)[1])
	{
	case	HIGHGUID_PLAYER:
		return GetPlayer((uint32)guid);
		break;
	case	HIGHGUID_UNIT:
		return GetCreature((uint32)guid);
		break;
	case	HIGHGUID_PET:
		return GetPet((uint32)guid);
		break;
	default:
		return NULL;
	}
}

Object* MapMgr::_GetObject(const uint64 & guid)
{
	switch (((uint32*)&guid)[1])
	{
	case	HIGHGUID_GAMEOBJECT:
		return GetGameObject((uint32)guid);
		break;
	case	HIGHGUID_CORPSE:
		return objmgr.GetCorpse((uint32)guid);
		break;
	case	HIGHGUID_DYNAMICOBJECT:
		return GetDynamicObject((uint32)guid);
		break;
	case	HIGHGUID_TRANSPORTER:
		return objmgr.GetTransporter((uint32)guid);
		break;
	default:
		return GetUnit(guid);
		break;
	}
}

void MapMgr::_PerformObjectDuties()
{
	++mLoopCounter;
	uint32 mstime = getMSTime();

	// Update creatures.
	{
		CreatureSet::iterator itr = activeCreatures.begin();
		Creature * ptr;
		for(; itr != activeCreatures.end();)
		{
			ptr = *itr;
			++itr;
			ptr->Update(mstime - lastUnitUpdate);
		}
	}

	// Update any events.
	eventHolder.Update(mstime - lastUnitUpdate);

	// Update players.
	{
		PlayerStorageMap::iterator itr = m_PlayerStorage.begin();
		Player * ptr;
		for(; itr != m_PlayerStorage.end();)
		{
			ptr = ((Player*)(itr->second));
			++itr;
			ptr->Update(mstime - lastUnitUpdate);
		}

		lastUnitUpdate = mstime;
	}

	// Update gameobjects (not on every loop, however)
	if(mLoopCounter % 2)
	{
		GameObjectSet::iterator itr = activeGameObjects.begin();
		GameObject * ptr;
		for(; itr != activeGameObjects.end();)
		{
			ptr = *itr;
			++itr;
			ptr->Update(mstime - lastGameobjectUpdate);
		}

		lastGameobjectUpdate = mstime;
	}	

	// Sessions are updated every loop.
	{
		int result;
		WorldSession* session;
		SessionSet::iterator itr = Sessions.begin();
		SessionSet::iterator it2;

		for(; itr != Sessions.end();)
		{
			session = (*itr);
			it2 = itr;
			++itr;

			if(session->GetInstance() != m_instanceID)
			{
				Sessions.erase(it2);
				continue;
			}

			// Don't update players not on our map.
			// If we abort in the handler, it means we will "lose" packets, or not process this.
			// .. and that could be diasterous to our client :P
			if(session->GetPlayer() && (session->GetPlayer()->GetMapMgr() != this && session->GetPlayer()->GetMapMgr() != 0))
				continue;

            MapSessionFilter updater(session);

			if ((result = session->Update(m_instanceID, updater)))
			{
				if(result == 1)
					sWorld.DeleteSession(session);

				Sessions.erase(it2);
			}
		}
	}

	// Finally, A9 Building/Distribution
	_UpdateObjects();
}

void MapMgr::EventCorpseDespawn(uint64 guid)
{
	Corpse * pCorpse = objmgr.GetCorpse(guid);
	if(pCorpse == 0)	// Already Deleted
		return;

	if(pCorpse->GetMapMgr() != this)
		return;

	pCorpse->Despawn();
	delete pCorpse;
}

void MapMgr::RespawnMapMgr()
{
	//Despawn Creatures
	for(uint32 x=1;x<m_CreatureArraySize;x++)
	if(m_CreatureStorage[x])//have creature
	{
		m_CreatureStorage[x]->RemoveFromWorld(false);
		delete m_CreatureStorage[x];
		m_CreatureStorage[x] = NULL;
	}
	//reset guid 
	m_CreatureHighGuid = 0;


	//Despawn GOs
	for(uint32 x=1;x<m_GOArraySize;x++)
	if(m_GOStorage[x])//have creature
	{
		m_GOStorage[x]->RemoveFromWorld();
		delete m_GOStorage[x];
		m_GOStorage[x] = NULL;
	}
	//reset guid 
	m_GOHighGuid = 0;
	
	//Loop through cells to load objects
	CellSpawns * sp;
	Instance_Map_InstanceId_Holder * pInstance = sInstanceSavingManager.GetInstance(_mapId, GetInstanceID());

	for (uint32 i = 0; i < _sizeX; i++)
	{
		for (uint32 j = 0; j < _sizeY; j++)
		{	 
			if(_cells[i][j] != 0)
			{
				sp = _map->GetSpawnsList(i, j);
				if(sp)
					_cells[i][j]->LoadObjects(sp, pInstance);
			}
		}
	}
}

void MapMgr::TeleportPlayers()
{
	PlayerStorageMap::iterator itr =  m_PlayerStorage.begin();
	for(; itr !=  m_PlayerStorage.end();)
	{
		Object *p = itr->second;
		++itr;
		static_cast<Player*>(p)->SafeTeleport(static_cast<Player*>(p)->GetBindMapId(), 0, static_cast<Player*>(p)->GetBindPositionX(), static_cast<Player*>(p)->GetBindPositionY(), static_cast<Player*>(p)->GetBindPositionZ(), 3.14f);
	}
}

void MapMgr::SavePlayersToInstance()
{
	PlayerStorageMap::iterator itr =  m_PlayerStorage.begin();
	for(; itr !=  m_PlayerStorage.end();)
	{
		Object *p = itr->second;
		++itr;
		sInstanceSavingManager.SavePlayerToInstance(((Player*)p), _mapId);
	}
	sInstanceSavingManager.SaveInstanceIdToDB(m_instanceID, _mapId);
}

void MapMgr::SetNewExpireTime(time_t creation)
{
	CreationTime = creation;
	RaidExpireTime = creation + (pMapInfo ? pMapInfo->cooldown : 604800);
}

void MapMgr::SetCreator(Player *pPlayer)
{
	m_iCreator = pPlayer->GetGUID();
}
