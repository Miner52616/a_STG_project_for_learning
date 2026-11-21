#pragma once
#include "lua_packages/LuaPackages.h"
#include "lua_packages/LuaEntity.h"

class LuaDependency
{
public:
    LuaResource resource_;
    LuaEntity entity_;

public:
    LuaDependency(LuaResource resource_,LuaEntity entity_);
};