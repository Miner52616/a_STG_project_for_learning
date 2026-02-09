#pragma once
#include "phases/basicphases/EventPhase.h"
#include "entities/Boss.h"

class Player;

class BossPhase:public EventPhase
{
protected:
    Boss* boss_;
    Player &player_;

public:
    BossPhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,Boss *boss,Player &player);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void be_damage(float damage) override;
    void ProcessCollision() override;
};