#pragma once
#include "entities/Bullet.h"

class application;
class Frame;

class PlayerBullet:public Bullet
{
private:
    //Frame &outline_;

public:
    PlayerBullet(const sf::Texture &texture,sf::Vector2f position);
    PlayerBullet(const sf::Texture &texture,sf::Vector2f position,float damage);
    void update() override;
};