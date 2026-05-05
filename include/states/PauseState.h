#pragma once
#include "basicstates/ButtonState.h"
#include "ui/Text.h"

//总按钮数为4
constexpr int PauButtonNum=3;

//暂停菜单页面
class PauseState:public ButtonState<PauseState>
{
private:
    Text title_;
    Text title2_;

public:
    using ButtonState<PauseState>::HandleEvent;
    PauseState(application &app);
    void Render(sf::RenderWindow& window);
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);

    bool blocksRender() const {return false;}
};