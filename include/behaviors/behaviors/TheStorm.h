#pragma once
#include "behaviors/ShootBehavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"

class Entity;

class TheStorm1:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    BulletConfig bulletconfig2_;
    Clock shoot_clock_;
    Clock shoot_clock2_;
    Clock shoot_clock3_1_;
    Clock shoot_clock3_2_;

    sf::Vector2f translation_;
    Clock shoot_num_clock_;
    Clock shoot_num_clock2_;
    sf::Vector2f initial_radius_;
    sf::Vector2f radius_;
    sf::Vector2f radius2_;
    sf::Vector2f direction_;
    sf::Vector2f direction2_;
    float initial_angle_;
    float rotate_angle_;
    float rotate_angle2_;

    std::vector<sf::Vector2f> shoot_direction_list_;
    std::vector<int> angle_list_;

private:
    void setBulletConfig() override;
public:
    TheStorm1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};