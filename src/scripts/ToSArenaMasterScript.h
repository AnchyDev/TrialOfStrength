#ifndef MODULE_TRIAL_OF_STRENGTH_ARENA_MASTER_H
#define MODULE_TRIAL_OF_STRENGTH_ARENA_MASTER_H

class ToSArenaMasterScript : public CreatureScript
{
public:
    ToSArenaMasterScript() : CreatureScript("ToSArenaMasterScript") { }

    enum ArenaMasterConstants {
        TOS_ARENA_MASTER_TEXT_GREETING = 441250,
        TOS_ARENA_MASTER_TEXT_PRE_TRIAL = 441251,
        TOS_ARENA_MASTER_TEXT_WAVE_NOT_FINISHED = 441252,
        TOS_ARENA_MASTER_TEXT_WAVE_NEXT = 441253,
        TOS_ARENA_MASTER_TEXT_CONGRATULATE = 441254,
        TOS_ARENA_MASTER_TEXT_DENY_ENTRY = 441255,
        TOS_ARENA_MASTER_TEXT_DENY_ENTRY_NO_TICKET = 441256,

        TOS_GOSSIP_TELEPORT_TO = 1,
        TOS_GOSSIP_TELEPORT_FROM = 2,
        TOS_GOSSIP_ENCOUNTER_START = 3,
        TOS_GOSSIP_ENCOUNTER_NEXT_WAVE = 4,
        TOS_GOSSIP_ENCOUNTER_RESET = 5
    };

    virtual bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (!sConfigMgr->GetOption<bool>("TrialOfStrength.Enable", false))
        {
            return false;
        }

        ClearGossipMenuFor(player);

        if (!sToSMapMgr->CanPlayerEnter(player))
        {
            SendGossipMenuFor(player, TOS_ARENA_MASTER_TEXT_DENY_ENTRY, creature);

            return true;
        }

