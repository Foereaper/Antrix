/****************************************************************************
 *
 * Profession Defines
 *
 */

#ifndef _PROFFESIONS_H
#define _PROFFESIONS_H

uint32 GetGOReqSkill(GameObject * gameObjTarget);
void UseFishing(Player *player);
void AddItemFromDisenchant(ItemPrototype *proto,Player*owner);
void AddItemFromProspecting(ItemPrototype *proto,Player*owner);

#endif
