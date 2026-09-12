#pragma once
#include "Entity.h"
#include "core/Clock.h"
#include "packages/Resource.h"
#include "packages/YellowPage.h"
#include "packages/BulletConfig.h"
#include "packages/BombConfig.h"
#include "packages/EffectConfig.h"
#include "overlays/overlays/texturecurtains/MissCurtain.h"

class application;
class Frame;
class BulletManager;
class Child_Plane;

//玩家，作为游戏中的自机
class Player:public Entity
{
private:
    bool hitbox_exist_;
    float a_low_;
    float a_high_;
    float a_;
    float v_low_;
    float v_high_;
    float speed_x_;
    float speed_y_;
    float v_limit_;
    int grazebox_r;
    bool shining_;
    int control_mode_;
    Clock shining_clock_;//闪烁速度
    Clock clock_;
    Clock life_clock_;//miss冷却（miss后无敌时间）
    Clock bomb_clock_;//bomb冷却
    Clock auto_clock_;
    //Frame &outline_;
    YellowPage* yellowpage_;
    Resource* resource_;
    std::unique_ptr<BulletConfig> bulletconfig_;
    std::unique_ptr<EffectConfig> effectconfig_;
    std::unique_ptr<OverlayConfig> overlayconfig_;
    std::unique_ptr<BombConfig> bombconfig_;
    std::vector<std::unique_ptr<Child_Plane>> child_planes_;

    sf::Sprite hitbox_texture_;
    sf::CircleShape point_;

    MissCurtain miss_curtain_;

    bool continued_=false;
    bool missed_=false;
    int life_;
    int bomb_;
    int power_;

private:
    void check_position();
    void setBulletConfig();
    void setEffectConfig();
    void setBombConfig();
    void setOverlayConfig();
    void resetBombConfig();
    void useBomb();

public:
    Player(const sf::Texture &texture/*,Frame &outline*/,Resource* resource);  //初始化资源引用，默认玩家设置
    void update();  //更新玩家属性
    void drawwindow(sf::RenderWindow& window) override;  //渲染玩家至屏幕
    void drawtexture(sf::RenderTexture& texture) override;
    void drawMissShaders(sf::RenderTexture& texture);
    void clock_count();

    void setContinued(bool continued);
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    void setPosition() override;
    void setPosition(sf::Vector2f position) override;
    bool isContinued();
    bool isMissed();
    void setMissed(bool miss);
    int getLifeNum();
    void setLifeNum(int life);
    int getBombNum();
    int getGrazebox_r();
    void be_damage();
};

class Child_Plane:public Entity
{
friend Player;
private:
    Player* player_;
    Clock clock_;
    sf::Vector2f relative_position_;
    sf::Vector2f target_position_;
    Resource* resource_;
    std::shared_ptr<BulletConfig> bulletconfig_;
    std::unique_ptr<EffectConfig> effectconfig_;

public:
    Child_Plane(const sf::Texture &texture);
    Child_Plane(const sf::Texture &texture,Resource* resource,Player* player);
    void update();
    //void drawtexture(sf::RenderTexture& texture);
    sf::Vector2f getRelativePosition();
    void setRelativePosition(sf::Vector2f position);
    void setPosition(sf::Vector2f position) override;
    void setTargetPosition(sf::Vector2f target_position);
    void setBulletDirection(sf::Vector2f direction);
    void setBulletConfig();
    void setEffectConfig();
    void setResource(Resource* resource,Player* player);
    void clock_count();
};