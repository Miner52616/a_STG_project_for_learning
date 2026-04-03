#pragma once
#include "phases/Phase.h"
#include <sol/sol.hpp>

class LuaManager;
class Resource;
class YellowPage;
class MidPhase;
class Enemy;
class Behavior;

class PEBFactory
{
private:
    Resource* resource_;
    YellowPage* yellowpage_;
    

public:
    using BehaviorCreator=std::function<std::unique_ptr<Behavior>(Enemy*, sol::table)>;
private:
    std::unordered_map<std::string, BehaviorCreator> registry_;
public:
    PEBFactory();
    void registerBehavior(const std::string& name, BehaviorCreator creator);
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    std::unique_ptr<MidPhase> createMidPhase(const sol::table& phasescript);
    std::unique_ptr<Enemy> createEnemy(const sol::table& enemyscript);
    std::unique_ptr<Behavior> createBehavior(Enemy* enemy,const sol::table& behaviorscript);
    //std::unique_ptr<Behavior> createBehavior(const sol::table& behaviorscript);
};

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
    std::unique_ptr<Behavior> buildBehavior(Enemy* enemy,const sol::table& behaviorscript);

public:
    ScriptLoader(LuaManager& lua);
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    std::unique_ptr<Phase> buildPhase(const sol::table& phasescript);
    void loadPhase(const std::string& path);
}; 