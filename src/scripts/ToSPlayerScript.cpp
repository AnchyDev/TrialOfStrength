#include "ToSPlayerScript.h"

#include "TrialOfStrength.h"

bool ToSPlayerScript::CanRepopAtGraveyard(Player* player)
{
    if (!player)
    {
        return true;
    }

    if (player->GetMapId() != TOS_MAP_ID)
    {
        return true;
    }

    player->TeleportTo(TOS_MAP_ID, 176.724, -116.484, 18.677, 4.732);

    if (player->isDead())
    {
        player->ResurrectPlayer(100, false);

        if (player->HasCorpse())
        {
            player->RemoveCorpse();
        }
    }

    return false;
}
