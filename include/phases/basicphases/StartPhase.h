#pragma once
#include "phases/Phase.h"

class StartPhase:public Phase
{
public:
    StartPhase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager);
    void update() override;
    void render(sf::RenderWindow& window) override;
};