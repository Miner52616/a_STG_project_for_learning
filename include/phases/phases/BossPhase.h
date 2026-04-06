#pragma once
#include "phases/basicphases/EventPhase.h"
#include "entities/Boss.h"

class Player;

class BossPhase:public EventPhase
{
protected:
    std::unique_ptr<Boss> boss_;

public:
    BossPhase(Resource* resource,YellowPage* yellowpage,std::unique_ptr<Boss> boss);
    BossPhase(Resource* resource,YellowPage* yellowpage);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void render(sf::RenderTexture& texture) override;
    void setBoss(std::unique_ptr<Boss> boss);
    Boss* getBoss();
    void be_damage(float damage) override;
    void ProcessCollision() override;
    sf::Vector2f get_targetposition_for_LeiTan(AimMove2* move) override;
};