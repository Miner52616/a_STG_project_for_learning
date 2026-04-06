#pragma once
#include <SFML/Graphics.hpp>
#include "ui/Frame.h"

enum BulletClasses
{
    LinearBullet=0,
    PlayerBullet=1
};

class BulletConfig
{
public:
    float v_=0;
    float r_=0;
    float damage_=0;
    sf::Vector2f direction_={0,-1};
    sf::Vector2f spawn_point_={0,0};
    sf::Vector2f target_point_={0,0};
    BulletClasses bulletclass_=BulletClasses::PlayerBullet;
    sf::Texture& texture_;

public:
    BulletConfig(sf::Texture& texture);
};