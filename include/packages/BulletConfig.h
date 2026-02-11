#pragma once
#include <SFML/Graphics.hpp>
#include "ui/Frame.h"

enum class BulletClasses
{
    LinearBullet,
    PlayerBullet
};

typedef struct BulletConfig
{
    float v_;
    float r_;
    float damage_;
    Frame &frame_;
    sf::Vector2f spawn_point_;
    sf::Vector2f target_point_;
    BulletClasses bulletclass_;
    sf::Texture& texture_;
}BulletConfig;