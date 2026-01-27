#include "entities/Entity.h"
#include <iostream>

Entity::Entity(const sf::Texture &texture):
    texture_(texture),hitbox_r_(5),picture_(texture_),position_({0,0})
    {
        hitbox_.setRadius(hitbox_r_);

        hitbox_.setOrigin(hitbox_.getGlobalBounds().getCenter());
        picture_.setOrigin(picture_.getGlobalBounds().getCenter());

        setPosition();
    }

void Entity::setPosition()
{
    hitbox_.setPosition(position_);
    picture_.setPosition(position_);
}

void Entity::setPosition(sf::Vector2f position)
{
    position_=position;
    setPosition();
}

sf::Vector2f Entity::getPosition()
{
    return position_;
}

int Entity::getHitbox_r()
{
    return hitbox_r_;
}

void Entity::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
    window.draw(hitbox_);
}