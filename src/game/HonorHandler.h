/****************************************************************************
 *
 * Honor System
 *
 */

#ifndef HONORHANDLER_H
#define HONORHANDLER_H

class HonorHandler
{
public:
    static int32 CalculateHonorPointsForKill(Player *pPlayer, Unit* pVictim);
    
    static void RecalculateHonorFields(Player *pPlayer);
    static void DailyFieldMove(Player *pPlayer);

    static void PerformStartupTasks();

    static void AddHonorPointsToPlayer(Player *pPlayer, uint32 uAmount);
    static void OnPlayerKilledUnit(Player *pPlayer, Unit* pVictim);
    static time_t GetNextUpdateTime();
    
};


#endif
