#include "manager/ScriptLoader.h"
#include "core/application.h"
#include "packages/Resource.h"
#include "packages/YellowPage.h"
#include "phases/phases/MidPhase.h"
#include "entities/Enemy.h"
#include <iostream>
#include <sol/sol.hpp>

ScriptLoader::ScriptLoader(LuaManager& lua,Resource* resource,YellowPage* yellowpage):
lua_(lua),resource_(resource),yellowpage_(yellowpage)
{
    ;
}

std::unique_ptr<Phase> ScriptLoader::loadPhase(const std::string& path)
{
    lua_.loadScript(path);

    sol::table phasescript=lua_.lua_["phase"];

    std::string type=phasescript["type"];

    if(type=="MidPhase")
    {
        std::unique_ptr<MidPhase> phase=buildMidPhase(phasescript);
        return std::move(phase);
    }
}

std::unique_ptr<MidPhase> ScriptLoader::buildMidPhase(const sol::table& phasescript)
{
    std::unique_ptr<MidPhase> phase=PEBfactory_.createMidPhase(phasescript);

    sol::table enemytable=phasescript["enemytable"];
    int enemytablesize=enemytable.size();
    for(int i=1;i<=enemytablesize;i++)
    {
        sol::table enemyscript=enemytable[i];
        std::unique_ptr<Enemy> enemy=buildEnemy(enemyscript);
    }

    return std::move(phase);
}

std::unique_ptr<Enemy> ScriptLoader::buildEnemy(const sol::table& enemyscript)
{
    std::unique_ptr<Enemy> enemy=PEBfactory_.createEnemy(enemyscript);
    enemy->setPosition({(float)enemyscript["x"],(float)enemyscript["y"]});
    enemy->setHP(enemyscript["HP"]);
    enemy->set_start_end(enemyscript["start"],enemyscript["end"]);

    sol::table behaviortable=enemyscript["behaviortable"];
    int behaviortablesize=behaviortable.size();
    for(int i=1;i<=behaviortablesize;i++)
    {
        sol::table behaviorscript=behaviortable[i];
        std::unique_ptr<Behavior> behavior=buildBehavior(behaviorscript);
    }

    return std::move(enemy);
}

std::unique_ptr<Behavior> ScriptLoader::buildBehavior(const sol::table& behaviorscript)
{
    std::unique_ptr<Behavior> behavior=PEBfactory_.createBehavior(behaviorscript);


    return std::move(behavior);
}

//**********************************************
//以下为PEBFactory
//***********************************************

std::unique_ptr<MidPhase> PEBFactory::createMidPhase(const sol::table& phasescript)
{
    std::unique_ptr<MidPhase> phase=std::make_unique<MidPhase>(resource_,yellowpage_,phasescript["time"]);
    return std::move(phase);
}

std::unique_ptr<Enemy> PEBFactory::createEnemy(const sol::table& enemyscript)
{
    std::unique_ptr<Enemy> enemy=std::make_unique<Enemy>(resource_->app_.enemyTexture_);
    return std::move(enemy);
}

std::unique_ptr<Behavior> PEBFactory::createBehavior(const sol::table& behaviorscript)
{
    std::unique_ptr<Behavior> behavior;
    
    return std::move(behavior); 
}