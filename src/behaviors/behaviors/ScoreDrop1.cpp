#include "core/application.h"
#include "behaviors/behaviors/ScoreDrop1.h"
#include "packages/DropConfig.h"
#include "manager/DropManager.h"
#include "entities/Drop.h"
#include "entities/Enemy.h"
#include <iostream>

ScoreDrop1::ScoreDrop1(std::shared_ptr<Entity> entity):
    entity_(entity)
{
    ;
}

ScoreDrop1::ScoreDrop1()
{
    ;
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
        dropconfig_->spawn_point_=entity_->getPosition();
        resource_->dropmanager_.add_process(dropconfig_);
    }
}

void ScoreDrop1::set_entity(std::shared_ptr<Entity> entity)
{
    entity_=std::move(entity);
}