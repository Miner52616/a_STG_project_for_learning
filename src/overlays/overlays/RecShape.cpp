#include "overlays/overlays/RecShape.h"

RecShape::RecShape()
{
    overlay_.setFillColor(sf::Color(128,128,128,128));
    overlay_.setPosition({0,1580});
    overlay_.setSize({250,50});
    targetposition_={0,0};
    v_=0.08;
}

sf::Vector2f RecShape::getPosition()
{
    return overlay_.getPosition();
}

void RecShape::setPosition(sf::Vector2f position)
{
    overlay_.setPosition(position);
}

void RecShape::setTargetPosition(sf::Vector2f position)
{
    targetposition_=position;
}

void RecShape::setspeed(float v)
{
    v_=v;
}

void RecShape::setSize(sf::Vector2f size)
{
    overlay_.setSize(size);
}