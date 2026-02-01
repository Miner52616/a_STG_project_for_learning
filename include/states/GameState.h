#pragma once
#include "core/state.h"
#include "ui/Frame.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Bullet.h"

class GameState:public State
{
private:
    long long int frame_;
    Player player_;
    Enemy enemy1_;
    Frame outline1;

    std::vector<std::unique_ptr<Bullet>> player_bulletlist;

public:
    void ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;  //处理被分发到的事件
    void Update() override;  //统一更新属性
    void Render(sf::RenderWindow& window) override;  //统一渲染至屏幕

public:
    GameState(application &app);  //初始化起始帧，初始化资源引用，初始化实体设置

protected:
    void player_bulletlist_update();  //更新玩家子弹数组

protected:
    void player_bulletlist_move();  //所有子弹按规定移动
    void player_bulletlist_clear();  //清理无效子弹
    void player_bulletlist_add();   //加入新的子弹
    void player_bulletlist_drawwindow(sf::RenderWindow& window);  //渲染玩家子弹
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Closed);  //处理“关闭窗口”事件
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Resized&);  //拉伸窗口时保证宽高比一致
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key);//处理“按钮按下”（单点）事件
    void HandleEvent(sf::RenderWindow& window,auto){};  //其它无反应事件
};