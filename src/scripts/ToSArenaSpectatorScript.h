#ifndef MODULE_TRIAL_OF_STRENGTH_ARENA_SPECTATOR_H
#define MODULE_TRIAL_OF_STRENGTH_ARENA_SPECTATOR_H

#include "ToSInstanceScript.h"

#include "ScriptedCreature.h"

class ToSArenaSpectatorScript : public CreatureScript
{
public:
    ToSArenaSpectatorScript() : CreatureScript("ToSArenaSpectatorScript") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new ToSArenaSpectatorAIScript(creature);
    }

    class ToSArenaSpectatorAIScript : public ScriptedAI
    {
        enum ToSSpectatorConstants
        {
            TOS_ARENA_SPEC_DO_EMOTE = 1
        };

    public:
        ToSArenaSpectatorAIScript(Creature* creature) : ScriptedAI(creature)
        {
            events.Reset();
            events.ScheduleEvent(TOS_ARENA_SPEC_DO_EMOTE, randtime(3s, 10s));

            crowdCheerAlternate = false;
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            switch (events.ExecuteEvent())
            {
            case TOS_ARENA_SPEC_DO_EMOTE:
                DoEmote();
                events.RescheduleEvent(TOS_ARENA_SPEC_DO_EMOTE, randtime(3s, 10s));
                break;
            }
        }

        void DoEmote()
        {
            auto iScript = (ToSInstanceScript*)me->GetInstanceScript();
            if (!iScript)
            {
                events.Reset();
                LOG_WARN("module", "Failed to find instance script for Arena Spectator.");
                return;
            }

            if (!iScript->IsEncounterInProgress() ||
                !iScript->IsWaveInProgress())
            {
                return;
            }

            switch (urand(0, 2))
            {
            case 0:
                me->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                break;

            case 1:
                me->HandleEmoteCommand(EMOTE_ONESHOT_DANCE);
                break;

            case 2:
                me->HandleEmoteCommand(EMOTE_ONESHOT_APPLAUD);
                break;
            }
        }

    private:
        EventMap events;
        bool crowdCheerAlternate;
    };

private:
    EventMap events;
};

#endif // MODULE_TRIAL_OF_STRENGTH_ARENA_SPECTATOR_H
