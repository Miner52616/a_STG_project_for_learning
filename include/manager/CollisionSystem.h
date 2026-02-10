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

    void HandleCollision(std::shared_ptr<Boss> A,Bullet *B);
    void HandleCollision(std::shared_ptr<Enemy> A,Bullet *B);
    void HandleCollision(std::shared_ptr<Player> A,Bullet *B);

public:
    CollisionSystem(std::vector<std::unique_ptr<Bullet>> &bulletlist);
    void ProcessCollision(std::shared_ptr<Boss> A);
    void ProcessCollision(std::shared_ptr<Enemy> A);
    void ProcessCollision(std::shared_ptr<Player> A);
};