#pragma once
#include "core/state.h"
#include "ui/Button.h"

//按钮类页面，有多个按钮
template<typename Derived>
class ButtonState:public State
{
protected:
    int focus_;
    std::vector<Button> buttonlist_;

public:
    ButtonState(application &app,int ButtonNum);  //初始化按钮数组，初始化按钮选中
    void setbuttonlistLength(int length);  //设置按钮类界面按钮数（设置按钮数组大小）
    void ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;  //处理被分发到的事件
    void Update() override;  //统一更新属性
    void Render(sf::RenderWindow& window) override;  //统一渲染至屏幕

protected:
    void DrawButton_(sf::RenderWindow& window);  //将按钮数组里的按钮渲染至屏幕
    void updatebuttonlist_();  //更新按钮数组的属性

protected:
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Closed&);  //处理“关闭窗口”事件
    void HandleEvent(sf::RenderWindow& window,const auto&){};  //其它无反应事件
};

#include "ButtonState.ipp"