#include "ToSInstanceScript.h"

#include <random>

void ToSInstanceScript::AddCurse(uint32 curseId)
{
    auto it = sToSMapMgr->CurseTemplates.find(curseId);
    if (it == sToSMapMgr->CurseTemplates.end())
    {
        LOG_WARN("module", "Tried to add curse {} to creature curses but it does not exist.", curseId);
        return;
    }

    auto curse = sToSMapMgr->GetCurseById(curseId);
    if (!curse)
    {
        return;
    }

    curses.push_back(curse);
}

void ToSInstanceScript::OnCreatureCreate(Creature* creature)
{
    if (creature &&
        creature->GetEntry() == TOS_NPC_ARENA_MASTER)
    {
        arenaMaster = creature;
    }
}

bool ToSInstanceScript::IsSubWaveCleared() const
{
    return waveInProgress && GetRemainingAlive() == 0;
}

bool ToSInstanceScript::IsWaveCleared() const
{
    return waveCleared;
}

bool ToSInstanceScript::HasMoreWaves() const
{
    return currentWave < totalWaves ? true : false;
}

bool ToSInstanceScript::IsWaveInProgress() const
{
    return waveInProgress;
}

void ToSInstanceScript::SpawnNextWave(ToSWaveTemplate* waveTemplate = nullptr)
{
    if (!waveTemplate)
    {
        waveTemplate = sToSMapMgr->GetWaveTemplateForWave(currentWave);
    }

    if (!waveTemplate)
    {
        LOG_WARN("module", "Wave template is nullptr.");
        return;
    }

    auto enemies = sToSMapMgr->GetEnemiesFromGroup(waveTemplate->enemyGroup, currentSubGroup);
    if (enemies.empty())
    {
        LOG_WARN("module", "No enemies found in wave template.");
        return;
    }

    waveCleared = false;
    CleanupCreatures();
    ApplyCursesToPlayers();

    uint32 i = 0;

    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        auto enemy = (*it);

        auto diff = sToSMapMgr->LinearDistribution(-4, 4, enemies.size(), i);

        Position tempPos(combatantPosStart->GetPositionX(), combatantPosStart->GetPositionY() + diff, combatantPosStart->GetPositionZ(), combatantPosStart->GetOrientation());

        auto summon = sToSMapMgr->SpawnNPC(enemy->creatureEntry, instance, &tempPos);

        ApplyCurses(summon);

        waveCreatures.push_back(summon);

        if (currentSubGroup == 1)
            summon->SetFaction(FACTION_FRIENDLY);

        summon->CastSpell(summon, TOS_SPELL_TELEPORT_VISUAL);
        MakeEntrance(summon);

        i++;
    }

    events.ScheduleEvent(TOS_DATA_ENCOUNTER_COMBATANTS_HOSTILE, 5s);
    events.ScheduleEvent(TOS_DATA_ENCOUNTER_CHECK_WAVE_COMPLETE, 10s);
    events.ScheduleEvent(TOS_DATA_ENCOUNTER_CHECK_FAILURE, 5s);
}

void ToSInstanceScript::MakeEntrance(Creature* creature)
{
    creature->GetMotionMaster()->MovePoint(0, *combatantPosEnd);
    creature->SetHomePosition(*combatantPosEnd);
}

void ToSInstanceScript::ApplyCurses(Unit* unit)
{
    if (!unit ||
        curses.empty())
    {
        return;
    }

    for (auto const& curse : curses)
    {
        if (unit->ToPlayer() &&
            curse->type == TOS_CURSE_TYPE_PLAYER &&
            !unit->HasAura(curse->aura))
        {
            unit->AddAura(curse->aura, unit);
            continue;
        }

        if (!unit->ToPlayer() &&
            curse->type == TOS_CURSE_TYPE_ENEMY &&
            !unit->HasAura(curse->aura))
        {
            unit->AddAura(curse->aura, unit);
            continue;
        }
    }
}

void ToSInstanceScript::ApplyCursesToPlayers()
{
    Map::PlayerList const& players = instance->GetPlayers();

    for (const auto& it : players)
    {
        Player* player = it.GetSource();

        if (!player)
            continue;

        ApplyCurses(player);
    }
}

void ToSInstanceScript::ClearCursesFromPlayers()
{
    Map::PlayerList const& players = instance->GetPlayers();

    for (const auto& it : players)
    {
        Player* player = it.GetSource();

        if (!player)
        {
            continue;
        }

        sToSMapMgr->ClearCurses(player);
    }
}

