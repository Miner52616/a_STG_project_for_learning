#pragma once
#include "overlays/Overlay.h"

class RecShape1:public Overlay
{
protected:
    sf::RectangleShape overlay_;
    sf::Vector2f targetposition_;
    float v_;

public:
    RecShape1();
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);
    void setTargetPosition(sf::Vector2f position);
    void setspeed(float v);
    void setSize(sf::Vector2f size);
    void update() override;
    void render(sf::RenderWindow& window) override;
};