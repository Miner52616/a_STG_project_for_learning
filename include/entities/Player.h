#pragma once
#include "Entity.h"

struct Rate
{
    int frame;
    int current;
};

//玩家，作为游戏中的自机
class Player:public Entity
{
private:
    bool hitbox_exist_;
    int speed_;
    Rate rate_;
    bool request_shoot_;

public:
    bool Handle_shoot_request();  //是否有发弹申请，使用后处理发弹申请

public:
    Player(const sf::Texture &texture);  //初始化资源引用，默认玩家设置

    void Player_update();  //更新玩家属性
    void drawwindow(sf::RenderWindow& window) override;  //渲染玩家至屏幕
};