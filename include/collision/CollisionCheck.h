#pragma once
#include <SFML/Graphics.hpp>

class Entity;
class Drop;

bool isCollision(Entity &a,Entity &b);

bool isGet(Entity &a,Drop &b);