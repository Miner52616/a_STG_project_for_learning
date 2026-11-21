#pragma once
#include <sol/sol.hpp>

void registerSFMLBindings(sol::state& lua);
void registerClockBindings(sol::state& lua);
void registerAssetsResourceBindings(sol::state& lua);
void registerBulletConfigBindings(sol::state& lua);
void registerEffectConfigBindings(sol::state& lua);
void registerBatchConfigBindings(sol::state& lua);
void registerLuaPackageBindings(sol::state& lua);