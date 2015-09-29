#ifndef __FACTION_H
#define __FACTION_H

#include "Unit.h"


#include "StdAfx.h"

inline bool isHostile(Object* objA, Object* objB)// B is hostile for A?
{
    if(!objA || !objB)
        return false;
    bool hostile = false;

    if(objB->m_faction == NULL || objA->m_faction == NULL)
        return true;

    if(objA == objB)
        return false;   // can't attack self.. this causes problems with buffs if we dont have it :p

    if(objA->GetTypeId() == TYPEID_CORPSE)
        return false;

    if(objB->GetTypeId() == TYPEID_CORPSE)
        return false;

    uint32 faction = objB->m_faction->Mask;
    uint32 host = objA->m_faction->HostileMask;

    if(faction & host)
    {
        hostile = true;
    }
    // check friend/enemy list
    for(uint32 i = 0; i < 4; i++)
    {
        if(objA->m_faction->EnemyFactions[i] == objB->m_faction->Faction)
        {
            hostile = true;
            break;
        }
        if(objA->m_faction->FriendlyFactions[i] == objB->m_faction->Faction)
        {
            hostile = false;
            break;
        }
    }

    // PvP Flag System Checks
    // We check this after the normal isHostile test, that way if we're
    // on the opposite team we'll already know :p

    if(hostile && 
        ( objA->IsPlayer() || objA->IsPet() || ( objA->IsUnit() && !objA->IsPlayer() && static_cast<Creature *>(objA)->IsTotem() && static_cast<Creature *>(objA)->GetTotemOwner()->IsPvPFlagged() ) ) )
    {
        if(objB->IsPlayer())
        {
            // Check PvP Flags.
            if(static_cast<Player*>(objB)->IsPvPFlagged())
                return true;
            else
                return false;
        }
        if(objB->IsPet())
        {
            // Check PvP Flags.
            if(static_cast<Pet*>(objB)->GetPetOwner() && static_cast<Pet*>(objB)->GetPetOwner()->IsPvPFlagged())
                return true;
            else
                return false;
        }
    }

    // Reputation System Checks
    if(objA->IsPlayer() && !objB->IsPlayer())       // PvE
    {
        if(objB->m_factionDBC->RepListId >= 0)
            hostile = ((Player*)objA)->IsHostileBasedOnReputation(objB->m_factionDBC);
    }
    
    if(objB->IsPlayer() && !objA->IsPlayer())       // PvE
    {
        if(objA->m_factionDBC->RepListId >= 0)
            hostile = ((Player*)objB)->IsHostileBasedOnReputation(objA->m_factionDBC);
    }

    return hostile;
}

