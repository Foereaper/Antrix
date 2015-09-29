/****************************************************************************
 *
 * General Object Type File
 *
 */

/* echo send/received packets to console */
//#define ECHO_PACKET_LOG_TO_CONSOLE

// Class WorldSocket - Main network code functions, handles
// reading/writing of all packets.

#include "StdAfx.h"
#include "../shared/AuthCodes.h"

#ifndef CLUSTERING
#pragma pack(push, 1)
struct ClientPktHeader
{
    uint16 size;
    uint32 cmd;
};

struct ServerPktHeader
{
    uint16 size;
    uint16 cmd;
};
#pragma pack(pop)

WorldSocket::WorldSocket(SOCKET fd) : Socket(fd, WORLDSOCKET_SENDBUF_SIZE, WORLDSOCKET_RECVBUF_SIZE)
{
    Authed = false;
    mSize = mOpcode = mRemaining = 0;
    _latency = 0;
    mSession = NULL;
    mSeed = rand() % 0xFFFFFFF0 + 10;
    pAuthenticationPacket = NULL;
    mQueued = false;
    mRequestID = 0;
    m_nagleEanbled = false;
}

WorldSocket::~WorldSocket()
{

}

void WorldSocket::OnDisconnect()
{
    if(mSession)
        mSession->SetSocket(0);

    if(mRequestID != 0)
    {
        sLogonCommHandler.UnauthedSocketClose(mRequestID);
        mRequestID = 0;
    }

    if(mQueued)
        sWorld.RemoveQueuedSocket(this);    // Remove from queued sockets.
}

void WorldSocket::OutPacket(uint16 opcode, uint16 len, const void* data)
{
    bool rv;
    if(opcode == 0 || !IsConnected())
        return;

    BurstBegin();

    // Packet logger :)
    sWorldLog.LogPacket(len, opcode, (const uint8*)data, 1);

    // Encrypt the packet
    // First, create the header.
    ServerPktHeader Header;
    Header.cmd = opcode;
    Header.size = ntohs((uint16)len + 2);
    _crypt.EncryptSend((uint8*)&Header, 4);

    // Pass the header to our send buffer
    rv = BurstSend((const uint8*)&Header, 4);

    // Pass the rest of the packet to our send buffer (if there is any)
    if(len > 0 && rv)
    {
        rv = BurstSend((const uint8*)data, len);
    }

    if(rv) BurstPush();
    BurstEnd();
}

void WorldSocket::OnConnect()
{
    sWorld.mAcceptedConnections++;
    OutPacket(SMSG_AUTH_CHALLENGE, 4, &mSeed);
    _latency = getMSTime();
}

void WorldSocket::_HandleAuthSession(WorldPacket* recvPacket)
{
    std::string account;
    uint32 unk2;
    _latency = getMSTime() - _latency;

    try
    {
        *recvPacket >> mClientBuild;
        *recvPacket >> unk2;
        *recvPacket >> account;
        *recvPacket >> mClientSeed;
    }
    catch(ByteBuffer::error &)
    {
        sLog.outDetail("Incomplete copy of AUTH_SESSION recieved.");
        return;
    }

    // Send out a request for this account.
    mRequestID = sLogonCommHandler.ClientConnected(account, this);
    
    if(mRequestID == 0xFFFFFFFF)
    {
        Disconnect();
        return;
    }

    // Set the authentication packet 
    pAuthenticationPacket = recvPacket;
}

