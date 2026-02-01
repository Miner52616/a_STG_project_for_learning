#include "entities/Bullet.h"
#include <iostream>

Bullet::Bullet(application &app,const sf::Texture &texture,sf::Vector2f position):
    Entity(app,texture),exist_(true),dead_(false)
{
    position_=position;
}

bool Bullet::isDead()
{
    return dead_;
}

void Bullet::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
}