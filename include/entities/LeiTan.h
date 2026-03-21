#pragma once
#include "entities/Bomb.h"
#include "behaviors/behaviors/RoundMove1.h"
#include "behaviors/behaviors/AimMove2.h"
#include "packages/YellowPage.h"
#include "core/Clock.h"

class LeiTan:public Bomb
{
private:
    Resource* resource_;
    YellowPage* yellowpage_;

    int phase_=1;
    
    std::unique_ptr<RoundMove1> roundmove1_;
    std::unique_ptr<AimMove2> aimmove2_;

    Clock clock_;
    float damage1_=8;
    float damage2_=500;

public:
    LeiTan(const sf::Texture &texture,sf::Vector2f position,YellowPage* yellowpage);
    LeiTan(const sf::Texture &texture,sf::Vector2f position,float damage,YellowPage* yellowpage);
    LeiTan(const sf::Texture &texture,sf::Vector2f position,sf::Vector2f direction,float damage,float v,YellowPage* yellowpage,Resource* resource);

private:

public:
    void update() override;
    void phase_change();
    int getPhase() override;
    float getDamage() override;
};