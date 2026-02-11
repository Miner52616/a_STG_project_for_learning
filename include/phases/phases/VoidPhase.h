#pragma once
#include "phases/basicphases/TimePhase.h"

class Player;

class VoidPhase:public TimePhase
{
public:
    VoidPhase(std::shared_ptr<Resourse> resourse,int target_frame);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void be_damage(float damage);
    void ProcessCollision() override;
};