#include "ui/Button.h"
#include <iostream>

Button::Button(const sf::Font &font):
    font_(font),text_(font_),focused_(not_befocused),locked_(unlocked)
{
    text_.setString("input");
    text_.setCharacterSize(50);
    text_.setFillColor(sf::Color::White);
    text_.setOrigin(text_.getGlobalBounds().getCenter());
}

sf::Text Button::getButtonText_()
{
    return text_;
}

void Button::setButtonText(const std::string text)
{
    text_.setString(text);
}

void Button::setButtonPosition(sf::Vector2f position)
{
    text_.setPosition(position);
}

void Button::setButtonFocused(int focus)
{
    focused_=focus;
 /*   if(focus==befocused)
    text_.setFillColor(sf::Color::Yellow);
    else
    text_.setFillColor(sf::Color::White);*/
}

/*
void Button::removeButtonFocused()
{
    focused_=not_befocused;
    text_.setFillColor(sf::Color::White);
}
*/

void Button::setButtonLock(int lock)
{
    locked_=lock;
}

int Button::getButtonLocked()
{
    return locked_;
}

void Button::updateButton()
{
    if(locked_==unlocked)
    {
        text_.setStyle(sf::Text::Bold);
        if(focused_==befocused)
        {
            text_.setFillColor(sf::Color::Yellow);
        }
        else
        {
            text_.setFillColor(sf::Color::White);
        }
    }
    else
    {
        text_.setStyle(sf::Text::Regular);
        text_.setFillColor(sf::Color::White);
    }
}