#pragma  once
#include "basicstates/ButtonState.h"

//总按钮数为4
constexpr int MenuButtonNum=4;

//主菜单页面
class MenuState:public ButtonState<MenuState>
{
public:
    using ButtonState<MenuState>::HandleEvent;
    MenuState(application &app);  //初始化所有按钮的属性
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);  //处理“按键按下”事件
};