#include "phases/Phase.h"
#include "core/application.h"
#include "manager/PhaseController.h"
#include "manager/BulletManager.h"
#include "manager/CollisionSystem.h"

Phase::Phase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem):
    app_(app),bulletmanager_(bulletmanager),collisionsystem_(collisionsystem),change_(false)
{
    ;
}

bool Phase::isFinish()
{
    return change_;
}



/*
void Phase::phase_change()
{
    phasecontroller_.phase_change();
}
    */