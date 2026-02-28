#include "behaviors/behaviors/DropMove1.h"
#include "entities/Entity.h"

DropMove1::DropMove1(std::shared_ptr<Entity> entity):
    entity_(entity),nextposition_({385,100}),v_(-20),a_(0.5)
{
    ;
}

DropMove1::DropMove1():
    nextposition_({385,100}),v_(-20),a_(0.5)
{
    ;
}

void DropMove1::update()
{
    entity_->store_position();
    entity_->setPosition({entity_->getPosition().x,entity_->getPosition().y+v_});
    v_=v_+a_;
}

void DropMove1::set_entity(std::shared_ptr<Entity> entity)
{
    entity_=entity;
}

void DropMove1::set_va(int v,int a)
{
    v_=v;
    a_=a;
}