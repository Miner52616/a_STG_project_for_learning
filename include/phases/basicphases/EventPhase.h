#pragma once
#include "phases/Phase.h"

class EventPhase:public Phase
{
protected:
    bool change_;

public:
    EventPhase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager);

    void change_phase();
    bool isChange();
};