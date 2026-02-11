#pragma once
#include "phases/basicphases/TimePhase.h"
#include "core/Clock.h"
#include "behaviors/Behavior.h"

class Player;
class Boss;

class SpellPhase:public TimePhase
{
protected:
    std::shared_ptr<Boss> boss_;
    Clock moveclock_;
    Clock shootclock_;
    sf::Vector2f nextposition_;
    std::vector<std::shared_ptr<Behavior>> behaviorlist_;
    sf::RectangleShape HPline_;
    float fullHP_;
    float HP_;

public:
    SpellPhase(std::shared_ptr<Resource> resource,int target_frame);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void addBehavior(std::shared_ptr<Behavior> behavior);
    void setHP(float HP);
    void be_damage(float damage) override;
    void ProcessCollision() override;
    void setBoss(std::shared_ptr<Boss> boss);
};