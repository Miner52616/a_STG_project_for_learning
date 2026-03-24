#pragma once
#include <memory>
#include "packages/YellowPage.h"

class application;
class BulletManager;
class DropManager;
class BombManager;
class EffectManager;
class CollisionSystem;
class PhaseController;
class Player;
class NumLine1;

class Resource
{
public:
    Resource(application &app,BulletManager &bulletmanager,DropManager &dropmanager,BombManager &bombmanager,EffectManager &effectmanager,CollisionSystem &collisionsystem,PhaseController &phasecontroller);
    application &app_;
    BulletManager &bulletmanager_;
    DropManager &dropmanager_;
    BombManager &bombmanager_;
    EffectManager &effectmanager_;
    CollisionSystem &collisionsystem_;
    PhaseController &phasecontroller_;
    //Player* player_;
    //YellowPage yellowpage_;
    //NumLine1 &high_score_line_;
    //NumLine1 &score_line_;

public:
    //void setPlayer(Player* player);
};