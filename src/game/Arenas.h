class Arena : public Battleground
{
public:
	Arena();
	~Arena();

	uint32 m_BGTime;
	uint32 m_MaxScore;

	std::set<GameObject*> m_Gates;

	void HandleBattlegroundAreaTrigger(Player *plr, uint32 TriggerID);
	void HandleBattlegroundEvent(Object *src, Object *dst, uint16 EventID, uint32 params1 = 0, uint32 params2 = 0);
	void SetupBattleground();
	void SpawnBattleground();

	void Remove();

	void Start();
	void EventUpdate(uint32 diff);
};
