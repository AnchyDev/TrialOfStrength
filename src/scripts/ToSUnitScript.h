#ifndef MODULE_TRIAL_OF_STRENGTH_UNIT_SCRIPT_H
#define MODULE_TRIAL_OF_STRENGTH_UNIT_SCRIPT_H

#include "ScriptMgr.h"

#include "Player.h"

class ToSUnitScript : public UnitScript
{
public:
    ToSUnitScript() : UnitScript("ToSUnitScript") { }

    void OnUnitDeath(Unit* /*unit*/, Unit* /*killer*/) override;

    void ModifyMeleeDamage(Unit* /*target*/, Unit* /*attacker*/, uint32& /*damage*/) override;
};

#endif // MODULE_TRIAL_OF_STRENGTH_UNIT_SCRIPT_H
