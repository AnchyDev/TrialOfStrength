#include "ToSUnitScript.h"
#include "TrialOfStrength.h"

void ToSUnitScript::OnUnitDeath(Unit* unit, Unit* /*killer*/)
{
    if (!sConfigMgr->GetOption<bool>("TrialOfStrength.Enable", false))
    {
        return;
    }

    if (!unit)
    {
        return;
    }

    if (unit->IsPlayer())
    {
        return;
    }

    if (unit->GetMapId() != TOS_MAP_ID)
    {
        return;
    }

    unit->RemoveDynamicFlag(UNIT_DYNFLAG_LOOTABLE);

    auto iScript = unit->GetInstanceScript();
    if (!iScript)
    {
        return;
    }

    iScript->SetData(TOS_DATA_ENCOUNTER_UPDATE_INVADERS, 1);
}

void ToSUnitScript::ModifySpellDamageTaken(Unit* /*target*/, Unit* attacker, int32& damage, SpellInfo const* /*spellInfo*/)
{
    if (!sConfigMgr->GetOption<bool>("TrialOfStrength.Enable", false))
    {
        return;
    }

    if (!attacker)
    {
        return;
    }

    if (attacker->IsPlayer())
    {
        return;
    }

    if (attacker->GetMapId() != TOS_MAP_ID)
    {
        return;
    }

    if (!sConfigMgr->GetOption<bool>("TrialOfStrength.AutoScaling", true))
    {
        return;
    }

    auto map = attacker->GetMap();
    if (!map)
    {
        return;
    }

    auto instance = map->ToInstanceMap();
    if (!instance)
    {
        return;
    }

    auto iScript = instance->GetInstanceScript();
    if (!iScript)
    {
        return;
    }

    uint32 originalLevel = attacker->ToCreature()->GetCreatureTemplate()->maxlevel;

    uint32 currentWave = iScript->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE);
    uint32 damageDivider = sConfigMgr->GetOption<uint32>("TrialOfStrength.AutoScaling.BaseDamage.SpellDivider", 15);

    uint32 newDamage = ((damage) * ((83 - originalLevel) / 2) / damageDivider) * currentWave;
}
