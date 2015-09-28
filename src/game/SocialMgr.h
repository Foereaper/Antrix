/****************************************************************************
 *
 * Friends System
 *
 */

#ifndef __SOCIALMGR_H
#define __SOCIALMGR_H

struct SocialStr
{
	uint64 pGuid;
	uint32 Area;
	uint8 Level;
	uint8 Class;
};

class SocialMgr;
class SocialMgr :  public Singleton < SocialMgr >
{
public:
	SocialMgr();
	~SocialMgr();

	void AddFriend(Player* plr, std::string friendname);
	void AddIgnore(Player* plr, std::string ignorename);
	void DelFriend(Player* plr, uint64 friendguid);
	void DelIgnore(Player* plr, uint64 ignoreguid);

	bool IsFriend(uint64 plrguid, uint64 target);
	inline bool HasFriend(uint64 plrguid, uint64 mfriend); // Checking before adding a friend
	bool IsIgnore(uint64 plrguid, uint64 target);
	inline bool HasIgnore(uint64 plrguid, uint64 mignore); // Checking before adding an ignore
	bool HasIgnore(Player* plr, Player* mignore); // Checking for whispers blocking

	void SendFriendList(Player* plr);
	void SendIgnoreList(Player* plr);
	void SendUpdateToFriends(Player* plr);

	inline void SendOnlinePkt(Player* plr, SocialStr* pNfo);
	inline void SendOfflinePkt(Player* plr, uint64 fGuid);

	void LoggedIn(Player* plr); // To send a friend status update 'online' to people having him in their list
	void LoggedOut(Player* plr); // To send a friend status update 'offline' to people having him in their list
	void RemovePlayer(Player* plr); // When deleting a character from the server

	void LoadFromDB();
	
private:
	std::map<uint64, std::set<uint64>*> m_isInFriendList;
	std::map<uint64, std::set<uint64>*> m_hasInFriendList;
	std::map<uint64, std::set<uint64>*> m_isInIgnoreList;
	std::map<uint64, std::set<uint64>*> m_hasInIgnoreList;
	std::map<uint64, std::set<uint64>*> m_needsBlockNotice;

};

#define sSocialMgr SocialMgr::getSingleton()

#endif
