#ifndef MODULE_TRIAL_OF_STRENGTH_PLAYER_SCRIPT_H
#define MODULE_TRIAL_OF_STRENGTH_PLAYER_SCRIPT_H

#include "ScriptMgr.h"

#include "Player.h"

class ToSPlayerScript : public PlayerScript
{
public:
    ToSPlayerScript() : PlayerScript("ToSPlayerScript") { }

    bool CanRepopAtGraveyard(Player* /*player*/) override;
};

#endif // MODULE_TRIAL_OF_STRENGTH_PLAYER_SCRIPT_H
