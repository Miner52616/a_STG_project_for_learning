#pragma once
#include "Entity.h"
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"
#include "packages/EffectConfig.h"

class Behavior;
class Resource;
class UpdateTableLibrary;
class UpdateSpecialLibrary;
class Debug;

//子弹
class Bullet:public Entity
{
//更新函数表函数声明为友元函数
friend UpdateTableLibrary;

//单独全局更新函数声明为友元函数
friend UpdateSpecialLibrary;

//debug相关属性
protected:
    bool show_hitbox_;

protected:
    Resource* resource_;//追踪弹将向phasecontroller申请最近的目标位置
    YellowPage* yellowpage_;//自机狙将访问player获取player位置
    sf::Texture* bullet_texture_;
    bool ofplayer_;
    bool exist_;
    bool grazed_;
    bool dead_;
    bool active_;
    float damage_;
    BulletConfig bulletconfig_;
    BulletConfig sonconfig_;
    EffectConfig effectconfig_;
    sf::CircleShape hitbox_draw_;

private:
    void selfbehavior();

public:
    Bullet(sf::Texture &texture,sf::Vector2f position);  //初始化子弹位置，初始化资源引用，默认子弹设置
    Bullet(sf::Texture &texture,sf::Vector2f position,Debug debug);
    Bullet(sf::Texture &texture,sf::Vector2f position,float damage);

public:
    virtual void update();
    void drawtexture(sf::RenderTexture& texture) override;
    void setPosition(sf::Vector2f position) override;

    bool isDead() const;
    bool isAcitve();
    bool isGrazed();
    bool isPlayer();
    bool isNotClear();
    bool isOut();
    void rebuild();
    //void rebuild(sf::Texture &texture,sf::Vector2f position);
    //void rebuild(sf::Texture &texture,sf::Vector2f position,float damage);
    void rebuild_Initialize();
    void initialize();
    //void setBulletConfig(std::unique_ptr<BulletConfig> bulletconfig);
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

//以下为更新函数表的函数
class UpdateTableLibrary
{
public:
    static void aim_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
    static void aim_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
    static void direct_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
    static void direct_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
    static void direct_move3(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
    static void gravity_move(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
    static void rotate_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
    static void behavior_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
    static void rotate_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource);//绕着中心点的多阶段的移动函数
    static void rotate_move3(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
    static void void_update(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
};

using UpdateFunc = void(*)(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
extern UpdateFunc update_table[];

/**************************************************************************************** */
//以下为不在函数表内统一调度的override_update_function
//这里面一般一个函数只有某种极特定的子弹会调用，故直接写在外面，需要时直接取用函数指针指定

class UpdateSpecialLibrary
{
public:
    static void divide_sea1(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
    static void divide_sea2(Bullet& bullet,YellowPage* yellowpage,Resource* resource);
};