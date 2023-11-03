#include "ToSPlayerScript.h"

#include "TrialOfStrength.h"
#include "ToSMapMgr.h"

#include "Chat.h"

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

bool ToSPlayerScript::OnBeforeTeleport(Player* player, uint32 mapId, float /*x*/, float /*y*/, float /*z*/, float /*orientation*/, uint32 /*options*/, Unit* /*target*/)
{
    if (!player)
    {
        return true;
    }

    if (!sToSMapMgr->CanPlayerEnter(player) && mapId == TOS_MAP_ID)
    {
        ChatHandler(player->GetSession()).SendSysMessage("|cffFF0000You do not meet the requirements to enter the Trial of Strength.|r");
        return false;
    }

    auto oldMapId = player->GetMapId();
    if (oldMapId != TOS_MAP_ID)
    {
        return true;
    }

    if (mapId == TOS_MAP_ID)
    {
        return true;
    }

    sToSMapMgr->ClearCurses(player);

    return true;
}

void ToSPlayerScript::OnLogin(Player* player)
{
    if (!player)
    {
        return;
    }

    sToSMapMgr->ClearCurses(player);
}
