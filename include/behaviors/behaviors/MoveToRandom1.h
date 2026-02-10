#pragma once
#include "behaviors/Behavior.h"

class Entity;

class MoveToRandom1:public Behavior
{
private:
    std::shared_ptr<Entity> entity_;
    sf::Vector2f nextposition_;

public:
    MoveToRandom1(std::shared_ptr<Entity> entity);
    MoveToRandom1();
    void update() override;
    void set_entity(std::shared_ptr<Entity> entity);
};