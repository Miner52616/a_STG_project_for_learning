#include "phases/Phase.h"
#include "core/application.h"
#include "manager/PhaseController.h"
#include "manager/BulletManager.h"

Phase::Phase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager):
    app_(app),phasecontroller_(phasecontroller),bulletmanager_(bulletmanager)
{
    ;
}

void Phase::phase_change()
{
    phasecontroller_.phase_change();
}