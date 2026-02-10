#pragma once
#include "core/state.h"
#include "core/Clock.h"
#include "ui/Frame.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Boss.h"
#include "entities/Bullet.h"
#include "phases/phases/SpellPhase.h"
#include "enemies/Enemy1.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "manager/CollisionSystem.h"

class GameState:public State
{
private:
    long long int frame_;
    Frame outline1;
    sf::RectangleShape top_cover1;
    sf::RectangleShape top_cover2;
    sf::RectangleShape left_cover1;
    sf::RectangleShape left_cover2;
    sf::RectangleShape right_cover1;
    sf::RectangleShape right_cover2;
    sf::RectangleShape bottom_cover1;
    sf::RectangleShape bottom_cover2;

    std::vector<std::unique_ptr<Bullet>> bulletlist_;
    std::vector<std::shared_ptr<Phase>> phaselist_;

    BulletManager bulletmanager_;
    CollisionSystem collisionsystem_;
    PhaseController phasecontroller_;

    std::shared_ptr<Player> player_;
//    Boss boss1_;
    std::shared_ptr<Boss> boss1_;
    std::shared_ptr<SpellPhase> spell1_;

public:
    void ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;  //处理被分发到的事件
    void Update() override;  //统一更新属性
    void Render(sf::RenderWindow& window) override;  //统一渲染至屏幕

public:
    GameState(application &app);  //初始化起始帧，初始化资源引用，初始化实体设置

protected:
    void clock_update();
    void handlecollision();
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Closed);  //处理“关闭窗口”事件
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Resized&);  //拉伸窗口时保证宽高比一致
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key);//处理“按钮按下”（单点）事件
    void HandleEvent(sf::RenderWindow& window,auto){};  //其它无反应事件
};