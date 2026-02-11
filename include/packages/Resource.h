#pragma once
#include <memory>

class application;
class BulletManager;
class CollisionSystem;
class Player;

class Resourse
{
public:
    Resourse(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,std::shared_ptr<Player> player);
    application &app_;
    BulletManager &bulletmanager_;
    CollisionSystem &collisionsystem_;
    std::shared_ptr<Player> player_;
};