#pragma once
#include "behaviors/ShootBehavior.h"
#include "packages/BulletConfig.h"
#include "behaviors/behaviors/BasicShooter.h"
#include "packages/BatchConfig.h"
#include "core/Clock.h"

class Entity;
class Batch;

//手画星星然后爆开的弹幕
class NonSpell3:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    std::vector<ShootLine> lines_;

    int line_bullet_num_;
    int gap_;
    int shoot_clock_gap_;

    BatchConfig batchconfig_;
    Batch* current_batch_;

    Clock draw_clock_;

private:
    void setBulletConfig() override;
    void setBatchConfig();

public:
    NonSpell3(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};