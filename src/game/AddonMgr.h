#ifndef __ADDONMGR_H
#define __ADDONMGR_H

struct AddonEntry
{
	std::string name;
	uint64 crc;
	bool banned;
	bool isNew;
	bool showinlist;
};

class AddonMgr :  public Singleton < AddonMgr >
{
public:
	AddonMgr();
	~AddonMgr();

	void LoadFromDB();
	void SaveToDB();

	void SendAddonInfoPacket(WorldPacket *source, uint32 pos, WorldSession *m_session);
	bool AppendPublicKey(WorldPacket& data, string AddonName, uint32 CRC);

private:
	std::map<std::string, AddonEntry*> KnownAddons;
	map<string, ByteBuffer> AddonData;

	bool IsAddonBanned(uint64 crc, std::string name = "");
	bool IsAddonBanned(std::string name, uint64 crc = 0);
	bool ShouldShowInList(std::string name);
};

#define sAddonMgr AddonMgr::getSingleton()

#endif
