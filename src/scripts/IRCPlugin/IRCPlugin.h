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

#ifndef _IRC_PLUGIN_H
#define _IRC_PLUGIN_H

#include "StdAfx.h"
#include "IRCSocket.h"
#include "CPUMem.h"

/* state vars */
enum IRC_STATES
{
	STATE_CONNECTING,
	STATE_CONNECTED,
	STATE_REGISTER,
	STATE_JOINCHANNELS,
	STATE_FULLCONNECTED,
};

class IRCThread : public ThreadBase
{
public:
	/* settings */
	string NickName;
	string AltNickName;
	string Server;
	uint32 Port;
	string Channel;
	IRC_STATES State;

	/* our current connection */
	IRCSocket * socket;

	void run();

	/* state handlers */
	void _HandleConnecting();
	void _HandleConnected();
};

#endif
