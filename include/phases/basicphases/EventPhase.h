#pragma once
#include "phases/Phase.h"

class EventPhase:public Phase
{
public:
    EventPhase(Resource* resource,YellowPage* yellowpage);
};