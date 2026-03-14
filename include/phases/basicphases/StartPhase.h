#pragma once
#include "phases/Phase.h"

class StartPhase:public Phase
{
public:
    StartPhase(Resource* resource,YellowPage* yellowpage);
    void render(sf::RenderWindow& window) override;
};