#pragma once
#include <SFML/Graphics.hpp>

class Entity;
class Drop;
class Player;
class Bullet;

bool isCollision(Entity &a,Entity &b);

bool isGet(Entity &a,Drop &b);

bool isGraze(Player &a,Bullet &b);