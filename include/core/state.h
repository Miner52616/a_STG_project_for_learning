#pragma once
#include <SFML/Graphics.hpp>

class application;

//页面，所有类型页面的基类
class State
{
public:
    explicit State(application &app);  //初始化application引用，初始化资源引用
    virtual ~State()=default;

    virtual void ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event)=0;  //处理被分发到的事件
    virtual void Update()=0;  //统一更新属性
    virtual void Render(sf::RenderWindow& window)=0;  //统一渲染至屏幕

    virtual bool blocksUpdate() const {return true;}  //是否阻断叠加下方的页面更新
    virtual bool blocksRender() const {return true;}  //是否阻断叠加下方的页面渲染

protected:
    application &app_;
    const sf::Font &font_;

};