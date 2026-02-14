#include "states/GameState.h"
#include "states/PauseState.h"
#include "phases/phases/MidPhase.h"
#include "phases/phases/VoidPhase.h"
#include "phases/phases/BossPhase.h"
#include "core/application.h"
#include "collision/CollisionCheck.h"
#include <iostream>

GameState::GameState(application &app):
    State(app),
    frame_(0),
    outline1({75,30},{845,930},5,sf::Color::Black,sf::Color(128,128,128)),
    bulletmanager_(app,bulletlist_,bulletfactory_),
    collisionsystem_(bulletlist_),
    phasecontroller_(app,phaselist_)
{
    std::cout<<"Game Loading..."<<std::endl;

    //****第一步————以下为创建对象，与资源无关设置初始化部分
    curtain_.setPosition({0,0});
    
    //初始化设置固定ui
    top_cover1.setPosition({0,0});
    top_cover1.setSize({1280,25});
    top_cover1.setFillColor(sf::Color::Black);
    top_cover2.setPosition({70,25});
    top_cover2.setSize({780,5});
    top_cover2.setFillColor(sf::Color(128,128,128));
    left_cover1.setPosition({0,0});
    left_cover1.setSize({70,960});
    left_cover1.setFillColor(sf::Color::Black);
    left_cover2.setPosition({70,25});
    left_cover2.setSize({5,910});
    left_cover2.setFillColor(sf::Color(128,128,128));
    right_cover1.setPosition({850,0});
    right_cover1.setSize({430,960});
    right_cover1.setFillColor(sf::Color::Black);
    right_cover2.setPosition({845,25});
    right_cover2.setSize({5,910});
    right_cover2.setFillColor(sf::Color(128,128,128));
    bottom_cover1.setPosition({0,935});
    bottom_cover1.setSize({1280,25});
    bottom_cover1.setFillColor(sf::Color::Black);
    bottom_cover2.setPosition({70,930});
    bottom_cover2.setSize({780,5});
    bottom_cover2.setFillColor(sf::Color(128,128,128));
    std::cout<<"UI Set"<<std::endl;

    //创建并“半"初始化资源。此时是弱资源，player指针为随机，访问会导致错误
    resource_=std::make_shared<Resource>(app,bulletmanager_,collisionsystem_,player_);
    std::cout<<"Resource Set"<<std::endl;

    //resource和player互相持有对方指针。先创建的需要在后创建的创建后重新获取指针
    //创建并初始化玩家对象
    player_=std::make_shared<Player>(app.playerTexture_,outline1,resource_);
    player_->setBulletConfig();
    player_->setPosition({640,480});
    player_->setResource(resource_);
    //完全初始化资源
    resource_->setPlayer(player_);//此时resource获取player指针
    std::cout<<"Player Set"<<std::endl;

    //创建行为对象
    enemy1_move_=std::make_shared<MoveToRandom1>();
    enemy1_shoot_=std::make_shared<AimShoot1>(); 
    enemy2_move_=std::make_shared<MoveToRandom1>();
    enemy2_shoot_=std::make_shared<AimShoot1>(); 
    spell1_move_=std::make_shared<MoveToRandom1>();
    spell1_shoot_=std::make_shared<AimShoot1>(); 
    
    //创建并初始化敌人/Boss对象
    enemy1_=std::make_shared<Enemy>(app.enemyTexture_);
    enemy1_->setPosition({460,100});
    enemy1_->setHP(200);
    enemy1_->set_start_end(240,216000);
    enemy2_=std::make_shared<Enemy>(app.enemyTexture_);
    enemy2_->setPosition({460,100});
    enemy2_->setHP(200);
    enemy2_->set_start_end(240,216000);
    boss1_=std::make_shared<Boss>(app.playerTexture_,resource_);
    boss1_->setPosition({460,150});
    spell1_=std::make_shared<SpellPhase>(resource_,360);
    
    //****第二步————资源绑定部分
    //行为对象资源绑定
    enemy1_move_->set_resource(resource_);
    enemy1_shoot_->set_resource(resource_);
    enemy2_move_->set_resource(resource_);
    enemy2_shoot_->set_resource(resource_);
    spell1_move_->set_resource(resource_);
    spell1_shoot_->set_resource(resource_);

    //****第三步————与资源相关的对象创建/设置初始化部分
    //行为对象资源相关初始化
    enemy1_shoot_->setBulletConfig();
    enemy2_shoot_->setBulletConfig();
    spell1_shoot_->setBulletConfig();

    //游戏阶段对象创建并初始化
    midphase1_=std::make_shared<MidPhase>(resource_,600);
    voidphase1_=std::make_shared<VoidPhase>(resource_,180);
    bossphase1_=std::make_shared<BossPhase>(resource_);
    voidphase2_=std::make_shared<VoidPhase>(resource_,180);

    //****第四步————对象间运行信息流上下级绑定部分
    //敌人/Boss对象与其下级行为/符卡相互绑定
    enemy1_move_->set_entity(enemy1_);
    enemy1_->addBehavior(enemy1_move_);
    enemy1_shoot_->set_entity(enemy1_);
    enemy1_->addBehavior(enemy1_shoot_);
    enemy2_move_->set_entity(enemy2_);
    enemy2_->addBehavior(enemy2_move_);
    enemy2_shoot_->set_entity(enemy2_);
    enemy2_->addBehavior(enemy2_shoot_);
    spell1_move_->set_entity(boss1_);
    spell1_->addBehavior(spell1_move_);
    spell1_shoot_->set_entity(boss1_);
    spell1_->addBehavior(spell1_shoot_);
    spell1_->setBoss(boss1_);
    boss1_->add_phase(spell1_);
    
    //游戏阶段对象与敌人/Boss对象相互绑定
    midphase1_->add_enemy(enemy1_);
    midphase1_->add_enemy(enemy2_);
    bossphase1_->setBoss(boss1_);

    //游戏阶段对象与游戏阶段控制器相互绑定
    phasecontroller_.add_process(midphase1_);
    phasecontroller_.add_process(voidphase1_);
    phasecontroller_.add_process(bossphase1_);
    phasecontroller_.add_process(voidphase2_);

    std::cout<<"Game Prepared"<<std::endl;
}

