#pragma once
#include "phases/basicphases/TimePhase.h"
#include "core/Clock.h"

class Player;
class Boss;

class SpellPhase:public TimePhase
{
protected:
    std::shared_ptr<Player> player_;
    std::shared_ptr<Boss> boss_;
    Clock moveclock_;
    Clock shootclock_;
    sf::Vector2f nextposition_;
    sf::RectangleShape HPline_;
    float fullHP_;
    float HP_;

public:
    SpellPhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,int target_frame,std::shared_ptr<Player> player);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void setHP(float HP);
    void be_damage(float damage) override;
    void ProcessCollision() override;
    void setBoss(std::shared_ptr<Boss> boss);
};