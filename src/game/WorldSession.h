/****************************************************************************
 *
 * General Object Type File
 *
 */

//
//
// WorldSession.h
//

#ifndef __WORLDSESSION_H
#define __WORLDSESSION_H

class Player;
class WorldPacket;
class WorldSocket;
class WorldSession;
class MapMgr;
class Creature;
class MovementInfo;
struct TrainerSpell;

struct OpcodeHandler;

struct AccountDataEntry
{
    char * data;
    uint32 sz;
    bool bIsDirty;
};

typedef struct Cords {
    float x,y,z;
}Cords;


class MovementInfo
{
public:
    uint32 time;
    float unk6;//pitch
    //on slip 8 is zero, on jump some other number
    //9,10 changes if you are not on foot
    uint32 unk8, unk9, unk10, unk11, unk12, unk13;
    uint32 unklast;//something related to collision

    float x, y, z, orientation;
    uint32 flags;
    uint32 FallTime;
    uint64 transGuid;
    float transX, transY, transZ, transO, transUnk;

    void init(WorldPacket & data)
    {
        transGuid = 0;
        unk13 = 0;
        data >> flags >> time;
        data >> x >> y >> z >> orientation;

        if (flags & 0x200) // Transport
        {
            data >> transGuid >> transX >> transY >> transZ >> transO >> transUnk;
        }
        if (flags & 0x200000) // Swimming
        {
            data >> unk6;
        }
        if (flags & 0x2000) // Falling
        {
            data >> FallTime >> unk8 >> unk9 >> unk10;
        }
        if (flags & 0x4000000)
        {
            data >> unk12;
        }

        data >> unklast;
        if(data.rpos() != data.wpos())
        {
            if(data.rpos() + 4 == data.wpos())
                data >> unk13;
            else
                sLog.outDebug("Extra bits of movement packet left");
        }
    }

    void write(WorldPacket & data)
    {
        data << flags << getMSTime();

        data << x << y << z << orientation;

        if (flags & 0x200) // Transport
        {
            data << transGuid << transX << transY << transZ << transO << transUnk;
        }
        if (flags & 0x200000) // Swimming
        {
            data << unk6;
        }
        if (flags & 0x2000) // Falling
        {
            data << FallTime << unk8 << unk9 << unk10;
        }
        if (flags & 0x4000000)
        {
            data << unk12;
        }
        data << unklast;
        if(unk13)
            data << unk13;
    }
};

#define NOTIFICATION_MESSAGE_NO_PERMISSION "You do not have permission to perform that function."
//#define CHECK_PACKET_SIZE(x, y) if(y > 0 && x.size() < y) { _socket->Disconnect(); return; }

void EncodeHex(const char* source, char* dest, uint32 size);
void DecodeHex(const char* source, char* dest, uint32 size);

extern OpcodeHandler WorldPacketHandlers[NUM_MSG_TYPES];
void CapitalizeString(string& arg);

// class to deal with packet processing
// allows to determine if next packet is safe to be processed
class PacketFilter
{
public:
    explicit PacketFilter(WorldSession* pSession) : m_pSession(pSession) { }
    virtual ~PacketFilter() { }

    virtual bool Process(WorldPacket* /*packet*/)
    {
        return true;
    }

    virtual bool ProcessLogout() const
    {
        return true;
    }

protected:
    WorldSession* const m_pSession;
};

// process only thread-safe packets in Map::Update()
class MapSessionFilter : public PacketFilter
{
public:
    explicit MapSessionFilter(WorldSession* pSession) : PacketFilter(pSession) { }
    ~MapSessionFilter() { }

    virtual bool Process(WorldPacket* packet) override;
    // in Map::Update() we do not process player logout!
    virtual bool ProcessLogout() const override
    {
        return false;
    }
};

// class used to filer only thread-unsafe packets from queue
// in order to update only be used in World::UpdateSessions()
class WorldSessionFilter : public PacketFilter
{
public:
    explicit WorldSessionFilter(WorldSession* pSession) : PacketFilter(pSession) { }
    ~WorldSessionFilter() { }

