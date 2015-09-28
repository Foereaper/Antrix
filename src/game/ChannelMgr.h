class ChannelMgr :  public Singleton < ChannelMgr >
{
 
public:
	ChannelMgr()
	{
		
	}

	~ChannelMgr();

	Channel *GetJoinChannel(const char *name, Player *p)
	{ 
		ChannelList* cl=&Channels[0];
		if(seperatechannels)
			cl = &Channels[p->GetTeam()];

		ChannelList::iterator i=cl->find(string(name));
		if(i!=cl->end())
			return i->second;
		else 
		{
			Channel *nchan = new Channel(name,p);
			(*cl)[name]=nchan;
			return nchan;
		}

	}
	Channel *GetChannel(const char *name, Player *p)
	{ 
		ChannelList* cl=&Channels[0];
		if(seperatechannels)
			cl = &Channels[p->GetTeam()];

		ChannelList::iterator i=cl->find(string(name));
		if(i!=cl->end())
			return i->second;
		else 
		{
			WorldPacket data(100);
			data.SetOpcode (SMSG_CHANNEL_NOTIFY);
			data << (uint8)0x05 << string(name);
			p->GetSession()->SendPacket(&data);
			return NULL;
		}
	}
	bool LeftChannel(const char *name,Player*p)
	{ 
		ChannelList* cl=&Channels[0];
		if(seperatechannels)
			cl = &Channels[p->GetTeam()];

		ChannelList::iterator i=cl->find(string(name));
		if(i!=cl->end())
		{
			Channel *ch=i->second;

			ch->Leave(p);
			if(!ch->IsConstant()  && ch->GetNumPlayers() == 0 )
			{
				cl->erase(i);
				delete ch;
			}
			return true;
		}
		return false;
	}
	bool seperatechannels;
private:
	//team 0: aliance, team 1 horde
	typedef map<string,Channel *> ChannelList;
	ChannelList Channels[2];

};

#define channelmgr ChannelMgr::getSingleton()
