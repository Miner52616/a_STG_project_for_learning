#pragma once
#include "behaviors/Behavior.h"

class Entity;

class DirectMove1:public Behavior
{
private:
    Entity* entity_;
    float v_;
    sf::Vector2f direction_;

public:
    DirectMove1(Entity* entity,float v,sf::Vector2f direction);
    void update() override;
};