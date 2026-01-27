#pragma once
#include "Entity.h"

class Bullet:public Entity
{
private:
    bool exist_;

public:
    Bullet(const sf::Texture &texture,sf::Vector2f position);

public:
    void drawwindow(sf::RenderWindow& window) override;
};