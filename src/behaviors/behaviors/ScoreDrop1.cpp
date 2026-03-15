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
    dropconfig_=std::make_shared<DropConfig>(resource_->app_.score_dropTexture_);
    dropconfig_->droptype_=DropType::Score;
}

void ScoreDrop1::update()
{
    if(entity_->isDead())
    {
        std::cout<<"score"<<std::endl;
        sf::Vector2f point=entity_->getPosition();       
        //dropconfig_->spawn_point_=entity_->getPosition()+sf::Vector2f{getRandomNum(-80,80),getRandomNum(-80,80)};
        for(int i=1;i<=10;i++)
        {
            dropconfig_->spawn_point_=point+sf::Vector2f{getRandomNum(-80,80),getRandomNum(-80,80)};
            resource_->dropmanager_.add_process(dropconfig_);
        }
        std::cout<<"score ok"<<std::endl;
    }
}

void ScoreDrop1::set_entity(Entity* entity)
{
    entity_=entity;
}