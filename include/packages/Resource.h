#pragma once
#include <memory>

class application;
class BulletManager;
class DropManager;
class CollisionSystem;
class Player;

class Resource
{
public:
    Resource(application &app,BulletManager &bulletmanager,DropManager &dropmanager,CollisionSystem &collisionsystem,std::shared_ptr<Player> player);
    application &app_;
    BulletManager &bulletmanager_;
    DropManager &dropmanager_;
    CollisionSystem &collisionsystem_;
    std::shared_ptr<Player> player_;

public:
    void setPlayer(std::shared_ptr<Player> player);
};