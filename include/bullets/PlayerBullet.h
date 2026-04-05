#pragma once
#include "entities/Bullet.h"

class application;
class Frame;

class PlayerBullet:public Bullet
{
private:
    float v_=50;
    //Frame &outline_;

public:
    PlayerBullet(sf::Texture &texture,sf::Vector2f position);
    PlayerBullet(sf::Texture &texture,sf::Vector2f position,float damage);
    void setv(float v);
    void update() override;
};