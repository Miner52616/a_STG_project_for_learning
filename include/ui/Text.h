#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Text
{
private:
    const sf::Font &font_;
    sf::Text text_;
public:
    Text(const sf::Font& font);

public:
    void setTextText(const std::string text);
    void setTextPosition(sf::Vector2f position);
    void setTextSize(int size);
    void setTextColor(sf::Color color);

    void DrawText(sf::RenderWindow& window);
};