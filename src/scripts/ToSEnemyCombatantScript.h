#ifndef MODULE_TRIAL_OF_STRENGTH_ENEMY_COMBATANT_H
#define MODULE_TRIAL_OF_STRENGTH_ENEMY_COMBATANT_H

#include "ScriptMgr.h"

class ToSEnemyCombatantScript : public CreatureScript
{
public:
    ToSEnemyCombatantScript() : CreatureScript("ToSEnemyCombatantScript") { }

    virtual CreatureAI* GetAI(Creature* creature) const
    {
        return new ToSEnemyCombatantAI(creature);
    }

    struct ToSEnemyCombatantAI : public CombatAI
    {
        enum CombatantEvents
        {
            TOS_EVENT_COMBATANT_DO_FISTING = 1
        };

        EventMap events;

        bool startFisting;
        bool roidRaging;
        bool takeThis;

        ToSEnemyCombatantAI(Creature* creature) : CombatAI(creature)
        {
            events.Reset();

            startFisting = false;
            roidRaging = false;
            takeThis = false;
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            switch (events.ExecuteEvent())
            {
            case TOS_EVENT_COMBATANT_DO_FISTING:
                TryFisting();

                events.RescheduleEvent(TOS_EVENT_COMBATANT_DO_FISTING, 3s);
                break;
            }

            if (me->GetHealthPct() < 66 && !startFisting)
            {
                startFisting = true;

                me->Yell("They call me mister fister.", LANG_UNIVERSAL);

                events.ScheduleEvent(TOS_EVENT_COMBATANT_DO_FISTING, 1s);
            }

            if (me->GetHealthPct() < 33 && !roidRaging)
            {
                me->AddAura(68335 /* Enrage */, me);

                me->Yell("I'm gonna beat your dick!", LANG_UNIVERSAL);

                roidRaging = true;
            }

            DoMeleeAttackIfReady();
        }

        void TryFisting()
        {
            auto creature = me->GetVictim();
            if (!creature)
            {
                return;
            }

            me->CastSpell(creature, 29581 /* Punch */);

            if (!takeThis)
            {
                me->Yell("Take this!", LANG_UNIVERSAL);
                takeThis = true;
            }
            else
            {
                auto rand = urand(1, 8);
                switch (rand)
                {
                case 1:
                    me->Yell("POW!", LANG_UNIVERSAL);
                    break;

                case 2:
                    me->Yell("WHAM!", LANG_UNIVERSAL);
                    break;

                case 3:
                    me->Yell("SMACK!", LANG_UNIVERSAL);
                    break;

                case 4:
                    me->Yell("BAM!", LANG_UNIVERSAL);
                    break;

                default:
                    // Do nothing to prevent spam
                    break;
                }
            }
        }

        void JustEngagedWith(Unit* who) override
        {
            me->Yell("What the fuck did you say about me you little bitch?", LANG_UNIVERSAL);
        }

        void JustDied(Unit* killer) override
        {
            me->Yell("Ah fuck, I can't believe you've done this..", LANG_UNIVERSAL);
        }
    };
};

#endif // MODULE_TRIAL_OF_STRENGTH_ENEMY_COMBATANT_H