void ToSInstanceScript::SpawnCurseCrystals()
{
    auto randomCurses = GetRandomAvailableCurses(3);

    // Crystal 1
    if(auto curse1 = randomCurses.at(0))
    {
        Position* tempPos = new Position(255.072, -95.140, 18.679, 0);
        if (curseCrystal1 = instance->SummonGameObject(TOS_GOB_CURSE, *tempPos, 0.0, 0.0, 0.0, 0.0, 0, true))
        {
            curseId1 = curse1;
        }
    }

    // Crystal 2
    if (auto curse2 = randomCurses.at(1))
    {
        Position* tempPos = new Position(259.940, -100.025, 18.679, 0);
        if (curseCrystal2 = instance->SummonGameObject(TOS_GOB_CURSE, *tempPos, 0.0, 0.0, 0.0, 0.0, 0, true))
        {
            curseId2 = curse2;
        }
    }

    // Crystal 3
    if (auto curse3 = randomCurses.at(2))
    {
        Position* tempPos = new Position(255.067, -104.689, 18.679, 0);
        if (curseCrystal3 = instance->SummonGameObject(TOS_GOB_CURSE, *tempPos, 0.0, 0.0, 0.0, 0.0, 0, true))
        {
            curseId3 = curse3;
        }
    }
}

void ToSInstanceScript::DespawnCurseCrystals()
{
    if (curseCrystal1)
    {
        curseCrystal1->DespawnOrUnsummon(1s);
        curseCrystal1 = nullptr;
    }

    if (curseCrystal2)
    {
        curseCrystal2->DespawnOrUnsummon(1s);
        curseCrystal2 = nullptr;
    }

    if (curseCrystal3)
    {
        curseCrystal3->DespawnOrUnsummon(1s);
        curseCrystal3 = nullptr;
    }
}

uint32 ToSInstanceScript::GetCurseForGUID(ObjectGuid guid)
{
    if (curseCrystal1 &&
        guid == curseCrystal1->GetGUID())
    {
        return curseId1;
    }

    if (curseCrystal2 &&
        guid == curseCrystal2->GetGUID())
    {
        return curseId2;
    }

    if (curseCrystal3 &&
        guid == curseCrystal3->GetGUID())
    {
        return curseId3;
    }

    return 0;
}

void ToSInstanceScript::ReloadCurses()
{
    availableCurseIds.clear();

    for (auto const& curseTemplate : sToSMapMgr->CurseTemplates)
    {
        const ToSCurseTemplate* curse = &curseTemplate.second;
        availableCurseIds.push_back(curse->id);
    }
}

uint32 ToSInstanceScript::GetRandomAvailableCurse()
{
    if (availableCurseIds.size() < 1)
    {
        return 0;
    }

    auto index = urand(0, availableCurseIds.size() - 1);
    auto curseId = availableCurseIds.at(index);

    if (!curseId)
    {
        return 0;
    }

    return curseId;
}

