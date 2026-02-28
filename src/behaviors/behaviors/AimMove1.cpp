#include "behaviors/behaviors/AimMove1.h"
#include "entities/Entity.h"
#include "entities/Player.h"

AimMove1::AimMove1(std::shared_ptr<Entity> entity):
    entity_(entity),v_(20)
{
    ;
}

AimMove1::AimMove1():
    v_(20)
{
    ;
}

void AimMove1::update()
{
    entity_->store_position();
    entity_->setPosition(entity_->getPosition()+v_*((resource_->player_->getPosition()-entity_->getPosition())/((resource_->player_->getPosition()-entity_->getPosition()).length())));
}

void AimMove1::set_entity(std::shared_ptr<Entity> entity)
{
    entity_=entity;
}

void AimMove1::set_v(int v)
{
    v_=v;
}