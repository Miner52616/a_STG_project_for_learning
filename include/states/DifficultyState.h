#pragma  once
#include "basicstates/ButtonState.h"

constexpr int DifButtonNum=4;

class DifficultyState:public ButtonState<DifficultyState>
{
public:
    using ButtonState<DifficultyState>::HandleEvent;
    DifficultyState(application &app);  //初始化所有按钮的属性
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);  //处理“按键按下”事件
};