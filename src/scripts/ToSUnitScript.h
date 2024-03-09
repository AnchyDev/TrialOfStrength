#ifndef MODULE_TRIAL_OF_STRENGTH_UNIT_SCRIPT_H
#define MODULE_TRIAL_OF_STRENGTH_UNIT_SCRIPT_H

#include "ScriptMgr.h"

#include "Player.h"

class ToSUnitScript : public UnitScript
{
public:
    ToSUnitScript() : UnitScript("ToSUnitScript") { }

    void OnUnitDeath(Unit* /*unit*/, Unit* /*killer*/) override;

    void ModifySpellDamageTaken(Unit* /*target*/, Unit* /*attacker*/, int32& /*damage*/, SpellInfo const* /*spellInfo*/) override;
};

#endif // MODULE_TRIAL_OF_STRENGTH_UNIT_SCRIPT_H
