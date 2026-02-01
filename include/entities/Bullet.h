#pragma once
#include "Entity.h"

//子弹
class Bullet:public Entity
{
protected:
    bool exist_;
    bool dead_;

public:
    Bullet(application &app,const sf::Texture &texture,sf::Vector2f position);  //初始化子弹位置，初始化资源引用，默认子弹设置

public:
    virtual void update()=0;
    bool isDead();
    void drawwindow(sf::RenderWindow& window) override;  //渲染子弹至屏幕
};