#ifndef MODULE_TRIAL_OF_STRENGTH_HELPER_H
#define MODULE_TRIAL_OF_STRENGTH_HELPER_H

Creature* SpawnNPC(Map* map, uint32 entry)
{
    if (!map)
    {
        return nullptr;
    }

    Position* pos = new Position(301.269, -99.976, 30.823, 3.146);
    auto creature = map->SummonCreature(entry, *pos);

    return creature;
}

#endif // MODULE_TRIAL_OF_STRENGTH_HELPER_H
