#ifndef MODULE_TRIAL_OF_STRENGTH_AI_MELEE_CRITTER_H
#define MODULE_TRIAL_OF_STRENGTH_AI_MELEE_CRITTER_H

#include "ScriptMgr.h"

class ToSAIMeleeCritter : public CreatureScript
{
public:
    ToSAIMeleeCritter() : CreatureScript("ToSAIMeleeCritter") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new ToSAIMeleeCritterAI(creature);
    }

    struct ToSAIMeleeCritterAI : public CombatAI
    {
        enum CombatantEvents
        {
            TOS_EVENT_COMBATANT_ATTACK = 1,
            TOS_EVENT_COMBATANT_SPELL_ID_RIP = 40199, // damage over time
            TOS_EVENT_COMBATANT_SPELL_ID_TENDON_RIP = 44622, // 75% movespeed reduction
        };

        EventMap events;

        ToSAIMeleeCritterAI(Creature* creature) : CombatAI(creature)
        {
            Reset();
        }

        void Reset() override
        {
            events.Reset();

            events.ScheduleEvent(TOS_EVENT_COMBATANT_ATTACK, 5s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            switch (events.ExecuteEvent())
            {
            case TOS_EVENT_COMBATANT_ATTACK:
                AttackTarget();
                break;
            }

            DoMeleeAttackIfReady();
        }

        void AttackTarget()
        {
            auto creature = me->GetVictim();
            if (!creature)
            {
                return;
            }

            uint32 spell = 0;
            switch (urand(0, 2))
            {
            case 0:
                // Do nothing
                break;
            case 1:
                spell = TOS_EVENT_COMBATANT_SPELL_ID_RIP;
                break;

            case 2:
                spell = TOS_EVENT_COMBATANT_SPELL_ID_TENDON_RIP;
                break;
            }

            if (!spell)
            {
                return;
            }

            me->CastSpell(creature, spell);

            events.ScheduleEvent(TOS_EVENT_COMBATANT_ATTACK, 5s);
        }
    };
};

#endif // MODULE_TRIAL_OF_STRENGTH_AI_MELEE_CRITTER_H