    virtual bool Process(WorldPacket* packet) override;
};

class SERVER_DECL WorldSession
{
    friend class WorldSocket;
public:
    WorldSession(uint32 id, string Name, WorldSocket *sock);
    ~WorldSession();

    inline void SendPacket(WorldPacket* packet)
    {
        if(_socket && _socket->IsConnected())
            _socket->SendPacket(packet);
    }

    inline void SendPacket(StackBufferBase * packet)
    {
        if(_socket && _socket->IsConnected())
            _socket->SendPacket(packet);
    }

    inline void OutPacket(uint16 opcode)
    {
        if(_socket && _socket->IsConnected())
            _socket->OutPacket(opcode, 0, NULL);
    }

    bool SendThrottledPacket(WorldPacket * packet, bool allocated);
    void UpdateThrottledPackets();

    uint32 m_currMsTime;
    uint32 m_lastPing;

    inline uint32 GetAccountId() const { return _accountId; }
    inline Player* GetPlayer() { return _player; }
    
    /* Acct flags */
    void SetAccountFlags(uint32 flags) { _accountFlags = flags; }
    bool HasFlag(uint32 flag) { return (_accountFlags & flag) != 0; }
    uint32 GetSide() { return _side; }
    void SetSide(uint32 side) { _side = side; };

    /* GM Permission System */
    void LoadSecurity(std::string securitystring);
    void SetSecurity(std::string securitystring);
    inline char* GetPermissions() { return permissions; }
    inline int GetPermissionCount() { return permissioncount; }
    inline bool HasPermissions() { return (permissioncount > 0) ? true : false; }
    inline bool HasGMPermissions()
    {
        if(!permissioncount)
            return false;

        return (strchr(permissions,'a')!=NULL) ? true : false;
    }
   
    bool CanUseCommand(char cmdstr);

    
    inline void SetSocket(WorldSocket *sock)
    {
        _socket = sock;
    }
    inline void SetPlayer(Player *plr) { _player = plr; }
    
    inline void SetAccountData(uint32 index, char* data, bool initial,uint32 sz)
    {
        ASSERT(index < 8);
        if(sAccountData[index].data)
            delete [] sAccountData[index].data;
        sAccountData[index].data = data;
        sAccountData[index].sz = sz;
        if(!initial && !sAccountData[index].bIsDirty)        // Mark as "changed" or "dirty"
            sAccountData[index].bIsDirty = true;
        else if(initial)
            sAccountData[index].bIsDirty = false;
    }
    
    inline AccountDataEntry* GetAccountData(uint32 index)
    {
        ASSERT(index < 8);
        return &sAccountData[index];
    }

    void SetLogoutTimer(uint32 ms)
    {
        if(ms)  _logoutTime = m_currMsTime+ms;
        else    _logoutTime = 0;
    }

    void LogoutPlayer(bool Save);

    inline void QueuePacket(WorldPacket* packet)
    {
        _recvQueue.Push(packet);
    }
    
    void OutPacket(uint16 opcode, uint16 len, const void* data)
    {
        if(_socket && _socket->IsConnected())
            _socket->OutPacket(opcode, len, data);
    }

    inline WorldSocket* GetSocket() { return _socket; }
    
    void Disconnect()
    {
        if(_socket && _socket->IsConnected())
            _socket->Disconnect();
    }

    int __fastcall Update(uint32 InstanceID, PacketFilter& updater);

    void BuildItemPushResult(WorldPacket *data, uint64 guid, uint32 type, uint32 count, uint32 itemid, uint32 randomprop, uint8 unk = 0xFF, uint32 unk2 = 0, uint32 unk3 = 1, uint32 count_have = 0);
    void SendBuyFailed(uint64 guid, uint32 itemid, uint8 error);
    void SendSellItem(uint64 vendorguid, uint64 itemid, uint8 error);
    void SendNotification(const char *message, ...);

