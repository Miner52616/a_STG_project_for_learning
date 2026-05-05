#pragma once
#include "behaviors/ShootBehavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"
#include "behaviors/behaviors/NonSpell1.h"

class Entity;

class StarRite1:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;

    int phase_;
    bool trigger_;
    bool center_initialize_;
    sf::Vector2f center_;
    float gap_;
    int bullet_num_;
    sf::Vector2f shoot_position_;
    sf::Vector2f position_move_direction_;

    Clock shoot_clock_;
    Clock shoot2_delay_;
    Clock shoot_clock2_;
    Clock shoot_num_clock_;
    Clock shoot_times_clock2_;
    Clock phase_clock_;
    Clock trigger_delay_;
    Clock trigger_clock_;

private:
    void setBulletConfig() override;

public:
    StarRite1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class StarRite:public Behavior
{
private:
    StarRite1 starrite1_;
    NonSpell1_1 starrite2_;
    Clock delay_clock_;

public:
    StarRite(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};