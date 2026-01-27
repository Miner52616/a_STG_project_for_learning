#pragma once
#include "core/state.h"
#include "ui/Button.h"
//class Button;

//constexpr int ButtonNum=4;

template<typename Derived>
class ButtonState:public State
{
protected:
    int focus_;
    std::vector<Button> buttonlist_;

public:
    ButtonState(application &app,int ButtonNum);
    void setbuttonlistLength(int length);
    void ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;

protected:
    void DrawButton_(sf::RenderWindow& window);
    void updatebuttonlist_();

protected:
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Closed&);
//    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);
    void HandleEvent(sf::RenderWindow& window,const auto&){};//其它无反应事件
};

#include "ButtonState.ipp"