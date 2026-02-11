#pragma once
#include "phases/Phase.h"

class StartPhase:public Phase
{
public:
    StartPhase(std::shared_ptr<Resourse> resourse);
    void render(sf::RenderWindow& window) override;
};