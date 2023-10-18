#ifndef MODULE_TRIAL_OF_STRENGTH_INSTANCE_MAP_SCRIPT_H
#define MODULE_TRIAL_OF_STRENGTH_INSTANCE_MAP_SCRIPT_H

#include "ScriptMgr.h"

class ToSInstanceMapScript : public InstanceMapScript
{
public:
    ToSInstanceMapScript() : InstanceMapScript("instance_trial_of_strength", 44) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override;
};

#endif // MODULE_TRIAL_OF_STRENGTH_INSTANCE_MAP_SCRIPT_H
