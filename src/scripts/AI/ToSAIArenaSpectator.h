#ifndef MODULE_TRIAL_OF_STRENGTH_AI_ARENA_SPECTATOR_H
#define MODULE_TRIAL_OF_STRENGTH_AI_ARENA_SPECTATOR_H

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ToSInstanceScript.h"

class ToSAIArenaSpectator : public CreatureScript
{
public:
    ToSAIArenaSpectator() : CreatureScript("ToSAIArenaSpectator") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new ToSAIArenaSpectatorAI(creature);
    }

    struct ToSAIArenaSpectatorAI : public ScriptedAI
    {
        enum ToSSpectatorConstants
        {
            TOS_ARENA_SPEC_DO_EMOTE = 1
        };

        EventMap events;

        ToSAIArenaSpectatorAI(Creature* creature) : ScriptedAI(creature)
        {
            events.Reset();
            events.ScheduleEvent(TOS_ARENA_SPEC_DO_EMOTE, randtime(3s, 10s));
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
    };
};

#endif // MODULE_TRIAL_OF_STRENGTH_AI_ARENA_SPECTATOR_H
