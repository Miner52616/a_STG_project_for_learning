#pragma once
#include "Entity.h"

//子弹
class Bullet:public Entity
{
private:
    bool exist_;

public:
    Bullet(const sf::Texture &texture,sf::Vector2f position);  //初始化子弹位置，初始化资源引用，默认子弹设置

public:
    void drawwindow(sf::RenderWindow& window) override;  //渲染子弹至屏幕
};