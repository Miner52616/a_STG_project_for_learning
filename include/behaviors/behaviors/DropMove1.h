#pragma once
#include "behaviors/Behavior.h"

class Entity;

class DropMove1:public Behavior
{
private:
    std::shared_ptr<Entity> entity_;
    sf::Vector2f nextposition_;
    float v_;
    float a_;

public:
    DropMove1(std::shared_ptr<Entity> entity);
    DropMove1();
    void update() override;
    void set_entity(std::shared_ptr<Entity> entity);
    void set_va(int v,int a);
};