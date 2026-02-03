#include "phases/basicphases/EventPhase.h"

EventPhase::EventPhase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager):
    Phase(app,phasecontroller,bulletmanager),change_(false)
{
    ;
}

void EventPhase::change_phase()
{
    change_=true;
}

bool EventPhase::isChange()
{
    return change_;
}