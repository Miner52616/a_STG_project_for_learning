#pragma once
#include <memory>

class application;
class BulletManager;
class DropManager;
class CollisionSystem;
class Player;
class NumLine1;

class Resource
{
public:
    Resource(application &app,BulletManager &bulletmanager,DropManager &dropmanager,CollisionSystem &collisionsystem,std::shared_ptr<Player> player,NumLine1 &high_score_line,NumLine1 &score_line);
    application &app_;
    BulletManager &bulletmanager_;
    DropManager &dropmanager_;
    CollisionSystem &collisionsystem_;
    std::shared_ptr<Player> player_;
    NumLine1 &high_score_line_;
    NumLine1 &score_line_;

public:
    void setPlayer(std::shared_ptr<Player> player);
};