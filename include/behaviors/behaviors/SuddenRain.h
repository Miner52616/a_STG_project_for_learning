#pragma once
#include "behaviors/ShootBehavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"

class Entity;

//下雨重力弹部分
class SuddenRain1:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    Clock shoot_clock_;

    float gap_;
    sf::Vector2f shoot_position_;
    sf::Vector2f shoot_move_direction_;
    std::vector<sf::Vector2f> shoot_direction_list_;
    std::vector<int> angle_list_;

private:
    void setBulletConfig() override;

public:
    SuddenRain1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

//曲线弹风弹部分
class SuddenRain2:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    Clock shoot_clock_;
    Clock shoot_clock2_;

    int direction_num_;
    float error_;
    Clock bullet_num_clock_;
    float shoot_rotate_angle_;
    std::vector<sf::Vector2f> shoot_direction_list_;

private:
    void setBulletConfig() override;

public:
    SuddenRain2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class SuddenRain:public Behavior
{
private:
    SuddenRain1 rain_;
    SuddenRain2 wind_;

public:
    SuddenRain(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};