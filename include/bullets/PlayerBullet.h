#pragma once
#include "entities/Bullet.h"

class application;
class Frame;

class PlayerBullet:public Bullet
{
private:
    Frame &outline_;

public:
    PlayerBullet(const sf::Texture &texture,sf::Vector2f position,Frame &outline);
    void update() override;
};