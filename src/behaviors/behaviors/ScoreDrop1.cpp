#include "core/application.h"
#include "behaviors/behaviors/ScoreDrop1.h"
#include "packages/DropConfig.h"
#include "mathematics/mathematics.h"
#include "manager/DropManager.h"
#include "entities/Drop.h"
#include "entities/Enemy.h"
#include <iostream>

ScoreDrop1::ScoreDrop1(Entity* entity):
    entity_(entity)
{
    ;
}

ScoreDrop1::ScoreDrop1()
{
    ;
}

ScoreDrop1::ScoreDrop1(Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage)
{
    setDropConfig();
}

void ScoreDrop1::setDropConfig()
{
    dropconfig_=std::make_unique<DropConfig>(resource_->app_.score_dropTexture_);
    dropconfig_->droptype_=DropType::Score;
    dropconfig_->dropnum_=10;
}

void ScoreDrop1::setDropConfig(DropType type,int dropnum)
{
    dropconfig_=std::make_unique<DropConfig>(resource_->app_.score_dropTexture_);
    dropconfig_->droptype_=type;
    dropconfig_->dropnum_=dropnum;
}

void ScoreDrop1::update()
{
    if(entity_->isDead())
    {
        std::cout<<"score"<<std::endl;
        sf::Vector2f point=entity_->getPosition();       
        //dropconfig_->spawn_point_=entity_->getPosition()+sf::Vector2f{getRandomNum(-80,80),getRandomNum(-80,80)};
        for(int i=1;i<=dropconfig_->dropnum_;i++)
        {
            dropconfig_->spawn_point_=point+sf::Vector2f{getRandomNum(-80,80),getRandomNum(-80,80)};
            resource_->dropmanager_.add_process(dropconfig_.get());
        }
        std::cout<<"score ok"<<std::endl;
    }
}

void ScoreDrop1::set_entity(Entity* entity)
{
    entity_=entity;
}