#pragma once
#include "basicstates/ButtonState.h"

//总按钮数为3
constexpr int EndButtonNum=3;

class EndState:public ButtonState<EndState>
{
public:
    using ButtonState<EndState>::HandleEvent;
    EndState(application &app);
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);

    bool blocksRender() const {return false;}
};