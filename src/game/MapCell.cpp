/****************************************************************************
 *
 * General Object Type File
 *
 */

//
// MapCell.cpp
//
#include "StdAfx.h"

MapCell::~MapCell()
{
	RemoveObjects();
}

void MapCell::Init(uint32 x, uint32 y, uint32 mapid, MapMgr *mapmgr)
{
	_mapmgr = mapmgr;
	_active = false;
	_loaded = false;
	_playerCount = 0;
}

void MapCell::AddObject(Object *obj)
{
	if(obj->IsPlayer())
		++_playerCount;

	_objects.insert(obj);
}

void MapCell::RemoveObject(Object *obj)
{
	if(obj->IsPlayer())
		--_playerCount;

	_objects.erase(obj);
}

void MapCell::SetActivity(bool state)
{	
	if(!_active && state)
	{
		// Move all objects to active set.
		for(ObjectSet::iterator itr = _objects.begin(); itr != _objects.end(); ++itr)
		{
			if(!(*itr)->Active && (*itr)->CanActivate())
				(*itr)->Activate(_mapmgr);
		}
	} else if(_active && !state)
	{
		// Move all objects from active set.
		for(ObjectSet::iterator itr = _objects.begin(); itr != _objects.end(); ++itr)
		{
			if((*itr)->Active)
				(*itr)->Deactivate(_mapmgr);
		}
	}

	_active = state; 

}
void MapCell::RemoveObjects()
{
	ObjectSet::iterator itr;
	uint32 count = 0;
	//uint32 ltime = getMSTime();

	//This time it's simpler! We just remove everything :)
	for(itr = _objects.begin(); itr != _objects.end(); )
	{
		count++;

		Object *obj = (*itr);

		itr++;

		if (obj->IsInWorld())
			obj->RemoveFromWorld();
  
		if (obj->IsPlayer())
			delete ((Player*)obj);
		else if (obj->GetTypeId() == TYPEID_UNIT)
		{
			if(obj->IsPet())
				delete ((Pet*)(obj));
			else
				delete ((Creature*)obj);
		}
		else if (obj->GetTypeId() == TYPEID_GAMEOBJECT)
		{
			if(UINT32_LOPART(obj->GetGUIDHigh())==HIGHGUID_TRANSPORTER)
			{}
			else
			{
				delete ((GameObject*)obj);
			}
		}
		else if (obj->GetTypeId() == TYPEID_DYNAMICOBJECT)
			delete ((DynamicObject*)obj);
		else if (obj->GetTypeId() == TYPEID_CORPSE)
		{
			delete ((Corpse*)obj);
		}
	}

	_objects.clear();
	_playerCount = 0;
	_loaded = false;
}


void MapCell::LoadObjects(CellSpawns * sp, Instance_Map_InstanceId_Holder * pInstance)
{
	_loaded = true;

	if(sp->CreatureSpawns.size())//got creatures
	{
		for(CreatureSpawnList::iterator i=sp->CreatureSpawns.begin();i!=sp->CreatureSpawns.end();i++)
		{
			if(pInstance && pInstance->FindObject((*i)->id) || pInstance && pInstance->FindObject((*i)->respawnNpcLink))
			{
				continue;
			}
			Creature * c=_mapmgr->CreateCreature();

			c->SetMapId(_mapmgr->GetMapId());
			c->SetInstanceID(_mapmgr->GetInstanceID());

            if(c->Load(*i, _mapmgr->iInstanceMode, _mapmgr->GetMapInfo()))
			{
				if(!c->CanAddToWorld())
					delete c;

				c->PushToWorld(_mapmgr);
			}
			else
				delete c;//missing proto or smth of that kind
		}
	}

	if(sp->GOSpawns.size())//got GOs
	{
		for(GOSpawnList::iterator i=sp->GOSpawns.begin();i!=sp->GOSpawns.end();i++)
		{
			GameObject * go=_mapmgr->CreateGameObject();
			if(go->Load(*i))
			{
				uint32 state = go->GetUInt32Value(GAMEOBJECT_STATE);
				if(pInstance && pInstance->FindObject((*i)->stateNpcLink))
				{
					go->SetUInt32Value(GAMEOBJECT_STATE, (state ? 0 : 1));
				}
			   

				go->PushToWorld(_mapmgr);
			}
			else
				delete go;//missing proto or smth of that kind
		}
	}
}
