#pragma once
#include <SFML/Graphics.hpp>

class NumLine1
{
protected:
    int current_num_;
    int max_num_;
    const sf::Font &font_;
    sf::Text text_;

    sf::Vector2f position_;

public:
    NumLine1(const sf::Font &font);
    int getCurrentNum();
    void setLineText(const std::string text);
    void setLinePosition(sf::Vector2f position);
    void setLineSize(float size);
    void setMaxNum(int num);
    void setCurrentNum(int num);
    virtual void render(sf::RenderWindow& window);
};