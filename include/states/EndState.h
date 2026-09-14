#pragma once
#include "basicstates/ButtonState.h"
#include "ui/Text.h"

//总按钮数为2
constexpr int EndButtonNum=2;

class GameState;

class EndState:public ButtonState<EndState>
{
private:
    GameState& gamestate_;
    Text title_;
    Text title2_;
    Text title3_;

public:
    using ButtonState<EndState>::HandleEvent;
    bool blocksRender() const {return false;}
    
    EndState(Application &app,GameState& gamestate);
    void render(sf::RenderWindow& window) override;
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);
};