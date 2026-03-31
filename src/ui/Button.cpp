#include "ui/Button.h"
#include <iostream>

Button::Button(const sf::Font &font):
    font_(font),text_(font_),focused_(not_befocused),locked_(unlocked),shine_clock_(3),shine_length_(20),phase_(1),done_(false)
{
    shine_clock_.reset();
    shine_length_.reset();
    text_.setString("input");
    text_.setCharacterSize(50);
    text_.setFillColor(sf::Color::White);
    shake_=std::make_unique<RandomShake>(this,sf::Vector2f{0,0},0,15);
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
    text_.setString(sf::String::fromUtf8(text.begin(),text.end()));
}

void Button::setButtonPosition(sf::Vector2f position)
{
    text_.setPosition(position);
}

void Button::setButtonShake(float shake_range,int shake_time)
{
    shake_=std::make_unique<RandomShake>(this,getButtonPosition(),shake_range,shake_time);
}

void Button::setButtonFocused(int focus)
{
    focused_=focus;
}

void Button::setButtonLock(int lock)
{
    locked_=lock;
}

int Button::getButtonLocked()
{
    return locked_;
}

void Button::update()
{
    if(locked_==unlocked)
    {
        text_.setStyle(sf::Text::Bold);
        if(focused_==befocused)
        {
            switch (phase_)
            {
            case 1:
                text_.setFillColor(sf::Color::Yellow);
                break;

            case 2:
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
                if(shine_length_.get_condition())
                {
                    shine_length_.reset();
                    shine_clock_.reset();
                    setPhase(1);
                    done_=true;
                }

                shine_length_.count();
                shine_clock_.count();
                break;
            
            default:
                break;
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

    shake_->update();
}

void Button::setPhase(int phase)
{
    phase_=phase;
}

bool Button::isDone()
{
    return done_;
}

void Button::setDone(bool done)
{
    done_=done;
}

void Button::shake()
{
    //std::cout<<"shake"<<std::endl;
    shake_->reset();
}

void Button::setButtonSize(int size)
{
    text_.setCharacterSize(size);
}