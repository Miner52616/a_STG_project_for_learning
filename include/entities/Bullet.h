#pragma once
#include "Entity.h"
#include "behaviors/Behavior.h"

class Behavior;

//子弹
class Bullet:public Entity
{
protected:
    sf::Texture &bullet_texture_;
    bool ofplayer_;
    bool exist_;
    bool grazed_;
    bool dead_;
    bool active_;
    float damage_;
    std::vector<std::unique_ptr<Behavior>> behaviorlist_;

public:
    Bullet(sf::Texture &texture,sf::Vector2f position);  //初始化子弹位置，初始化资源引用，默认子弹设置
    Bullet(sf::Texture &texture,sf::Vector2f position,float damage);

public:
    virtual void update();
    bool isDead() const;
    bool isAcitve();
    bool isGrazed();
    bool isPlayer();
    bool isOut();
    void rebuild(sf::Texture &texture,sf::Vector2f position);
    void rebuild(sf::Texture &texture,sf::Vector2f position,float damage);
    void initialize();
    void setDead(bool dead);
    void setbelong(bool ofplayer);
    void addBehavior(std::unique_ptr<Behavior> behavior);
    void markDead();
    void setActive(bool active);
    void markGrazed();
    float getDamage();

    Bullet(const Bullet&) = delete;
    Bullet& operator=(const Bullet&) = delete;

    // 允许移动
    Bullet(Bullet&&) = default;
    Bullet& operator=(Bullet&&) = default;

    //void drawwindow(sf::RenderWindow& window) override;  //渲染子弹至屏幕
    //void drawtexture(sf::RenderTexture& texture) override;
};