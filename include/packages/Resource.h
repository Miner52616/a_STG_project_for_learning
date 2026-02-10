#pragma once

class application;
class BulletManager;
class CollisionSystem;
class Player;

class Resourse
{
public:
    application &app_;
    BulletManager &bulletmanager_;
    CollisionSystem &collisionsystem_;
    std::shared_ptr<Player> player_;
};