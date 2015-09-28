#include "StdAfx.h"
#include "Setup.h"

bool Preparation(uint32 i, Spell * pSpell)
{
    Player * playerTarget = pSpell->p_caster;
    if(playerTarget == 0) return true;

    playerTarget->ClearCooldownsOnLine(39, pSpell->m_spellInfo->Id); // line - subtlety
    playerTarget->ClearCooldownsOnLine(38, pSpell->m_spellInfo->Id); // line - combat
    playerTarget->ClearCooldownsOnLine(253, pSpell->m_spellInfo->Id);// line - assassination
    return true;
}

void SetupRogueSpells(ScriptMgr * mgr)
{
    mgr->register_dummy_spell(14185, &Preparation);
}
