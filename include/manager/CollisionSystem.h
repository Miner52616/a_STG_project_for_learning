#pragma once
#include "entities/Bullet.h"

class Entity;
class Bullet;
class Boss;
class Enemy;
class Player;

class CollisionSystem
{
protected:
    std::vector<std::unique_ptr<Bullet>> &bulletlist_;

    void HandleCollision(Boss *A,Bullet *B);
    void HandleCollision(Enemy *A,Bullet *B);
    void HandleCollision(Player *A,Bullet *B);

public:
    CollisionSystem(std::vector<std::unique_ptr<Bullet>> &bulletlist);
    void ProcessCollision(Boss *&A);
    void ProcessCollision(Enemy *&A);
    void ProcessCollision(Player *&A);
};