#pragma once
#include "core/state.h"
#include "ui/Page.h"

//文字类页面，有多页
template<typename Derived>
class TextState:public State
{
protected:
    int focus_;
    std::vector<Page> pagelist_;

protected:
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Closed&);  //处理“关闭窗口”事件
    void HandleEvent(sf::RenderWindow& window,const auto&){};  //其它无反应事件

public:
    void setPagelistLength(int length);  //设置文字类页面页数（设置页面数组大小）

public:
    TextState(application &app,int PageNum);  //初始化页数，初始化页选择
    void ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;  //处理分发到的事件
    void Update() override;  //统一更新属性
    void Render(sf::RenderWindow& window) override;  //统一渲染至屏幕
};

#include "TextState.ipp"