#include "behaviors/behaviors/RoundMove1.h"
#include "mathematics/mathematics.h"
#include "entities/Entity.h"
#include <iostream>

RoundMove1::RoundMove1(sf::Vector2f direction,float omega,long long int time,Entity* entity):
    entity_(entity),direction_(direction), omega_(omega),nextposition_({0,0}),clock_(time)
{
    std::vector<long long int> possible_time={0,30,60,90};
    clock_.set_target(time+get_random_from(possible_time));

    clock_.reset();
}

RoundMove1::RoundMove1(sf::Vector2f direction,float omega):
    direction_(direction), omega_(omega),nextposition_({0,0}),clock_(120)
{
    std::vector<long long int> possible_time={0,30,60,90};
    clock_.set_target(120+get_random_from(possible_time));

    clock_.reset();
}

RoundMove1::RoundMove1(sf::Vector2f direction,float omega,long long int time,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),direction_(direction), omega_(omega),nextposition_({0,0}),clock_(time)
{
    std::vector<long long int> possible_time={0,30,60,90};
    clock_.set_target(time+get_random_from(possible_time));

    clock_.reset();
}

void RoundMove1::update()
{
    entity_->store_position();
    direction_=round(direction_,omega_);
    nextposition_=nextposition_+(direction_-nextposition_)*omega_/(float)150;
    entity_->setPosition(center_->getPosition()+nextposition_);
    clock_.count();
    if(clock_.get_condition())
    {
        done_=true;
    }
}

void RoundMove1::set_entity(Entity* entity)
{
    entity_=entity;
}

void RoundMove1::set_center(Entity* center)
{
    center_=center;
}

bool RoundMove1::isDone()
{
    return done_;
}