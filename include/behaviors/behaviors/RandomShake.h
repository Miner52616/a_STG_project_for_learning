#pragma once
#include "behaviors/Behavior.h"
#include "core/Clock.h"

class Button;

class RandomShake:public Behavior
{
private:
    Button* button_;
    sf::Vector2f centerposition_;
    sf::Vector2f nextposition_;
    float shake_range_;
    Clock clock_;

public:
    RandomShake(Button* button,sf::Vector2f centerposition,float shake_range,int shake_time);
    void setPosition(sf::Vector2f position);
    void update() override;
    void reset();
};