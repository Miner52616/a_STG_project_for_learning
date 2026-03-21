#include "behaviors/behaviors/AimMove2.h"
#include "entities/Entity.h"
#include "mathematics/mathematics.h"
#include "manager/PhaseController.h"
#include <iostream>

AimMove2::AimMove2(sf::Vector2f v,float a,Entity* entity,long long int time,Resource* resource):
    entity_(entity),v_(v), a_(a),clock_(time),startposition_({0,0}),nextposition_({0,0}),targetposition_({0,0}),aimstate_(AimState::DYNAMIC)
{
    clock_.reset();
    resource_=resource;
}

void AimMove2::update()
{
    entity_->store_position();
    if(aimstate_==AimState::DYNAMIC)
    {
        targetposition_=resource_->phasecontroller_.get_targetposition_for_LeiTan(this);
        //std::cout<<targetposition_.x<<" "<<targetposition_.y<<std::endl;
    }

    sf::Vector2f direction=normalize(targetposition_-entity_->getPosition());
    v_=normalize(v_+limit_a_*direction)*v_.length();

    sf::Vector2f limited_v_=v_;
    if((targetposition_-entity_->getPosition()).length()<50&&aimstate_==AimState::LOCKED)
    {
        if(limit_low_v>0.01)
        {
            limit_low_v=limit_low_v*0.9;
        }
        limit_noise_v=0.01;//noise_v_(targetposition_-entity_->getPosition()).length()/15;  
    }
    float slowing_r=(targetposition_-startposition_).length();
    if((targetposition_-entity_->getPosition()).length()<slowing_r)
    {
        limited_v_=v_*(targetposition_-entity_->getPosition()).length()/slowing_r;
        if(limited_v_.length()<limit_low_v)
        {
            limited_v_=normalize(v_)*(limit_low_v+limit_noise_v*getRandomNum(-1,1));
        }
    }

    nextposition_=entity_->getPosition()+limited_v_;
    entity_->setPosition(nextposition_);

    clock_.count();
    if(clock_.get_condition())
    {
        done_=true;
    }
    /*
    if(aimstate_==AimState::DYNAMIC)
    {
        low_v_=8;
        noise_v_=1;
        if((targetposition_-entity_->getPosition()).length()<15)
        {
            done_=true;
        }
    }
        */
}

void AimMove2::set_entity(Entity* entity)
{
    entity_=entity;
}

void AimMove2::set_v(sf::Vector2f v)
{
    v_=v;
}

void AimMove2::set_targetposition(sf::Vector2f position)
{
    targetposition_=position;
}

sf::Vector2f AimMove2::get_v()
{
    return v_;
}

void AimMove2::set_aimstate(AimState aimstate)
{
    aimstate_=aimstate;
}

void AimMove2::set_startposition(sf::Vector2f position)
{
    startposition_=position;
}

bool AimMove2::isDone()
{
    return done_;
}

sf::Vector2f AimMove2::get_position()
{
    return entity_->getPosition();
}