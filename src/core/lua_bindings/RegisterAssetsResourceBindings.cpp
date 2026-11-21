#include "core/LuaBindings.h"
#include "packages/AssetsResource.h"

void registerAssetsResourceBindings(sol::state& lua)
{
    lua.new_usertype<AssetsResource>
    (
        "AssetsResource",
        sol::no_constructor,
        "bulletsheetTexture_",&AssetsResource::bulletsheetTexture_,
        "bulletsheetTexture2_",&AssetsResource::bulletsheetTexture2_,
        "effectsheetTexture_",&AssetsResource::effectsheetTexture_,
        "playersheetTexture_",&AssetsResource::playersheetTexture_
    );
}