#include "TrialOfStrength.h"
#include "ToSMapMgr.h"

#include "scripts/AI/ToSAIArenaSpectator.h"

#include "scripts/ToSArenaMasterScript.h"

#include "scripts/ToSInstanceScript.h"
#include "scripts/ToSInstanceMapScript.h"

#include "scripts/ToSPlayerScript.h"
#include "scripts/ToSCurseCrystalScript.h"

#include "scripts/ToSUnitScript.h"

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

        sToSMapMgr->WaveTemplates.emplace(waveTemplate.wave, waveTemplate);

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

        sToSMapMgr->EnemyGroups.emplace(enemyGroup.id, enemyGroup);

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
        rewardTemplate.countCap = fields[4].Get<uint32>();
        rewardTemplate.chance = fields[5].Get<uint32>();
        rewardTemplate.curseScalar = fields[6].Get<float>();

        auto templates = sToSMapMgr->GetRewardTemplates(rewardId);
        if (!templates)
        {
            std::vector<ToSRewardTemplate> newTemplates;
            newTemplates.push_back(rewardTemplate);
            sToSMapMgr->RewardTemplates.emplace(rewardId, newTemplates);
        }
        else
        {
            templates->push_back(rewardTemplate);
        }

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
        curseTemplate.id = curseId;
        curseTemplate.type = fields[1].Get<uint32>();
        curseTemplate.difficulty = fields[2].Get<uint32>();
        curseTemplate.aura = fields[3].Get<uint32>();
        curseTemplate.name = fields[4].Get<std::string>();
        curseTemplate.description = fields[5].Get<std::string>();

        sToSMapMgr->CurseTemplates.emplace(curseId, curseTemplate);

        count++;
    } while (qResult->NextRow());

    LOG_INFO("module", "Loaded '{}' trial of strength curse templates.", count);
}

void ToSWorldScript::OnAfterConfigLoad(bool reload)
{
    if (reload)
    {
        sToSMapMgr->WaveTemplates.clear();
        sToSMapMgr->EnemyGroups.clear();
        sToSMapMgr->RewardTemplates.clear();
        sToSMapMgr->CurseTemplates.clear();
    }

    if (!sConfigMgr->GetOption<bool>("TrialOfStrength.Enable", false))
    {
        return;
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
    new ToSAIArenaSpectator();

    new ToSInstanceMapScript();

    new ToSPlayerScript();
    new ToSCurseCrystalScript();

    new ToSUnitScript();
}
