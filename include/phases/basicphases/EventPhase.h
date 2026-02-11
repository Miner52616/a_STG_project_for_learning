#pragma once
#include "phases/Phase.h"

class EventPhase:public Phase
{
public:
    EventPhase(std::shared_ptr<Resource> resource);
};