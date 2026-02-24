#pragma once
#include "Entity.h"

//子弹
class Bullet:public Entity
{
protected:
    bool ofplayer_;
    bool exist_;
    bool dead_;
    float damage_;

public:
    Bullet(const sf::Texture &texture,sf::Vector2f position);  //初始化子弹位置，初始化资源引用，默认子弹设置
    Bullet(const sf::Texture &texture,sf::Vector2f position,float damage);

public:
    virtual void update()=0;
    bool isDead();
    bool isPlayer();
    bool isOut();
    void markDead();
    float getDamage();
    //void drawwindow(sf::RenderWindow& window) override;  //渲染子弹至屏幕
    //void drawtexture(sf::RenderTexture& texture) override;
};