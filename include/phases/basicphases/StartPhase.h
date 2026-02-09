#pragma once
#include "phases/Phase.h"

class StartPhase:public Phase
{
public:
    StartPhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem);
    void render(sf::RenderWindow& window) override;
};