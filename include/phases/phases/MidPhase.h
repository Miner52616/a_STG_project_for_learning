#pragma once
#include "phases/basicphases/TimePhase.h"
#include "manager/EnemyManager.h"
#include "enemies/Enemy1.h"

class Player;

class MidPhase:public TimePhase
{
protected:
    std::shared_ptr<Player> player_;
    //EnemyManager &enemymanager_;
    std::vector<std::shared_ptr<Enemy>> enemylist_;
    EnemyManager enemymanager_;
    std::shared_ptr<Enemy1> enemy1_;

public:
    MidPhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,int target_frame,std::shared_ptr<Player> player);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void be_damage(float damage) override;
    void ProcessCollision() override;
};