#pragma once
#include "ui/NumLine1.h"

class NumLine1_1:public NumLine1
{
private:
    sf::Texture &texture_;
    sf::Sprite store_;

public:
    NumLine1_1(const sf::Font &font,sf::Texture &texture);
    void render(sf::RenderWindow& window) override;
};