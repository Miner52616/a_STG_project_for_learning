#include "manager/ScriptLoader.h"
#include "core/application.h"
#include "core/LuaManager.h"
#include "packages/Resource.h"
#include "packages/YellowPage.h"
#include "manager/PhaseController.h"
#include "phases/phases/MidPhase.h"
#include "phases/phases/BossPhase.h"
#include "phases/phases/SpellPhase.h"
#include "entities/Enemy.h"
#include "behaviors/behaviors/MoveToRandom1.h"
#include "behaviors/behaviors/ScoreDrop1.h"
#include "behaviors/behaviors/AimShoot.h"
#include "behaviors/behaviors/BreezyBlossom1.h"
#include "behaviors/behaviors/BreezyBlossom2.h"
#include "behaviors/behaviors/BreezyBlossom3.h"
#include "behaviors/behaviors/BreezyBlossom4.h"
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
    Pfactory_.setResource(resource_);
}

void ScriptLoader::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
    Pfactory_.setYellowPage(yellowpage_);
}

void ScriptLoader::loadPhase(const std::string& path)
{
    lua_.loadScript(path);
    std::cout<<"-------------------------------------"<<std::endl;
    std::cout<<"Script Loading"<<std::endl;

    sol::table phasetable=lua_.lua_["phasetable"];
    int phasetablesize=phasetable.size();
    std::cout<<"phase num"<<phasetablesize<<std::endl;
    for(int i=1;i<=phasetablesize;i++)
    {
        std::cout<<"Load Phase "<<i<<std::endl;
        sol::table phasescript=phasetable[i];
        std::unique_ptr<Phase> phase=Pfactory_.buildPhase(phasescript);
        resource_->phasecontroller_.add_process(std::move(phase));
    }
    std::cout<<"Script Successfully Loaded"<<std::endl;
    std::cout<<"-------------------------------------"<<std::endl;
}

//********************************************** */

PFactory::PFactory()
{
    registerPhase("MidPhase",
        [this](const sol::table& phasescript)
        {
            std::cout<<"MidPhase"<<std::endl;
            std::unique_ptr<MidPhase> phase=std::make_unique<MidPhase>(resource_,yellowpage_,phasescript["time"]);

            sol::table enemytable=phasescript["enemytable"];
            int enemytablesize=enemytable.size();
            std::cout<<enemytablesize<<std::endl;
            for(int i=1;i<=enemytablesize;i++)
            {
                std::cout<<"Load Enemy "<<i<<std::endl;
                sol::table enemyscript=enemytable[i];
                std::unique_ptr<Enemy> enemy=Efactory_.buildEnemy(enemyscript);
                phase->add_enemy(std::move(enemy));
            }

            return std::move(phase);
        }
    );

    
    registerPhase("BossPhase",
        [this](const sol::table& phasescript)
        {
            std::cout<<"BossPhase"<<std::endl;
            std::unique_ptr<BossPhase> phase=std::make_unique<BossPhase>(resource_,yellowpage_);
            std::unique_ptr<Boss> new_boss=std::make_unique<Boss>(resource_->app_.playerTexture_,resource_);
            new_boss->setPosition({460,-50});
            phase->setBoss(std::move(new_boss));

            Boss* boss=phase->getBoss();

            sol::table spelltable=phasescript["spelltable"];
            int spelltablesize=spelltable.size();
            std::cout<<spelltablesize<<std::endl;
            for(int i=1;i<=spelltablesize;i++)
            {
                std::cout<<"Load Spell "<<i<<std::endl;
                sol::table spellscript=spelltable[i];
                std::unique_ptr<SpellPhase> spell=Sfactory_.buildSpell(boss,spellscript);
                spell->setBoss(boss);
                boss->add_phase(std::move(spell));
            }

            return std::move(phase);
        }
    );
        
}

void PFactory::registerPhase(const std::string& name,PhaseCreator creator)
{
    phaseregistry_[name]=creator;
}

void PFactory::setResource(Resource* resource)
{
    resource_=resource;
    Efactory_.setResource(resource_);
    Sfactory_.setResource(resource_);
}

void PFactory::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
    Efactory_.setYellowPage(yellowpage_);
    Sfactory_.setYellowPage(yellowpage_);
}

std::unique_ptr<Phase> PFactory::buildPhase(const sol::table& phasescript)
{
    std::unique_ptr<Phase> phase;

    std::string type=phasescript["type"];

    auto it=phaseregistry_.find(type);
    if(it!=phaseregistry_.end())
    {
        return it->second(phasescript);
    }

    std::cout <<"Unknown Phase: "<<type<<std::endl;
    std::cout<<"bug in buildPhase!"<<std::endl;
    return nullptr;
}

