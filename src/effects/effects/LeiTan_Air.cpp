#include "effects/effects/LeiTan_Air.h"
#include "behaviors/behaviors/AimMove3.h"

LeiTan_Air::LeiTan_Air(const sf::Texture &texture,sf::Vector2f position,long long int time,sf::Vector2f direction,float v):
    Effect(texture,position,time),direction_(direction),v_(v)
{
    std::unique_ptr<AimMove3> behavior=std::make_unique<AimMove3>(this,v_,position_+direction_);
    behaviorlist_.emplace_back(std::move(behavior));
}

void LeiTan_Air::setDirection(sf::Vector2f direction)
{
    direction_=direction;
}

void LeiTan_Air::setV(float v)
{
    v_=v;
}