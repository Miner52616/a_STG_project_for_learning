#pragma once
#include "Entity.h"
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"
#include "packages/EffectConfig.h"

class Behavior;
class Resource;
//子弹
class Bullet:public Entity
{
friend void aim_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
friend void aim_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
friend void direct_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
friend void direct_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
friend void direct_move3(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
friend void gravity_move(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
friend void rotate_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
friend void behavior_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
friend void rotate_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource);

protected:
    bool show_hitbox_=false;

    Resource* resource_;//追踪弹将向phasecontroller申请最近的目标位置
    YellowPage* yellowpage_;//自机狙将访问player获取player位置
    sf::Texture* bullet_texture_;
    bool ofplayer_;
    bool exist_;
    bool grazed_;
    bool dead_;
    bool active_;
    float damage_;
    std::unique_ptr<BulletConfig> bulletconfig_;
    std::unique_ptr<BulletConfig> sonconfig_;
    EffectConfig effectconfig_;
    sf::CircleShape hitbox_draw_;

private:
    void selfbehavior();

public:
    Bullet(sf::Texture &texture,sf::Vector2f position);  //初始化子弹位置，初始化资源引用，默认子弹设置
    Bullet(sf::Texture &texture,sf::Vector2f position,float damage);

public:
    virtual void update();
    void drawtexture(sf::RenderTexture& texture) override;
    void setPosition(sf::Vector2f position) override;

    bool isDead() const;
    bool isAcitve();
    bool isGrazed();
    bool isPlayer();
    bool isOut();
    void rebuild(sf::Texture &texture,sf::Vector2f position);
    void rebuild(sf::Texture &texture,sf::Vector2f position,float damage);
    void rebuild_Initialize();
    void initialize();
    void setBulletConfig(std::unique_ptr<BulletConfig> bulletconfig);
    //void initialize_EffectConfig();
    //void initialize_playerEffectConfig();
    //void reset_EffectConfig();
    BulletConfig* getBulletConfig();
    EffectConfig* getEffectConfig();
    void setYellowPage(YellowPage* yellowpage);
    void setResource(Resource* resource);
    void setDead(bool dead);
    void setHitbox_r(int r);
    void setbelong(bool ofplayer);
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

using UpdateFunc = void(*)(Bullet& bullet,YellowPage* yellowpage,Resource* resource);

void aim_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
void aim_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
void direct_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
void direct_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
void direct_move3(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
void gravity_move(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
void rotate_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
void behavior_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
void rotate_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource);//绕着中心点的多阶段的移动函数

extern UpdateFunc update_table[];