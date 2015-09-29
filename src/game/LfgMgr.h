/****************************************************************************
 *
 * LFG System
 *
 */

enum LFGTypes 
{
    LFG_NONE = 0,
    LFG_INSTANCE = 1,
    LFG_RAID = 2,
    LFG_QUEST = 3,
    LFG_ZONE = 4,
    LFG_HEROIC_DUNGEON = 5, // from client
};

#define MAX_DUNGEONS 166 // check max entrys +1 on lfgdungeons.dbc

class LfgMgr : public Singleton < LfgMgr >
{
public:    
    
    LfgMgr();
    ~LfgMgr();
    
    void SetPlayerInLFGqueue(Player *pl,uint32 LfgDungeonId);
    void RemoveFromLfgQueue(Player *pl,uint32 LfgDungeonId);
    uint32 GetLfgQueueSize(uint32 LfgDungeonId);
    std::set<Player*>::iterator GetLfgQueueBegin(uint32 LfgDungeonId);
    std::set<Player*>::iterator GetLfgQueueEnd(uint32 LfgDungeonId);
    
protected:
    
    std::set<Player*> m_LFGqueueMembers[MAX_DUNGEONS];
    
    
};

#define sLfgMgr LfgMgr::getSingleton()
