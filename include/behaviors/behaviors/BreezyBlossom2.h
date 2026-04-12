#pragma once
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"

class Entity;

class BreezyBlossom2:public Behavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;

    Clock shoot_clock_;

public:
    BreezyBlossom2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
    void setBulletConfig();
};