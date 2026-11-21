#pragma once
#include <sol/sol.hpp>

class LuaDependency;

class LuaFunction
{
private:
    sol::table instance_;

public:
    LuaFunction(sol::state& lua,const std::string& path,LuaDependency dependency);
    void function();
};