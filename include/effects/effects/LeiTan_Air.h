#pragma once
#include "effects/Effect.h"
#include "behaviors/behaviors/AimMove1.h"

class LeiTan_Air:public Effect
{
private:
    sf::Vector2f direction_;
    float v_;


public:
    LeiTan_Air(const sf::Texture &texture,sf::Vector2f position,long long int time,sf::Vector2f direction,float v);
    void setDirection(sf::Vector2f direction);
    void setV(float v);
};
