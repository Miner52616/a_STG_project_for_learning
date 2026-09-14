#pragma once
#include <SFML/Graphics.hpp>

class Application;

//页面，所有类型页面的基类
class State
{
public:
    explicit State(Application &app);  //初始化application引用，初始化资源引用
    virtual ~State()=default;

    virtual void processEvent(sf::RenderWindow& window,const std::optional<sf::Event> event)=0;  //处理被分发到的事件
    virtual void update()=0;  //统一更新属性
    virtual void render(sf::RenderWindow& window)=0;  //统一渲染至屏幕

    virtual bool blocksUpdate() const {return true;}  //是否阻断叠加下方的页面更新
    virtual bool blocksRender() const {return true;}  //是否阻断叠加下方的页面渲染

protected:
    Application &app_;
    const sf::Font &font_;

};