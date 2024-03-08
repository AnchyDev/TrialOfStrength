#include "ToSUnitScript.h"
#include "TrialOfStrength.h"

void ToSUnitScript::OnUnitDeath(Unit* unit, Unit* /*killer*/)
{
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
}

void ToSUnitScript::ModifyMeleeDamage(Unit* /*target*/, Unit* attacker, uint32& damage)
{
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

    uint32 currentWave = iScript->GetData(TOS_DATA_ENCOUNTER_CURRENT_WAVE);

    uint32 baseDamage = 500;
    uint32 damageDivider = 15;

    uint32 newDamage = baseDamage * (1.0f + (float(currentWave) / float(damageDivider)));

    damage = urand(newDamage / 2, newDamage);
}
