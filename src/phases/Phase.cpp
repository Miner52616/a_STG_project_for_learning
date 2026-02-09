#include "phases/Phase.h"
#include "core/application.h"
#include "manager/PhaseController.h"
#include "manager/BulletManager.h"

Phase::Phase(application &app,BulletManager &bulletmanager):
    app_(app),bulletmanager_(bulletmanager),change_(false)
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