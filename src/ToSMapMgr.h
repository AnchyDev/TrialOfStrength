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
    std::string GetDifficultyString(uint32 difficulty);
    std::vector<ToSCurseTemplate> GetCurses();
    void ClearCurses(Unit* unit);
    ToSCurseTemplate* GetCurseById(uint32 curseId);
    ToSWaveTemplate* GetWaveTemplateForWave(uint32 wave);
    uint32 GetTotalWaves();
    std::vector<ToSEnemyGroup*> GetEnemiesFromGroup(uint32 groupId, uint32 subGroup);
    uint32 GetEnemyCountForGroup(uint32 groupId);
    std::vector<ToSRewardTemplate>* GetRewardTemplates(uint32 rewardId);
    std::vector<uint32> GetSubGroups(uint32 groupId);
    Creature* SpawnNPC(uint32 entry, Map* map, Position* position);
    double LinearDistribution(double min, double max, double count, double index);
    void ResetCooldowns(Player* player);
    bool CanPlayerEnter(Player* player);
public:
    std::unordered_map<uint32, ToSWaveTemplate> WaveTemplates;
    std::unordered_map<uint32, ToSEnemyGroup> EnemyGroups;
    std::unordered_map<uint32, std::vector<ToSRewardTemplate>> RewardTemplates;
    std::unordered_map<uint32, ToSCurseTemplate> CurseTemplates;

    const std::string TOS_ICON_CROWN = "|TInterface\\LFGFrame\\LFGROLE:16:16:::64:16:0:16:0:16|t";
    const std::string TOS_ICON_CROWN_BW = "|TInterface\\LFGFrame\\LFGROLE_BW:16:16:::64:16:0:16:0:16|t";
private:
    inline static ToSMapManager* instance;
};

#define sToSMapMgr ToSMapManager::GetInstance()

#endif // MODULE_TRIAL_OF_STRENGTH_MAP_MGR_H
