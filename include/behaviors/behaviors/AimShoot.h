#pragma once
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"

class Entity;
class BulletManager;

class AimShoot1:public Behavior
{
private:
    Entity* entity_;
    std::shared_ptr<BulletConfig> bulletconfig_;

public:
    AimShoot1(Entity* entity);
    AimShoot1();
    void update() override;
    void set_entity(Entity* entity);
    void setBulletConfig();
};