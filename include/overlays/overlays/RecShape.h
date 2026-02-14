#pragma once
#include "overlays/Overlay.h"

class RecShape:public Overlay
{
protected:
    sf::RectangleShape overlay_;
    sf::Vector2f targetposition_;
    float v_;

public:
    RecShape();
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);
    void setTargetPosition(sf::Vector2f position);
    void setspeed(float v);
    void setSize(sf::Vector2f size);
};