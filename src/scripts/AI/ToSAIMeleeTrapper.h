#ifndef MODULE_TRIAL_OF_STRENGTH_AI_MELEE_TRAPPER_H
#define MODULE_TRIAL_OF_STRENGTH_AI_MELEE_TRAPPER_H

#include "ScriptMgr.h"

class ToSAIMeleeTrapper : public CreatureScript
{
public:
    ToSAIMeleeTrapper() : CreatureScript("ToSAIMeleeTrapper") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new ToSAIMeleeTrapperAI(creature);
    }

    struct ToSAIMeleeTrapperAI : public CombatAI
    {
        enum CombatantEvents
        {
            TOS_EVENT_COMBATANT_SPELL_ID_NET = 50762, // Net

            TOS_EVENT_COMBATANT_SPELL_RANDOM = 1,
        };

        EventMap events;

        ToSAIMeleeTrapperAI(Creature* creature) : CombatAI(creature)
        {
            Reset();
        }

        void Reset() override
        {
            events.Reset();

            events.ScheduleEvent(TOS_EVENT_COMBATANT_SPELL_RANDOM, 3s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            switch (events.ExecuteEvent())
            {
            case TOS_EVENT_COMBATANT_SPELL_RANDOM:
                RandomAttack();
                break;
            }

            DoMeleeAttackIfReady();
        }

        void RandomAttack()
        {
            auto creature = me->GetVictim();
            if (!creature)
            {
                return;
            }

            me->CastSpell(creature, TOS_EVENT_COMBATANT_SPELL_ID_NET);

            events.ScheduleEvent(TOS_EVENT_COMBATANT_SPELL_RANDOM, 15s);
        }
    };
};

#endif // MODULE_TRIAL_OF_STRENGTH_AI_MELEE_TRAPPER_H
