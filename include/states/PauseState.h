#pragma once
#include "basicstates/ButtonState.h"
#include "ui/Text.h"

class GameState;

//总按钮数为4
constexpr int PauButtonNum=4;

//暂停菜单页面
class PauseState:public ButtonState<PauseState>
{
private:
    GameState* game_;

    Text title_;
    Text title2_;

public:
    using ButtonState<PauseState>::HandleEvent;
    PauseState(Application &app,GameState* game);
    void render(sf::RenderWindow& window);
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);

    bool blocksRender() const {return false;}
};