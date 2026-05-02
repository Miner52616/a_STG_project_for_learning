#pragma once
#include "behaviors/ShootBehavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"

class Entity;

class NewNonSpell1:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    std::vector<int> left_right_;

    int bullet_num_;
    sf::Vector2f start_position_;
    sf::Vector2f set_direction_;
    sf::Vector2f bullet_direction_;
    float gap_;

    Clock start_clock_;
    Clock shoot_clock_;
private:
    void setBulletConfig();
    //void rotate();
public:
    NewNonSpell1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};
