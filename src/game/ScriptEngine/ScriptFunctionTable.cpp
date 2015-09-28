/****************************************************************************
 *
 * Script Engine
 * Copyright (c) 2007 Antrix Team
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech ASA of Norway and appearing in the file
 * COPYING included in the packaging of this file.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * GameMonkey Script License
 * Copyright (c) 2003 Auran Development Ltd.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 */

#include "StdAfx.h"

void ScriptEngine::SetPlayerFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "BroadcastMessage",					Player_BroadcastMessage				},
		{ "SendAreaTriggerMessage",				Player_SendAreaTriggerMessage		},
		{ "GetLevel",							Player_GetLevel						},
		{ "GetClass",							Player_GetClass						},
		{ "GetRace",							Player_GetRace						},
		{ "Teleport",							Player_Teleport						},
		{ "GetStanding",						Player_GetReputationValue			},
		{ "GetStandingRank",					Player_GetReputationRank			},
		{ "HasFinishedQuest",					Player_HasFinishedQuest				},
		{ "LearnSpell",							Player_LearnSpell					},
		{ "UnlearnSpell",						Player_RemoveSpell					},
		{ "AddItem",							Player_AddItem						},
		{ "RemoveItem",							Player_RemoveItem					},
		{ "MarkQuestObjectiveAsComplete",		Player_MarkQuestObjectiveAsComplete	},
		{ "SendSystemMessage",					Player_SendSystemMessage			},
		{ "SendNotification",					Player_SendNotification				},
		{ "Knockback",							Player_Knockback					},
		{ "JoinInstance",						Player_JoinInstance					},

		// Imported Unit Functions
		{ "Emote",								Unit_Emote							},
		{ "SendChatMessage",					Unit_SendChatMessage				},
		{ "Despawn",							Unit_Despawn						},
		{ "CastSpell",							Unit_CastSpell						},
		{ "CastSpellOnTarget",					Unit_CastSpellOnTarget				},
		{ "SpawnMonster",						Unit_SpawnMonster					},
		{ "RegisterEvent",						GM_RegisterEvent					},
		{ "SpawnWithoutWorld",					Unit_SpawnWithoutWorld				},
		{ "StopMovement",						Unit_HaltMovement					},

		{ "GetUnit",							Unit_GetUnit						},
		{ "GetGameObject",						Unit_GetGameObject					},
		{ "GetPlayer",							Unit_GetPlayer						},
		{ "GetGuid",							Unit_GetGuid						},
		{ "PlaySoundToSet",						Unit_PlaySoundToSet					},
	};

	m_machine->RegisterTypeLibrary(m_playerType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetUnitFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "Emote",								Unit_Emote							},
		{ "SendChatMessageAltEntry",			Unit_SendChatMessageAltEntry		},
		{ "SendChatMessage",					Unit_SendChatMessage				},
		{ "Despawn",							Unit_Despawn						},
		{ "CastSpell",							Unit_CastSpell						},
		{ "CastSpellOnTarget",					Unit_CastSpellOnTarget				},
		{ "TimedEmote",							Unit_TimedEmote						},
		{ "RegisterTimer",						Unit_RegisterTimer					},
		{ "DeregisterTimer",					Unit_DeregisterTimer				},
		{ "SpawnMonster",						Unit_SpawnMonster					},
		{ "SetStandState",						Unit_SetStandState					},
		{ "RegisterEvent",						GM_RegisterEvent					},
		{ "SpawnWithoutWorld",					Unit_SpawnWithoutWorld				},
		{ "AddToWorld",							Unit_AddToWorld						},
		{ "CreateCustomWaypointMap",			Unit_CreateCustomWaypointMap		},
		{ "CreateWaypoint",						Unit_CreateWaypoint					},
		{ "MoveToWaypoint",						Unit_MoveToWaypoint					},
		{ "Delete",								Unit_Delete							},
		{ "SetCombatCapable",					Unit_SetCombatCapable				},
		{ "StopMovement",						Unit_HaltMovement					},
		{ "SetMovementType",					Unit_SetMovementType				},
		{ "SetEscortTarget",					Unit_SetEscortTarget				},
		{ "GetEscortTarget",					Unit_GetEscortTarget				},
		{ "HasEscortTarget",					Unit_HasEscortTarget				},
		{ "SetNPCFlags",						Unit_SetNPCFlags					},
		{ "DestroyCustomWaypointMap",			Unit_DestroyCustomWaypointMap		},
		{ "ClearEscortTarget",					Unit_ClearEscortTarget				},
		{ "GetUnit",							Unit_GetUnit						},
		{ "GetGameObject",						Unit_GetGameObject					},
		{ "GetPlayer",							Unit_GetPlayer						},
		{ "GetGuid",							Unit_GetGuid						},
		{ "ChangeEntry",						Unit_ChangeEntry					},
		{ "ChangeModel",						Unit_ChangeModel					},
		{ "ChangeScale",						Unit_ChangeScale					},
		{ "ChangeFaction",						Unit_ChangeFaction					},
		{ "TextEmote",							Unit_TextEmote						},
		{ "PlaySoundToSet",						Unit_PlaySoundToSet					},
	};

	m_machine->RegisterTypeLibrary(m_unitType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetQuestFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "GetID",								Quest_GetID						},
	};

	m_machine->RegisterTypeLibrary(m_questType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetGameObjectFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "Despawn",							GameObject_Despawn					},
		{ "SetActive",							GameObject_SetActive				},
		{ "PlayCustomAnim",						GameObject_PlayCustomAnim			},
		{ "GetUnit",							Unit_GetUnit						},
		{ "GetGameObject",						Unit_GetGameObject					},
		{ "GetPlayer",							Unit_GetPlayer						},
		{ "GetGuid",							Unit_GetGuid						},
		{ "RegisterEvent",						GM_RegisterEvent					},
		{ "PlaySoundToSet",						Unit_PlaySoundToSet					},
	};

	m_machine->RegisterTypeLibrary(m_gameObjectType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetSpellFunctionTable()
{
	/*static gmFunctionEntry table[] = {
		{ "test", 0 },
	};*/

	//m_machine->RegisterTypeLibrary(m_playerType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetAuraFunctionTable()
{
	/*static gmFunctionEntry table[] = {
		{ "test", 0 },
	};*/

	//m_machine->RegisterTypeLibrary(m_playerType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetAreaTriggerFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "GetEntry",							AreaTrigger_GetEntry			},
	};

	m_machine->RegisterTypeLibrary(m_areaTriggerType, table, sizeof(table) / sizeof(table[0]));
}

void ScriptEngine::SetScriptEngineFunctionTable()
{
	static gmFunctionEntry table[] = {
		{ "RegisterUnitEvent",					ScriptEngine_RegisterUnitEvent	},
		{ "RegisterGameObjectEvent",			ScriptEngine_RegisterGameObjectEvent },
		{ "RegisterPlayerEvent",				ScriptEngine_RegisterPlayerEvent },
		{ "RegisterAreaTriggerEvent",			ScriptEngine_RegisterAreaTriggerEvent },
		{ "RegisterQuestEvent",					ScriptEngine_RegisterQuestEvent	},
	};

	m_machine->RegisterTypeLibrary(m_scriptEngineType, table, sizeof(table) / sizeof(table[0]));

	// Register Normal Functions
	m_machine->RegisterLibraryFunction("Rand", GM_RAND, 0, 0);
	m_machine->RegisterLibraryFunction("GetUnitBySqlId", GM_GetUnitBySqlId, 0, 0);
}



