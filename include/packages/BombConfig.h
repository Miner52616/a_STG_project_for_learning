#pragma once
#include <SFML/Graphics.hpp>

enum class BombType
{
    LeiTan
};

class BombConfig
{
public:
    sf::Vector2f spawn_point_={0,0};
    BombType bombtype_=BombType::LeiTan;
    float damage1_=2;
    float damage2_=120;
    float v_=3;
    sf::Vector2f direction_={100,0};
    sf::Texture &texture_;
public:
    BombConfig(sf::Texture& texture);
};