#pragma once
#include "phases/basicphases/EventPhase.h"
#include "entities/Boss.h"

class Player;

class BossPhase:public EventPhase
{
protected:
    std::shared_ptr<Boss> boss_;
    std::shared_ptr<Player> player_;

public:
    BossPhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,std::shared_ptr<Boss> boss,std::shared_ptr<Player> player);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void be_damage(float damage) override;
    void ProcessCollision() override;
};