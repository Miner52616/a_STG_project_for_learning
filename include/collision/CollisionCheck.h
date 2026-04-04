#pragma once
#include <SFML/Graphics.hpp>

class Entity;
class Drop;
class Player;
class Bullet;
class Bomb;
class LeiTan;

bool isCollision(Entity &a,Entity &b);
bool isCollisionSimple(Entity &a,Entity &b);

bool isGetSimple(Entity &a,Drop &b);
bool isGet(Entity &a,Drop &b);

bool isBomb(Entity &a,Bomb &b);

bool isGraze(Player &a,Bullet &b);