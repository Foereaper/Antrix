/****************************************************************************
 *
 * Honor System
 *
 */

#include "StdAfx.h"

void WorldSession::HandleSetVisibleRankOpcode(WorldPacket& recv_data)
{
    CHECK_PACKET_SIZE(recv_data, 4);
    uint32 ChosenRank;
    recv_data >> ChosenRank; 
    if(ChosenRank == 0xFFFFFFFF)
        _player->SetUInt32Value(PLAYER_CHOSEN_TITLE, 0);
    else
        _player->SetUInt32Value(PLAYER_CHOSEN_TITLE, ChosenRank);
}

void HonorHandler::AddHonorPointsToPlayer(Player *pPlayer, uint32 uAmount)
{
    pPlayer->m_honorPoints += uAmount;
    pPlayer->m_honorToday += uAmount;
    pPlayer->HandleProc(PROC_ON_GAIN_EXPIERIENCE, pPlayer, NULL);

    RecalculateHonorFields(pPlayer);
}

time_t HonorHandler::GetNextUpdateTime()
{
    time_t ct = time(NULL);
    struct tm * tp = localtime(&ct);
    tm now_time = *tp;
    now_time.tm_hour = now_time.tm_min = now_time.tm_sec = 0;

    return mktime(&now_time);
}

void HonorHandler::PerformStartupTasks()
{
    sLog.outString("Initializing Honor System...");
    sLog.outString("  - Checking for out of date players and moving their kill values...");
    uint32 next_update = GetNextUpdateTime();
    uint32 now_update = time(NULL);
    QueryResult * result = CharacterDatabase.Query("SELECT guid, killsToday, killsYesterday, killsLifeTime, honorToday, honorYesterday, honorPoints FROM characters WHERE lastDailyReset < %u", next_update);
    if(!result)
    {
        sLog.outString("  - No players need to be updated.");
    }
    else
    {
        Field * fields = result->Fetch();
        do 
        {
            uint32 guid = fields[0].GetUInt32();
            uint32 killsToday = fields[1].GetUInt32();
            uint32 killsYesterday = fields[2].GetUInt32();
            uint32 killsLifeTime = fields[3].GetUInt32();
            uint32 honorToday = fields[4].GetUInt32();
            uint32 honorYesterday = fields[5].GetUInt32();
            uint32 honorPoints = fields[6].GetUInt32();

            killsYesterday = killsToday;
            honorYesterday = honorToday;
            killsToday = honorToday = 0;

            CharacterDatabase.WaitExecute("UPDATE characters SET lastDailyReset = %u WHERE guid = %u", now_update, guid);
            CharacterDatabase.WaitExecute("UPDATE characters SET killsToday = %u WHERE guid = %u", killsToday, guid);
            CharacterDatabase.WaitExecute("UPDATE characters SET killsYesterday = %u WHERE guid = %u", killsYesterday, guid);
            CharacterDatabase.WaitExecute("UPDATE characters SET killsLifeTime = %u WHERE guid = %u", killsLifeTime, guid);
            CharacterDatabase.WaitExecute("UPDATE characters SET honorToday = %u WHERE guid = %u", honorToday, guid);
            CharacterDatabase.WaitExecute("UPDATE characters SET honorYesterday = %u WHERE guid = %u", honorYesterday, guid);
            CharacterDatabase.WaitExecute("UPDATE characters SET honorPoints = %u WHERE guid = %u", honorPoints, guid);

        } while(result->NextRow());
        sLog.outString("  - Honor re-calculated for %u players.", result->GetRowCount());
        delete result;
    }
    sLog.outString("Honor System Ready.");
}

