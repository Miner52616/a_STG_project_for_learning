#include "core/LuaBindings.h"
#include "lua_packages/LuaPackages.h"
#include "lua_packages/LuaEntity.h"
#include "lua_packages/LuaBatch.h"
#include "packages/LuaDependency.h"
#include "packages/AssetsResource.h"

void registerLuaPackageBindings(sol::state& lua)
{
    lua.new_usertype<LuaResource>
    (
        "Resource",
        "addBullet",&LuaResource::addBullet,
        "addBatch",&LuaResource::addBatch,
        "getAssetResource",&LuaResource::getAssetsResource
    );

    lua.new_usertype<LuaEntity>
    (
        "Entity",
        "getPosition",&LuaEntity::getPosition
    );

    lua.new_usertype<LuaBatch>
    (
        "LuaBatch",
        "bundle_config",&LuaBatch::bundle_config,
        "set_add_finished",&LuaBatch::set_add_finished
    );

    lua.new_usertype<LuaDependency>
    (
        "LuaDependency",
        //sol::constructors<LuaDependency(LuaResource,LuaEntity)>(),
        "resource_",&LuaDependency::resource_,
        "entity_",&LuaDependency::entity_
    );
}