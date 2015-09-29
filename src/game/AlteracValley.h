#define MAXOFBANNERS 14

class AlteracValley : public Battleground
{
public:
    AlteracValley();
    ~AlteracValley();

    uint32 m_BGTime;
    
    GameObject *gcbanner[MAXOFBANNERS];

    std::set<GameObject*> m_Gates;

    void HandleBanner(Player *p_caster,GameObject *go,uint32 spellid);
    void HandleBattlegroundAreaTrigger(Player *plr, uint32 TriggerID);
    void HandleBattlegroundEvent(Object *src, Object *dst, uint16 EventID, uint32 params1 = 0, uint32 params2 = 0);
    void SetupBattleground();
    void SpawnBattleground();
    
    void Remove();

    void Start();
    void EventUpdate(uint32 diff);
    void EventCaptureBase(Player *src,uint32 bannerslot);
};
