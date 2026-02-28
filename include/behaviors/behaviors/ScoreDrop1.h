#pragma once
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"

class Entity;
class DropConfig;

class ScoreDrop1:public Behavior
{
private:
    std::shared_ptr<Entity> entity_;
    std::shared_ptr<DropConfig> dropconfig_;

public:
    ScoreDrop1(std::shared_ptr<Entity> entity);
    ScoreDrop1();
    void update() override;
    void set_entity(std::shared_ptr<Entity> entity);
    void setDropConfig();
};