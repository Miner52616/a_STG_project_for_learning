#pragma once
#include "behaviors/Behavior.h"

class Entity;

class RoundMove1:public Behavior
{
private:
    Entity* entity_;
    Entity* center_;
    sf::Vector2f nextposition_;
    float omega_;

public:
    RoundMove1(sf::Vector2f nextposition,float omega,Entity* entity);
    RoundMove1(sf::Vector2f nextposition,float omega);
    RoundMove1(sf::Vector2f nextposition,float omega,Resource* resource,YellowPage* yellowpage);
    void update() override;
    void set_entity(Entity* entity);
    void set_center(Entity* center);
};