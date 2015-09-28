/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef __LOGONOPCODES_H
#define __LOGONOPCODES_H

enum RealmListOpcodes
{
	// Initialization of server/client connection...
	RCMSG_REGISTER_REALM						= 1,
	RSMSG_REALM_REGISTERED						= 2,

	// Upon client connect (for WS)
	RCMSG_REQUEST_SESSION						= 3,
	RSMSG_SESSION_RESULT						= 4,

	// Ping/Pong
	RCMSG_PING									= 5,
	RSMSG_PONG									= 6,

	// SQL Query Execute
	RCMSG_SQL_EXECUTE							= 7,
	RCMSG_RELOAD_ACCOUNTS						= 8,

	// Authentication
	RCMSG_AUTH_CHALLENGE						= 9,
	RSMSG_AUTH_RESPONSE							= 10,

	// Character->Account Transmission
	RSMSG_REQUEST_ACCOUNT_CHARACTER_MAPPING		= 11,
	RCMSG_ACCOUNT_CHARACTER_MAPPING_REPLY		= 12,

	// Update Character->Account Mapping
	RCMSG_UPDATE_CHARACTER_MAPPING_COUNT		= 13,

	// count
	RMSG_COUNT									= 14,
};

#endif
