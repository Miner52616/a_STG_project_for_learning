#include "entities/Bullet.h"
#include <iostream>

Bullet::Bullet(const sf::Texture &texture,sf::Vector2f position):
    Entity(texture),exist_(true),dead_(false),ofplayer_(true),damage_(100)
{
    position_=position;
}

Bullet::Bullet(const sf::Texture &texture,sf::Vector2f position,float damage):
    Entity(texture),exist_(true),dead_(false),ofplayer_(true),damage_(damage)
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
    if(getPosition().x<=0||getPosition().y<=0||getPosition().x>=770||getPosition().y>=900)
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

float Bullet::getDamage()
{
    return damage_;
}

/*
void Bullet::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
}
    */