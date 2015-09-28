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

#ifndef _IRC_SOCKET_H
#define _IRC_SOCKET_H

class IRCThread;
class IRCSocket : public Socket
{
public:
	IRCSocket(SOCKET fd);
	~IRCSocket();

	void OnRead();
	void SendLine(const char * format, ...);
	void SendMessage(const char * destination_user, const char * format, ...);
	void SendBoldMessage(const char * destination_user, const char * format, ...);

	Mutex m_recvQLock;
	string recvq;

	bool BufferReady();
	string GetLine();
	IRCThread * Thread;

	void PollRecvQ();

	char * Parameters[10];

	/** Handlers **/
	void Handle001();			// Sent on connect.
	void Handle433();			// Nickname already in use
	void HandleJoin();
	void HandlePrivMsg();
};

void info_cmd(const char* source, IRCSocket * s, int argc, char ** argv);
void kick_cmd(const char* source, IRCSocket * s, int argc, char ** argv);
void uptime_cmd(const char* source, IRCSocket * s, int argc, char ** argv);
void gm_cmd(const char* source, IRCSocket * s, int argc, char ** argv);
void announce_cmd(const char* source, IRCSocket * s, int argc, char ** argv);
void wannounce_cmd(const char* source, IRCSocket * s, int argc, char ** argv);

#endif
