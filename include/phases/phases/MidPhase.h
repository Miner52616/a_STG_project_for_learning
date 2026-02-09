#pragma once
#include "phases/basicphases/TimePhase.h"
#include "manager/EnemyManager.h"
#include "enemies/Enemy1.h"

class Player;

class MidPhase:public TimePhase
{
protected:
    Player &player_;
    //EnemyManager &enemymanager_;
    std::vector<std::unique_ptr<Enemy>> enemylist_;
    EnemyManager enemymanager_;
    std::unique_ptr<Enemy1> enemy1_;

public:
    MidPhase(application &app,BulletManager &bulletmanager,int target_frame,Player &player);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void be_damage(float damage) override;
};