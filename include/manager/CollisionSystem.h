#pragma once
#include "entities/Bullet.h"

class Entity;
class Bullet;
class Drop;
class Boss;
class Enemy;
class Player;
class Resource;
class YellowPage;

class CollisionSystem
{
protected:
    std::vector<std::unique_ptr<Bullet>> &bulletlist_;
    std::vector<std::unique_ptr<Drop>> &droplist_;
    Resource* resource_;
    YellowPage* yellowpage_;

    void HandleCollision(Boss* A,Bullet *B);
    void HandleCollision(Enemy* A,Bullet *B);
    void HandleCollision(Player* A,Bullet *B);
    void HandleCollision(Player* A,Drop *B);
    void HandleBeGet(Player* A,Drop *B);

public:
    CollisionSystem(std::vector<std::unique_ptr<Bullet>> &bulletlist,std::vector<std::unique_ptr<Drop>> &droplist);
    void set_resource(Resource* resource);
    void set_yellowpage(YellowPage *yellowpage);
    
    void ProcessCollision(Boss* A);
    void ProcessCollision(Enemy* A);
    void ProcessCollision(Player* A);
};