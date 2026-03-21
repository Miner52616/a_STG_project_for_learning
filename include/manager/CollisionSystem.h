#pragma once
#include <vector>
#include <memory>
#include "entities/Bullet.h"
#include "entities/Drop.h"
#include "entities/Bomb.h"
#include "entities/LeiTan.h"


class Entity;
class Bullet;
class Drop;
class Bomb;
class Boss;
class Enemy;
class Player;
class Bomb;
class Resource;
class YellowPage;

class CollisionSystem
{
protected:
    std::vector<std::unique_ptr<Bullet>> &bulletlist_;
    std::vector<std::unique_ptr<Drop>> &droplist_;
    std::vector<std::unique_ptr<Bomb>> &bomblist_;
    Resource* resource_;
    YellowPage* yellowpage_;

    void HandleCollision(Boss* A,Bullet *B);
    void HandleCollision(Enemy* A,Bullet *B);
    void HandleCollision(Player* A,Bullet *B);
    void HandleCollision(Player* A,Drop *B);
    void HandleBeGet(Player* A,Drop *B);
    void HandleCollision(Bomb* A,Bullet *B);
    void HandleCollision(Enemy* A,Bomb* B);
    void HandleCollision(Boss* A,Bomb* B);

public:
    CollisionSystem(std::vector<std::unique_ptr<Bullet>> &bulletlist,std::vector<std::unique_ptr<Drop>> &droplist,std::vector<std::unique_ptr<Bomb>> &bomblist);
    void set_resource(Resource* resource);
    void set_yellowpage(YellowPage *yellowpage);
    
    void ProcessCollision(Boss* A);
    void ProcessCollision(Enemy* A);
    void ProcessCollision(Player* A);
    void ProcessCollision(Bomb* A);
};