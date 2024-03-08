#include "ToSMapMgr.h"

std::string ToSMapManager::GetHexColorFromClass(uint8 classId)
{
    switch (classId)
    {
    case CLASS_DEATH_KNIGHT:
        return "|cffFC2A43";
    case CLASS_HUNTER:
        return "|cffAAD174";
    case CLASS_PALADIN:
        return "|cffF28CBC";
    case CLASS_ROGUE:
        return "|cffFEF262";
    case CLASS_WARLOCK:
        return "|cff9A81C2";
    case CLASS_DRUID:
        return "|cffF67404";
    case CLASS_MAGE:
        return "|cff70C9F1";
    case CLASS_PRIEST:
        return "|cffF5F3F6";
    case CLASS_SHAMAN:
        return "|cff05D7BA";
    case CLASS_WARRIOR:
        return "|cffC9A074";
    }

    return "|cffFFFFFF";
}

std::string ToSMapManager::GetDifficultyString(uint32 difficulty)
{
    std::stringstream ss;

    ss << ((difficulty >= 0) ? TOS_ICON_CROWN : TOS_ICON_CROWN_BW);
    ss << ((difficulty >= 20) ? TOS_ICON_CROWN : TOS_ICON_CROWN_BW);
    ss << ((difficulty >= 40) ? TOS_ICON_CROWN : TOS_ICON_CROWN_BW);
    ss << ((difficulty >= 60) ? TOS_ICON_CROWN : TOS_ICON_CROWN_BW);
    ss << ((difficulty >= 80) ? TOS_ICON_CROWN : TOS_ICON_CROWN_BW);

    return ss.str();
}

std::vector<ToSCurseTemplate> ToSMapManager::GetCurses()
{
    std::vector<ToSCurseTemplate> curses;

    for (auto curse : CurseTemplates)
    {
        curses.push_back(curse.second);
    }

    return curses;
}

void ToSMapManager::ClearCurses(Unit* unit)
{
    if (!unit)
    {
        return;
    }

    for (auto const& curse : sToSMapMgr->GetCurses())
    {
        if (unit->HasAura(curse.aura))
        {
            unit->RemoveAura(curse.aura);
        }
    }
}

ToSCurseTemplate* ToSMapManager::GetCurseById(uint32 curseId)
{
    auto it = CurseTemplates.find(curseId);
    if (it == CurseTemplates.end())
    {
        return nullptr;
    }

    return &it->second;
}

ToSWaveTemplate* ToSMapManager::GetWaveTemplateForWave(uint32 wave)
{
    auto it = WaveTemplates.find(wave);
    if (it == WaveTemplates.end())
    {
        return nullptr;
    }

    return &it->second;
}

uint32 ToSMapManager::GetTotalWaves()
{
    return WaveTemplates.size();
}

std::vector<ToSEnemyGroup*> ToSMapManager::GetEnemiesFromGroup(uint32 groupId, uint32 subGroup)
{
    std::vector<ToSEnemyGroup*> groups;

    for (auto it = EnemyGroups.begin(); it != EnemyGroups.end(); ++it)
    {
        if (it->second.group == groupId &&
            it->second.subGroup == subGroup)
        {
            groups.push_back(&it->second);
        }
    }

    return groups;
}

uint32 ToSMapManager::GetEnemyCountForGroup(uint32 groupId)
{
    uint32 count = 0;

    for (auto it = EnemyGroups.begin(); it != EnemyGroups.end(); ++it)
    {
        if (it->second.group == groupId)
        {
            count++;
        }
    }

    return count;
}

std::vector<uint32> ToSMapManager::GetSubGroups(uint32 groupId)
{
    std::vector<uint32> subgroups;

    for (auto it = EnemyGroups.begin(); it != EnemyGroups.end(); ++it)
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

std::vector<ToSRewardTemplate>* ToSMapManager::GetRewardTemplates(uint32 rewardId)
{
    auto it = RewardTemplates.find(rewardId);
    if (it == RewardTemplates.end())
    {
        return nullptr;
    }

    return &it->second;
}

Creature* ToSMapManager::SpawnNPC(uint32 entry, Map* map, Position* position)
{
    if (!map || !position)
    {
        return nullptr;
    }

    if (!sObjectMgr->GetCreatureTemplate(entry))
    {
        return nullptr;
    }

    return map->SummonCreature(entry, *position);
}

double ToSMapManager::LinearDistribution(double min, double max, double count, double index)
{
    double total = abs(min) + abs(max);

    double amount = total / count;

    return (min + (amount * index) + (amount / 2.0));
}

void ToSMapManager::ResetCooldowns(Player* player)
{
    if (!player)
    {
        return;
    }

    player->RemoveAllSpellCooldown();
}

bool ToSMapManager::CanPlayerEnter(Player* player)
{
    if (!player)
    {
        return false;
    }

    if (player->GetLevel() < 80)
    {
        return false;
    }

    return true;
}
