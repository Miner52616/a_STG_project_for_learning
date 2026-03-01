#pragma once
#include "entities/Bullet.h"

class Entity;
class Bullet;
class Drop;
class Boss;
class Enemy;
class Player;

class CollisionSystem
{
protected:
    std::vector<std::unique_ptr<Bullet>> &bulletlist_;
    std::vector<std::unique_ptr<Drop>> &droplist_;

    void HandleCollision(std::shared_ptr<Boss> A,Bullet *B);
    void HandleCollision(std::shared_ptr<Enemy> A,Bullet *B);
    void HandleCollision(std::shared_ptr<Player> A,Bullet *B);
    void HandleCollision(std::shared_ptr<Player> A,Drop *B);
    void HandleBeGet(std::shared_ptr<Player> A,Drop *B);

public:
    CollisionSystem(std::vector<std::unique_ptr<Bullet>> &bulletlist,std::vector<std::unique_ptr<Drop>> &droplist);
    void ProcessCollision(std::shared_ptr<Boss> A);
    void ProcessCollision(std::shared_ptr<Enemy> A);
    void ProcessCollision(std::shared_ptr<Player> A);
};