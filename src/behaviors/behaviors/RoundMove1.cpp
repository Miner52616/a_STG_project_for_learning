#include "behaviors/behaviors/RoundMove1.h"
#include "mathematics/mathematics.h"
#include "entities/Entity.h"
#include <iostream>

RoundMove1::RoundMove1(sf::Vector2f nextposition,float omega,Entity* entity):
    entity_(entity),nextposition_(nextposition), omega_(omega)
{
    ;
}

RoundMove1::RoundMove1(sf::Vector2f nextposition,float omega):
    nextposition_(nextposition), omega_(omega)
{
    ;   
}

RoundMove1::RoundMove1(sf::Vector2f nextposition,float omega,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),nextposition_(nextposition), omega_(omega)
{
    ;
}

void RoundMove1::update()
{
    entity_->store_position();
    nextposition_=round(nextposition_,omega_);
    entity_->setPosition(center_->getPosition()+nextposition_);
}

void RoundMove1::set_entity(Entity* entity)
{
    entity_=entity;
}

void RoundMove1::set_center(Entity* center)
{
    center_=center;
}