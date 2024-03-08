#ifndef MODULE_TRIAL_OF_STRENGTH_H
#define MODULE_TRIAL_OF_STRENGTH_H

#include "Player.h"
#include "ScriptMgr.h"
#include "CombatAI.h"
#include "Config.h"
#include "ScriptedGossip.h"

#include <vector>
#include <unordered_map>
#include <sstream>

enum ToSConstants {
    TOS_MAP_ID = 44,
    TOS_NPC_ARENA_MASTER = 441250,
    TOS_SPELL_TELEPORT_VISUAL = 64446,
    TOS_ENTRY_TICKET_ID = 25747,

    TOS_DATA_ENCOUNTER_START = 1,
    TOS_DATA_ENCOUNTER_CURRENT_WAVE = 2,
    TOS_DATA_ENCOUNTER_CURRENT_WAVE_CLEARED = 3,
    TOS_DATA_ENCOUNTER_HAS_MORE_WAVES = 4,
    TOS_DATA_ENCOUNTER_RESET = 5,
    TOS_DATA_ENCOUNTER_CURRENT_WAVE_REMAINING = 6,
    TOS_DATA_ENCOUNTER_COMBATANTS_HOSTILE = 7,
    TOS_DATA_ENCOUNTER_CHECK_WAVE_COMPLETE = 8,
    TOS_DATA_ENCOUNTER_START_NEXT_WAVE = 9,
    TOS_DATA_ENCOUNTER_CHECK_FAILURE = 10,
    TOS_DATA_ENCOUNTER_CURRENT_SUBWAVE = 11,
    TOS_DATA_ENCOUNTER_TOTAL_SUBWAVE = 12,
    TOS_DATA_ENCOUNTER_TRIAL_COMPLETED = 13,
    TOS_DATA_ENCOUNTER_CHECK_ARENA_MASTER_RELOCATE = 14,
    TOS_DATA_ENCOUNTER_WAVE_IN_PROGRESS = 15,
    TOS_DATA_ENCOUNTER_CROWD = 16,
    TOS_DATA_PORTAL_TRY_TELEPORT = 17,
    TOS_DATA_ENCOUNTER_UPDATE_INVADERS = 18,

    TOS_CURSE_TYPE_ENEMY = 0,
    TOS_CURSE_TYPE_PLAYER = 1,

    TOS_DATA_UINT32_BASE = 4411,
    TOS_DATA_UINT32_CURSE_ID = 0,
};

struct ToSWaveTemplate {
    uint32 wave;
    uint32 enemyGroup;
    bool hasReward;
    uint32 rewardTemplate;
};

struct ToSEnemyGroup {
    uint32 id;
    uint32 group;
    uint32 subGroup;
    uint32 creatureEntry;
};

struct ToSRewardTemplate {
    uint32 itemEntry;
    uint32 countMin;
    uint32 countMax;
    uint32 countCap;
    uint32 chance;
    float curseScalar;
};

struct ToSCurseTemplate {
    uint32 id;
    uint32 type;
    uint32 difficulty;
    uint32 aura;

    std::string name;
    std::string description;
};

class ToSWorldScript : public WorldScript
{
public:
    ToSWorldScript() : WorldScript("ToSWorldScript") { }

    void OnAfterConfigLoad(bool /*reload*/) override;
};

#endif // MODULE_TRIAL_OF_STRENGTH_H
