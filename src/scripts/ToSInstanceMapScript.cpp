#include "ToSInstanceMapScript.h"
#include "ToSInstanceScript.h"

InstanceScript* ToSInstanceMapScript::GetInstanceScript(InstanceMap* map) const
{
    return new ToSInstanceScript(map);
}
