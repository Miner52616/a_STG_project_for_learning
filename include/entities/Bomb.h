#pragma once
#include "Entity.h"

class Behavior;

class Bomb:public Entity
{
protected:
    bool dead_;
    float damage_;
    
    std::vector<Behavior*> behaviorlist_;

public:
    Bomb(const sf::Texture &texture,sf::Vector2f position);  //初始化炸弹位置，初始化资源引用，默认炸弹设置
    Bomb(const sf::Texture &texture,sf::Vector2f position,float damage);  //初始化炸弹位置，初始化资源引用，默认炸弹设置

public:
    virtual void update()=0;
    bool isDead() const override;
    void markDead();
    float getDamage();
};