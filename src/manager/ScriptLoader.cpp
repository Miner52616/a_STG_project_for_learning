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
#include "behaviors/behaviors/Move.h"
#include "behaviors/behaviors/ScoreDrop1.h"
#include "behaviors/behaviors/AimShoot.h"
#include "behaviors/behaviors/NonSpell1.h"
#include "behaviors/behaviors/NonSpell2.h"
#include "behaviors/behaviors/NonSpell3.h"
#include "behaviors/behaviors/NewNonSpell1.h"
#include "behaviors/behaviors/SuddenRain.h"
#include "behaviors/behaviors/TheStorm.h"
#include "behaviors/behaviors/StarRite.h"
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
    std::cout<<"phase num "<<phasetablesize<<std::endl;
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
            std::cout<<"    MidPhase"<<std::endl;
            std::unique_ptr<MidPhase> phase=std::make_unique<MidPhase>(resource_,yellowpage_,phasescript["time"]);

            sol::table enemytable=phasescript["enemytable"];
            int enemytablesize=enemytable.size();
            std::cout<<"    enemy num "<<enemytablesize<<std::endl;
            for(int i=1;i<=enemytablesize;i++)
            {
                std::cout<<"    Load Enemy "<<i<<std::endl;
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
            std::cout<<"    BossPhase"<<std::endl;
            std::unique_ptr<BossPhase> phase=std::make_unique<BossPhase>(resource_,yellowpage_);
            std::unique_ptr<Boss> new_boss=std::make_unique<Boss>(resource_->app_.playerTexture_,resource_);
            new_boss->setPosition({460,-50});
            phase->setBoss(std::move(new_boss));

            Boss* boss=phase->getBoss();

            sol::table spelltable=phasescript["spelltable"];
            int spelltablesize=spelltable.size();
            std::cout<<"    spell num "<<spelltablesize<<std::endl;
            for(int i=1;i<=spelltablesize;i++)
            {
                std::cout<<"    Load Spell "<<i<<std::endl;
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
    std::cout<<"        behavior num "<<behaviortablesize<<std::endl;
    for(int i=1;i<=behaviortablesize;i++)
    {
        std::cout<<"        Load Behavior "<<i<<std::endl;
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
    spell->setBossName_SpellNum(spellscript["bossname"],spellscript["spellnum"]);
    spell->setTextName(spellscript["spellname"]);
    float x=spellscript["name_x"];
    float y=spellscript["name_y"];
    spell->setTextPosition(sf::Vector2f{x,y});
    spell->setHP(spellscript["HP"]);
    spell->setVoidSpell(spellscript["voidspell"]);
    spell->setSpellCard(spellscript["spellcard"]);

    sol::table behaviortable=spellscript["behaviortable"];
    int behaviortablesize=behaviortable.size();
    for(int i=1;i<=behaviortablesize;i++)
    {
        std::cout<<"        Load Behavior "<<i<<std::endl;
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
            std::cout<<"            MoveToRandom1"<<std::endl;
            std::unique_ptr<MoveToRandom1> movetorandom1=std::make_unique<MoveToRandom1>(resource_,yellowpage_);
            movetorandom1->set_entity(enemy);
            int start=behaviorscript["start_time"];
            movetorandom1->set_start(start);
        
            return std::move(movetorandom1);
        }
    );

    registerBehavior("MoveTo",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            MoveTo"<<std::endl;
            std::unique_ptr<MoveTo> moveto=std::make_unique<MoveTo>(enemy,resource_,yellowpage_);
            float v=behaviorscript["v"];
            moveto->setV(v);
            float x=behaviorscript["x"];
            float y=behaviorscript["y"];
            sf::Vector2f position={x,y};
            moveto->setTargetPosition(position);

            return std::move(moveto);
        }
    );

    registerBehavior("ScoreDrop1",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            ScoreDrop1"<<std::endl;
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
            std::cout<<"            AimShoot1"<<std::endl;
            std::unique_ptr<AimShoot1> aimshoot1=std::make_unique<AimShoot1>(resource_,yellowpage_);
            aimshoot1->set_entity(enemy);

            return std::move(aimshoot1);
        }
    );

    registerBehavior("BreezyBlossom1",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            BreezyBlossom1"<<std::endl;
            std::unique_ptr<BreezyBlossom1> breezyblossom1=std::make_unique<BreezyBlossom1>(enemy,resource_,yellowpage_);

            return std::move(breezyblossom1);
        }
    );

    registerBehavior("BreezyBlossom2",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            BreezyBlossom2"<<std::endl;
            std::unique_ptr<BreezyBlossom2> breezyblossom2=std::make_unique<BreezyBlossom2>(enemy,resource_,yellowpage_);

            return std::move(breezyblossom2);
        }
    );

    registerBehavior("BreezyBlossom3",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            BreezyBlossom3"<<std::endl;
            std::unique_ptr<BreezyBlossom3> breezyblossom3=std::make_unique<BreezyBlossom3>(enemy,resource_,yellowpage_);

            return std::move(breezyblossom3);
        }
    );

    registerBehavior("BreezyBlossom4",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            BreezyBlossom4"<<std::endl;
            std::unique_ptr<BreezyBlossom4> breezyblossom4=std::make_unique<BreezyBlossom4>(enemy,resource_,yellowpage_);

            return std::move(breezyblossom4);
        }
    );

    registerBehavior("NonSpell1",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            NonSpell1"<<std::endl;
            std::unique_ptr<NonSpell1> nonspell1=std::make_unique<NonSpell1>(enemy,resource_,yellowpage_);

            return std::move(nonspell1);
        }
    );

    registerBehavior("NonSpell2",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            NonSpell2"<<std::endl;
            std::unique_ptr<NonSpell2> nonspell2=std::make_unique<NonSpell2>(enemy,resource_,yellowpage_);

            return std::move(nonspell2);
        }
    );

    registerBehavior("NonSpell3",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            NonSpell3"<<std::endl;
            std::unique_ptr<NonSpell3> nonspell3=std::make_unique<NonSpell3>(enemy,resource_,yellowpage_);

            return std::move(nonspell3);
        }
    );

    registerBehavior("SuddenRain",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            SuddenRain"<<std::endl;
            std::unique_ptr<SuddenRain> suddenrain=std::make_unique<SuddenRain>(enemy,resource_,yellowpage_);

            return std::move(suddenrain);
        }
    );

    registerBehavior("TheStorm",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            TheStorm"<<std::endl;
            std::unique_ptr<TheStorm> thestorm=std::make_unique<TheStorm>(enemy,resource_,yellowpage_);

            return std::move(thestorm);
        }
    );

    registerBehavior("NewNonSpell1",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            NewNonSpell1"<<std::endl;
            std::unique_ptr<NewNonSpell1> nonspell1=std::make_unique<NewNonSpell1>(enemy,resource_,yellowpage_);

            return std::move(nonspell1);
        }
    );

    registerBehavior("StarRite",
        [this](Entity* enemy,const sol::table& behaviorscript)
        {
            std::cout<<"            StarRite"<<std::endl;
            std::unique_ptr<StarRite> starrite=std::make_unique<StarRite>(enemy,resource_,yellowpage_);

            return std::move(starrite);
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