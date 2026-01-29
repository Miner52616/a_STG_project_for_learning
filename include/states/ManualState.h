#pragma once
#include "basicstates/TextState.h"

//总页数为5
constexpr int ManPageNum=5;

//游戏说明页
class ManualState:public TextState<ManualState>
{
public:
    using TextState<ManualState>::HandleEvent;
    ManualState(application &app);  //初始化各页，初始化各页的各文字
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);  //处理“按钮按下”事件
};