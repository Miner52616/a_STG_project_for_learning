#pragma once
#include <SFML/Graphics.hpp>

enum class DropType
{
    Score,
    Power
};

class DropConfig
{
public:
    sf::Vector2f spawn_point_={0,0};
    DropType droptype_=DropType::Score;
    sf::Texture &texture_;

public:
    DropConfig(sf::Texture& texture);
};