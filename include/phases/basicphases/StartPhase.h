#pragma once
#include "phases/Phase.h"

class StartPhase:public Phase
{
public:
    StartPhase(std::shared_ptr<Resource> resource);
    void render(sf::RenderWindow& window) override;
};