void GameState::ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event)
{
    event->visit
    (
        [this,&window](const auto event)
        {
            this->HandleEvent(window,event);
        }
    );
}

void GameState::Update()
{
    curtain_.update();

    player_->Player_update();

    phasecontroller_.update();

//    enemymanager_.update(frame_);

    bulletmanager_.update();//后续需要把清理子弹放到帧末统一处理，以不影响碰撞检测

    handlecollision();

    bulletmanager_.clear();

    clock_update();

    frame_++;
}

void GameState::Render(sf::RenderWindow& window)
{
    outline1.drawwindow(window);

    player_->drawwindow(window);

    phasecontroller_.render(window);
    if(!phasecontroller_.apply_change())
    {
        std::cout<<"Game Over"<<std::endl;
        app_.stack_.pushRequest(std::make_unique<PauseState>(app_));
    }

    bulletmanager_.render(window);

    window.draw(top_cover1);
    window.draw(top_cover2);
    window.draw(left_cover1);
    window.draw(left_cover2);
    window.draw(right_cover1);
    window.draw(right_cover2);
    window.draw(bottom_cover1);
    window.draw(bottom_cover2);

    curtain_.render(window);
}

void GameState::clock_update()
{
    player_->clock_count();
}

void GameState::handlecollision()
{
    phasecontroller_.ProcessCollision();
}

void GameState::HandleEvent(sf::RenderWindow& window,const sf::Event::Closed)
{
    window.close();
    std::cout<<"window closed";
}

void GameState::HandleEvent(sf::RenderWindow& window,const sf::Event::Resized&)
{
    app_.applyLetterBox();
    app_.window_.setView(app_.gameview_);
}

void GameState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if(key.code==sf::Keyboard::Key::Escape)
    {
        std::cout<<"Game Pause"<<std::endl;
        app_.stack_.pushRequest(std::make_unique<PauseState>(app_));
    }
}