    inline void SetInstance(uint32 Instance) { instanceId = Instance; }
    inline uint32 GetLatency() { return _latency; }
    inline string GetAccountName() { return _accountName; }

    inline uint32 GetClientBuild() { return client_build; }
    inline void SetClientBuild(uint32 build) { client_build = build; }
    bool bDeleted;
    inline uint32 GetInstance() { return instanceId; }
    Mutex deleteMutex;
    void _HandleAreaTriggerOpcode(uint32 id);//real handle


public:

    void Handle_NULL(WorldPacket& recvPacket);
    void Handle_EarlyProccess(WorldPacket& recvPacket);
    void Handle_ServerSide(WorldPacket& recvPacket);
    void Handle_Deprecated(WorldPacket& recvPacket);

    /// Login screen opcodes (PlayerHandler.cpp):
    void HandleCharEnumOpcode(WorldPacket& recvPacket);
    void HandleCharDeleteOpcode(WorldPacket& recvPacket);
    void HandleCharCreateOpcode(WorldPacket& recvPacket);
    void HandlePlayerLoginOpcode(WorldPacket& recvPacket);

    /// Authentification and misc opcodes (MiscHandler.cpp):
    void HandlePingOpcode(WorldPacket& recvPacket);
    void HandleAuthSessionOpcode(WorldPacket& recvPacket);
    void HandleRepopRequestOpcode(WorldPacket& recvPacket);
    void HandleAutostoreLootItemOpcode(WorldPacket& recvPacket);
    void HandleLootMoneyOpcode(WorldPacket& recvPacket);
    void HandleLootOpcode(WorldPacket& recvPacket);
    void HandleLootReleaseOpcode(WorldPacket& recvPacket);
    void HandleLootMasterGiveOpcode(WorldPacket& recv_data);
    void HandleLootRollOpcode(WorldPacket& recv_data);
    void HandleWhoOpcode(WorldPacket& recvPacket);
    void HandleLogoutRequestOpcode(WorldPacket& recvPacket);
    void HandlePlayerLogoutOpcode(WorldPacket& recvPacket);
    void HandleLogoutCancelOpcode(WorldPacket& recvPacket);
    void HandleZoneUpdateOpcode(WorldPacket& recvPacket);
    void HandleSetTargetOpcode(WorldPacket& recvPacket);
    void HandleSetSelectionOpcode(WorldPacket& recvPacket);
    void HandleStandStateChangeOpcode(WorldPacket& recvPacket);
    void HandleDismountOpcode(WorldPacket & recvPacket);
    void HandleFriendListOpcode(WorldPacket& recvPacket);
    void HandleAddFriendOpcode(WorldPacket& recvPacket);
    void HandleDelFriendOpcode(WorldPacket& recvPacket);
    void HandleAddIgnoreOpcode(WorldPacket& recvPacket);
    void HandleDelIgnoreOpcode(WorldPacket& recvPacket);
    void HandleBugOpcode(WorldPacket& recvPacket);
    void HandleAreaTriggerOpcode(WorldPacket& recvPacket);
    void HandleUpdateAccountData(WorldPacket& recvPacket);
    void HandleRequestAccountData(WorldPacket& recvPacket);
    void HandleSetActionButtonOpcode(WorldPacket& recvPacket);
    void HandleSetAtWarOpcode(WorldPacket& recvPacket);
    void HandleSetWatchedFactionIndexOpcode(WorldPacket& recvPacket);
    void HandleTogglePVPOpcode(WorldPacket& recvPacket);
    void HandleAmmoSetOpcode(WorldPacket& recvPacket);
    void HandleGameObjectUse(WorldPacket& recvPacket);
    //void HandleJoinChannelOpcode(WorldPacket& recvPacket);
    //void HandleLeaveChannelOpcode(WorldPacket& recvPacket);
    void HandlePlayedTimeOpcode(WorldPacket & recv_data);
    void HandleSetSheathedOpcode(WorldPacket & recv_data);
    void HandleCompleteCinematic(WorldPacket & recv_data);