std::vector<uint32> ToSInstanceScript::GetRandomAvailableCurses(uint32 count)
{
    std::vector<uint32> randomCurses;

    if (availableCurseIds.size() < 1)
    {
        return randomCurses;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(availableCurseIds.begin(), availableCurseIds.end(), g);

    for (uint32 i = 0; i < count; i++)
    {
        if (availableCurseIds.size() < count)
        {
            break;
        }

        randomCurses.push_back(availableCurseIds.at(i));
    }

    return randomCurses;
}

void ToSInstanceScript::RemoveAvailableCurse(uint32 curseId)
{
    uint32 i = 0;
    for (const auto& curse : availableCurseIds)
    {
        if (curse == curseId)
        {
            availableCurseIds.erase(availableCurseIds.begin() + i);
        }

        i++;
    }
}

void ToSInstanceScript::SetCombatantsHostile()
{
    for (auto it = waveCreatures.begin(); it != waveCreatures.end(); ++it)
    {
        auto creature = *it;

        creature->SetFaction(FACTION_MONSTER);
        creature->SetInCombatWithZone();

        if (auto player = creature->SelectNearestPlayer(100.0f))
        {
            if (creature->Attack(player, true))
                creature->GetMotionMaster()->MoveChase(player);
        }
    }
}

void ToSInstanceScript::Update(uint32 diff)
{
    events.Update(diff);

    switch (events.ExecuteEvent())
    {
    case TOS_DATA_ENCOUNTER_START:
        SetupEncounter();
        break;

    case TOS_DATA_ENCOUNTER_COMBATANTS_HOSTILE:
        SetCombatantsHostile();
        break;

    case TOS_DATA_ENCOUNTER_CHECK_WAVE_COMPLETE:
        CheckWaveCompletion();
        break;

    case TOS_DATA_ENCOUNTER_START_NEXT_WAVE:
        SpawnNextWave();
        break;

    case TOS_DATA_ENCOUNTER_CHECK_FAILURE:
        if (!CheckFailure())
        {
            events.RescheduleEvent(TOS_DATA_ENCOUNTER_CHECK_FAILURE, 3s);
        }
        break;
    case TOS_DATA_ENCOUNTER_CHECK_ARENA_MASTER_RELOCATE:
        CheckArenaMasterRelocate();
        events.RescheduleEvent(TOS_DATA_ENCOUNTER_CHECK_ARENA_MASTER_RELOCATE, 3s);
        break;

    case TOS_DATA_ENCOUNTER_CROWD:
        PlayCrowd();
        events.RescheduleEvent(TOS_DATA_ENCOUNTER_CROWD, 1s);
        break;
    }
}

void ToSInstanceScript::PlayCrowd()
{
    if (IsEncounterInProgress() && IsWaveCleared() && !cheerPlayed)
    {
        instance->PlayDirectSoundToMap(TOS_SOUND_CHEER);
        cheerPlayed = true;
    }
}

void ToSInstanceScript::CheckArenaMasterRelocate()
{
    if (!arenaMaster)
    {
        return;
    }

    if (!IsEncounterInProgress())
    {
        return;
    }

    if (IsWaveInProgress() && !arenaMasterLeft)
    {
        RelocateArenaMaster(false);
        arenaMasterLeft = true;
        return;
    }

    if (!IsWaveInProgress() && arenaMasterLeft)
    {
        RelocateArenaMaster(true);
        arenaMasterLeft = false;
        return;
    }
}

void ToSInstanceScript::RelocateArenaMaster(bool returning)
{
    if (!arenaMaster || !arenaMaster->IsInWorld())
    {
        return;
    }

    arenaMaster->CastSpell(arenaMaster, TOS_SPELL_TELEPORT_VISUAL);

    if (returning)
    {
        arenaMaster->NearTeleportTo(249.918, -100.063, 18.679, 0.030);
    }
    else
    {
        arenaMaster->NearTeleportTo(272.296, -100.024, 28.869, 3.169);
    }
}

bool ToSInstanceScript::AnyPlayerAlive()
{
    Map::PlayerList const& players = instance->GetPlayers();

    for (const auto& it : players)
    {
        Player* player = it.GetSource();

        if (!player)
            continue;

        if (!player->isDead())
        {
            return true;
        }
    }

    return false;
}

bool ToSInstanceScript::CheckFailure()
{
    // Check if all players are dead.
    if (AnyPlayerAlive())
    {
        return false;
    }

    NotifyFailure();
    ResetEncounter();

    return true;
}

void ToSInstanceScript::NotifyFailure()
{
    std::string message = Acore::StringFormatFmt("|cffFF9900Trial of Strength Failed!|r", currentWave);
    Map::PlayerList const& players = instance->GetPlayers();

    for (const auto& it : players)
    {
        Player* player = it.GetSource();

        if (!player)
            continue;

        player->SendSystemMessage(message);
        player->PlayDirectSound(TOS_SOUND_FAIL);

        {
            WorldPacket data(SMSG_NOTIFICATION, (message.size() + 1));
            data << message;

            player->SendDirectMessage(&data);
        }
    }
}

void ToSInstanceScript::SetupEncounter()
{
    encounterInProgress = true;
    waveInProgress = true;
    waveCleared = false;

    auto waveTemplate = sToSMapMgr->GetWaveTemplateForWave(currentWave);
    if (!waveTemplate)
    {
        LOG_WARN("module", "Wave template is nullptr.");
        return;
    }

    totalWaves = sToSMapMgr->GetTotalWaves();

    currentSubGroup = 1;
    auto subGroups = sToSMapMgr->GetSubGroups(waveTemplate->enemyGroup);
    totalSubGroups = subGroups.size();

    if (totalSubGroups < 1)
    {
        LOG_WARN("module", "There were no subgroups found for wave {}.", currentWave);
        return;
    }

    instance->PlayDirectSoundToMap(TOS_SOUND_HORN);

    CleanupCreatures();
    CleanupGameObjects();
    DespawnCurseCrystals();

    events.ScheduleEvent(TOS_DATA_ENCOUNTER_START_NEXT_WAVE, 5s);
    events.ScheduleEvent(TOS_DATA_ENCOUNTER_CROWD, 1s);
}

void ToSInstanceScript::CheckWaveCompletion()
{
    if (!IsSubWaveCleared())
    {
        events.RescheduleEvent(TOS_DATA_ENCOUNTER_CHECK_WAVE_COMPLETE, 2s);
        return;
    }

    LOG_INFO("module", "Sub group {} complete.", currentSubGroup);

    if (currentSubGroup < totalSubGroups)
    {
        LOG_INFO("module", "Spawning next subgroup..");
        currentSubGroup++;

        instance->PlayDirectSoundToMap(TOS_SOUND_HORN);
        events.ScheduleEvent(TOS_DATA_ENCOUNTER_START_NEXT_WAVE, 5s);
    }
    else
    {
        NotifyPlayers();
        PopulateRewardChest();

        waveInProgress = false;
        waveCleared = true;
        cheerPlayed = false;

        if (currentWave == totalWaves)
        {
            trialCompleted = true;
            AnnounceCompletion();
        }
        else
        {
            SpawnCurseCrystals();
        }
    }
}

void ToSInstanceScript::NotifyPlayers()
{
    Map::PlayerList const& players = instance->GetPlayers();

    for (const auto& it : players)
    {
        Player* player = it.GetSource();

        if (!player)
            continue;

        std::string message = Acore::StringFormatFmt("|cffFFFFFFWave |cff00FF00{}|r |cffFFFFFFcleared!|r", currentWave);

        player->SendSystemMessage(message);
        player->PlayDirectSound(17316 /* RDF Reward Sound */);

        {
            WorldPacket data(SMSG_NOTIFICATION, (message.size() + 1));
            data << message;

            player->SendDirectMessage(&data);
        }
    }
}

void ToSInstanceScript::PopulateRewardChest()
{
    auto waveTemplate = sToSMapMgr->GetWaveTemplateForWave(currentWave);
    if (!waveTemplate)
    {
        return;
    }

    if (!waveTemplate->hasReward)
    {
        return;
    }

    auto rewardId = waveTemplate->rewardTemplate;

    if (!rewardId)
    {
        return;
    }

    Position* tempPos = new Position(255.194, -99.974, 18.677, 6.270);
    if (rewardChest = instance->SummonGameObject(TOS_GOB_REWARD_CHEST, *tempPos))
    {
        rewardChest->loot.clear();
        rewardChest->SetLootRecipient(instance);

        rewardChest->loot.items.reserve(MAX_NR_LOOT_ITEMS);

        auto rewardTemplates = sToSMapMgr->GetRewardTemplates(rewardId);

        for (auto rewardTemplate = rewardTemplates->begin(); rewardTemplate != rewardTemplates->end(); ++rewardTemplate)
        {
            LootStoreItem* lootStoreItem = new LootStoreItem(rewardTemplate->itemEntry, 0, 0, false, 1, 0, 1, 1);

            LootItem lootItem(*lootStoreItem);
            lootItem.itemIndex = rewardChest->loot.items.size();
            lootItem.itemid = rewardTemplate->itemEntry;
            lootItem.count = urand(rewardTemplate->countMin, rewardTemplate->countMax);

            rewardChest->loot.items.push_back(lootItem);
        }

        rewardChest->loot.generateMoneyLoot(500, 5000);

        rewardChest->SetLootGenerationTime();
        rewardChest->SetLootState(GO_ACTIVATED);
    }

    rewardBeam = instance->SummonGameObject(TOS_GOB_REWARD_BEAM, *tempPos, 0.0, 0.0, 0.0, 0.0, 0, true);
}

void ToSInstanceScript::SetData(uint32 dataId, uint32 value)
{
    switch (dataId)
    {
    case TOS_DATA_ENCOUNTER_START:
        events.ScheduleEvent(TOS_DATA_ENCOUNTER_START, 0s);
        break;

    case TOS_DATA_ENCOUNTER_CURRENT_WAVE:
        currentWave = value;
        break;

    case TOS_DATA_ENCOUNTER_RESET:
        ResetEncounter();
        break;
    }
}

uint32 ToSInstanceScript::GetData(uint32 dataId) const
{
    switch (dataId)
    {
    case TOS_DATA_ENCOUNTER_START:
        return encounterInProgress;

    case TOS_DATA_ENCOUNTER_CURRENT_WAVE:
        return currentWave;

    case TOS_DATA_ENCOUNTER_CURRENT_WAVE_CLEARED:
        return IsWaveCleared();

    case TOS_DATA_ENCOUNTER_HAS_MORE_WAVES:
        return HasMoreWaves();

    case TOS_DATA_ENCOUNTER_CURRENT_WAVE_REMAINING:
        return GetRemainingAlive();

    case TOS_DATA_ENCOUNTER_CURRENT_SUBWAVE:
        return currentSubGroup;

    case TOS_DATA_ENCOUNTER_TOTAL_SUBWAVE:
        return totalSubGroups;

    case TOS_DATA_ENCOUNTER_TRIAL_COMPLETED:
        return trialCompleted;

    case TOS_DATA_ENCOUNTER_WAVE_IN_PROGRESS:
        return waveInProgress;
    }

    return 0;
}

bool ToSInstanceScript::IsEncounterInProgress() const
{
    return encounterInProgress;
}

uint32 ToSInstanceScript::GetRemainingAlive() const
{
    if (waveCreatures.empty())
    {
        return 0;
    }

    uint32 count = 0;
    for (auto it = waveCreatures.begin(); it != waveCreatures.end(); ++it)
    {
        auto creature = *it;

        if (!creature)
        {
            continue;
        }

        if (creature->IsInWorld() &&
            creature->IsAlive() &&
            creature->GetMapId() == TOS_MAP_ID /*When creatures are cleaned up they end up on another map, wtf?*/)
        {
            count++;
        }
    }

    return count;
}

void ToSInstanceScript::CleanupCreatures()
{
    if (waveCreatures.empty())
    {
        return;
    }

    for (auto it = waveCreatures.begin(); it != waveCreatures.end(); ++it)
    {
        auto creature = *it;

        if (!creature || !creature->IsInWorld())
        {
            continue;
        }

        creature->DespawnOrUnsummon();
    }

    waveCreatures.clear();
}

void ToSInstanceScript::CleanupGameObjects()
{
    if (rewardBeam &&
        rewardBeam->IsInWorld())
    {
        rewardBeam->DespawnOrUnsummon();
        rewardBeam = nullptr;
    }

    if (rewardChest &&
        rewardChest->IsInWorld())
    {
        rewardChest->DespawnOrUnsummon();
        rewardChest = nullptr;
    }
}

void ToSInstanceScript::ResetEncounter()
{
    encounterInProgress = false;
    waveInProgress = false;
    cheerPlayed = false;

    currentWave = 1;
    totalWaves = 0;
    currentSubGroup = 1;
    totalSubGroups = 0;

    waveCleared = false;
    trialCompleted = false;

    events.Reset();
    events.ScheduleEvent(TOS_DATA_ENCOUNTER_CHECK_ARENA_MASTER_RELOCATE, 3s);

    CleanupCreatures();
    CleanupGameObjects();
    DespawnCurseCrystals();

    ClearCursesFromPlayers();

    curses.clear();
    ReloadCurses();

    if (arenaMasterLeft)
    {
        RelocateArenaMaster(true);
        arenaMasterLeft = false;
    }
}

void ToSInstanceScript::AnnounceCompletion()
{
    bool hasCurses = curses.size() > 0;

    std::stringstream ss;
    ss << "|TInterface\\WorldMap\\Skull_64Red:16|t |cffFFFFFFCongratulations to player(s) ";

    Map::PlayerList const& players = instance->GetPlayers();
    auto playerCount = players.getSize();

    uint32 i = 0;
    for (const auto& it : players)
    {
        i++;

        Player* player = it.GetSource();

        if (!player)
        {
            continue;
        }

        ss << Acore::StringFormatFmt("{}{}", sToSMapMgr->GetHexColorFromClass(player->getClass()), player->GetName());

        if (i != playerCount)
        {
            ss << "|cffFFFFFF, ";
        }
    }

    ss << Acore::StringFormatFmt(" |cffFFFFFFfor defeating all waves ({}) in the |cffFF2651Trial of Strength", sToSMapMgr->GetTotalWaves());

    if (hasCurses)
    {
        ss << Acore::StringFormatFmt(" with |cffC436C1{}|cffFFFFFF curses!|r", curses.size());
    }
    else
    {
        ss << "!|r";
    }

    sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str());
}
