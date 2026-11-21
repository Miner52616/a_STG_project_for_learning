#include "core/LuaBindings.h"
#include "core/Clock.h"

void registerClockBindings(sol::state& lua)
{
    lua.new_usertype<Clock>
    (
        "Clock",
        sol::no_constructor,
        "count",&Clock::count,
        "reset",&Clock::reset,
        "set_ready",&Clock::set_ready,
        "get_condition",&Clock::get_condition,
        "get_target",&Clock::get_target,
        "set_target",&Clock::set_target
    );
}