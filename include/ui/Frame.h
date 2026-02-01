#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Frame
{
private:
    sf::RectangleShape frame_in_;
    sf::RectangleShape frame_out_;
    
public:
    Frame(sf::Vector2f lefttop,sf::Vector2f rightbottom,int width,sf::Color color_in,sf::Color color_out);
    sf::FloatRect getGlobalBounds();
    float getBounds_top();
    float getBounds_bottom();
    float getBounds_left();
    float getBounds_right();
    void drawwindow(sf::RenderWindow& window);
};