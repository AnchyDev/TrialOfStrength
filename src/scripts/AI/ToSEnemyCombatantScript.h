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
            TOS_EVENT_COMBATANT_START_PUNCHING = 1,
            TOS_EVENT_COMBATANT_AURA_ANGRY = 68335, /* Enrage */
            TOS_EVENT_COMBATANT_SPELL_PUNCH = 29581,
        };

        EventMap events;

        bool isPunching;
        bool isAngry;

        ToSEnemyCombatantAI(Creature* creature) : CombatAI(creature)
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

            auto rand = urand(0, 8);
            switch (rand)
            {
            case 1:
                me->Yell("Not bad, I'm all fired up now!", LANG_UNIVERSAL);
                break;

            case 2:
                me->Yell("Now you're getting me angry..", LANG_UNIVERSAL);
                break;

            case 3:
                me->Yell("It's going to be like that is it?", LANG_UNIVERSAL);
                break;

            case 4:
                me->Yell("Now I'm going to get serious!", LANG_UNIVERSAL);
                break;

            default:
                return;
            }
        }

        void TryPunching()
        {
            auto creature = me->GetVictim();
            if (!creature)
            {
                return;
            }

            me->CastSpell(creature, TOS_EVENT_COMBATANT_SPELL_PUNCH);
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            auto rand = urand(0, 6);
            std::string message;

            switch (rand)
            {
            case 0:
                message = "In the arena of champions, only the strong survive. Let's see if you have what it takes to be a legend!";
                break;

            case 1:
                message = "I will test your mettle in the crucible of combat. Show me your strength!";
                break;

            case 2:
                message = "Your feeble attempts amuse me. Do you truly believe you can best me in combat?";
                break;

            case 3:
                message = "You dare challenge me, mortal? Prepare to face the might of a true warrior!";
                break;

            default:
                return;
            }

            me->Yell(message, LANG_UNIVERSAL);
        }

        void JustDied(Unit* /*killer*/) override
        {
            auto rand = urand(0, 6);
            std::string message;

            switch (rand)
            {
            case 0:
                message = "It's not fair..";
                break;

            case 1:
                message = "I will see you in the next life..";
                break;

            case 2:
                message = "Ughh.. agh...";
                break;

            case 3:
                message = "I don't understand.. I thought..";
                break;

            default:
                return;
            }

            me->Yell(message, LANG_UNIVERSAL);
        }
    };
};

#endif // MODULE_TRIAL_OF_STRENGTH_ENEMY_COMBATANT_H