int32 HonorHandler::CalculateHonorPointsForKill(Player *pPlayer, Unit* pVictim)
{
    // this sucks.. ;p
    if(!pVictim)
    {
        int pts = rand() % 100 + 100;
        return pts;
    }

    if(pVictim != pPlayer && pVictim->GetTypeId() == TYPEID_PLAYER)
    {
        uint32 k_level =  pPlayer->GetUInt32Value(UNIT_FIELD_LEVEL);
        uint32 v_level =  pVictim->GetUInt32Value(UNIT_FIELD_LEVEL);
        int k_honor = pPlayer->m_honorPoints; // or whatever function is :P
        int v_honor = static_cast<Player*>(pVictim)->m_honorPoints;
        //uint32 total_kills = pPlayer->m_killsToday;
        uint32 k_grey = 0;

        if (k_level > 5 && k_level < 40) {
            k_grey = k_level - (uint32)(5 + floor(float(float(k_level) / 10.0f)));
        } else {
            k_grey = k_level - (uint32)(1 + floor(float(float(k_level) / 5.0f)));
        }

        float tmp =  (float)(k_level - k_grey);
        if(tmp == 0.0f)
            tmp = 1.0f;
        if(k_honor == 0)
            k_honor = 1;

        float diff_level = ((float)(v_level-k_grey)) / ((float)(k_level - k_grey));
        if(diff_level > 2) diff_level = 2.0;
        if(diff_level < 0) diff_level = 0.0;

        float diff_honor = ((float)v_honor) / ((float)k_honor);
        if(diff_honor > 3) diff_honor = 3.0;
        if(diff_honor < 0) diff_honor = 0.0;

        float honor_points = diff_level * (150 + diff_honor*60);
        honor_points *= ((float)k_level) / 70.0;
        honor_points *= World::getSingleton().getRate(RATE_HONOR);

        return float2int32(honor_points);
    }
    return 0;
}

void HonorHandler::OnPlayerKilledUnit(Player *pPlayer, Unit* pVictim)
{
    if(pVictim && (!pVictim->IsPlayer() || static_cast<Player*>(pVictim)->m_honorless))
        return;

    // Calculate points
    int32 Points = CalculateHonorPointsForKill(pPlayer, pVictim);

    if(Points > 0)
    {
        if(pPlayer->GetGroup())
        {
            Group *pGroup = pPlayer->GetGroup();
            Player *gPlayer = NULL;
            int32 GroupPoints;
            GroupPoints = (Points / (pGroup->MemberCount() ? pGroup->MemberCount() : 1));
            GroupMembersSet::iterator gitr;
            for(uint32 k = 0; k < pGroup->GetSubGroupCount(); k++)
            {
                for(gitr = pGroup->GetSubGroup(k)->GetGroupMembersBegin(); gitr != pGroup->GetSubGroup(k)->GetGroupMembersEnd(); ++gitr)
                {
                    gPlayer = (*gitr);
                    
                    if(gPlayer->isInRange(pPlayer,100.0f)) // visible range
                    {
                        gPlayer->m_killsToday++;
                        gPlayer->m_killsLifetime++;
                        AddHonorPointsToPlayer(gPlayer, GroupPoints);
                        if(pVictim)
                        {
                            // Send PVP credit
                            WorldPacket data(SMSG_PVP_CREDIT, 12);
                            uint32 pvppoints = GroupPoints * 10;
                            data << pvppoints << pVictim->GetGUID() << uint32(static_cast<Player*>(pVictim)->GetPVPRank());
                            gPlayer->GetSession()->SendPacket(&data);
                        }
                    }

                }
            }
        
        }
        else
        {
            pPlayer->m_killsToday++;
            pPlayer->m_killsLifetime++;
            AddHonorPointsToPlayer(pPlayer, Points);
            
            if(pVictim)
            {
                // Send PVP credit
                WorldPacket data(SMSG_PVP_CREDIT, 12);
                uint32 pvppoints = Points * 10;
                data << pvppoints << pVictim->GetGUID() << uint32(static_cast<Player*>(pVictim)->GetPVPRank());
                pPlayer->GetSession()->SendPacket(&data);
            }
        }
    }
}

