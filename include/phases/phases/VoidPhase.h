#pragma once
#include "phases/basicphases/TimePhase.h"

class VoidPhase:public TimePhase
{
protected:

public:
    VoidPhase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager,EnemyManager &enemymanager,int target_frame);
};