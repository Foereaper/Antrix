#include "StdAfx.h"
#include "Setup.h"

bool ColdSnap(uint32 i, Spell * pSpell)
{
    if(!pSpell->p_caster) return true;
    pSpell->p_caster->ClearCooldownsOnLine(6, pSpell->m_spellInfo->Id);
    return true;
}

void SetupMageSpells(ScriptMgr * mgr)
{
    mgr->register_dummy_spell(12472, &ColdSnap);
}
