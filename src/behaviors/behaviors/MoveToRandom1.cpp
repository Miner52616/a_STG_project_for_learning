#include "behaviors/behaviors/MoveToRandom1.h"
#include "mathematics/mathematics.h"
#include "entities/Entity.h"

MoveToRandom1::MoveToRandom1(Entity* entity):
    entity_(entity),nextposition_({385,100}),clock2_(60)
{
    clock2_.reset();
}

MoveToRandom1::MoveToRandom1():
    nextposition_({385,100}),clock2_(60)
{
    clock2_.reset();   
}

MoveToRandom1::MoveToRandom1(Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),nextposition_({385,100}),clock2_(60)
{
    clock2_.reset();
}

void MoveToRandom1::update()
{
    if(!clock2_.get_condition())
    {
        clock2_.count();
    }
    else
    {
        entity_->store_position();
        entity_->setPosition((nextposition_-entity_->getPosition())*0.01f+entity_->getPosition());
        if(clock_.get_condition())
        {
            nextposition_={getRandomNum(50,720),getRandomNum(20,300)};
            clock_.reset();
        }
        clock_.count();
    }
}   

void MoveToRandom1::set_entity(Entity* entity)
{
    entity_=entity;
}

void MoveToRandom1::set_start(int start)
{
    clock2_.set_target(start);
}