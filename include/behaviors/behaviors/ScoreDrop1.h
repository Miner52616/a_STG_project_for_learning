#pragma once
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"

class Entity;
class DropConfig;

class ScoreDrop1:public Behavior
{
private:
    Entity* entity_;
    std::shared_ptr<DropConfig> dropconfig_;

public:
    ScoreDrop1(Entity* entity);
    ScoreDrop1();
    ScoreDrop1(Resource* resource,YellowPage* yellowpage);
    void update() override;
    void set_entity(Entity* entity);
    void setDropConfig();
};