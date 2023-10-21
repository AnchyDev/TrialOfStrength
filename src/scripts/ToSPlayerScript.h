#ifndef MODULE_TRIAL_OF_STRENGTH_PLAYER_SCRIPT_H
#define MODULE_TRIAL_OF_STRENGTH_PLAYER_SCRIPT_H

#include "ScriptMgr.h"

#include "Player.h"

class ToSPlayerScript : public PlayerScript
{
public:
    ToSPlayerScript() : PlayerScript("ToSPlayerScript") { }

    bool CanRepopAtGraveyard(Player* /*player*/) override;
    bool OnBeforeTeleport(Player* /*player*/, uint32 /*mapId*/, float /*x*/, float /*y*/, float /*z*/, float /*orientation*/, uint32 /*options*/, Unit* /*target*/) override;
    void OnLogin(Player* /*player*/) override;
};

#endif // MODULE_TRIAL_OF_STRENGTH_PLAYER_SCRIPT_H
