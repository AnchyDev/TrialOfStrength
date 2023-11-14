#ifndef MODULE_TRIAL_OF_STRENGTH_AI_MELEE_ANGRY_H
#define MODULE_TRIAL_OF_STRENGTH_AI_MELEE_ANGRY_H

#include "ScriptMgr.h"

class ToSAIMeleeAngry : public CreatureScript
{
public:
    ToSAIMeleeAngry() : CreatureScript("ToSAIMeleeAngry") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new ToSAIMeleeAngryAI(creature);
    }

    struct ToSAIMeleeAngryAI : public CombatAI
    {
        enum CombatantEvents
        {
            TOS_EVENT_COMBATANT_START_PUNCHING = 1,
            TOS_EVENT_COMBATANT_AURA_ANGRY = 23128, /* Enrage */
            TOS_EVENT_COMBATANT_SPELL_PUNCH = 29581,
        };

        EventMap events;

        bool isPunching;
        bool isAngry;

        ToSAIMeleeAngryAI(Creature* creature) : CombatAI(creature)
        {
            events.Reset();

            isPunching = false;
            isAngry = false;
        }

        void Reset() override
        {
            if (me->HasAura(TOS_EVENT_COMBATANT_AURA_ANGRY))
            {
                me->RemoveAura(TOS_EVENT_COMBATANT_AURA_ANGRY);
            }

            isPunching = false;
            isAngry = false;

            events.Reset();
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            switch (events.ExecuteEvent())
            {
            case TOS_EVENT_COMBATANT_START_PUNCHING:
                TryPunching();

                events.RescheduleEvent(TOS_EVENT_COMBATANT_START_PUNCHING, 3s);
                break;
            }

            if (me->GetHealthPct() < 66 && !isPunching)
            {
                isPunching = true;

                events.ScheduleEvent(TOS_EVENT_COMBATANT_START_PUNCHING, 1s);
            }

            if (me->GetHealthPct() < 50 && !isAngry)
            {
                GetAngry();
            }

            DoMeleeAttackIfReady();
        }

        void GetAngry()
        {
            me->AddAura(TOS_EVENT_COMBATANT_AURA_ANGRY, me);

            isAngry = true;
        }

        void TryPunching()
        {
            auto creature = me->GetVictim();
            if (!creature)
            {
                return;
            }

            // Outside 5yd range.
            if (creature->GetPosition().GetExactDist(me->GetPosition()) > 5.0f)
            {
                return;
            }

            me->CastSpell(creature, TOS_EVENT_COMBATANT_SPELL_PUNCH);
        }
    };
};

#endif // MODULE_TRIAL_OF_STRENGTH_AI_MELEE_ANGRY_H
