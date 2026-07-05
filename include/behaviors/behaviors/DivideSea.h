#pragma once
#include "behaviors/ShootBehavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"
#include "packages/BatchConfig.h"

class Entity;
class Batch;

class DivideSea1:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    BatchConfig batchconfig_;
    Batch* batch_;

    int bullet_num_;
    bool create_batch_;
    bool close_batch_;
    Clock shoot_clock_;
    int line_;

private:
    void setBulletConfig() override;
    void setBatchConfig();

public:
    DivideSea1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class DivideSea2:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    Clock shoot_clock_;
    int current_frame_;

private:
    void setBulletConfig() override;

public:
    DivideSea2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

/********************************************************** */
class DivideSea3:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    Clock shoot_clock_;
    int current_frame_;

private:
    void setBulletConfig() override;

public:
    DivideSea3(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

/************************************************************* */

class DivideSea4:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    Clock shoot_clock_;

private:
    void setBulletConfig() override;

public:
    DivideSea4(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

/**************************************************** */

class DivideSea:public Behavior
{
private:
    DivideSea1 dividesea1_;
    DivideSea2 dividesea2_;
    DivideSea3 dividesea3_;
    DivideSea4 dividesea4_;

    Clock delay_;

public:
    DivideSea(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};