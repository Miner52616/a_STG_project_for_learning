#include "core/LuaBindings.h"
#include "packages/BatchConfig.h"

void registerBatchConfigBindings(sol::state& lua)
{
    lua.new_usertype<BatchConfig>
    (
        "BatchConfig",
        sol::constructors<BatchConfig()>(),
        "target_time_",&BatchConfig::target_time_,
        "target_time2_",&BatchConfig::target_time2_,
        "target_time3_",&BatchConfig::target_time3_
    );
}