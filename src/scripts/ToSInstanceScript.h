#ifndef MODULE_TRIAL_OF_STRENGTH_INSTANCE_SCRIPT_H
#define MODULE_TRIAL_OF_STRENGTH_INSTANCE_SCRIPT_H

class instance_trial_of_strength : public InstanceMapScript
{
public:
    instance_trial_of_strength() : InstanceMapScript("instance_trial_of_strength", 44) { }

    struct trial_of_strength_InstanceScript : public InstanceScript
    {
        EventMap events;

        bool encounterInProgress;
        bool waveInProgress;

        uint32 currentWave;
        uint32 totalWaves;
        uint32 currentSubGroup;
        uint32 totalSubGroups;

        bool waveCleared;
        bool trialCompleted;

        std::vector<Creature*> waveCreatures;
        std::vector<ToSCurseTemplate*> curses;

        Creature* arenaMaster;
        bool arenaMasterLeft;

        Position* combatantPosStart;
        Position* combatantPosEnd;

        GameObject* rewardChest;
        GameObject* rewardBeam;

        trial_of_strength_InstanceScript(Map* map) : InstanceScript(map)
        {
            arenaMaster = nullptr;
            arenaMasterLeft = false;

            rewardChest = nullptr;
            rewardBeam = nullptr;

            combatantPosStart = new Position(228.324, -99.921, 18.007, 6.282);
            combatantPosEnd = new Position(265.175, -100.163, 18.677, 3.121);

            ResetEncounter();
        }

        void AddCurse(uint32 curseId)
        {
            auto it = curseTemplates.find(curseId);
            if (it == curseTemplates.end())
            {
                LOG_WARN("module", "Tried to add curse {} to creature curses but it does not exist.", curseId);
                return;
            }

            auto curse = GetCurseById(curseId);
            if (!curse)
            {
                return;
            }

            curses.push_back(curse);
        }

        void OnCreatureCreate(Creature* creature) override
        {
            if (creature &&
                creature->GetEntry() == TOS_NPC_ARENA_MASTER)
            {
                arenaMaster = creature;
            }
        }

        bool IsSubWaveCleared() const
        {
            return waveInProgress && GetRemainingAlive() == 0;
        }

        bool IsWaveCleared() const
        {
            return waveCleared;
        }

        bool HasMoreWaves() const
        {
            return currentWave < totalWaves ? true : false;
        }

        bool IsWaveInProgress() const
        {
            return waveInProgress;
        }

        void SpawnNextWave(ToSWaveTemplate* waveTemplate = nullptr)
        {
            if (!waveTemplate)
            {
                waveTemplate = GetWaveTemplateForWave(currentWave);
            }

            if (!waveTemplate)
            {
                LOG_WARN("module", "Wave template is nullptr.");
                return;
            }

            auto enemies = GetEnemiesFromGroup(waveTemplate->enemyGroup, currentSubGroup);
            if (enemies.empty())
            {
                LOG_WARN("module", "No enemies found in wave template.");
                return;
            }

            waveCleared = false;
            CleanupCreatures();
            ApplyCursesToPlayers();

            for (auto it = enemies.begin(); it != enemies.end(); ++it)
            {
                auto enemy = (*it);
                auto summon = SpawnNPC(enemy->creatureEntry, instance, combatantPosStart);

                ApplyCurses(summon);

                waveCreatures.push_back(summon);

                if(currentSubGroup == 1)
                    summon->SetFaction(FACTION_FRIENDLY);

                MakeEntrance(summon);
            }

            events.ScheduleEvent(TOS_DATA_ENCOUNTER_COMBATANTS_HOSTILE, 5s);
            events.ScheduleEvent(TOS_DATA_ENCOUNTER_CHECK_WAVE_COMPLETE, 10s);
            events.ScheduleEvent(TOS_DATA_ENCOUNTER_CHECK_FAILURE, 5s);
        }

        void MakeEntrance(Creature* creature)
        {
            creature->GetMotionMaster()->MovePoint(0, *combatantPosEnd);
            creature->SetHomePosition(*combatantPosEnd);
        }

        void ApplyCurses(Unit* unit)
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

