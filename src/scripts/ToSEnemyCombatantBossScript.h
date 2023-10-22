#ifndef MODULE_TRIAL_OF_STRENGTH_ENEMY_COMBATANT_BOSS_H
#define MODULE_TRIAL_OF_STRENGTH_ENEMY_COMBATANT_BOSS_H

#include "ScriptMgr.h"

class ToSEnemyCombatantBossScript : public CreatureScript
{
public:
    ToSEnemyCombatantBossScript() : CreatureScript("ToSEnemyCombatantBossScript") { }

    virtual CreatureAI* GetAI(Creature* creature) const
    {
        return new ToSEnemyCombatantBossAI(creature);
    }

    struct ToSEnemyCombatantBossAI : public CombatAI
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

        ToSEnemyCombatantBossAI(Creature* creature) : CombatAI(creature)
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

            auto rand = urand(0, 3);
            switch (rand)
            {
            case 0:
                me->Yell("I will show you real strength!", LANG_UNIVERSAL);
                break;

            case 1:
                me->Yell("I was just warming up!", LANG_UNIVERSAL);
                break;

            case 2:
                me->Yell("I am going to pound you into the dirt.", LANG_UNIVERSAL);
                break;

            case 3:
                me->Yell("Am I a joke to you?", LANG_UNIVERSAL);
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
            auto rand = urand(0, 3);
            std::string message;

            switch (rand)
            {
            case 0:
                message = "You may have bested my constituents, but you havent fought me yet.";
                break;

            case 1:
                message = "You will pay for your bloodshed.";
                break;

            case 2:
                message = "Now the real challenge begins.";
                break;

            case 3:
                message = "What time is it? Pounding time.";
                break;

            default:
                return;
            }

            me->Yell(message, LANG_UNIVERSAL);
        }

        void JustDied(Unit* /*killer*/) override
        {
            auto rand = urand(0, 3);
            std::string message;

            switch (rand)
            {
            case 0:
                message = "You are stronger.. than you appear..";
                break;

            case 1:
                message = "This isn't how it was supposed to go..";
                break;

            case 2:
                message = "Who are you?..";
                break;

            case 3:
                message = "Ugh..";
                break;

            default:
                return;
            }

            me->Yell(message, LANG_UNIVERSAL);
        }
    };
};

#endif // MODULE_TRIAL_OF_STRENGTH_ENEMY_COMBATANT_BOSS_H
