#ifndef MODULE_TRIAL_OF_STRENGTH_HELPER_H
#define MODULE_TRIAL_OF_STRENGTH_HELPER_H

Creature* SpawnNPC(uint32 entry, Map* map, Position* position)
{
    if (!map || !position)
    {
        return nullptr;
    }

    if (!sObjectMgr->GetCreatureTemplate(entry))
    {
        return nullptr;
    }

    return map->SummonCreature(entry, *position);
}

#endif // MODULE_TRIAL_OF_STRENGTH_HELPER_H