                if(!unit->ToPlayer() &&
                    curse->type == TOS_CURSE_TYPE_ENEMY &&
                    !unit->HasAura(curse->aura))
                {
                    unit->AddAura(curse->aura, unit);
                    continue;
                }
            }
        }

        void ApplyCursesToPlayers()
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

        void ClearCurses(Unit* unit)
        {
            if (!unit)
            {
                return;
            }

            for (auto const& curse : curses)
            {
                if (!curse)
                {
                    continue;
                }

                if (unit->HasAura(curse->aura))
                {
                    unit->RemoveAura(curse->aura);
                }
            }
        }

        void ClearCursesFromPlayers()
        {
            Map::PlayerList const& players = instance->GetPlayers();

            for (const auto& it : players)
            {
                Player* player = it.GetSource();

                if (!player)
                {
                    continue;
                }

                ClearCurses(player);
            }
        }

        void SetCombatantsHostile()
        {
            for (auto it = waveCreatures.begin(); it != waveCreatures.end(); ++it)
            {
                auto creature = *it;

                creature->SetFaction(FACTION_MONSTER);
                creature->SetInCombatWithZone();

                if (auto player = creature->SelectNearestPlayer(100.0f))
                {
                    if(creature->Attack(player, true))
                        creature->GetMotionMaster()->MoveChase(player);
                }
            }
        }

        void Update(uint32 diff) override
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
            }
        }

        void CheckArenaMasterRelocate()
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

        void RelocateArenaMaster(bool returning)
        {
            if (!arenaMaster || !arenaMaster->IsInWorld())
            {
                return;
            }

            arenaMaster->CastSpell(arenaMaster, 64446);

            if (returning)
            {
                arenaMaster->NearTeleportTo(244.114, -99.9485, 23.7741, 3.16135);
            }
            else
            {
                arenaMaster->NearTeleportTo(211.368, -91.809, 18.677, 4.730);
            }
        }

        bool AnyPlayerAlive()
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

        bool CheckFailure()
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

        void NotifyFailure()
        {
            std::string message = Acore::StringFormatFmt("|cffFF9900Wave failed!|r", currentWave);
            Map::PlayerList const& players = instance->GetPlayers();

            for (const auto& it : players)
            {
                Player* player = it.GetSource();

                if (!player)
                    continue;

                player->SendSystemMessage(message);
                player->PlayDirectSound(847 /* Quest Failed Sound */);

                {
                    WorldPacket data(SMSG_NOTIFICATION, (message.size() + 1));
                    data << message;

                    player->SendDirectMessage(&data);
                }
            }
        }

        void SetupEncounter()
        {
            encounterInProgress = true;
            waveInProgress = true;
            waveCleared = false;

            auto waveTemplate = GetWaveTemplateForWave(currentWave);
            if (!waveTemplate)
            {
                LOG_WARN("module", "Wave template is nullptr.");
                return;
            }

            totalWaves = GetTotalWaves();

            currentSubGroup = 1;
            auto subGroups = GetSubGroups(waveTemplate->enemyGroup);
            totalSubGroups = subGroups.size();

            if (totalSubGroups < 1)
            {
                LOG_WARN("module", "There were no subgroups found for wave {}.", currentWave);
                return;
            }

            events.ScheduleEvent(TOS_DATA_ENCOUNTER_START_NEXT_WAVE, 5s);
        }

        void CheckWaveCompletion()
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

                events.ScheduleEvent(TOS_DATA_ENCOUNTER_START_NEXT_WAVE, 5s);
            }
            else
            {
                NotifyPlayers();
                PopulateRewardChest();
                CleanupCreatures();

                waveInProgress = false;
                waveCleared = true;

                if (currentWave == totalWaves)
                {
                    trialCompleted = true;
                    AnnounceCompletion();
                }
            }
        }

        void NotifyPlayers()
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

        void PopulateRewardChest()
        {
            auto waveTemplate = GetWaveTemplateForWave(currentWave);
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

            Position* tempPos = new Position(269.173, -100.046, 18.679, 3.180);
            rewardChest = instance->SummonGameObject(441250, *tempPos);
            if (!rewardChest)
            {
                rewardChest->DespawnOrUnsummon();
                return;
            }

            rewardBeam = instance->SummonGameObject(177705, *tempPos);
            if (!rewardBeam)
            {
                rewardBeam->DespawnOrUnsummon();
            }

            rewardChest->loot.clear();
            rewardChest->SetLootRecipient(instance);

            rewardChest->loot.items.reserve(MAX_NR_LOOT_ITEMS);

            auto rewardTemplates = GetRewardTemplates(rewardId);

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

        void SetData(uint32 dataId, uint32 value) override
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

        uint32 GetData(uint32 dataId) const override
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

        bool IsEncounterInProgress() const override
        {
            return encounterInProgress;
        }

        uint32 GetRemainingAlive() const
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

        void CleanupCreatures()
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

        void CleanupGameObjects()
        {
            if (rewardBeam && rewardBeam->IsInWorld())
            {
                rewardBeam->DespawnOrUnsummon();
            }

            if (rewardChest && rewardChest->IsInWorld())
            {
                rewardChest->DespawnOrUnsummon();
            }
        }

        void ResetEncounter()
        {
            encounterInProgress = false;
            waveInProgress = false;

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
            ClearCursesFromPlayers();
            curses.clear();

            if (arenaMasterLeft)
            {
                RelocateArenaMaster(true);
                arenaMasterLeft = false;
            }
        }

        void AnnounceCompletion()
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

                ss << Acore::StringFormatFmt("{}{}", GetHexColorFromClass(player->getClass()), player->GetName());

                if (i != playerCount)
                {
                    ss << "|cffFFFFFF, ";
                }
            }

            ss << Acore::StringFormatFmt(" |cffFFFFFFfor defeating all waves ({}) in the |cffFF2651Trial of Strength", GetTotalWaves());

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
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new trial_of_strength_InstanceScript(map);
    }
};

#endif // MODULE_TRIAL_OF_STRENGTH_INSTANCE_SCRIPT_H
