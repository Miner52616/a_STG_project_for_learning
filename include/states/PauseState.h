#pragma once
#include "basicstates/ButtonState.h"

//总按钮数为4
constexpr int PauButtonNum=4;

//暂停菜单页面
class PauseState:public ButtonState<PauseState>
{
public:
    using ButtonState<PauseState>::HandleEvent;
    PauseState(application &app);
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);

    bool blocksRender() const {return false;}
};