#ifndef MODULE_TRIAL_OF_STRENGTH_AI_SPELL_RADIOACTIVE_H
#define MODULE_TRIAL_OF_STRENGTH_AI_SPELL_RADIOACTIVE_H

#include "ScriptMgr.h"

class ToSAISpellRadioactive : public CreatureScript
{
public:
    ToSAISpellRadioactive() : CreatureScript("ToSAISpellRadioactive") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new ToSAISpellRadioactiveAI(creature);
    }

    struct ToSAISpellRadioactiveAI : public CombatAI
    {
        enum CombatantEvents
        {
            TOS_EVENT_COMBATANT_SPELL_CAST_RADIATION = 1,
            TOS_EVENT_COMBATANT_SPELL_ID_RADIATION = 31283
        };

        EventMap events;

        ToSAISpellRadioactiveAI(Creature* creature) : CombatAI(creature)
        {
            Reset();
        }

        void Reset() override
        {
            events.Reset();

            events.ScheduleEvent(TOS_EVENT_COMBATANT_SPELL_CAST_RADIATION, 2s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            switch (events.ExecuteEvent())
            {
            case TOS_EVENT_COMBATANT_SPELL_CAST_RADIATION:
                CastRadiation();
                break;
            }
        }

        void CastRadiation()
        {
            auto target = me->GetVictim();

            if (!target)
            {
                events.RescheduleEvent(TOS_EVENT_COMBATANT_SPELL_CAST_RADIATION, 2s);
                return;
            }

            auto damage = irand(500, 1000);
            me->CastCustomSpell(target, TOS_EVENT_COMBATANT_SPELL_ID_RADIATION, &damage, nullptr, nullptr, false);

            events.RescheduleEvent(TOS_EVENT_COMBATANT_SPELL_CAST_RADIATION, 2s);
        }
    };
};

#endif // MODULE_TRIAL_OF_STRENGTH_AI_SPELL_RADIOACTIVE_H
