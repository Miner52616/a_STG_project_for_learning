#pragma once
#include <SFML/Graphics.hpp>

enum class EffectType
{
    LeiTan_Air
};

enum class OverlayType
{
    Picture_Overlay
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

class OverlayConfig
{
public:
    sf::Vector2f spawn_position_={0,0};
    sf::Vector2f target_position_={0,0};
    OverlayType overlaytype_=OverlayType::Picture_Overlay;
    float v1_=12;
    float v2_=5;
    const sf::Texture& texture_;

    sf::Vector2f direction_;
    sf::Vector2f center_position_;
    
public:
    OverlayConfig(const sf::Texture& texture);
};