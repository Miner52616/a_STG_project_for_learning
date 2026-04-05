#pragma once
#include "behaviors/Behavior.h"

class Entity;

//越靠近目标实体，速度越慢
//这是直接速度追踪目标实体的AimMove

class AimMove1:public Behavior
{
private:
    std::shared_ptr<Entity> entity_;
    float v_;

public:
    AimMove1(std::shared_ptr<Entity> entity);
    AimMove1();
    AimMove1(Resource* resource,YellowPage* yellowpage);
    void update() override;
    void set_entity(std::shared_ptr<Entity> entity);
    void set_v(int v);
};