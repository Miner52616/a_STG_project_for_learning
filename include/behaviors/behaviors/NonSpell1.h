#pragma once
#include "behaviors/ShootBehavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"

class Entity;

class NonSpell1_1:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;

    sf::Vector2f bullet_direction_;
    float direction_angle_;
    std::vector<sf::Vector2f> direction_list_;
    std::vector<float> angle_list_;

    Clock shoot_clock_;

private:
    void setBulletConfig();
    void rotate();
public:
    NonSpell1_1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class NonSpell1_2:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    int bulletnum_;

    sf::Vector2f bullet_direction_;
    std::vector<sf::Vector2f> direction_list_;

    Clock shoot_clock_;
private:
    void setBulletConfig();
    void initial();
public:
    NonSpell1_2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class NonSpell1:public Behavior
{
private:
    Entity* entity_;
    NonSpell1_1 spell1;
    NonSpell1_2 spell2;

public:
    NonSpell1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};