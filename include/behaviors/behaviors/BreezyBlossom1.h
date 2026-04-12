#pragma once
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"

class Entity;

class BreezyBlossom1:public Behavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;

    sf::Vector2f center_position_;
    sf::Vector2f bullet_direction_;
    
    sf::Vector2f shoot_position_;
    sf::Vector2f shoot_direction_;

    Clock shoot_clock_;
    Clock set_bullet_clock_;
    Clock bullet_num_clock_;
    int delay_time_;

public:
    BreezyBlossom1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
    void set_entity(Entity* entity);
    void setBulletConfig();
    void reset();
};