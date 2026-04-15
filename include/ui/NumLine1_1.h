#pragma once
#include "ui/NumLine1.h"

class NumLine1_1:public NumLine1
{
private:
    sf::Texture &texture_;
    sf::Sprite store_;
    float y_gap_;
    float gap_;
    float initial_gap_;

public:
    NumLine1_1(const sf::Font &font,sf::Texture &texture);
    void setGap(float gap);
    void setY_Gap(float gap);
    void setInitialGap(float gap);
    void render(sf::RenderWindow& window) override;
    void render(sf::RenderTexture& texture) override;
};