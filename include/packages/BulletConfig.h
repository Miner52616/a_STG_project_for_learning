#pragma once
#include <SFML/Graphics.hpp>
#include "ui/Frame.h"
#include "core/Clock.h"

enum BulletClasses
{
    LinearBullet=0,
    PlayerBullet=1,
    DirectBullet1=2,
    DirectBullet2=3
};

class BulletConfig
{
public:
    float v_=0;
    float a_=0;
    float v2_=0;
    float r_=2;
    float damage_=0;
    Clock clock1_;
    sf::Vector2f direction_={0,-1};
    sf::Vector2f spawn_point_={0,0};
    sf::Vector2f target_point_={0,0};
    BulletClasses bulletclass_=BulletClasses::PlayerBullet;
    sf::Texture& texture_;

public:
    BulletConfig(sf::Texture& texture);
    void setClock1(int target);
};