#pragma once
#include "phases/basicphases/TimePhase.h"

class Player;

class VoidPhase:public TimePhase
{
protected:
    std::shared_ptr<Player> player_;

public:
    VoidPhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,int target_frame,std::shared_ptr<Player> player);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void be_damage(float damage);
    void ProcessCollision() override;
};