    /// Gm Ticket System in GMTicket.cpp:
    void HandleGMTicketCreateOpcode(WorldPacket& recvPacket);
    void HandleGMTicketUpdateOpcode(WorldPacket& recvPacket);
    void HandleGMTicketDeleteOpcode(WorldPacket& recvPacket);
    void HandleGMTicketGetTicketOpcode(WorldPacket& recvPacket);
    void HandleGMTicketSystemStatusOpcode(WorldPacket& recvPacket);
    void HandleGMTicketToggleSystemStatusOpcode(WorldPacket& recvPacket);

    /// Opcodes implemented in QueryHandler.cpp:
    void HandleNameQueryOpcode(WorldPacket& recvPacket);
    void HandleQueryTimeOpcode(WorldPacket& recvPacket);
    void HandleCreatureQueryOpcode(WorldPacket& recvPacket);
    void HandleGameObjectQueryOpcode(WorldPacket& recvPacket);
    void HandleItemNameQueryOpcode( WorldPacket & recv_data );
    void HandlePageTextQueryOpcode( WorldPacket & recv_data );

    /// Opcodes implemented in MovementHandler.cpp
    void HandleMoveHeartbeatOpcode( WorldPacket& recvPacket );
    void HandleMoveWorldportAckOpcode( WorldPacket& recvPacket );
    void HandleMoveStopOpcode( WorldPacket& recvPacket );
    void HandleMovementOpcodes( WorldPacket& recvPacket );
    void HandleFallOpcode( WorldPacket & recv_data );
    void HandleMoveTimeSkippedOpcode( WorldPacket & recv_data );
    void HandleMoveNotActiveMoverOpcode( WorldPacket & recv_data );
    void HandleSetActiveMoverOpcode( WorldPacket & recv_data );
    void HandleMoveTeleportAckOpcode( WorldPacket & recv_data );
    void HandleBasicMovementOpcodes( WorldPacket& recvPacket );

    /// Opcodes implemented in GroupHandler.cpp:
    void HandleGroupInviteOpcode(WorldPacket& recvPacket);
    void HandleGroupCancelOpcode(WorldPacket& recvPacket);
    void HandleGroupAcceptOpcode(WorldPacket& recvPacket);
    void HandleGroupDeclineOpcode(WorldPacket& recvPacket);
    void HandleGroupUninviteOpcode(WorldPacket& recvPacket);
    void HandleGroupUninviteGuildOpcode(WorldPacket& recvPacket);
    void HandleGroupSetLeaderOpcode(WorldPacket& recvPacket);
    void HandleGroupDisbandOpcode(WorldPacket& recvPacket);
    void HandleLootMethodOpcode(WorldPacket& recvPacket);
    void HandleMinimapPingOpcode(WorldPacket& recvPacket);
    void HandleSetPlayerIconOpcode(WorldPacket& recv_data);
    void SendPartyCommandResult(Player *pPlayer, uint32 p1, std::string name, uint32 err);

    // Raid
    void HandleConvertGroupToRaidOpcode(WorldPacket& recvPacket);
    void HandleGroupChangeSubGroup(WorldPacket& recvPacket);
    void HandleGroupAssistantLeader(WorldPacket& recvPacket);
    void HandleRequestRaidInfoOpcode(WorldPacket& recvPacket);
    void HandleReadyCheckOpcode(WorldPacket& recv_data);
    
    // LFG opcodes
    void HandleEnableAutoJoin(WorldPacket& recvPacket);
    void HandleDisableAutoJoin(WorldPacket& recvPacket);
    void HandleEnableAutoAddMembers(WorldPacket& recvPacket);
    void HandleDisableAutoAddMembers(WorldPacket& recvPacket);
    void HandleSetLookingForGroupComment(WorldPacket& recvPacket);
    void HandleMsgLookingForGroup(WorldPacket& recvPacket);
    void HandleSetLookingForGroup(WorldPacket& recvPacket);

