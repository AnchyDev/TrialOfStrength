#include "TrialOfStrength.h"

#include "ToSHelpers.h"

#include "scripts/ToSEnemyCombatantScript.h"
#include "scripts/ToSEnemyCombatantBossScript.h"

#include "scripts/ToSArenaMasterScript.h"
#include "scripts/ToSInstanceScript.h"

void LoadWaveTemplates()
{
    auto qResult = WorldDatabase.Query("SELECT * FROM tos_wave_template");

    if (!qResult)
    {
        return;
    }

    LOG_INFO("module", "Loading trial of strength wave templates from 'tos_wave_template'..");

    int count = 0;

    do
    {
        auto fields = qResult->Fetch();

        ToSWaveTemplate waveTemplate;
        waveTemplate.wave = fields[0].Get<uint32>();
        waveTemplate.enemyGroup = fields[1].Get<uint32>();
        waveTemplate.hasReward = fields[2].Get<bool>();
        waveTemplate.rewardTemplate = fields[3].Get<uint32>();

        waveTemplates.emplace(waveTemplate.wave, waveTemplate);

        count++;
    } while (qResult->NextRow());

    LOG_INFO("module", "Loaded '{}' trial of strength wave templates.", count);
}

void LoadEnemyGroups()
{
    auto qResult = WorldDatabase.Query("SELECT * FROM tos_wave_groups");

    if (!qResult)
    {
        return;
    }

    LOG_INFO("module", "Loading trial of strength wave groups from 'tos_wave_groups'..");

    int count = 0;

    do
    {
        auto fields = qResult->Fetch();

        ToSEnemyGroup enemyGroup;

        enemyGroup.id = fields[0].Get<uint32>();
        enemyGroup.group = fields[1].Get<uint32>();
        enemyGroup.subGroup = fields[2].Get<uint32>();
        enemyGroup.creatureEntry = fields[3].Get<uint32>();

        enemyGroups.emplace(enemyGroup.id, enemyGroup);

        count++;
    } while (qResult->NextRow());

    LOG_INFO("module", "Loaded '{}' trial of strength wave groups.", count);
}

void LoadRewardTemplates()
{
    auto qResult = WorldDatabase.Query("SELECT * FROM tos_reward_template");

    if (!qResult)
    {
        return;
    }

    LOG_INFO("module", "Loading trial of strength reward templates from 'tos_reward_template'..");

    int count = 0;

    do
    {
        auto fields = qResult->Fetch();

        ToSRewardTemplate rewardTemplate;

        auto rewardId = fields[0].Get<uint32>();
        rewardTemplate.itemEntry = fields[1].Get<uint32>();
        rewardTemplate.countMin = fields[2].Get<uint32>();
        rewardTemplate.countMax = fields[3].Get<uint32>();
        rewardTemplate.chance = fields[4].Get<uint32>();

        rewardTemplates.emplace(rewardId, rewardTemplate);

        count++;
    } while (qResult->NextRow());

    LOG_INFO("module", "Loaded '{}' trial of strength reward templates.", count);
}

void LoadCurseTemplates()
{
    auto qResult = WorldDatabase.Query("SELECT * FROM tos_curse_template");

    if (!qResult)
    {
        return;
    }

    LOG_INFO("module", "Loading trial of strength curse templates from 'tos_curse_template'..");

    int count = 0;

    do
    {
        auto fields = qResult->Fetch();

        ToSCurseTemplate curseTemplate;

        auto curseId = fields[0].Get<uint32>();
        curseTemplate.type = fields[1].Get<uint32>();
        curseTemplate.difficulty = fields[2].Get<uint32>();
        curseTemplate.aura = fields[3].Get<uint32>();
        curseTemplate.name = fields[4].Get<std::string>();
        curseTemplate.description = fields[5].Get<std::string>();

        curseTemplates.emplace(curseId, curseTemplate);

        count++;
    } while (qResult->NextRow());

    LOG_INFO("module", "Loaded '{}' trial of strength curse templates.", count);
}

ToSCurseTemplate* GetCurseById(uint32 curseId)
{
    auto it = curseTemplates.find(curseId);
    if (it == curseTemplates.end())
    {
        return nullptr;
    }

    return &it->second;
}

ToSWaveTemplate* GetWaveTemplateForWave(uint32 wave)
{
    auto it = waveTemplates.find(wave);
    if (it == waveTemplates.end())
    {
        return nullptr;
    }

    return &it->second;
}

uint32 GetTotalWaves()
{
    return waveTemplates.size();
}

std::vector<ToSEnemyGroup*> GetEnemiesFromGroup(uint32 groupId, uint32 subGroup)
{
    std::vector<ToSEnemyGroup*> groups;

    for (auto it = enemyGroups.begin(); it != enemyGroups.end(); ++it)
    {
        if (it->second.group == groupId &&
            it->second.subGroup == subGroup)
        {
            groups.push_back(&it->second);
        }
    }

    return groups;
}

std::vector<uint32> GetSubGroups(uint32 groupId)
{
    std::vector<uint32> subgroups;

    for (auto it = enemyGroups.begin(); it != enemyGroups.end(); ++it)
    {
        if (it->second.group == groupId)
        {
            uint32 subgroup = it->second.subGroup;

            auto it = std::find(subgroups.begin(), subgroups.end(), subgroup);
            if (it != subgroups.end())
            {
                continue;
            }

            subgroups.push_back(subgroup);
        }
    }

    return subgroups;
}

ToSRewardTemplate* GetRewardTemplate(uint32 rewardId)
{
    auto it = rewardTemplates.find(rewardId);
    if (it == rewardTemplates.end())
    {
        return nullptr;
    }

    return &it->second;
}

void ToSWorldScript::OnAfterConfigLoad(bool reload)
{
    if (reload)
    {
        waveTemplates.clear();
        enemyGroups.clear();
        rewardTemplates.clear();
        curseTemplates.clear();
    }

    LoadWaveTemplates();
    LoadEnemyGroups();
    LoadRewardTemplates();
    LoadCurseTemplates();
}

void SC_AddTrialOfStrengthScripts()
{
    new ToSWorldScript();
    new ToSArenaMasterScript();

    new ToSEnemyCombatantScript();
    new ToSEnemyCombatantBossScript();

    new instance_trial_of_strength();
}
