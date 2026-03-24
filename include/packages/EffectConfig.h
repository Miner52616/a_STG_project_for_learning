#pragma once
#include <SFML/Graphics.hpp>

enum class EffectType
{
    LeiTan_Air
};

class EffectConfig
{
public:
    sf::Vector2f spawn_point_={0,0};
    EffectType effecttype_=EffectType::LeiTan_Air;
    long long int time_=48;
    float v_=0.08;
    sf::Vector2f direction_={100,0};
    const sf::Texture &texture_;

public:
    EffectConfig(const sf::Texture& texture_);
};