//*********************************************** */

void EFactory::setResource(Resource* resource)
{
    resource_=resource;
    Bfactory_.setResource(resource_);
}

void EFactory::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
    Bfactory_.setYellowPage(yellowpage_);
}

std::unique_ptr<Enemy> EFactory::buildEnemy(const sol::table& enemyscript)
{
    std::unique_ptr<Enemy> enemy=std::make_unique<Enemy>(resource_->app_.enemyTexture_);
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
        std::unique_ptr<Behavior> behavior=Bfactory_.buildBehavior(enemy.get(),behaviorscript);
        enemy->addBehavior(std::move(behavior));
    }

    return std::move(enemy);
}

/************************************************* */

void SFactory::setResource(Resource* resource)
{
    resource_=resource;
    Bfactory_.setResource(resource_);
}

void SFactory::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
    Bfactory_.setYellowPage(yellowpage_);
}

std::unique_ptr<SpellPhase> SFactory::buildSpell(Boss* boss,const sol::table& spellscript)
{
    std::unique_ptr<SpellPhase> spell=std::make_unique<SpellPhase>(resource_,yellowpage_,spellscript["time"]);
    spell->setHP(spellscript["HP"]);
    spell->setVoidSpell(spellscript["voidspell"]);

    sol::table behaviortable=spellscript["behaviortable"];
    int behaviortablesize=behaviortable.size();
    for(int i=1;i<=behaviortablesize;i++)
    {
        std::cout<<"Load Behavior "<<i<<std::endl;
        sol::table behaviorscript=behaviortable[i];
        std::unique_ptr<Behavior> behavior=Bfactory_.buildBehavior(boss,behaviorscript);
        spell->addBehavior(std::move(behavior));
    }

    return std::move(spell);
}

/************************************************* */

BFactory::BFactory()
{
    registerBehavior("MoveToRandom1",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"MoveToRandom1"<<std::endl;
            std::unique_ptr<MoveToRandom1> movetorandom1=std::make_unique<MoveToRandom1>(resource_,yellowpage_);
            movetorandom1->set_entity(enemy);
        
            return std::move(movetorandom1);
        }
    );

    registerBehavior("ScoreDrop1",
        [this](Entity* enemy,const sol::table& behaviorscript)
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
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"AimShoot1"<<std::endl;
            std::unique_ptr<AimShoot1> aimshoot1=std::make_unique<AimShoot1>(resource_,yellowpage_);
            aimshoot1->set_entity(enemy);

            return std::move(aimshoot1);
        }
    );

    registerBehavior("BreezyBlossom1",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"BreezyBlossom1"<<std::endl;
            std::unique_ptr<BreezyBlossom1> breezyblossom1=std::make_unique<BreezyBlossom1>(enemy,resource_,yellowpage_);

            return std::move(breezyblossom1);
        }
    );

    registerBehavior("BreezyBlossom2",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"BreezyBlossom2"<<std::endl;
            std::unique_ptr<BreezyBlossom2> breezyblossom2=std::make_unique<BreezyBlossom2>(enemy,resource_,yellowpage_);

            return std::move(breezyblossom2);
        }
    );

    registerBehavior("BreezyBlossom3",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"BreezyBlossom3"<<std::endl;
            std::unique_ptr<BreezyBlossom3> breezyblossom3=std::make_unique<BreezyBlossom3>(enemy,resource_,yellowpage_);

            return std::move(breezyblossom3);
        }
    );

    registerBehavior("BreezyBlossom4",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"BreezyBlossom4"<<std::endl;
            std::unique_ptr<BreezyBlossom4> breezyblossom4=std::make_unique<BreezyBlossom4>(enemy,resource_,yellowpage_);

            return std::move(breezyblossom4);
        }
    );
}

void BFactory::registerBehavior(const std::string& name,BehaviorCreator creator)
{
    behaviorregistry_[name]=creator;
}

void BFactory::setResource(Resource* resource)
{
    resource_=resource;
}

void BFactory::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
}

std::unique_ptr<Behavior> BFactory::buildBehavior(Entity* enemy,const sol::table& behaviorscript)
{
    std::string type=behaviorscript["type"];

    auto it=behaviorregistry_.find(type);
    if(it!=behaviorregistry_.end())
    {
        return it->second(enemy,behaviorscript);
    }

    std::cout << "Unknown Behavior: " << type << std::endl;
    std::cout<<"bug in buildBehavior!"<<std::endl;
    return nullptr;
}