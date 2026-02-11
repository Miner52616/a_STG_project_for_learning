#pragma once
#include "behaviors/Behavior.h"

class Entity;
class BulletManager;

class AimShoot1:public Behavior
{
private:
    std::shared_ptr<Entity> entity_;

public:
    AimShoot1(std::shared_ptr<Entity> entity);
    AimShoot1();
    void update() override;
    void set_entity(std::shared_ptr<Entity> entity);
};