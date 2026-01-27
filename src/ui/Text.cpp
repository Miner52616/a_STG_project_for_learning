#include "ui/Text.h"
#include <iostream>


//    font_("abc.ttf"),text_(font_)
Text::Text(const sf::Font& font):
    font_(font),text_(font_)
{
    
//    text_.setFont(font_);
//    text_.setString("input");
//    text_.setCharacterSize(50);
    text_.setFillColor(sf::Color::White);
    text_.setOrigin(text_.getGlobalBounds().getCenter());
}

void Text::setTextText(const std::string text)
{
    text_.setString(text);
}

void Text::setTextPosition(sf::Vector2f position)
{
    text_.setPosition(position);
}

void Text::setTextColor(sf::Color color)
{
    text_.setFillColor(color);
}

void Text::setTextSize(int size)
{
    text_.setCharacterSize(size);
}

void Text::DrawText(sf::RenderWindow& window)
{
    window.draw(text_);
}