void HonorHandler::RecalculateHonorFields(Player *pPlayer)
{
    // Why are we multiplying by 10.. ho well
    pPlayer->SetUInt32Value(PLAYER_FIELD_KILLS, pPlayer->m_killsToday);
    pPlayer->SetUInt32Value(PLAYER_FIELD_TODAY_CONTRIBUTION, pPlayer->m_honorToday);
    pPlayer->SetUInt32Value(PLAYER_FIELD_YESTERDAY_CONTRIBUTION, pPlayer->m_killsYesterday | ( (pPlayer->m_honorYesterday * 10) << 16));
    pPlayer->SetUInt32Value(PLAYER_FIELD_LIFETIME_HONORBALE_KILLS, pPlayer->m_killsLifetime);
//    if(pPlayer->m_honorPoints < 0)
  //      return;
    pPlayer->SetUInt32Value(PLAYER_FIELD_HONOR_CURRENCY, pPlayer->m_honorPoints);
}

void HonorHandler::DailyFieldMove(Player *pPlayer)
{
    // Move fields
    pPlayer->m_honorYesterday = pPlayer->m_honorToday;
    pPlayer->m_killsYesterday = pPlayer->m_killsToday;
    
    pPlayer->m_killsToday = 0;
    pPlayer->m_honorToday = 0;

    // update fields
    RecalculateHonorFields(pPlayer);
    pPlayer->LastHonorResetTime(time(NULL));
    pPlayer->SaveHonorFields();
}

bool ChatHandler::HandleAddKillCommand(const char* args, WorldSession* m_session)
{
    uint32 KillAmount = args ? atol(args) : 1;
    Player *plr = getSelectedChar(m_session, true);
    if(plr == 0)
        return true;

    BlueSystemMessage(m_session, "Adding %u kills to player %s.", KillAmount, plr->GetName());
    GreenSystemMessage(plr->GetSession(), "You have had %u honor kills added to your character.", KillAmount);

    for(uint32 i = 0; i < KillAmount; ++i)
        HonorHandler::OnPlayerKilledUnit(plr, 0);

    return true;
}

bool ChatHandler::HandleAddHonorCommand(const char* args, WorldSession* m_session)
{
    uint32 HonorAmount = args ? atol(args) : 1;
    Player *plr = getSelectedChar(m_session, true);
    if(plr == 0)
        return true;

    BlueSystemMessage(m_session, "Adding %u honor to player %s.", HonorAmount, plr->GetName());
    GreenSystemMessage(plr->GetSession(), "You have had %u honor points added to your character.", HonorAmount);

    HonorHandler::AddHonorPointsToPlayer(plr, HonorAmount);
    return true;
}

bool ChatHandler::HandlePVPCreditCommand(const char* args, WorldSession* m_session)
{
    uint32 Rank, Points;
    if(sscanf(args, "%u %u", (unsigned int*)&Rank, (unsigned int*)&Points) != 2)
    {
        RedSystemMessage(m_session, "Command must be in format <rank> <points>.");
        return true;
    }
    Points *= 10;
    uint64 Guid = m_session->GetPlayer()->GetSelection();
    if(Guid == 0)
    {
        RedSystemMessage(m_session, "A selection of a unit or player is required.");
        return true;
    }

    BlueSystemMessage(m_session, "Building packet with Rank %u, Points %u, GUID " I64FMT ".", 
        Rank, Points, Guid);

    WorldPacket data(SMSG_PVP_CREDIT, 12);
    data << Points << Guid << Rank;
    m_session->SendPacket(&data);
    return true;
}

bool ChatHandler::HandleGlobalHonorDailyMaintenanceCommand(const char* args, WorldSession* m_session)
{
    return false;
}

bool ChatHandler::HandleNextDayCommand(const char* args, WorldSession* m_session)
{
    Player * plr = getSelectedChar(m_session);
    if(plr == 0)
        return true;

    BlueSystemMessage(m_session, "Moving honor fields to tomorrow for player %s.", plr->GetName());
    GreenSystemMessage(m_session, "%s moved your honor fields to tomorrow.", m_session->GetPlayer()->GetName());

    HonorHandler::DailyFieldMove(plr);
    return true;
}
