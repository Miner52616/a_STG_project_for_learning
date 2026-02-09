#pragma once
#include "phases/Phase.h"

class EventPhase:public Phase
{
public:
    EventPhase(application &app,BulletManager &bulletmanager);
};