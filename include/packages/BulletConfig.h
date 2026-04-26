#pragma once
#include <SFML/Graphics.hpp>
#include "ui/Frame.h"
#include "core/Clock.h"
#include "packages/EffectConfig.h"

enum BulletClasses
{
    LinearBullet=0,
    PlayerBullet=1,
    DirectBullet1=2,
    DirectBullet2=3,
    PlayerAimBullet=4,
    DirectBullet3=5
};

enum BulletBehavior
{
    Fix=0,
    Rotate=1,
    Direct=2
};

enum BulletSize
{
    Small=0,
    Big=1
};

class BulletConfig
{
public:
    float v_=0;
    float a_=0;
    float a2_=0;
    float v2_=0;
    float v3_=0;
    float r_=2;
    float damage_=0;
    float angle_=0;
    Clock clock1_;
    Clock clock2_;
    Clock clock3_;
    sf::Vector2f direction_={0,-1};
    sf::Vector2f direction2_={0,-1};
    sf::Vector2f spawn_point_={0,0};
    sf::Vector2f target_point_={0,0};
    BulletClasses bulletclass_=BulletClasses::PlayerBullet;
    BulletBehavior bulletbehavior_=BulletBehavior::Fix;
    BulletSize bulletsize_=BulletSize::Small;
    std::vector<int> bullet_index_={1,1};
    sf::Texture& texture_;

public:
    BulletConfig(sf::Texture& texture);
    void setClock1(int target);
};