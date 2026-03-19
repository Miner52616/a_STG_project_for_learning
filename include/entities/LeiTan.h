#pragma once
#include "entities/Bomb.h"
#include "behaviors/behaviors/RoundMove1.h"
#include "packages/YellowPage.h"
#include "core/Clock.h"

class LeiTan:public Bomb
{
private:
    YellowPage* yellowpage_;

    Clock clock_;
    std::unique_ptr<RoundMove1> roundmove1_;

public:
    LeiTan(const sf::Texture &texture,sf::Vector2f position,YellowPage* yellowpage);
    LeiTan(const sf::Texture &texture,sf::Vector2f position,float damage,YellowPage* yellowpage);
    LeiTan(const sf::Texture &texture,sf::Vector2f position,sf::Vector2f direction,float damage,float v,YellowPage* yellowpage);

public:
    void update() override;
};