    /// Taxi opcodes (TaxiHandler.cpp)
    void HandleTaxiNodeStatusQueryOpcode(WorldPacket& recvPacket);
    void HandleTaxiQueryAvaibleNodesOpcode(WorldPacket& recvPacket);
    void HandleActivateTaxiOpcode(WorldPacket& recvPacket);
    void HandleMultipleActivateTaxiOpcode(WorldPacket & recvPacket);

    /// NPC opcodes (NPCHandler.cpp)
    void HandleTabardVendorActivateOpcode(WorldPacket& recvPacket);
    void HandleBankerActivateOpcode(WorldPacket& recvPacket);
    void HandleBuyBankSlotOpcode(WorldPacket& recvPacket); 
    void HandleTrainerListOpcode(WorldPacket& recvPacket);
    void HandleTrainerBuySpellOpcode(WorldPacket& recvPacket);
    void HandleCharterShowListOpcode(WorldPacket& recvPacket);
    void HandleGossipHelloOpcode(WorldPacket& recvPacket);
    void HandleGossipSelectOptionOpcode(WorldPacket& recvPacket);
    void HandleSpiritHealerActivateOpcode(WorldPacket& recvPacket);
    void HandleNpcTextQueryOpcode(WorldPacket& recvPacket);
    void HandleBinderActivateOpcode(WorldPacket& recvPacket);

    // Auction House opcodes
    void HandleAuctionHelloOpcode(WorldPacket& recvPacket);
    void HandleAuctionListItems( WorldPacket & recv_data );
    void HandleAuctionListBidderItems( WorldPacket & recv_data );
    void HandleAuctionSellItem( WorldPacket & recv_data );
    void HandleAuctionListOwnerItems( WorldPacket & recv_data );
    void HandleAuctionPlaceBid( WorldPacket & recv_data );
    void HandleCancelAuction( WorldPacket & recv_data);

    // Mail opcodes
    void HandleGetMail( WorldPacket & recv_data );
    void HandleSendMail( WorldPacket & recv_data );
    void HandleTakeMoney( WorldPacket & recv_data );
    void HandleTakeItem( WorldPacket & recv_data );
    void HandleMarkAsRead( WorldPacket & recv_data );
    void HandleReturnToSender( WorldPacket & recv_data );
    void HandleMailDelete( WorldPacket & recv_data );
    void HandleItemTextQuery( WorldPacket & recv_data);
    void HandleMailTime(WorldPacket & recv_data);
    void HandleMailCreateTextItem(WorldPacket & recv_data );

    /// Item opcodes (ItemHandler.cpp)
    void HandleSwapInvItemOpcode(WorldPacket& recvPacket);
    void HandleSwapItemOpcode(WorldPacket& recvPacket);
    void HandleDestroyItemOpcode(WorldPacket& recvPacket);
    void HandleAutoEquipItemOpcode(WorldPacket& recvPacket);
    void HandleItemQuerySingleOpcode(WorldPacket& recvPacket);
    void HandleSellItemOpcode(WorldPacket& recvPacket);
    void HandleBuyItemInSlotOpcode(WorldPacket& recvPacket);
    void HandleBuyItemOpcode(WorldPacket& recvPacket);
    void HandleListInventoryOpcode(WorldPacket& recvPacket);
    void HandleAutoStoreBagItemOpcode(WorldPacket& recvPacket);
    void HandleBuyBackOpcode(WorldPacket& recvPacket);
    void HandleSplitOpcode(WorldPacket& recvPacket);
    void HandleReadItemOpcode(WorldPacket& recvPacket);
    void HandleRepairItemOpcode(WorldPacket &recvPacket);
    void HandleAutoBankItemOpcode(WorldPacket &recvPacket);
    void HandleAutoStoreBankItemOpcode(WorldPacket &recvPacket);
    void HandleCancelTemporaryEnchantmentOpcode(WorldPacket &recvPacket);
    void HandleInsertGemOpcode(WorldPacket &recvPacket);