        auto map = creature->GetMap();
        if (map && map->GetId() != TOS_MAP_ID)
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Yes, I would like to attempt the trials.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_TELEPORT_TO);
            SendGossipMenuFor(player, TOS_ARENA_MASTER_TEXT_GREETING, creature);

            return true;
        }

        auto iScript = (ToSInstanceScript*)creature->GetInstanceScript();
        if (!iScript)
        {
            CloseGossipMenuFor(player);

            return false;
        }

        auto currentWave = iScript->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE);
        auto currentSubWave = iScript->GetData(TOS_DATA_ENCOUNTER_CURRENT_SUBWAVE);
        auto totalSubWave = iScript->GetData(TOS_DATA_ENCOUNTER_TOTAL_SUBWAVE);
        auto waveCleared = iScript->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE_CLEARED) > 0;
        auto hasMoreWaves = iScript->GetData(TOS_DATA_ENCOUNTER_HAS_MORE_WAVES) > 0;
        auto remainingAlive = iScript->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE_REMAINING);
        auto trialCompleted = iScript->GetData(TOS_DATA_ENCOUNTER_TRIAL_COMPLETED) > 0;

        if (!iScript->IsEncounterInProgress() && !waveCleared)
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Yes, I am ready to start the Trial of Strength.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_ENCOUNTER_START);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I changed my mind, I would like to leave.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_TELEPORT_FROM);

            SendGossipMenuFor(player, TOS_ARENA_MASTER_TEXT_PRE_TRIAL, creature);

            return true;
        }

        if (iScript->IsEncounterInProgress() && !waveCleared)
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, Acore::StringFormatFmt("Encounter In Progress: {}|nCurrent Wave: |cff0000FF{}|r|nCurrent Sub-Wave: {}/{}|nWave Cleared: {}|nAlive: |cffFF0000{}|r|nMore Waves?: {}", iScript->IsEncounterInProgress() ? "true" : "false", currentWave, currentSubWave, totalSubWave, waveCleared ? "true" : "false", remainingAlive, hasMoreWaves ? "true" : "false"), GOSSIP_SENDER_MAIN, 0);

            SendGossipMenuFor(player, TOS_ARENA_MASTER_TEXT_WAVE_NOT_FINISHED, creature);

            return true;
        }

        if (iScript->IsEncounterInProgress() && waveCleared && hasMoreWaves)
        {
            if (iScript->IsRewardChestEmpty())
            {
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, Acore::StringFormatFmt("Yes, I would like to proceed to the next wave. ({})", currentWave + 1), GOSSIP_SENDER_MAIN, TOS_GOSSIP_ENCOUNTER_NEXT_WAVE);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to stop here.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_ENCOUNTER_RESET);
            }
            else
            {
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, Acore::StringFormatFmt("Yes, I would like to proceed to the next wave. ({})", currentWave + 1), GOSSIP_SENDER_MAIN, TOS_GOSSIP_ENCOUNTER_NEXT_WAVE, "You have unlooted items in the reward chest, are you sure you want to continue?", 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to stop here.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_ENCOUNTER_RESET, "You have unlooted items in the reward chest, are you sure you want to continue?", 0, false);
            }

            SendGossipMenuFor(player, TOS_ARENA_MASTER_TEXT_WAVE_NEXT, creature);

            return true;
        }

        if (trialCompleted)
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to attempt the trial again.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_ENCOUNTER_RESET);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want to leave this place.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_TELEPORT_FROM);

            SendGossipMenuFor(player, TOS_ARENA_MASTER_TEXT_CONGRATULATE, creature);

            return true;
        }

        CloseGossipMenuFor(player);

        return false;
    }

    virtual bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        if (!sConfigMgr->GetOption<bool>("TrialOfStrength.Enable", false))
        {
            return false;
        }

        if (action == 0)
        {
            OnGossipHello(player, creature);
        }

        if (action == TOS_GOSSIP_TELEPORT_TO)
        {
            CloseGossipMenuFor(player);
            player->TeleportTo(TOS_MAP_ID, 176.726, -126.015, 18.022, 4.739);
        }

        if (action == TOS_GOSSIP_TELEPORT_FROM)
        {
            CloseGossipMenuFor(player);
            player->TeleportTo(TOS_MAP_ID, 176.726, -126.015, 18.022, 4.739);
        }

        if (action == TOS_GOSSIP_ENCOUNTER_START)
        {
            ClearGossipMenuFor(player);

            auto ticketCount = player->GetItemCount(TOS_ENTRY_TICKET_ID);

            if (!ticketCount)
            {
                SendGossipMenuFor(player, TOS_ARENA_MASTER_TEXT_DENY_ENTRY_NO_TICKET, creature);
                return true;
            }

            player->DestroyItemCount(TOS_ENTRY_TICKET_ID, 1, true);

            CloseGossipMenuFor(player);

            if (InstanceScript* pInstance = creature->GetInstanceScript())
            {
                pInstance->SetData(TOS_DATA_ENCOUNTER_START, 1);
            }
        }

        if (action == TOS_GOSSIP_ENCOUNTER_RESET)
        {
            CloseGossipMenuFor(player);

            if (InstanceScript* pInstance = creature->GetInstanceScript())
            {
                pInstance->SetData(TOS_DATA_ENCOUNTER_RESET, 1);
            }
        }

        if (action == TOS_GOSSIP_ENCOUNTER_NEXT_WAVE)
        {
            CloseGossipMenuFor(player);

            if (InstanceScript* pInstance = creature->GetInstanceScript())
            {
                if (!pInstance->GetData(TOS_DATA_ENCOUNTER_WAVE_IN_PROGRESS))
                {
                    pInstance->SetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE, pInstance->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE) + 1);
                    pInstance->SetData(TOS_DATA_ENCOUNTER_START, 1);
                }
            }
        }

        return true;
    }
};

#endif // MODULE_TRIAL_OF_STRENGTH_ARENA_MASTER_H
