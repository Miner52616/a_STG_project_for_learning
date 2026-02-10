#pragma once
#include "behaviors/Behavior.h"

class Entity;
class BulletManager;

class AimShoot1:public Behavior
{
private:
    std::shared_ptr<Entity> entity_;
    BulletManager &bulletmanager_;

public:
    AimShoot1(std::shared_ptr<Entity> entity,BulletManager &bulletmanager);
    AimShoot1(BulletManager &bulletmanager);
    void update() override;
    void set_entity(std::shared_ptr<Entity> entity);
};