    /// Combat opcodes (CombatHandler.cpp)
    void HandleAttackSwingOpcode(WorldPacket& recvPacket);
    void HandleAttackStopOpcode(WorldPacket& recvPacket);

    /// Spell opcodes (SpellHandler.cpp)
    void HandleUseItemOpcode(WorldPacket& recvPacket);
    void HandleCastSpellOpcode(WorldPacket& recvPacket);
    void HandleCancelCastOpcode(WorldPacket& recvPacket);
    void HandleCancelAuraOpcode(WorldPacket& recvPacket);
    void HandleCancelChannellingOpcode(WorldPacket& recvPacket);
    void HandleCancelAutoRepeatSpellOpcode(WorldPacket& recv_data);
    void HandleAddDynamicTargetOpcode(WorldPacket & recvPacket);

    /// Skill opcodes (SkillHandler.spp)
    //void HandleSkillLevelUpOpcode(WorldPacket& recvPacket);
    void HandleLearnTalentOpcode(WorldPacket& recvPacket);
    void HandleUnlearnTalents( WorldPacket & recv_data );

    /// Quest opcodes (QuestHandler.cpp)
    void HandleQuestgiverStatusQueryOpcode(WorldPacket& recvPacket);
    void HandleQuestgiverHelloOpcode(WorldPacket& recvPacket);
    void HandleQuestgiverAcceptQuestOpcode(WorldPacket& recvPacket);
    void HandleQuestgiverCancelOpcode(WorldPacket& recvPacket);
    void HandleQuestgiverChooseRewardOpcode(WorldPacket& recvPacket);
    void HandleQuestgiverRequestRewardOpcode(WorldPacket& recvPacket);
    void HandleQuestGiverQueryQuestOpcode( WorldPacket& recvPacket );
    void HandleQuestQueryOpcode(WorldPacket& recvPacket);
    void HandleQuestgiverCompleteQuestOpcode( WorldPacket & recvPacket );
    void HandleQuestlogRemoveQuestOpcode(WorldPacket& recvPacket);
    void HandlePushQuestToPartyOpcode(WorldPacket &recvPacket);
    void HandleQuestPushResult(WorldPacket &recvPacket);


    /// Chat opcodes (Chat.cpp)
    void HandleMessagechatOpcode(WorldPacket& recvPacket);
    void HandleTextEmoteOpcode(WorldPacket& recvPacket);

    /// Corpse opcodes (Corpse.cpp)
    void HandleCorpseReclaimOpcode( WorldPacket& recvPacket );
    void HandleCorpseQueryOpcode( WorldPacket& recvPacket );
    void HandleResurrectResponseOpcode(WorldPacket& recvPacket);

    /// Channel Opcodes (ChannelHandler.cpp)
    void HandleChannelJoin(WorldPacket& recvPacket);
    void HandleChannelLeave(WorldPacket& recvPacket);
    void HandleChannelList(WorldPacket& recvPacket);
    void HandleChannelPassword(WorldPacket& recvPacket);
    void HandleChannelSetOwner(WorldPacket& recvPacket);
    void HandleChannelOwner(WorldPacket& recvPacket);
    void HandleChannelModerator(WorldPacket& recvPacket);
    void HandleChannelUnmoderator(WorldPacket& recvPacket);
    void HandleChannelMute(WorldPacket& recvPacket);
    void HandleChannelUnmute(WorldPacket& recvPacket);
    void HandleChannelInvite(WorldPacket& recvPacket);
    void HandleChannelKick(WorldPacket& recvPacket);
    void HandleChannelBan(WorldPacket& recvPacket);
    void HandleChannelUnban(WorldPacket& recvPacket);
    void HandleChannelAnnounce(WorldPacket& recvPacket);
    void HandleChannelModerate(WorldPacket& recvPacket);

    // Duel
    void HandleDuelAccepted(WorldPacket & recv_data);
    void HandleDuelCancelled(WorldPacket & recv_data);

