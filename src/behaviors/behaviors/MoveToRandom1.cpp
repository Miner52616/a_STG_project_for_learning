#include "behaviors/behaviors/MoveToRandom1.h"
#include "mathematics/mathematics.h"
#include "entities/Entity.h"

MoveToRandom1::MoveToRandom1(std::shared_ptr<Entity> entity):
    entity_(entity),nextposition_({460,100})
{
    ;
}

MoveToRandom1::MoveToRandom1():
    nextposition_({460,100})
{
    ;   
}

void MoveToRandom1::update()
{
    entity_->store_position();
    entity_->setPosition((nextposition_-entity_->getPosition())*0.01f+entity_->getPosition());
    if(clock_.get_condition())
    {
        nextposition_={getRandomNum(125,795),getRandomNum(20,300)};
        clock_.reset();
    }
}   

void MoveToRandom1::set_entity(std::shared_ptr<Entity> entity)
{
    entity_=std::move(entity);
}