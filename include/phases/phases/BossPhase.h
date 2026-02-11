#pragma once
#include "phases/basicphases/EventPhase.h"
#include "entities/Boss.h"

class Player;

class BossPhase:public EventPhase
{
protected:
    std::shared_ptr<Boss> boss_;

public:
    BossPhase(std::shared_ptr<Resource> resource,std::shared_ptr<Boss> boss);
    BossPhase(std::shared_ptr<Resource> resource);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void setBoss(std::shared_ptr<Boss> boss);
    void be_damage(float damage) override;
    void ProcessCollision() override;
};