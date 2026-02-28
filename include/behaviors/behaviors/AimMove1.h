#pragma once
#include "behaviors/Behavior.h"

class Entity;

class AimMove1:public Behavior
{
private:
    std::shared_ptr<Entity> entity_;
    float v_;

public:
    AimMove1(std::shared_ptr<Entity> entity);
    AimMove1();
    void update() override;
    void set_entity(std::shared_ptr<Entity> entity);
    void set_v(int v);
};