#pragma once
#include "phases/basicphases/EventPhase.h"
#include "entities/Boss.h"

class Player;

class BossPhase:public EventPhase
{
protected:
    Boss* boss_;

public:
    BossPhase(Resource* resource,YellowPage* yellowpage,Boss* boss);
    BossPhase(Resource* resource,YellowPage* yellowpage);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void render(sf::RenderTexture& texture) override;
    void setBoss(Boss* boss);
    void be_damage(float damage) override;
    void ProcessCollision() override;
};