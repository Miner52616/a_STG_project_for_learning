#pragma once
#include "phases/basicphases/TimePhase.h"
#include "core/Clock.h"

class Player;
class Boss;

class SpellPhase:public TimePhase
{
protected:
    Player  &player_;
    Boss* boss_;
    Clock moveclock_;
    Clock shootclock_;
    sf::Vector2f nextposition_;

public:
    SpellPhase(application &app,BulletManager &bulletmanager,int target_frame,Player &player);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void setBoss(Boss *boss);
};