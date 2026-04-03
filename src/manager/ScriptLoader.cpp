#include "manager/ScriptLoader.h"
#include "core/application.h"
#include "core/LuaManager.h"
#include "packages/Resource.h"
#include "packages/YellowPage.h"
#include "manager/PhaseController.h"
#include "phases/phases/MidPhase.h"
#include "entities/Enemy.h"
#include "behaviors/behaviors/MoveToRandom1.h"
#include "behaviors/behaviors/ScoreDrop1.h"
#include "behaviors/behaviors/AimShoot.h"
#include <iostream>
#include <sol/sol.hpp>

ScriptLoader::ScriptLoader(LuaManager& lua):
    lua_(lua)
{
    ;
}

void ScriptLoader::setResource(Resource* resource)
{
    resource_=resource;
    PEBfactory_.setResource(resource_);
}

void ScriptLoader::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
    PEBfactory_.setYellowPage(yellowpage_);
}

void ScriptLoader::loadPhase(const std::string& path)
{
    lua_.loadScript(path);
    std::cout<<"-------------------------------------"<<std::endl;
    std::cout<<"Script Loading"<<std::endl;

    sol::table phasetable=lua_.lua_["phasetable"];
    int phasetablesize=phasetable.size();
    std::cout<<phasetablesize<<std::endl;
    for(int i=1;i<=phasetablesize;i++)
    {
        std::cout<<"Load Phase "<<i<<std::endl;
        sol::table phasescript=phasetable[i];
        std::unique_ptr<Phase> phase=buildPhase(phasescript);
        resource_->phasecontroller_.add_process(std::move(phase));
    }
    std::cout<<"Script Successfully Loaded"<<std::endl;
    std::cout<<"-------------------------------------"<<std::endl;
}

std::unique_ptr<Phase> ScriptLoader::buildPhase(const sol::table& phasescript)
{
    //lua_.loadScript(path);
    std::unique_ptr<Phase> phase;

    std::string type=phasescript["type"];
    if(type=="MidPhase")
    {
        std::cout<<"MidPhase"<<std::endl;
        std::unique_ptr<MidPhase> midphase=buildMidPhase(phasescript);
        phase=std::move(midphase);
        return std::move(phase);
    }

    std::cout<<"bug in loadPhase"<<std::endl;
    return std::move(phase);
}

std::unique_ptr<MidPhase> ScriptLoader::buildMidPhase(const sol::table& phasescript)
{
    std::unique_ptr<MidPhase> phase=PEBfactory_.createMidPhase(phasescript);

    sol::table enemytable=phasescript["enemytable"];
    int enemytablesize=enemytable.size();
    std::cout<<enemytablesize<<std::endl;
    for(int i=1;i<=enemytablesize;i++)
    {
        std::cout<<"Load Enemy "<<i<<std::endl;
        sol::table enemyscript=enemytable[i];
        std::unique_ptr<Enemy> enemy=buildEnemy(enemyscript);
        phase->add_enemy(std::move(enemy));
    }

    return std::move(phase);
}

std::unique_ptr<Enemy> ScriptLoader::buildEnemy(const sol::table& enemyscript)
{
    std::unique_ptr<Enemy> enemy=PEBfactory_.createEnemy(enemyscript);
    float x=enemyscript["x"];
    float y=enemyscript["y"];
    enemy->setPosition({x,y});
    enemy->setHP(enemyscript["HP"]);
    enemy->set_start_end(enemyscript["start"],enemyscript["End"]);

    sol::table behaviortable=enemyscript["behaviortable"];
    int behaviortablesize=behaviortable.size();
    std::cout<<behaviortablesize<<std::endl;
    for(int i=1;i<=behaviortablesize;i++)
    {
        std::cout<<"Load Behavior "<<i<<std::endl;
        sol::table behaviorscript=behaviortable[i];
        std::unique_ptr<Behavior> behavior=buildBehavior(enemy.get(),behaviorscript);
        enemy->addBehavior(std::move(behavior));
    }

    return std::move(enemy);
}

std::unique_ptr<Behavior> ScriptLoader::buildBehavior(Enemy* enemy,const sol::table& behaviorscript)
{
    std::unique_ptr<Behavior> behavior;

    behavior=PEBfactory_.createBehavior(enemy,behaviorscript);
    return std::move(behavior);
}

//**********************************************
//以下为PEBFactory
//***********************************************
PEBFactory::PEBFactory()
{
    registerBehavior("MoveToRandom1",
        [this](Enemy* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"MoveToRandom1"<<std::endl;
            std::unique_ptr<MoveToRandom1> movetorandom1=std::make_unique<MoveToRandom1>(resource_,yellowpage_);
            movetorandom1->set_entity(enemy);
        
            return std::move(movetorandom1);
        }
    );

    registerBehavior("ScoreDrop1",
        [this](Enemy* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"ScoreDrop1"<<std::endl;
            std::unique_ptr<ScoreDrop1> scoredrop1=std::make_unique<ScoreDrop1>(resource_,yellowpage_);
            scoredrop1->set_entity(enemy);

            sol::table dropconfig=behaviorscript["dropconfig"];
            std::string droptype=dropconfig["droptype"];
            int dropnum=dropconfig["dropnum"];
            if(droptype=="Score")
            {
                scoredrop1->setDropConfig(DropType::Score,dropnum);
            }
            if(droptype=="Power")
            {
                scoredrop1->setDropConfig(DropType::Power,dropnum);
            }

            return std::move(scoredrop1);
        }
    );

    registerBehavior("AimShoot1",
        [this](Enemy* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"AimShoot1"<<std::endl;
            std::unique_ptr<AimShoot1> aimshoot1=std::make_unique<AimShoot1>(resource_,yellowpage_);
            aimshoot1->set_entity(enemy);

            return std::move(aimshoot1);
        }
    );
}

void PEBFactory::registerBehavior(const std::string& name, BehaviorCreator creator)
{
    registry_[name]=creator;
}

void PEBFactory::setResource(Resource* resource)
{
    resource_=resource;
}
void PEBFactory::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
}

std::unique_ptr<Behavior> PEBFactory::createBehavior(Enemy* enemy, const sol::table& behaviorscript)
{
    std::string type=behaviorscript["type"];

    auto it = registry_.find(type);
    if (it != registry_.end())
    {
        return it->second(enemy,behaviorscript);
    }

    std::cout << "Unknown Behavior: " << type << std::endl;
    std::cout<<"bug in buildBehavior!"<<std::endl;
    return NULL;
}

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

/*
std::unique_ptr<Behavior> PEBFactory::createBehavior(const sol::table& behaviorscript)
{
    std::unique_ptr<Behavior> behavior;
    
    return std::move(behavior); 
}
    */