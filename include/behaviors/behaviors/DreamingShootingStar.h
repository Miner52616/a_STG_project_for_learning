#pragma once
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"

class Entity;

//第一阶段的大星弹拖尾小星弹直线下落
class DreamingShootingStar1:public Behavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;

    Clock shoot_clock_;
private:
    void setBulletConfig();

public:
    DreamingShootingStar1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};