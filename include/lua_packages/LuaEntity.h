#pragma once
#include <SFML/Graphics.hpp>

class Entity;

class LuaEntity
{
private:
    Entity* entity_;

public:
    sf::Vector2f getPosition();

public:
    LuaEntity(Entity* entity);
};