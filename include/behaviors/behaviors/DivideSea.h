#pragma once
#include "behaviors/ShootBehavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"

class Entity;

class DivideSea1:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;

private:
    void setBulletConfig() override;

public:
    DivideSea1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

