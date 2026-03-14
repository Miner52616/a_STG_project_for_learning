#pragma once
#include "behaviors/Behavior.h"

class Entity;

class MoveToRandom1:public Behavior
{
private:
    Entity* entity_;
    sf::Vector2f nextposition_;

public:
    MoveToRandom1(Entity* entity);
    MoveToRandom1();
    void update() override;
    void set_entity(Entity* entity);
};