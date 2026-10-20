#pragma once
#include <SFML/Graphics.hpp>

class NumLine2
{
protected:
    float current_num_;
    float max_num_;
    const sf::Font &font_;
    sf::Text text_;
    sf::Text finaltext_;

    sf::Vector2f position_;

public:
    NumLine2(const sf::Font &font);
    int getCurrentNum();
    void setLineText(const std::string text);
    void setLinePosition(sf::Vector2f position);
    void setLineSize(float size);
    void setMaxNum(float num);
    void setCurrentNum(float num);
    virtual void render(sf::RenderWindow& window);
    virtual void render(sf::RenderTexture& texture);
};