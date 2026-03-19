#pragma once
#include <memory>
#include "packages/YellowPage.h"

class application;
class BulletManager;
class DropManager;
class BombManager;
class CollisionSystem;
class Player;
class NumLine1;

class Resource
{
public:
    Resource(application &app,BulletManager &bulletmanager,DropManager &dropmanager,BombManager &bombmanager,CollisionSystem &collisionsystem);
    application &app_;
    BulletManager &bulletmanager_;
    DropManager &dropmanager_;
    BombManager &bombmanager_;
    CollisionSystem &collisionsystem_;
    //Player* player_;
    //YellowPage yellowpage_;
    //NumLine1 &high_score_line_;
    //NumLine1 &score_line_;

public:
    //void setPlayer(Player* player);
};