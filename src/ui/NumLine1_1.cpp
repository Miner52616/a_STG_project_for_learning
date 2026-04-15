#include "ui/NumLine1_1.h"
#include <iostream>

NumLine1_1::NumLine1_1(const sf::Font &font,sf::Texture &texture):
    NumLine1(font),texture_(texture),store_(texture_),gap_(50),initial_gap_(80),y_gap_(0)
{
    ;
}

void NumLine1_1::setGap(float gap)
{
    gap_=gap;
}

void NumLine1_1::setY_Gap(float gap)
{
    y_gap_=gap;
}

void NumLine1_1::setInitialGap(float gap)
{
    initial_gap_=gap;
}

void NumLine1_1::render(sf::RenderWindow& window)
{
    window.draw(text_);
    for(int i=1;i<=current_num_;i++)
    {
        store_.setPosition({position_.x+initial_gap_+i*gap_,position_.y+10+y_gap_});
        window.draw(store_);
    }
}

void NumLine1_1::render(sf::RenderTexture& texture)
{
    texture.draw(text_);
    for(int i=1;i<=current_num_;i++)
    {
        store_.setPosition({position_.x+initial_gap_+i*gap_,position_.y+10+y_gap_});
        texture.draw(store_);
    }
}