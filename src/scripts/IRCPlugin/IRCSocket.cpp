/****************************************************************************
 *
 * IRC Plugin for Antrix
 * Copyright (c) 2007 Burlex, Antrix Team
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech ASA of Norway and appearing in the file
 * COPYING included in the packaging of this file.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "IRCPlugin.h"
#define COMMAND_PREFIX '.'

IRCSocket::IRCSocket(SOCKET fd) : Socket(fd, 65536, 65536)
{

}

IRCSocket::~IRCSocket()
{

}

void IRCSocket::SendLine(const char * format, ...)
{
	char buf[514];
	va_list ap;
	va_start(ap, format);
	BurstBegin();
	int len = vsnprintf(buf, 514, format, ap);
	strcat(buf, "\r\n");
	BurstSend((const uint8*)buf, len+2);
	BurstPush();
	BurstEnd();
	va_end(ap);
}

void IRCSocket::OnRead()
{
	m_recvQLock.Acquire();
	recvq.append((char*)GetReadBuffer(0), GetReadBufferSize());
	m_recvQLock.Release();
	RemoveReadBufferBytes(GetReadBufferSize(), false);
}

bool IRCSocket::BufferReady()
{
	m_recvQLock.Acquire();
	bool ret = (recvq.rfind("\n") != string::npos);
	m_recvQLock.Release();
	return ret;
}

string IRCSocket::GetLine()
{
	m_recvQLock.Acquire();

	/* strip any \r/\n's from the front */
	string::iterator t = recvq.begin();
	while (t != recvq.end() && (*t == '\r' || *t == '\n'))
	{
		recvq.erase(t);
		t = recvq.begin();
	}

	for(; t != recvq.end(); ++t)
	{
		if(*t == '\n')
		{
			string ret = string(recvq.begin(), t);
			recvq.erase(recvq.begin(), t + 1);
			m_recvQLock.Release();
			return ret;
		}
	}
	
	m_recvQLock.Release();
	return "";
}

struct IRCCommandHandler
{
	const char * Command;
	void(IRCSocket::*CommandHandler)();
};

IRCCommandHandler * getCommandHandlers()
{
	static IRCCommandHandler Handlers[] = {
		{ "JOIN", &IRCSocket::HandleJoin },
		{ "433", &IRCSocket::Handle433 },
		{ "001", &IRCSocket::Handle001 },
		{ "PRIVMSG", &IRCSocket::HandlePrivMsg },
		{ 0, 0 },
	};

	return Handlers;
}

void IRCSocket::PollRecvQ()
{
	if(!BufferReady())
		return;

	int paramter_count = 0;
	string line = GetLine();
	string::size_type r = line.rfind("\r");
	while(r != string::npos)
	{
		line.erase(r);
		r = line.rfind("\r");
	}
	string::size_type sp = line.find(" ");

	/* find the first instance of " " */
	if(sp == string::npos)
		return;

	/* skip the leading : */
	string source = line.substr(1, sp);

	/* find the next space */
	string::size_type sp2 = line.find(" ", sp+1);

	/* grab the numeric */
	string numeric = line.substr(sp+1, sp2-sp-1);
	
	/* find the command handler */
	IRCCommandHandler * ch = getCommandHandlers();
	for(; ch->Command != 0; ++ch)
	{
		if(!strcmp(ch->Command, numeric.c_str()))
			break;
	}

#ifdef _IRC_DEBUG
	printf("IRCLINE: %s\n", line.c_str());
	printf("Numeric: %s\n", numeric.c_str());
#endif

	/* split into parameters */
	Parameters[0] = (char*)source.c_str();			// source
	Parameters[1] = (char*)numeric.c_str();		// numeric
	Parameters[2] = (char*)line.c_str() + sp2+1;

	/* blah, execute it */
	if(ch->Command != 0)
		(this->*(ch->CommandHandler))();
}

void IRCSocket::Handle433()
{
	/* invalid nickname, try sending the alt */
	SendLine("NICK %s", Thread->AltNickName.c_str());
	Thread->NickName = Thread->AltNickName;
}

void IRCSocket::HandleJoin()
{
	/* joined channel */
}

void IRCSocket::Handle001()
{
	/* we're fully connected now */
	Thread->State = STATE_JOINCHANNELS;
}

struct IRCCommand 
{
	const char * command;
	void(*func)(const char *, IRCSocket *, int, char**);
};


void IRCSocket::HandlePrivMsg()
{
	char message[514];
	strcpy(message, Parameters[2]);

	/* message on channel */
	char * part2 = strchr(message, ' ');
	*(part2) = 0;
	part2 += 2;

	char * channel = message;
	printf("%s : %s\n", channel, part2);

	if(part2[0] != COMMAND_PREFIX)
		return;
	++part2;
	if(*part2 == '\0')
		return;

	static IRCCommand Handlers[] = {
		{ "info", info_cmd },
		{ "kick", kick_cmd },
		{ "gm", gm_cmd },
		{ "announce", announce_cmd },
		{ "wannounce", wannounce_cmd },
		{ "uptime", uptime_cmd },
		{ 0, 0 }
	};

	/* split the command up into arguments */
	char * argv[10];
	int argc = 1;
	char * f_param = strchr(part2, ' ');
	argv[0] = part2;
	while(f_param != 0)
	{
		*f_param = '\0';
		++f_param;
		argv[argc++] = f_param;
		f_param = strchr(f_param, ' ');
		if(argc == 10)
			break;
	}

#ifdef _IRC_DEBUG
	SendMessage(channel, "Got command message, argc = %u", argc);
	for(int i = 0; i < argc; ++i)
		SendMessage(channel, "argv[%u] = %s", i, argv[i]);
#endif

	int len = strlen(part2);
	IRCCommand * c = Handlers;
	for(; c->command != 0; ++c)
	{
		if(!strnicmp(c->command, part2, len))
		{
			c->func(channel, this, argc, argv);
			break;
		}
	}

	if(c->command == 0)
		SendMessage(channel, "Invalid command.");
}

void IRCSocket::SendMessage(const char * destination_user, const char * format, ...)
{
	char message[514];
	va_list ap;
	va_start(ap, format);
	vsprintf(message, format, ap);
	SendLine("PRIVMSG %s :%s", destination_user, message);
	va_end(ap);
}

void IRCSocket::SendBoldMessage(const char * destination_user, const char * format, ...)
{
	char message[514];
	va_list ap;
	va_start(ap, format);
	vsprintf(message, format, ap);
	SendLine("PRIVMSG %s :\x02%s", destination_user, message);
	va_end(ap);
}


