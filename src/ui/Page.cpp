#include "ui/Page.h"
#include <iostream>

Page::Page(const sf::Font &font):
    font_(font)
{
    //textlist_.resize(1);
    setTextlistLength(1);
}

void Page::addText()
{
    textlist_.emplace_back(font_);
}

void Page::Render(sf::RenderWindow& window)
{
    for(int i=1;i<=textlist_.size();i++)
    {
        textlist_[i-1].DrawText(window);
        //std::cout<<"success\n";
    }
}

void Page::setTextlistLength(int num)
{
    //textlist_.resize(num);
    for(;textlist_.size()<num;)
    {
        addText();
    }
}

void Page::setTextText(int num,const std::string text)
{
    textlist_[num-1].setTextText(text);
}

void Page::setTextPosition(int num,sf::Vector2f position)
{
    textlist_[num-1].setTextPosition(position);
}

void Page::setTextSize(int num,int size)
{
    textlist_[num-1].setTextSize(size);
}

void Page::setTextColor(int num,sf::Color color)
{
    textlist_[num-1].setTextColor(color);
}