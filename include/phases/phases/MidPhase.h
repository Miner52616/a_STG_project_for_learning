#pragma once
#include "phases/basicphases/TimePhase.h"
#include "enemies/Enemy1.h"

class Player;

class MidPhase:public TimePhase
{
private:
    Player &player_;

    Enemy1 enemy1_;

public:
    MidPhase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager,EnemyManager &enemymanager,int target_frame,Player &player);
};