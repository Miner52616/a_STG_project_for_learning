#include "ui/NumLine1_1.h"
#include <iostream>

NumLine1_1::NumLine1_1(const sf::Font &font,sf::Texture &texture):
    NumLine1(font),texture_(texture),store_(texture_)
{
    ;
}

void NumLine1_1::render(sf::RenderWindow& window)
{
    window.draw(text_);
    for(int i=1,gap=20;i<=current_num_;i++)
    {
        store_.setPosition({position_.x+80+gap,position_.y+10});
        window.draw(store_);
        gap=gap+50;
    }
}