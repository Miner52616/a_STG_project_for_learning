#include "ui/NumLine1.h"
#include <iostream>

NumLine1::NumLine1(const sf::Font &font):
    current_num_(0),max_num_(8),font_(font),text_(font_)
{
    text_.setCharacterSize(35);
}

int NumLine1::getCurrentNum()
{
    return current_num_;
}

void NumLine1::setLineText(const std::string text)
{
    text_.setString(text);
}

void NumLine1::setLinePosition(sf::Vector2f position)
{
    text_.setPosition(position);
    position_=position;
}

void NumLine1::setLineSize(float size)
{
    text_.setCharacterSize(size);
}

void NumLine1::setMaxNum(int num)
{
    max_num_=num;
}

void NumLine1::setCurrentNum(int num)
{
    current_num_=num;
    if(num>max_num_)
    {
        current_num_=max_num_;
    }
    //std::cout<<current_num_<<std::endl;
}

void NumLine1::render(sf::RenderWindow& window)
{
    sf::Text finaltext=text_;
    finaltext.setString(text_.getString()+"  "+std::to_string(current_num_));
    window.draw(finaltext);
}

