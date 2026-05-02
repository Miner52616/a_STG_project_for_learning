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
    Clock shoot_clock_;
    Clock shoot_clock2_;

    int initial_delay_time_;
    int delay_time_;
    sf::Vector2f translation_;
    Clock shoot_num_clock_;
    sf::Vector2f initial_radius_;
    sf::Vector2f radius_;
    sf::Vector2f direction_;
    float initial_angle_;
    float rotate_angle_;

private:
    void setBulletConfig() override;
public:
    TheStorm1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class TheStorm2:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    Clock start_clock_;
    Clock shoot_clock_;
    Clock shoot_clock2_;

    int initial_delay_time_;
    int delay_time_;
    sf::Vector2f translation_;
    Clock shoot_num_clock_;
    sf::Vector2f initial_radius_;
    sf::Vector2f radius_;
    sf::Vector2f direction_;
    float initial_angle_;
    float rotate_angle_;

private:
    void setBulletConfig() override;
public:
    TheStorm2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class TheStorm3:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    Clock start_clock_;
    Clock shoot_clock_;
    Clock shoot_clock2_;

    int initial_delay_time_;
    int delay_time_;
    sf::Vector2f initial_translation_;
    sf::Vector2f translation_;
    Clock shoot_num_clock_;
    sf::Vector2f initial_radius_;
    sf::Vector2f radius_;
    sf::Vector2f direction_;
    float initial_angle_;
    float rotate_angle_;

private:
    void setBulletConfig() override;
public:
    TheStorm3(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class TheStorm4:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    Clock start_clock_;
    Clock shoot_clock_;
    Clock shoot_clock2_;

    int initial_delay_time_;
    int delay_time_;
    sf::Vector2f initial_translation_;
    sf::Vector2f translation_;
    Clock shoot_num_clock_;
    sf::Vector2f initial_radius_;
    sf::Vector2f radius_;
    sf::Vector2f direction_;
    float initial_angle_;
    float rotate_angle_;

private:
    void setBulletConfig() override;
public:
    TheStorm4(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

//********************************************** */

class TheStorm:public Behavior
{
private:
    TheStorm1 storm1_;
    TheStorm2 storm2_;
    TheStorm3 storm3_;
    TheStorm4 storm4_;

public:
    TheStorm(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};