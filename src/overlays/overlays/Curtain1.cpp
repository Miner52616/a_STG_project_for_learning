#include "overlays/overlays/Curtain1.h"

Curtain1::Curtain1()
{
    overlay_.setSize({1280,960});
    overlay_.setPosition({-1280,0});
    overlay_.setFillColor(sf::Color::White);
    v_=32;
}

void Curtain1::update()
{
    if(overlay_.getPosition().x<=1280)
    {
        overlay_.setPosition(overlay_.getPosition()+sf::Vector2f({v_,0}));
    }
}

void Curtain1::render(sf::RenderWindow& window)
{
    window.draw(overlay_);
}