    // Trade
    void HandleInitiateTrade(WorldPacket & recv_data);
    void HandleBeginTrade(WorldPacket & recv_data);
    void HandleBusyTrade(WorldPacket & recv_data);
    void HandleIgnoreTrade(WorldPacket & recv_data);
    void HandleAcceptTrade(WorldPacket & recv_data);
    void HandleUnacceptTrade(WorldPacket & recv_data);
    void HandleCancelTrade(WorldPacket & recv_data);
    void HandleSetTradeItem(WorldPacket & recv_data);
    void HandleClearTradeItem(WorldPacket & recv_data);
    void HandleSetTradeGold(WorldPacket & recv_data);

    // Guild
    void HandleGuildQuery(WorldPacket & recv_data);
    void HandleCreateGuild(WorldPacket & recv_data);                   
    void HandleInviteToGuild(WorldPacket & recv_data);              
    void HandleGuildAccept(WorldPacket & recv_data);             
    void HandleGuildDecline(WorldPacket & recv_data);
    void HandleGuildInfo(WorldPacket & recv_data);
    void HandleGuildRoster(WorldPacket & recv_data);
    void HandleGuildPromote(WorldPacket & recv_data);
    void HandleGuildDemote(WorldPacket & recv_data);
    void HandleGuildLeave(WorldPacket & recv_data);
    void HandleGuildRemove(WorldPacket & recv_data);
    void HandleGuildDisband(WorldPacket & recv_data);
    void HandleGuildLeader(WorldPacket & recv_data);
    void HandleGuildMotd(WorldPacket & recv_data);
    void HandleGuildRank(WorldPacket & recv_data);
    void HandleGuildAddRank(WorldPacket & recv_data);
    void HandleGuildDelRank(WorldPacket & recv_data);
    void HandleGuildSetPublicNote(WorldPacket & recv_data);
    void HandleGuildSetOfficerNote(WorldPacket & recv_data);
    void HandleSaveGuildEmblem(WorldPacket & recv_data);
    void HandleCharterBuy(WorldPacket & recv_data);
    void HandleCharterShowSignatures(WorldPacket & recv_data);
    void HandleCharterTurnInCharter(WorldPacket & recv_data);
    void HandleCharterQuery(WorldPacket & recv_data);
    void HandleCharterOffer(WorldPacket & recv_data);
    void HandleCharterSign(WorldPacket &recv_data);
    void HandleCharterRename(WorldPacket & recv_data);
    void HandleSetGuildInformation(WorldPacket & recv_data);
    void SendGuildCommandResult(uint32 typecmd,const char *  str,uint32 cmdresult);

    // Pet
    void HandlePetAction(WorldPacket & recv_data);
    void HandlePetInfo(WorldPacket & recv_data);
    void HandlePetNameQuery(WorldPacket & recv_data);
    void HandleBuyStableSlot(WorldPacket & recv_data);
    void HandleStablePet(WorldPacket & recv_data);
    void HandleUnstablePet(WorldPacket & recv_data);
    void HandleStabledPetList(WorldPacket & recv_data);
    void HandlePetRename(WorldPacket & recv_data);
    void HandlePetAbandon(WorldPacket & recv_data);

    // Battleground
    void HandleBattlefieldPortOpcode(WorldPacket &recv_data);
    void HandleBattlefieldStatusOpcode(WorldPacket &recv_data);
    void HandleBattleMasterHelloOpcode(WorldPacket &recv_data);
    void HandleLeaveBattlefieldOpcode(WorldPacket &recv_data);
    void HandleAreaSpiritHealerQueryOpcode(WorldPacket &recv_data);
    void HandleAreaSpiritHealerQueueOpcode(WorldPacket &recv_data);
    void HandleBattlegroundPlayerPositionsOpcode(WorldPacket &recv_data);
    void HandleArenaJoinOpcode(WorldPacket &recv_data);
    void HandleBattleMasterJoinOpcode(WorldPacket &recv_data);
    void HandleInspectHonorStatsOpcode(WorldPacket &recv_data);
    void HandlePVPLogDataOpcode(WorldPacket &recv_data);
    void HandleBattlefieldListOpcode(WorldPacket &recv_data);

