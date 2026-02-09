#pragma once
#include "phases/basicphases/TimePhase.h"
#include "enemies/Enemy1.h"

class Player;

class MidPhase:public TimePhase
{
protected:
    Player &player_;
    EnemyManager &enemymanager_;
    Enemy1 enemy1_;

public:
    MidPhase(application &app,BulletManager &bulletmanager,EnemyManager &enemymanager,int target_frame,Player &player);
    void update() override;
    void render(sf::RenderWindow& window) override;
};