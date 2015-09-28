#include "IRCPlugin.h"

void info_cmd(const char * source, IRCSocket * s, int argc, char ** argv)
{
	char uptime_string[100];
	uint32 uptime = sWorld.GetUptime();

	// lock players reader
	objmgr._playerslock.AcquireReadLock();
	uint32 avg = 0;
	float AvgLat;
	uint32 gm = 0;
	uint32 count = 0;


	HM_NAMESPACE::hash_map<uint32, Player*>::const_iterator itr;
	for (itr = objmgr._players.begin(); itr != objmgr._players.end(); itr++)
	{
		if(itr->second->GetSession() && itr->second->IsInWorld())
		{
			count++;
			avg += itr->second->GetSession()->GetLatency();
			if(itr->second->GetSession()->GetPermissionCount())
				gm++;
		}            
	}
	objmgr._playerslock.ReleaseReadLock();

	AvgLat = count ? (float)((float)avg / (float)count) : 0;
	GenerateUptimeString(uptime_string, uptime);

	s->SendMessage(source, "Server Information:");
	s->SendBoldMessage(source, "CPU Usage:\x02 %.3f%%", GetCPUUsage());
	s->SendBoldMessage(source, "Memory Usage:\x02 %.3fMB", GetRAMUsage());
	s->SendBoldMessage(source, "Online Players:\x02 %u", count);
	s->SendBoldMessage(source, "Online GMs:\x02 %u", gm);
	s->SendBoldMessage(source, "Uptime:\x02 %s", uptime_string);
	s->SendBoldMessage(source, "Average Latency:\x02 %.3fms", AvgLat);
}

void kick_cmd(const char * source, IRCSocket * s, int argc, char ** argv)
{
	if(argc < 2)
	{
		s->SendMessage(source, "You must specify a player name to kick.");
		return;
	}

	s->SendMessage(source, "Removing %s from the server.", argv[1]);
}

void gm_cmd(const char* source, IRCSocket * s, int argc, char ** argv)
{
	s->SendMessage(source, "Online GM's:");
}

void announce_cmd(const char* source, IRCSocket * s, int argc, char ** argv)
{
	if(argc < 2)
	{
        s->SendMessage(source, "No message was specified.");
		return;
	}

	/* dirty hack for messages with spaces because of our argc/argv */
	char message[514] = {0};
	for(int i = 1; i < argc; ++i)
		strcat(message, argv[i]);

	s->SendMessage(source, "Sent the message to all online players.");
}

void wannounce_cmd(const char* source, IRCSocket * s, int argc, char ** argv)
{
	if(argc < 2)
	{
		s->SendMessage(source, "No message was specified.");
		return;
	}

	/* dirty hack for messages with spaces because of our argc/argv */
	char message[514] = {0};
	for(int i = 1; i < argc; ++i)
		strcat(message, argv[i]);

	s->SendMessage(source, "Sent the message to all online players.");
}

void uptime_cmd(const char* source, IRCSocket * s, int argc, char ** argv)
{

}
