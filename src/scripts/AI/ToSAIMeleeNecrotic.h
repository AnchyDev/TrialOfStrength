#ifndef MODULE_TRIAL_OF_STRENGTH_AI_MELEE_NECROTIC_H
#define MODULE_TRIAL_OF_STRENGTH_AI_MELEE_NECROTIC_H

#include "ScriptMgr.h"

class ToSAIMeleeNecrotic : public CreatureScript
{
public:
    ToSAIMeleeNecrotic() : CreatureScript("ToSAIMeleeNecrotic") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new ToSAIMeleeNecroticAI(creature);
    }

    struct ToSAIMeleeNecroticAI : public CombatAI
    {
        enum CombatantEvents
        {
            TOS_EVENT_COMBATANT_SPELL_ID_STRIKE = 69933, // Baleful Strike
            TOS_EVENT_COMBATANT_SPELL_ID_STRIKE_2 = 71924, // Plague Strike

            TOS_EVENT_COMBATANT_SPELL_RANDOM = 1,
        };

        EventMap events;

        ToSAIMeleeNecroticAI(Creature* creature) : CombatAI(creature)
        {
            Reset();
        }

        void Reset() override
        {
            events.Reset();

            events.ScheduleEvent(TOS_EVENT_COMBATANT_SPELL_RANDOM, 5s);
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

            switch (urand(0, 1))
            {
            case 0:
                me->CastSpell(creature, TOS_EVENT_COMBATANT_SPELL_ID_STRIKE);
                break;

            case 1:
                me->CastSpell(creature, TOS_EVENT_COMBATANT_SPELL_ID_STRIKE_2);
                break;
            }
            events.ScheduleEvent(TOS_EVENT_COMBATANT_SPELL_RANDOM, 5s);
        }
    };
};

#endif // MODULE_TRIAL_OF_STRENGTH_AI_MELEE_NECROTIC_H
