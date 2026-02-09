#pragma once
#include "phases/basicphases/TimePhase.h"

class VoidPhase:public TimePhase
{
protected:

public:
    VoidPhase(application &app,BulletManager &bulletmanager,int target_frame);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void be_damage(float damage);
};