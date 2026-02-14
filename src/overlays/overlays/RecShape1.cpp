#include "overlays/overlays/RecShape1.h"

RecShape1::RecShape1()
{
    overlay_.setFillColor(sf::Color(128,128,128,128));
    overlay_.setPosition({0,1580});
    overlay_.setSize({250,50});
    targetposition_={0,0};
    v_=0.08;
}

sf::Vector2f RecShape1::getPosition()
{
    return overlay_.getPosition();
}

void RecShape1::setPosition(sf::Vector2f position)
{
    overlay_.setPosition(position);
}

void RecShape1::setTargetPosition(sf::Vector2f position)
{
    targetposition_=position;
}

void RecShape1::setspeed(float v)
{
    v_=v;
}

void RecShape1::setSize(sf::Vector2f size)
{
    overlay_.setSize(size);
}

void RecShape1::update()
{
    setPosition((targetposition_-getPosition())*v_+getPosition());
}

void RecShape1::render(sf::RenderWindow& window)
{
    window.draw(overlay_);
}