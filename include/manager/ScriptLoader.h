#pragma once
#include "core/LuaManager.h"
#include "phases/Phase.h"

class Resource;
class YellowPage;
class MidPhase;
class Enemy;
class Behavior;

class ScriptLoader
{
private:
    LuaManager& lua_;
    Resource* resource_;
    YellowPage* yellowpage_;
    PEBFactory PEBfactory_;

private:
    std::unique_ptr<MidPhase> buildMidPhase(const sol::table& phasescript);
    std::unique_ptr<Enemy> buildEnemy(const sol::table& enemyscript);
    std::unique_ptr<Behavior> buildBehavior(const sol::table& behaviorscript);

public:
    ScriptLoader(LuaManager& lua,Resource* resource,YellowPage* yellowpage);
    std::unique_ptr<Phase> loadPhase(const std::string& path);
};

class PEBFactory
{
private:
    Resource* resource_;
    YellowPage* yellowpage_;

public:
    std::unique_ptr<MidPhase> createMidPhase(const sol::table& phasescript);
    std::unique_ptr<Enemy> createEnemy(const sol::table& enemyscript);
    std::unique_ptr<Behavior> createBehavior(const sol::table& behaviorscript);

};