    void HandleSetActionBarTogglesOpcode(WorldPacket &recvPacket);
    void HandleMoveSplineCompleteOpcode(WorldPacket &recvPacket);

    /// Helper functions
    void SetNpcFlagsForTalkToQuest(const uint64& guid, const uint64& targetGuid);

    //Tutorials
    void HandleTutorialFlag ( WorldPacket & recv_data );
    void HandleTutorialClear( WorldPacket & recv_data );
    void HandleTutorialReset( WorldPacket & recv_data );

    //Acknowledgements
    void HandleAcknowledgementOpcodes( WorldPacket & recv_data );
    void HandleMountSpecialAnimOpcode(WorldPacket& recv_data);    

    void HandleSelfResurrectOpcode(WorldPacket& recv_data);
    void HandleUnlearnSkillOpcode(WorldPacket &recv_data);
    void HandleRandomRollOpcode(WorldPacket &recv_data);
    void HandleOpenItemOpcode(WorldPacket &recv_data);
    
    void HandleToggleHelmOpcode(WorldPacket &recv_data);
    void HandleToggleCloakOpcode(WorldPacket &recv_data);
    void HandleSetVisibleRankOpcode(WorldPacket& recv_data);
    void HandlePetSetActionOpcode(WorldPacket& recv_data);

    void _HandleBreathing(WorldPacket &recv_data, MovementInfo &mi);
    void _SpeedCheck(MovementInfo &mi);

    //instances
    void HandleResetInstanceOpcode(WorldPacket& recv_data);
    void HandleDungeonDifficultyOpcode(WorldPacket& recv_data);

    uint8 TrainerGetSpellStatus(TrainerSpell* pSpell);
    void __fastcall CHECK_PACKET_SIZE(WorldPacket& data, uint32 size);
    void SendMailError(uint32 error);

    void HandleCharRenameOpcode(WorldPacket & recv_data);
    void HandlePartyMemberStatsOpcode(WorldPacket & recv_data);
    void HandleSummonResponseOpcode(WorldPacket & recv_data);

    void SendInventoryList(Creature* pCreature);
    void SendTrainerList(Creature* pCreature);
    void SendCharterRequest(Creature* pCreature);
    void SendTaxiList(Creature* pCreature);
    void SendInnkeeperBind(Creature* pCreature);
    void SendBattlegroundList(Creature* pCreature, uint32 mapid);
    void SendBankerList(Creature* pCreature);
    void SendTabardHelp(Creature* pCreature);
    void SendAuctionList(Creature* pCreature);
    void SendSpiritHealerRequest(Creature* pCreature);
    bool PlayerLogin(uint32 guid, uint32 forced_map_id, uint32 forced_instance_id);

private:
    friend class Player;
    Player *_player;
    WorldSocket *_socket;
        
    /* Preallocated buffers for movement handlers */
    MovementInfo movement_info;
    uint8 movement_packet[90];

    float m_wLevel; // Level of water the player is currently in
    bool m_bIsWLevelSet; // Does the m_wLevel variable contain up-to-date information about water level?
    
    uint32 _accountId;
    uint32 _accountFlags;
    string _accountName;
    uint32 _side;

    WoWGuid m_MoverWoWGuid;

    uint32 _logoutTime; // time we received a logout request -- wait 20 seconds, and quit

    AccountDataEntry sAccountData[8];

    FastQueue<WorldPacket*, Mutex> _recvQueue;
    FastQueue<WorldPacket*, Mutex> _throttledQueue;
    char *permissions;
    int permissioncount;

    bool m_playerRecentlyLoggedOut;
    bool m_playerLogout;
    uint32 _latency;
    uint32 client_build;
    uint32 instanceId;
public:

    time_t packetThrottleTimeout;
    uint32 packetThrottleCount;
    uint32 floodLines;
    uint32 floodTime;
};

typedef std::set<WorldSession*> SessionSet;

#endif
