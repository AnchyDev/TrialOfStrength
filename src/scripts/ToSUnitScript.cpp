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

    auto iScript = unit->GetInstanceScript();
    if (!iScript)
    {
        return;
    }

    iScript->SetData(TOS_DATA_ENCOUNTER_UPDATE_INVADERS, 1);
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

    uint32 baseDamage = sConfigMgr->GetOption<uint32>("TrialOfStrength.Scaling.BaseDamage.Physical", 500);
    uint32 damageDivider = sConfigMgr->GetOption<uint32>("TrialOfStrength.Scaling.BaseDamage.PhysicalDivider", 15);;

    uint32 newDamage = baseDamage * (1.0f + (float(currentWave) / float(damageDivider)));

    damage = urand(newDamage / 2, newDamage);
}

void ToSUnitScript::ModifySpellDamageTaken(Unit* /*target*/, Unit* attacker, int32& damage, SpellInfo const* /*spellInfo*/)
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

    uint32 baseDamage = sConfigMgr->GetOption<uint32>("TrialOfStrength.Scaling.BaseDamage.Spell", 2000);
    uint32 damageDivider = sConfigMgr->GetOption<uint32>("TrialOfStrength.Scaling.BaseDamage.SpellDivider", 15);;

    uint32 newDamage = baseDamage * (1.0f + (float(currentWave) / float(damageDivider)));

    damage = urand(newDamage / 2, newDamage);
}
