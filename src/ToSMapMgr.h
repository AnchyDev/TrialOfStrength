#ifndef MODULE_TRIAL_OF_STRENGTH_MAP_MGR_H
#define MODULE_TRIAL_OF_STRENGTH_MAP_MGR_H

#include "TrialOfStrength.h"

#include <unordered_map>

class ToSMapManager
{
private:
    ToSMapManager() { }
public:
    static ToSMapManager* GetInstance()
    {
        if (!instance)
        {
            instance = new ToSMapManager();
        }

        return instance;
    }

    std::string GetHexColorFromClass(uint8 classId);
    ToSCurseTemplate* GetCurseById(uint32 curseId);
    ToSWaveTemplate* GetWaveTemplateForWave(uint32 wave);
    uint32 GetTotalWaves();
    std::vector<ToSEnemyGroup*> GetEnemiesFromGroup(uint32 groupId, uint32 subGroup);
    std::vector<ToSRewardTemplate>* GetRewardTemplates(uint32 rewardId);
    std::vector<uint32> GetSubGroups(uint32 groupId);
    Creature* SpawnNPC(uint32 entry, Map* map, Position* position);
    double LinearDistribution(double min, double max, double count, double index);
public:
    std::unordered_map<uint32, ToSWaveTemplate> WaveTemplates;
    std::unordered_map<uint32, ToSEnemyGroup> EnemyGroups;
    std::unordered_map<uint32, std::vector<ToSRewardTemplate>> RewardTemplates;
    std::unordered_map<uint32, ToSCurseTemplate> CurseTemplates;
private:
    inline static ToSMapManager* instance;
};

#define sToSMapMgr ToSMapManager::GetInstance()

#endif // MODULE_TRIAL_OF_STRENGTH_MAP_MGR_H
