#pragma  once
#include "basicstates/ButtonState.h"
#include "overlays/overlays/RecShape1.h"
#include "core/Clock.h"

//总按钮数为4
constexpr int MenuButtonNum=4;

//主菜单页面
class MenuState:public ButtonState<MenuState>
{
private:
    int current_phase_;
    Clock clock_;
    RecShape1 rec_;

public:
    using ButtonState<MenuState>::HandleEvent;
    MenuState(application &app);  //初始化所有按钮的属性
    void ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);  //处理“按键按下”事件
};