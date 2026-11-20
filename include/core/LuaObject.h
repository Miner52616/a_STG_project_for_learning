#pragma once
#include <sol/sol.hpp>
#include "packages/LuaBulletContext.h"

class LuaFunction
{
private:
    sol::table instance_;

public:
    LuaFunction(sol::state& lua,const std::string& path,LuaBulletContext* context);
    void function();
};