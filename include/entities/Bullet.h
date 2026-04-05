#pragma once
#include "Entity.h"
#include "behaviors/Behavior.h"

class Behavior;

//子弹
class Bullet:public Entity
{
protected:
    bool ofplayer_;
    bool exist_;
    bool grazed_;
    bool dead_;
    bool active_;
    float damage_;
    std::vector<std::unique_ptr<Behavior>> behaviorlist_;

public:
    Bullet(const sf::Texture &texture,sf::Vector2f position);  //初始化子弹位置，初始化资源引用，默认子弹设置
    Bullet(const sf::Texture &texture,sf::Vector2f position,float damage);

public:
    virtual void update();
    bool isDead();
    bool isAcitve();
    bool isGrazed();
    bool isPlayer();
    bool isOut();
    void setbelong(bool ofplayer);
    void addBehavior(std::unique_ptr<Behavior> behavior);
    void markDead();
    void setActive(bool active);
    void markGrazed();
    float getDamage();
    //void drawwindow(sf::RenderWindow& window) override;  //渲染子弹至屏幕
    //void drawtexture(sf::RenderTexture& texture) override;
};