void WorldSocket::InformationRetreiveCallback(WorldPacket & recvData, uint32 requestid)
{
    if(requestid != mRequestID)
        return;

    uint32 error;
    recvData >> error;

    if(error != 0)
    {
        // something happened wrong @ the logon server
        OutPacket(SMSG_AUTH_RESPONSE, 1, "\x0D");
        return;
    }

    // Extract account information from the packet.
    string AccountName;
    uint32 AccountID;
    string GMFlags;
    uint32 AccountFlags;
    
    recvData >> AccountID >> AccountName >> GMFlags >> AccountFlags;
    sLog.outDebug( " >> got information packet from logon: `%s` ID %u (request %u)", AccountName.c_str(), AccountID, mRequestID);
//    sLog.outColor(TNORMAL, "\n");

    mRequestID = 0;
    // Pull the session key.
    uint8 K[40];
    recvData.read(K, 40);
    
    BigNumber BNK;
    BNK.SetBinary(K, 40);
    
    // Initialize crypto.
    _crypt.SetKey(K, 40);
    _crypt.Init();

    //checking if player is already connected
    //disconnect corrent player and login this one(blizzlike)
    WorldSession *session = sWorld.FindSession( AccountID );
    if( session)
    {
        // AUTH_FAILED = 0x0D
        session->Disconnect();
    }

    Sha1Hash sha;

    uint8 digest[20];
    pAuthenticationPacket->read(digest, 20);

    uint32 t = 0;
    sha.UpdateData(AccountName);
    sha.UpdateData((uint8 *)&t, 4);
    sha.UpdateData((uint8 *)&mClientSeed, 4);
    sha.UpdateData((uint8 *)&mSeed, 4);
    sha.UpdateBigNumbers(&BNK, NULL);
    sha.Finalize();

    if (memcmp(sha.GetDigest(), digest, 20))
    {
        // AUTH_UNKNOWN_ACCOUNT = 21
        OutPacket(SMSG_AUTH_RESPONSE, 1, "\x15");
        return;
    }

    // Allocate session
    mSession = new WorldSession(AccountID, AccountName, this);
    ASSERT(mSession);
    mSession->deleteMutex.Acquire();
    
    // Set session properties
    mSession->SetClientBuild(mClientBuild);
    mSession->LoadSecurity(GMFlags);
    mSession->SetAccountFlags(AccountFlags);
    mSession->m_lastPing = time(NULL);

    for(uint32 i = 0; i < 8; ++i)
        mSession->SetAccountData(i, NULL, true, 0);

    sLog.outString("> %s authenticated from %s:%u [%ums]", AccountName.c_str(), GetRemoteIP().c_str(), GetRemotePort(), _latency);

    // Check for queue.
    if( (sWorld.GetNonGmSessionCount() < sWorld.GetPlayerLimit()) || mSession->HasGMPermissions() ) {
        Authenticate();
    } else {
        mSession->deleteMutex.Release();
        // Queued, sucker.
        uint32 Position = sWorld.AddQueuedSocket(this);
        mQueued = true;
        sLog.outString("> %s added to queue in position %u", AccountName.c_str(), Position);

        // Send packet so we know what we're doing
        UpdateQueuePosition(Position);
    }
}

void WorldSocket::Authenticate()
{
    ASSERT(pAuthenticationPacket);
    mQueued = false;

    if(!mSession) return;

    if(mSession->HasFlag(ACCOUNT_FLAG_XPACK_01))
        OutPacket(SMSG_AUTH_RESPONSE, 11, "\x0C\x30\x78\x00\x00\x00\x00\x00\x00\x00\x01");
    else
        OutPacket(SMSG_AUTH_RESPONSE, 11, "\x0C\x30\x78\x00\x00\x00\x00\x00\x00\x00\x00");

    sAddonMgr.SendAddonInfoPacket(pAuthenticationPacket, pAuthenticationPacket->rpos(), mSession);
    mSession->_latency = _latency;

    delete pAuthenticationPacket;
    pAuthenticationPacket = 0;

    sLog.outDetail("> Account %u authentication complete, adding session.", mSession->GetAccountId());

    sWorld.AddSession(mSession);
    sWorld.AddGlobalSession(mSession);

    if(mSession->HasFlag(ACCOUNT_FLAG_XTEND_INFO))
        sWorld.AddExtendedSession(mSession);

    if(mSession->HasGMPermissions())
        sWorld.gmList.insert(mSession);

    mSession->deleteMutex.Release();
}

void WorldSocket::UpdateQueuePosition(uint32 Position)
{
    WorldPacket QueuePacket(SMSG_AUTH_RESPONSE, 15);
    QueuePacket << uint8(0x1B) << uint8(0x2C) << uint8(0x73) << uint8(0) << uint8(0);
    QueuePacket << uint32(0) << uint8(0);
    QueuePacket << Position;
    SendPacket(&QueuePacket);
}

void WorldSocket::_HandlePing(WorldPacket* recvPacket)
{
    uint32 ping;
    if(recvPacket->size() < 4)
    {
        sLog.outString("Socket closed due to incomplete ping packet.");
        Disconnect();
        return;
    }

    *recvPacket >> ping;
    if(mSession)
        mSession->m_lastPing = time(NULL);

    if(recvPacket->size() >= 8 && mSession)
    {
        *recvPacket >> _latency;
        if(!_latency)
            _latency = mSession->_latency;
        else
            mSession->_latency = _latency;
        //sLog.outDetail("Got ping packet with latency of %u and seq of %u", mSession->_latency, ping);
    }
    OutPacket(SMSG_PONG, 4, &ping);

#ifdef WIN32
    // Dynamically change nagle buffering status based on latency.
    if(_latency >= 250)
    {
        if(!m_nagleEanbled)
        {
            u_long arg = 0;
            setsockopt(GetFd(), 0x6, 0x1, (const char*)&arg, sizeof(arg));
            m_nagleEanbled = true;
        }
    }
    else
    {
        if(m_nagleEanbled)
        {
            u_long arg = 1;
            setsockopt(GetFd(), 0x6, 0x1, (const char*)&arg, sizeof(arg));
            m_nagleEanbled = false;
        }
    }
#endif
}

