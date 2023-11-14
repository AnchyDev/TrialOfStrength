#ifndef MODULE_TRIAL_OF_STRENGTH_AI_SPELL_ELEMENTAL_H
#define MODULE_TRIAL_OF_STRENGTH_AI_SPELL_ELEMENTAL_H

#include "ScriptMgr.h"

class ToSAISpellElemental : public CreatureScript
{
public:
    ToSAISpellElemental() : CreatureScript("ToSAISpellElemental") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new ToSAISpellElementalAI(creature);
    }

    struct ToSAISpellElementalAI : public CombatAI
    {
        enum CombatantEvents
        {
            TOS_EVENT_COMBATANT_SPELL_ID_FROST = 42842,
            TOS_EVENT_COMBATANT_SPELL_ID_FROST_SHIELD = 7301,
            TOS_EVENT_COMBATANT_SPELL_ID_FIRE = 42833,
            TOS_EVENT_COMBATANT_SPELL_ID_FIRE_SHIELD = 43046,
            TOS_EVENT_COMBATANT_SPELL_ID_LIGHTNING = 49238,
            TOS_EVENT_COMBATANT_SPELL_ID_LIGHTNING_SHIELD = 49281,
            TOS_EVENT_COMBATANT_SPELL_ID_EARTH = 48461,
            TOS_EVENT_COMBATANT_SPELL_ID_EARTH_SHIELD = 49284,

            TOS_EVENT_COMBATANT_SPELL_ID_MANA_REGEN = 29166,

            TOS_EVENT_COMBATANT_SPELL_CYCLE_ELEMENTS = 2
        };

        EventMap events;

        uint32 currentSpell;

        ToSAISpellElementalAI(Creature* creature) : CombatAI(creature)
        {
            Reset();
        }

        void Reset() override
        {
            events.Reset();

            currentSpell = TOS_EVENT_COMBATANT_SPELL_ID_FROST;
            me->AddAura(TOS_EVENT_COMBATANT_SPELL_ID_FROST_SHIELD, me);

            events.ScheduleEvent(TOS_EVENT_COMBATANT_SPELL_CYCLE_ELEMENTS, 5s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            switch (events.ExecuteEvent())
            {
            case TOS_EVENT_COMBATANT_SPELL_CYCLE_ELEMENTS:
                CycleElements();
                break;
            }

            DoSpellAttackIfReady(currentSpell);
        }

        void CycleElements()
        {
            if (me->HasUnitState(UNIT_STATE_CASTING))
            {
                events.RescheduleEvent(TOS_EVENT_COMBATANT_SPELL_CYCLE_ELEMENTS, 1s);
                return;
            }

            switch (currentSpell)
            {
            case TOS_EVENT_COMBATANT_SPELL_ID_FROST:
                currentSpell = TOS_EVENT_COMBATANT_SPELL_ID_FIRE;
                me->AddAura(TOS_EVENT_COMBATANT_SPELL_ID_FIRE_SHIELD, me);
                break;

            case TOS_EVENT_COMBATANT_SPELL_ID_FIRE:
                currentSpell = TOS_EVENT_COMBATANT_SPELL_ID_LIGHTNING;
                me->AddAura(TOS_EVENT_COMBATANT_SPELL_ID_LIGHTNING_SHIELD, me);
                me->AddAura(TOS_EVENT_COMBATANT_SPELL_ID_MANA_REGEN, me); // Allows the caster to regen mana to complete a cycle.
                break;

            case TOS_EVENT_COMBATANT_SPELL_ID_LIGHTNING:
                currentSpell = TOS_EVENT_COMBATANT_SPELL_ID_EARTH;
                me->AddAura(TOS_EVENT_COMBATANT_SPELL_ID_EARTH_SHIELD, me);
                break;

            case TOS_EVENT_COMBATANT_SPELL_ID_EARTH:
                currentSpell = TOS_EVENT_COMBATANT_SPELL_ID_FROST;
                me->AddAura(TOS_EVENT_COMBATANT_SPELL_ID_FROST_SHIELD, me);
                break;
            }

            events.RescheduleEvent(TOS_EVENT_COMBATANT_SPELL_CYCLE_ELEMENTS, 5s);
        }
    };
};

#endif // MODULE_TRIAL_OF_STRENGTH_AI_SPELL_ELEMENTAL_H
