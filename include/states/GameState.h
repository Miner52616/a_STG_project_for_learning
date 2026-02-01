#pragma once
#include "core/state.h"
#include "core/Clock.h"
#include "ui/Frame.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Bullet.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"

class GameState:public State
{
private:
    long long int frame_;
    Frame outline1;
    sf::RectangleShape top_cover1;
    sf::RectangleShape top_cover2;

    EnemyManager enemymanager_;
    BulletManager bulletmanager_;

    Player player_;
    Enemy enemy1_;

    std::vector<Enemy*> enemylist_;

public:
    void ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;  //处理被分发到的事件
    void Update() override;  //统一更新属性
    void Render(sf::RenderWindow& window) override;  //统一渲染至屏幕

public:
    GameState(application &app);  //初始化起始帧，初始化资源引用，初始化实体设置

protected:
    void enemylist_add(Enemy* enemy);
    void clock_update();
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Closed);  //处理“关闭窗口”事件
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Resized&);  //拉伸窗口时保证宽高比一致
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key);//处理“按钮按下”（单点）事件
    void HandleEvent(sf::RenderWindow& window,auto){};  //其它无反应事件
};