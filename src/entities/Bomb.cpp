#include "entities/Bomb.h"

Bomb::Bomb(const sf::Texture &texture,sf::Vector2f position):
    Entity(texture),dead_(false),damage_(500)
{
    position_=position;
}

Bomb::Bomb(const sf::Texture &texture,sf::Vector2f position,float damage):
    Entity(texture),dead_(false),damage_(damage)
{
    position_=position;
}

bool Bomb::isDead() const
{
    return dead_;
}

void Bomb::markDead()
{
    dead_=true;
}

float Bomb::getDamage()
{
    return damage_;
}

int Bomb::getBombbox_r()
{
    return bombbox_r_;
}