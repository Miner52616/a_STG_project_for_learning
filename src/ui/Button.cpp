#include "ui/Button.h"
#include <iostream>

Button::Button(const sf::Font &font):
    font_(font),text_(font_),focused_(not_befocused),locked_(unlocked),shining_(not_shining),shine_clock_(3)
{
    text_.setString("input");
    text_.setCharacterSize(50);
    text_.setFillColor(sf::Color::White);
    //text_.setOrigin(text_.getGlobalBounds().getCenter());//存在问题！！button的原点实际仍在左上角
}

sf::Text Button::getButtonText_()
{
    return text_;
}

sf::Vector2f Button::getButtonPosition()
{
    return text_.getPosition();
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
}

void Button::setButtonShining(int shining)
{
    shining_=shining;
}

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
            if(shining_==not_shining)
            {
                text_.setFillColor(sf::Color::Yellow);
            }
            else
            {
                if(shine_clock_.get_condition())
                {
                    shine_clock_.reset();
                    if(text_.getFillColor()==sf::Color::Yellow)
                    {
                        text_.setFillColor(sf::Color(128,128,102));
                    }
                    else
                    {
                        text_.setFillColor(sf::Color::Yellow);
                    }
                }
                shine_clock_.count();
            }
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