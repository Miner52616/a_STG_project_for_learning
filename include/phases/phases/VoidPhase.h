#pragma once
#include "phases/basicphases/TimePhase.h"

class Player;

class VoidPhase:public TimePhase
{
public:
    VoidPhase(Resource* resource,YellowPage* yellowpage,int target_frame);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void render(sf::RenderTexture& texture) override;
    void be_damage(float damage);
    void ProcessCollision() override;
    sf::Vector2f get_targetposition_for_LeiTan(AimMove2* move) override;
};