/****************************************************************************
 *
 * General Object Type File
 *
 */

#ifndef AUTHSOCKET_H
#define AUTHSOCKET_H

#include "AccountCache.h"
#include "AuthStructs.h"

class LogonCommServerSocket;

class AuthSocket : public Socket
{
    friend class LogonCommServerSocket;
public:

    ///////////////////////////////////////////////////
    // Netcore shit
    //////////////////////////
    AuthSocket(SOCKET fd);
    ~AuthSocket();

    void OnRead();

    ///////////////////////////////////////////////////
    // Client Packet Handlers
    //////////////////////////

    void HandleChallenge();
    void HandleProof();
    void HandleRealmlist();

    ///////////////////////////////////////////////////
    // Server Packet Builders
    //////////////////////////

    void SendChallengeError(uint8 Error);
    void SendProofError(uint8 Error, uint8 * M2);
    inline sAuthLogonChallenge_C * GetChallenge() { return &m_challenge; }
    inline void SendPacket(const uint8* data, const uint16 len) { Send(data, len); }
    void OnDisconnect();
    inline time_t GetLastRecv() { return last_recv; }
    bool removedFromSet;
    inline uint32 GetAccountID() { return m_account ? m_account->AccountId : 0; }

protected:

    sAuthLogonChallenge_C m_challenge;
    Account * m_account;
    bool m_authenticated;

    //////////////////////////////////////////////////
    // Authentication BigNumbers
    /////////////////////////
    BigNumber N, s, g, v;
    BigNumber b, B;
    BigNumber rs;

    //////////////////////////////////////////////////
    // Session Key
    /////////////////////////

    BigNumber m_sessionkey;
    time_t last_recv;
};

#endif
