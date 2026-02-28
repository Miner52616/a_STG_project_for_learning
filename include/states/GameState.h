#pragma once
#include "core/state.h"
#include "core/Clock.h"
#include "ui/Frame.h"
#include "ui/NumLine1_1.h"
#include "ui/NumLine1.h"
#include "ui/Text.h"
#include "overlays/overlays/Curtain1.h"
#include "packages/Resource.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Boss.h"
#include "entities/Bullet.h"
#include "entities/Drop.h"
#include "phases/phases/MidPhase.h"
#include "phases/phases/VoidPhase.h"
#include "phases/phases/BossPhase.h"
#include "phases/phases/SpellPhase.h"
#include "enemies/Enemy1.h"
#include "behaviors/behaviors/AimShoot.h"
#include "behaviors/behaviors/MoveToRandom1.h"
#include "behaviors/behaviors/ScoreDrop1.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/BulletFactory.h"
#include "manager/DropManager.h"
#include "manager/DropFactory.h"
#include "manager/PhaseController.h"
#include "manager/CollisionSystem.h"

class GameState:public State
{
private:
    long long int frame_;
    long long int high_score_;
    long long int score_;

    Frame outline1;
    Text difficulty_;
    NumLine1 high_score_line_;
    NumLine1 score_line_;
    NumLine1_1 life_line_;
    NumLine1_1 bomb_line_;

    sf::RenderTexture game_window_{{770u,900u}};
    sf::Sprite window_sprite_;

    Curtain1 curtain_;

    /*
    sf::RectangleShape top_cover1;
    sf::RectangleShape top_cover2;
    sf::RectangleShape left_cover1;
    sf::RectangleShape left_cover2;
    sf::RectangleShape right_cover1;
    sf::RectangleShape right_cover2;
    sf::RectangleShape bottom_cover1;
    sf::RectangleShape bottom_cover2;
    */

    std::vector<std::unique_ptr<Bullet>> bulletlist_;
    std::vector<std::unique_ptr<Drop>> droplist_;
    std::vector<std::shared_ptr<Phase>> phaselist_;

    BulletFactory bulletfactory_;
    DropFactory dropfactory_;

    BulletManager bulletmanager_;
    DropManager dropmanager_;
    CollisionSystem collisionsystem_;
    PhaseController phasecontroller_;

    std::shared_ptr<Player> player_;
    std::shared_ptr<Enemy> enemy1_;
    std::shared_ptr<Enemy> enemy2_;
    std::shared_ptr<Boss> boss1_;
    std::shared_ptr<SpellPhase> spell1_;

    std::shared_ptr<ScoreDrop1> enemy1_drop_;
    std::shared_ptr<AimShoot1> enemy1_shoot_;
    std::shared_ptr<MoveToRandom1> enemy1_move_;
    std::shared_ptr<AimShoot1> enemy2_shoot_;
    std::shared_ptr<MoveToRandom1> enemy2_move_;
    std::shared_ptr<AimShoot1> spell1_shoot_;
    std::shared_ptr<MoveToRandom1> spell1_move_;

    std::shared_ptr<MidPhase> midphase1_;
    std::shared_ptr<VoidPhase> voidphase1_;
    std::shared_ptr<BossPhase> bossphase1_;
    std::shared_ptr<VoidPhase> voidphase2_;

    std::shared_ptr<Resource> resource_;

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