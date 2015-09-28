/****************************************************************************
 *
 * LFG System
 *
 */

#include "StdAfx.h"

initialiseSingleton( LfgMgr );

LfgMgr::LfgMgr()
{
	
	
}

LfgMgr::~LfgMgr()
{
	
	
}

void LfgMgr::RemoveFromLfgQueue(Player *pl,uint32 LfgDungeonId)
{	
	if(!LfgDungeonId)
		return;
	
	std::set<Player*>::iterator itr;
	for(itr = GetLfgQueueBegin(LfgDungeonId); itr != GetLfgQueueEnd(LfgDungeonId) ; ++itr)
	{
		if((*itr) == pl)
		{
			m_LFGqueueMembers[LfgDungeonId].erase(itr);
			return;
		}
	}
}	

void LfgMgr::SetPlayerInLFGqueue(Player *pl,uint32 LfgDungeonId)
{
	m_LFGqueueMembers[LfgDungeonId].insert(pl);
}

uint32 LfgMgr::GetLfgQueueSize(uint32 LfgDungeonId)
{
	return m_LFGqueueMembers[LfgDungeonId].size();	
}

std::set<Player*>::iterator LfgMgr::GetLfgQueueBegin(uint32 LfgDungeonId)
{
	return m_LFGqueueMembers[LfgDungeonId].begin();
}

std::set<Player*>::iterator LfgMgr::GetLfgQueueEnd(uint32 LfgDungeonId)
{
	return m_LFGqueueMembers[LfgDungeonId].end();
}
