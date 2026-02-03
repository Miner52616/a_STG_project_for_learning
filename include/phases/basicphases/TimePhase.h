#pragma once
#include "phases/Phase.h"

class EnemyManager;

class TimePhase:public Phase
{
protected:
    int frame_;
    int target_frame_;
    EnemyManager &enemymanager_;
    
public:
    TimePhase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager,EnemyManager& enemymaanager,int target_frame);

protected:
    void frame_forward();
    void update() override;
    void render(sf::RenderWindow& window) override;
};