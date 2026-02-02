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

void Bullet::markDead()
{
    dead_=true;
}

void Bullet::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
}