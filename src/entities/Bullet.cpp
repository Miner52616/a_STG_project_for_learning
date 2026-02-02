#include "entities/Bullet.h"
#include <iostream>

Bullet::Bullet(application &app,const sf::Texture &texture,sf::Vector2f position):
    Entity(app,texture),exist_(true),dead_(false),ofplayer_(true)
{
    position_=position;
}

bool Bullet::isDead()
{
    return dead_;
}

bool Bullet::isPlayer()
{
    return ofplayer_;
}

bool Bullet::isOut()
{
    if(getPosition().x<=0||getPosition().y<=0||getPosition().x>=1280||getPosition().y>=960)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Bullet::markDead()
{
    dead_=true;
}

void Bullet::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
}