#pragma once
#include "Entity.h"
#include "core/Clock.h"

class application;
class Frame;
class BulletManager;

//玩家，作为游戏中的自机
class Player:public Entity
{
private:
    bool hitbox_exist_;
    int speed_;
    bool request_shoot_;
    Clock clock_;
    Frame &outline_;
    BulletManager &bulletmanager_;

private:
    void check_position();

public:
    bool Handle_shoot_request();  //是否有发弹申请，使用后处理发弹申请
    void clock_count();

public:
    Player(application &app,const sf::Texture &texture,Frame &outline,BulletManager& bulletmanager);  //初始化资源引用，默认玩家设置

    void Player_update();  //更新玩家属性
    void drawwindow(sf::RenderWindow& window) override;  //渲染玩家至屏幕
};