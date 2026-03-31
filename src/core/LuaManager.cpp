#include "core/LuaManager.h"

LuaManager::LuaManager()
{
    lua_.open_libraries
    (
        sol::lib::base,
        sol::lib::package,
        sol::lib::math,
        sol::lib::table
    );

}

void LuaManager::loadScript(const std::string& path)
{
    lua_.script_file(path);
}