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
        createMidPhase();
    }
}

std::unique_ptr<MidPhase> ScriptLoader::createMidPhase()
{
    sol::table phasescript=lua_.lua_["phase"];

    std::unique_ptr<MidPhase> phase=std::make_unique<MidPhase>(resource_,yellowpage_,phasescript["time"]);

    sol::table enemytable=phasescript["enemytable"];
    int enemytablesize=enemytable.size();
    for(int i=1;i<=enemytablesize;i++)
    {
        sol::table enemyscript=enemytable[i];
        std::unique_ptr<Enemy> enemy=std::make_unique<Enemy>(resource_->app_.enemyTexture_);
        enemy->setPosition({(float)enemyscript["x"],(float)enemyscript["y"]});
        enemy->setHP(enemyscript["HP"]);
        enemy->set_start_end(enemyscript["start"],enemyscript["end"]);
        
        sol::table behaviortable=enemyscript["behaviortable"];
        int behaviortablesize=behaviortable.size();
        for(int j=1;j<=behaviortablesize;j++)
        {
            ;
        }
        
    }
}