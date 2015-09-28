/****************************************************************************
 *
 * General Object Type File
 *
 */

// Class WorldSocket - Main network code functions, handles
// reading/writing of all packets.

#ifndef __WORLDSOCKET_H
#define __WORLDSOCKET_H

/* Normal WorldSocket when not using clustering */
#ifndef CLUSTERING

#define WORLDSOCKET_SENDBUF_SIZE 131078
#define WORLDSOCKET_RECVBUF_SIZE 16384

class WorldPacket;
class SocketHandler;
class WorldSession;

class WorldSocket : public Socket
{
public:
	WorldSocket(SOCKET fd);
	~WorldSocket();

	// vs8 fix - send null on empty buffer
	inline void SendPacket(WorldPacket* packet) { if(!packet) return; OutPacket(packet->GetOpcode(), packet->size(), (packet->size() ? (const void*)packet->contents() : NULL)); }
	inline void SendPacket(StackBufferBase * packet) { if(!packet) return; OutPacket(packet->GetOpcode(), packet->GetSize(), (packet->GetSize() ? (const void*)packet->GetBufferPointer() : NULL)); }

	void __fastcall OutPacket(uint16 opcode, uint16 len, const void* data);
   
	inline uint32 GetLatency() { return _latency; }

	void Authenticate();
	void InformationRetreiveCallback(WorldPacket & recvData, uint32 requestid);

	void __fastcall UpdateQueuePosition(uint32 Position);

	void OnRead();
	void OnConnect();
	void OnDisconnect();

	inline void SetSession(WorldSession * session) { mSession = session; }
	inline WorldSession * GetSession() { return mSession; }
	bool Authed;
	
protected:
	
	void _HandleAuthSession(WorldPacket* recvPacket);
	void _HandlePing(WorldPacket* recvPacket);

private:

	uint32 mOpcode;
	uint32 mRemaining;
	uint32 mSize;
	uint32 mSeed;
	uint32 mClientSeed;
	uint32 mClientBuild;
	uint32 mRequestID;

	WorldSession *mSession;
	WorldPacket * pAuthenticationPacket;

	WowCrypt _crypt;
	uint32 _latency;
	bool mQueued;
	bool m_nagleEanbled;
};

#endif

inline void FastGUIDPack(ByteBuffer & buf, const uint64 & oldguid)
{
	// hehe speed freaks
	uint8 guidmask = 0;
	uint8 guidfields[9] = {0,0,0,0,0,0,0,0};
	
	int j = 1;
	uint8 * test = (uint8*)&oldguid;

	if (*test) //7*8
	{
		guidfields[j] = *test;
		guidmask |= 1;
		j++;
	}
	if (*(test+1)) //6*8
	{
		guidfields[j] = *(test+1);
		guidmask |= 2;
		j++;
	}
	if (*(test+2)) //5*8
	{
		guidfields[j] = *(test+2);
		guidmask |= 4;
		j++;
	}
	if (*(test+3)) //4*8
	{
		guidfields[j] = *(test+3);
		guidmask |= 8;
		j++;
	}
	if (*(test+4)) //3*8
	{
		guidfields[j] = *(test+4);
		guidmask |= 16;
		j++;
	}
	if (*(test+5))//2*8
	{
		guidfields[j] = *(test+5);
		guidmask |= 32;
		j++;
	}
	if (*(test+6))//1*8
	{
		guidfields[j] = *(test+6);
		guidmask |= 64;
		j++;
	}
	if (*(test+7)) //0*8
	{
		guidfields[j] = *(test+7);
		guidmask |= 128;
		j++;
	}
	guidfields[0] = guidmask;

	buf.append(guidfields,j);
}

//!!! warning. This presumes that all guids can be compressed at least 1 byte
//make sure you choose highguids acordingly
inline unsigned int FastGUIDPack(const uint64 & oldguid, unsigned char * buffer, uint32 pos)
{
	// hehe speed freaks
	uint8 guidmask = 0;

	int j = 1 + pos;
	uint8 * test = (uint8*)&oldguid;

	if (*test) //7*8
	{
		buffer[j] = *test;
		guidmask |= 1;
		j++;
	}
	if (*(test+1)) //6*8
	{
		buffer[j] = *(test+1);
		guidmask |= 2;
		j++;
	}
	if (*(test+2)) //5*8
	{
		buffer[j] = *(test+2);
		guidmask |= 4;
		j++;
	}
	if (*(test+3)) //4*8
	{
		buffer[j] = *(test+3);
		guidmask |= 8;
		j++;
	}
	if (*(test+4)) //3*8
	{
		buffer[j] = *(test+4);
		guidmask |= 16;
		j++;
	}
	if (*(test+5))//2*8
	{
		buffer[j] = *(test+5);
		guidmask |= 32;
		j++;
	}
	if (*(test+6))//1*8
	{
		buffer[j] = *(test+6);
		guidmask |= 64;
		j++;
	}
	if (*(test+7)) //0*8
	{
		buffer[j] = *(test+7);
		guidmask |= 128;
		j++;
	}
	buffer[pos] = guidmask;
	return (j - pos);
}

/* Modified/Simplified WorldSocket for use with clustering */
#ifdef CLUSTERING
class WorldSocket
{
public:
	WorldSocket(uint32 sessionid);
	~WorldSocket();

	void Disconnect();
	bool IsConnected();
	inline string GetRemoteIP() { return string(inet_ntoa(m_address.sin_addr)); }
	inline uint32 GetRemotePort() { return ntohs(m_address.sin_port); }

	inline void SendPacket(WorldPacket* packet) { if(!packet) return; OutPacket(packet->GetOpcode(), packet->size(), (packet->size() ? (const void*)packet->contents() : NULL)); }
	inline void SendPacket(StackBufferBase * packet) { if(!packet) return; OutPacket(packet->GetOpcode(), packet->GetSize(), (packet->GetSize() ? (const void*)packet->GetBufferPointer() : NULL)); }
	void __fastcall OutPacket(uint16 opcode, uint16 len, const void* data);

protected:
	uint32 m_sessionId;
	sockaddr_in m_address;
};

#endif
#endif
