#pragma once
#include "Entity.h"
#include "core/Clock.h"
#include "packages/Resource.h"
#include "packages/YellowPage.h"
#include "packages/BulletConfig.h"
#include "packages/BombConfig.h"
#include "packages/EffectConfig.h"

class application;
class Frame;
class BulletManager;
class Child_Plane;

//玩家，作为游戏中的自机
class Player:public Entity
{
private:
    bool hitbox_exist_;
    int speed_;
    bool request_shoot_;
    Clock clock_;
    Clock life_clock_;
    Clock bomb_clock_;
    Frame &outline_;
    YellowPage* yellowpage_;
    Resource* resource_;
    std::shared_ptr<BulletConfig> bulletconfig_;
    std::unique_ptr<OverlayConfig> overlayconfig_;
    std::unique_ptr<BombConfig> bombconfig_;
    std::vector<std::unique_ptr<Child_Plane>> child_planes_;

    sf::CircleShape point_;

    int life_;
    int bomb_;
    int power_;

private:
    void check_position();

public:
    bool Handle_shoot_request();  //是否有发弹申请，使用后处理发弹申请
    void useBomb();
    void clock_count();

public:
    Player(const sf::Texture &texture,Frame &outline,Resource* resource);  //初始化资源引用，默认玩家设置

    void setBulletConfig();
    void setBombConfig();
    void setOverlayConfig();
    void resetBombConfig();
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    void setPosition() override;
    void setPosition(sf::Vector2f position) override;
    int getLifeNum();
    int getBombNum();
    void be_damage();
    void Player_update();  //更新玩家属性
    void drawwindow(sf::RenderWindow& window) override;  //渲染玩家至屏幕
    void drawtexture(sf::RenderTexture& texture) override;
};

class Child_Plane:public Entity
{
private:
    Player* player_;
    Clock clock_;
    sf::Vector2f relative_position_;
    sf::Vector2f target_position_;
    Resource* resource_;
    std::shared_ptr<BulletConfig> bulletconfig_;

public:
    Child_Plane(const sf::Texture &texture);
    Child_Plane(const sf::Texture &texture,Resource* resource,Player* player);
    void update();
    //void drawtexture(sf::RenderTexture& texture);
    sf::Vector2f getRelativePosition();
    void setRelativePosition(sf::Vector2f position);
    void setPosition(sf::Vector2f position) override;
    void setTargetPosition(sf::Vector2f target_position);
    void setBulletConfig();
    void setResource(Resource* resource,Player* player);
    void clock_count();
};