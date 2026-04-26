#pragma once
#include <SFML/Graphics.hpp>

enum EffectType
{
    LeiTan_Air=0,
    Bullet_Air=1,
    PlayerBullet_Air=2
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
    float a_=0;
    float v_=0.08;
    float v2_=0;
    sf::Vector2f direction_={100,0};
    sf::Texture &texture_;
    int texturelist_size_=0;
    int current_texture_num_=0;
    bool random_rotate_=true;
    std::vector<int> effect_index_={1,1};
    std::vector<sf::Texture*> texturelist_;

public:
    EffectConfig(sf::Texture& texture_);
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