inline bool isAttackable(Object* objA, Object* objB)// A can attack B?
{
    if(!objA || !objB || objB->m_factionDBC == NULL || objA->m_factionDBC == NULL)
        return false;

    if(objB->m_faction == NULL || objA->m_faction == NULL )
        return true;

    if(objA == objB)
        return false;   // can't attack self.. this causes problems with buffs if we dont have it :p

    if(objA->GetTypeId() == TYPEID_CORPSE)
        return false;

    if(objB->GetTypeId() == TYPEID_CORPSE)
        return false;
    
    // Players in fiegn death flags can't be attacked
    if(objA->IsPlayer())
        if(objA->HasFlag(UNIT_FIELD_FLAGS_2, 0x00000001))
            return false;
    if(objB->IsPlayer())
        if(objB->HasFlag(UNIT_FIELD_FLAGS_2, 0x00000001))
            return false;

    // Checks for untouchable, unattackable
    if(objA->IsUnit())
    {
        if(objA->HasFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_UNIT_UNTACKABLE_SELECT))
            return false;
        if(objA->HasFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_UNIT_UNTACKABLE_SELECT_2))
            return false;
        if(objA->HasFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_UNIT_UNTACKABLE_NO_SELECT))
            return false;
        if(objA->HasFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_MAKE_CHAR_UNTOUCHABLE))
            return false;
    }
    if(objB->IsUnit())
    {
        if(objB->HasFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_UNIT_UNTACKABLE_SELECT))
            return false;
        if(objB->HasFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_UNIT_UNTACKABLE_SELECT_2))
            return false;
        if(objB->HasFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_UNIT_UNTACKABLE_NO_SELECT))
            return false;
        if(objB->HasFlag(UNIT_FIELD_FLAGS, U_FIELD_FLAG_MAKE_CHAR_UNTOUCHABLE))
            return false;
    }

    if(objA->IsPlayer() && objB->IsPlayer())
    {
        if(
            static_cast<Player *>(objA)->DuelingWith == static_cast<Player *>(objB) && 
            static_cast<Player *>(objA)->GetDuelState() == DUEL_STATE_STARTED
            )
        return true;                    

        if(objA->HasFlag(PLAYER_FLAGS,PLAYER_FLAG_FREE_FOR_ALL_PVP) && objB->HasFlag(PLAYER_FLAGS,PLAYER_FLAG_FREE_FOR_ALL_PVP))
            return true;        // can hurt each other in FFA pvp
    }
    
    // handle for pets in duel
    if(objA->IsPet())
    {
        if(objB->IsPlayer())
            if(
                static_cast<Pet *>(objA)->GetPetOwner() &&
                static_cast<Pet *>(objA)->GetPetOwner()->DuelingWith == static_cast<Player *>(objB) && 
                static_cast<Pet *>(objA)->GetPetOwner()->GetDuelState() == DUEL_STATE_STARTED
                )
                return true;
        if(objB->IsPet())
            if(static_cast<Pet *>(objA)->GetPetOwner() &&
                static_cast<Pet *>(objB)->GetPetOwner() &&
                static_cast<Pet *>(objA)->GetPetOwner()->DuelingWith == static_cast<Pet *>(objB)->GetPetOwner() && 
                static_cast<Pet *>(objA)->GetPetOwner()->GetDuelState() == DUEL_STATE_STARTED
                )
                return true;
    }
    if(objB->IsPet())
    {
        if(objA->IsPlayer())
            if(
                static_cast<Pet*>(objB)->GetPetOwner() && static_cast<Pet *>(objB)->GetPetOwner() &&
                static_cast<Pet *>(objB)->GetPetOwner()->DuelingWith == static_cast<Player *>(objA) && 
                static_cast<Pet *>(objB)->GetPetOwner()->GetDuelState() == DUEL_STATE_STARTED
                )
                return true;
        else if(objA->IsPet())
            if(static_cast<Pet*>(objA)->GetPetOwner() && static_cast<Pet *>(objB)->GetPetOwner() &&
                static_cast<Pet*>(objB)->GetPetOwner() &&
                static_cast<Pet *>(objB)->GetPetOwner()->DuelingWith == static_cast<Pet *>(objA)->GetPetOwner() && 
                static_cast<Pet *>(objB)->GetPetOwner()->GetDuelState() == DUEL_STATE_STARTED
                )
                return true;
    }

    // handle for totems
    if(objA->IsUnit() && !objA->IsPlayer()) // must be creature
    {
        if(static_cast<Creature *>(objA)->IsTotem())
        {
            if(objB->IsPlayer())
                if( static_cast<Creature *>(objA)->GetTotemOwner() &&
                    static_cast<Creature *>(objA)->GetTotemOwner()->DuelingWith == static_cast<Player *>(objB) && 
                    static_cast<Creature *>(objA)->GetTotemOwner()->GetDuelState() == DUEL_STATE_STARTED
                    )
                    return true;
            if(objB->IsPet())
                if( static_cast<Creature *>(objA)->GetTotemOwner() &&
                    static_cast<Creature *>(objA)->GetTotemOwner()->DuelingWith == static_cast<Pet *>(objB)->GetPetOwner() && 
                    static_cast<Creature *>(objA)->GetTotemOwner()->GetDuelState() == DUEL_STATE_STARTED
                    )
                    return true;
        }
    }
    if(objB->IsUnit() && !objB->IsPlayer()) // must be creature
    {
        if(static_cast<Creature *>(objB)->IsTotem())
        {
            if(objA->IsPlayer())
                if( static_cast<Creature *>(objB)->GetTotemOwner() &&
                    static_cast<Creature *>(objB)->GetTotemOwner()->DuelingWith == static_cast<Player *>(objA) && 
                    static_cast<Creature *>(objB)->GetTotemOwner()->GetDuelState() == DUEL_STATE_STARTED
                    )
                    return true;
            if(objA->IsPet())
                if( static_cast<Creature *>(objB)->GetTotemOwner() &&
                    static_cast<Creature *>(objB)->GetTotemOwner()->DuelingWith == static_cast<Pet *>(objA)->GetPetOwner() && 
                    static_cast<Creature *>(objB)->GetTotemOwner()->GetDuelState() == DUEL_STATE_STARTED
                    )
                    return true;
        }
    }

    // do not let people attack each other in sancuary
    // Dueling is already catered for
    AreaTable *atA;
    AreaTable *atB;
    if(objA->IsPet() && ((Pet*)objA)->GetPetOwner())
        atA = sAreaStore.LookupEntry(static_cast<Pet *>(objA)->GetPetOwner()->GetAreaID());
    else if (objA->IsPlayer())
        atA = sAreaStore.LookupEntry(static_cast<Player *>(objA)->GetAreaID());
    else
        atA = NULL;

    if(objB->IsPet() && ((Pet*)objB)->GetPetOwner())
        atB = sAreaStore.LookupEntry(static_cast<Pet *>(objB)->GetPetOwner()->GetAreaID());
    else if (objB->IsPlayer())
        atB = sAreaStore.LookupEntry(static_cast<Player *>(objB)->GetAreaID());
    else
        atB = NULL;

    // We have the area codes
    // We know they arent dueling
    if (atA && atB)
    {
        if(atA->AreaFlags & 0x800 || atB->AreaFlags & 0x800)
            return false;
    }

    if(objA->m_faction == objB->m_faction)  // same faction can't kill each other unless in ffa pvp/duel
        return false;

    bool attackable = isHostile(objA, objB); // B is attackable if its hostile for A
    /*if((objA->m_faction->HostileMask & 8) && (objB->m_factionDBC->RepListId != 0) && 
        (objB->GetTypeId() != TYPEID_PLAYER) && objB->m_faction->Faction != 31) // B is attackable if its a neutral Creature*/

    // Neutral Creature Check
    if(objA->IsPlayer() || objA->IsPet())
    {
        if(objB->m_factionDBC->RepListId == -1 && objB->m_faction->HostileMask == 0 && objB->m_faction->FriendlyMask == 0)
        {
            attackable = true;
        }
    }
    else if(objB->IsPlayer() || objB->IsPet())
    {
        if(objA->m_factionDBC->RepListId == -1 && objA->m_faction->HostileMask == 0 && objA->m_faction->FriendlyMask == 0)
        {
            attackable = true;
        }
    }

    return attackable;
}



inline bool isFriendly(Object* objA, Object* objB)// B is friendly to A if its not hostile
{
    return !isHostile(objA, objB);
}

inline bool isCombatSupport(Object* objA, Object* objB)// B combat supports A?
{
    if(!objA || !objB)
        return false;

    if(objA->GetTypeId() == TYPEID_CORPSE)
        return false;

    if(objB->GetTypeId() == TYPEID_CORPSE)
        return false;

    if(objB->m_faction == 0 || objA->m_faction == 0)
        return false;

    bool combatSupport = false;

    uint32 fSupport = objB->m_faction->FriendlyMask;
    uint32 myFaction = objA->m_faction->Mask;

    if(myFaction & fSupport)
    {
        combatSupport = true;
    }
    // check friend/enemy list
    for(uint32 i = 0; i < 4; i++)
    {
        if(objB->m_faction->EnemyFactions[i] == objA->m_faction->Faction)
        {
            combatSupport = false;
            break;
        }
        if(objB->m_faction->FriendlyFactions[i] == objA->m_faction->Faction)
        {
            combatSupport = true;
            break;
        }
    }
    return combatSupport;
}
#endif
