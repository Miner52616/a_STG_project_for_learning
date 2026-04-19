#pragma once
#include "behaviors/Behavior.h"

class Entity;

//AimMove1重制版本
class MoveTo:public Behavior
{
private:
    Entity* entity_;
    sf::Vector2f nextposition_;
    float v_;

public:
    MoveTo(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
    void setV(float v); 
    void setTargetPosition(sf::Vector2f position);
};