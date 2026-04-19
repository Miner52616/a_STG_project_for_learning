#include "behaviors/behaviors/Move.h"
#include "mathematics/mathematics.h"
#include "entities/Entity.h"

MoveTo::MoveTo(Entity* entity,Resource* resource,YellowPage* yellowpage):
    entity_(entity),Behavior(resource,yellowpage)
{
    v_=0.01;
}

void MoveTo::update()
{
    entity_->setPosition((nextposition_-entity_->getPosition())*v_+entity_->getPosition());
}

void MoveTo::setV(float v)
{
    v_=v;
}

void MoveTo::setTargetPosition(sf::Vector2f position)
{
    nextposition_=position;
}