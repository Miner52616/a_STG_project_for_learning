#include "entities/Bullet.h"
#include <iostream>

Bullet::Bullet(const sf::Texture &texture,sf::Vector2f position):
    Entity(texture),exist_(true)
{
    position_=position;
}

void Bullet::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
}