#ifndef MODULE_TRIAL_OF_STRENGTH_ARENA_MASTER_H
#define MODULE_TRIAL_OF_STRENGTH_ARENA_MASTER_H

class ToSArenaMasterScript : public CreatureScript
{
public:
    ToSArenaMasterScript() : CreatureScript("ToSArenaMasterScript") { }

    virtual bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (!sConfigMgr->GetOption<bool>("TrialOfStrength.Enable", false))
        {
            return false;
        }

        ClearGossipMenuFor(player);

        auto map = creature->GetMap();
        if (map && map->GetId() != TOS_MAP_ID)
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Yes, I would like to attempt the trials.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_TELEPORT_TO);

            SendGossipMenuFor(player, 1, creature);

            return true;
        }

        if (InstanceScript* pInstance = creature->GetInstanceScript())
        {
            auto encounterInProgress = pInstance->IsEncounterInProgress() ? "|cff00FF00true|r" : "|cffFF0000false|r";
            auto currentWave = pInstance->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE);
            auto waveCleared = pInstance->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE_CLEARED) > 0 ? "|cff00FF00true|r" : "|cffFF0000false|r";
            auto moreWaves = pInstance->GetData(TOS_DATA_ENCOUNTER_HAS_MORE_WAVES) > 0 ? "|cff00FF00yes|r" : "|cffFF0000no|r";
            auto remainingAlive = pInstance->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE_REMAINING);

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, Acore::StringFormatFmt("Encounter In Progress:{}|nCurrent Wave: |cff0000FF{}|r|nWave Cleared: {}|nAlive: |cffFF0000{}|r|nMore Waves?: {}", encounterInProgress, currentWave, waveCleared, remainingAlive, moreWaves), GOSSIP_SENDER_MAIN, 0);

            if (!pInstance->GetData(TOS_DATA_ENCOUNTER_START))
            {
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to start the trial.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_ENCOUNTER_START);
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I changed my mind, I would like to leave.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_TELEPORT_FROM);
            }
            else
            {
                if (pInstance->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE_CLEARED) &&
                    pInstance->GetData(TOS_DATA_ENCOUNTER_HAS_MORE_WAVES))
                {
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, Acore::StringFormatFmt("I would like to move to the next wave ({}).", (pInstance->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE) + 1)), GOSSIP_SENDER_MAIN, TOS_GOSSIP_ENCOUNTER_NEXT_WAVE);
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to stop.", GOSSIP_SENDER_MAIN, TOS_GOSSIP_TELEPORT_FROM);
                }
            }

            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Reset encounter", GOSSIP_SENDER_MAIN, TOS_GOSSIP_ENCOUNTER_RESET);
        }

        SendGossipMenuFor(player, 1, creature);

        return true;
    }

    virtual bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
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
            player->TeleportTo(TOS_MAP_ID, 239.045, -99.930, 23.773, 6.271);
        }

        if (action == TOS_GOSSIP_TELEPORT_FROM)
        {
            CloseGossipMenuFor(player);
            player->TeleportTo(TOS_MAP_ID, 239.045, -99.930, 23.773, 6.271);
        }

        if (action == TOS_GOSSIP_ENCOUNTER_START)
        {
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
                pInstance->SetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE_CLEARED, 0);
                pInstance->SetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE, pInstance->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE) + 1);
                pInstance->SetData(TOS_DATA_ENCOUNTER_START, 1);
            }
        }

        return true;
    }
};

#endif // MODULE_TRIAL_OF_STRENGTH_ARENA_MASTER_H