void WorldSocket::OnRead()
{
    for(;;)
    {
        // Check for the header if we don't have any bytes to wait for.
        if(mRemaining == 0)
        {
            if(GetReadBufferSize() < 6)
            {
                // No header in the packet, let's wait.
                return;
            }

            // Copy from packet buffer into header local var
            ClientPktHeader Header;
            Read(6, (uint8*)&Header);

            // Decrypt the header
            _crypt.DecryptRecv((uint8*)&Header, 6);

            mRemaining = mSize = ntohs(Header.size) - 4;
            mOpcode = Header.cmd;
        }

        WorldPacket * Packet;

        if(mRemaining > 0)
        {
            if( GetReadBufferSize() < mRemaining )
            {
                // We have a fragmented packet. Wait for the complete one before proceeding.
                return;
            }
        }

        Packet = new WorldPacket(mOpcode, mSize);
        Packet->resize(mSize);

        if(mRemaining > 0)
        {
            // Copy from packet buffer into our actual buffer.
            Read(mRemaining, (uint8*)Packet->contents());
        }

        sWorldLog.LogPacket(mSize, mOpcode, mSize ? Packet->contents() : NULL, 0);
        mRemaining = mSize = mOpcode = 0;

        // Check for packets that we handle
        switch(Packet->GetOpcode())
        {
        case CMSG_PING:
            {
                _HandlePing(Packet);
                delete Packet;
            }break;
        case CMSG_AUTH_SESSION:
            {
                _HandleAuthSession(Packet);
            }break;
        default:
            {
                if(mSession) mSession->QueuePacket(Packet);
                else delete Packet;
            }break;
        }
    }
}

#endif

void WorldLog::LogPacket(uint32 len, uint16 opcode, const uint8* data, uint8 direction)
{
#ifdef ECHO_PACKET_LOG_TO_CONSOLE
    sLog.outString("[%s]: %s %s (0x%03X) of %u bytes.", direction ? "SERVER" : "CLIENT", direction ? "sent" : "received",
        LookupName(opcode, g_worldOpcodeNames), opcode, len);
#endif

    if(bEnabled)
    {
        mutex.Acquire();
        unsigned int line = 1;
        unsigned int countpos = 0;
        uint16 lenght = len;
        unsigned int count = 0;

        log->AddFormat("{%s} Packet: (0x%04X) %s PacketSize = %u\n", (direction ? "SERVER" : "CLIENT"), opcode,
            LookupOpcodeName(opcode), lenght);
        log->Add("|------------------------------------------------|----------------|\n");
        log->Add("|00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |0123456789ABCDEF|\n");
        log->Add("|------------------------------------------------|----------------|\n");

        if(lenght > 0)
        {
            log->Add("|");
            for (count = 0 ; count < lenght ; count++)
            {
                if (countpos == 16)
                {
                    countpos = 0;

                    log->Add("|");

                    for (unsigned int a = count-16; a < count;a++)
                    {
                        if ((data[a] < 32) || (data[a] > 126))
                            log->Add(".");
                        else
                            log->AddFormat("%c",data[a]);
                    }

                    log->Add("|\n");

                    line++;
                    log->Add("|");
                }

                log->AddFormat("%02X ",data[count]);

                //FIX TO PARSE PACKETS WITH LENGHT < OR = TO 16 BYTES.
                if (count+1 == lenght && lenght <= 16)
                {
                    for (unsigned int b = countpos+1; b < 16;b++)
                        log->Add("   ");

                    log->Add("|");

                    for (unsigned int a = 0; a < lenght;a++)
                    {
                        if ((data[a] < 32) || (data[a] > 126))
                            log->Add(".");
                        else
                            log->AddFormat("%c",data[a]);
                    }

                    for (unsigned int c = count; c < 15;c++)
                        log->Add(" ");

                    log->Add("|\n");
                }

                //FIX TO PARSE THE LAST LINE OF THE PACKETS WHEN THE LENGHT IS > 16 AND ITS IN THE LAST LINE.
                if (count+1 == lenght && lenght > 16)
                {
                    for (unsigned int b = countpos+1; b < 16;b++)
                        log->Add("   ");

                    log->Add("|");

                    unsigned short print = 0;

                    for (unsigned int a = line * 16 - 16; a < lenght;a++)
                    {
                        if ((data[a] < 32) || (data[a] > 126))
                            log->Add(".");
                        else
                            log->AddFormat("%c",data[a]);

                        print++;
                    }

                    for (unsigned int c = print; c < 16;c++)
                        log->Add(" ");

                    log->Add("|\n");
                }

                countpos++;
            }
        }
        log->Add("-------------------------------------------------------------------\n\n");
        mutex.Release();
    }
}
