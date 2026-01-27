#pragma  once
#include "basicstates/ButtonState.h"

constexpr int MenuButtonNum=4;

class MenuState:public ButtonState<MenuState>
{
public:
    using ButtonState<MenuState>::HandleEvent;
    MenuState(application &app);
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);
};

/*
#pragma once
#include "state.h"
#include "Button.h"
//class Button;

constexpr int ButtonNum=4;

class MenuState:public State
{
private:
    int focus;
    Button buttonlist[ButtonNum];

public:
    MenuState(application &app);
    void ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;

private:
    void DrawButton(sf::RenderWindow& window);
    void updatebuttonlist();

public:
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Closed&);
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);
    void HandleEvent(sf::RenderWindow& window,const auto&){};//其它无反应事件
};

*/