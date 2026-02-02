#pragma once
#include "entities/Bullet.h"

class LinearBullet:public Bullet
{
private:
    sf::Vector2f targetposition_;
    float v_;
public:
    LinearBullet(application &app,const sf::Texture &texture,sf::Vector2f position,sf::Vector2f targetposition,float v,int r);
    void update() override;
};