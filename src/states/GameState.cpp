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
    high_score_(0),
    score_(0),
    difficulty_(app_.mainFont_),
    high_score_line_(app_.mainFont_),
    score_line_(app_.mainFont_),
    life_line_(app_.mainFont_,app_.lifeUI_),
    bomb_line_(app_.mainFont_,app_.bombUI_),
    outline1({75,30},{845,930},5,sf::Color::Black,sf::Color(128,128,128)),
    window_sprite_(game_window_.getTexture()),
    bulletmanager_(app,bulletlist_,bulletfactory_),
    dropmanager_(droplist_,dropfactory_),
    bombmanager_(bomblist_,bombfactory_),
    collisionsystem_(bulletlist_,droplist_,bomblist_),
    phasecontroller_(app,phaselist_)
{
    std::cout<<"Game Loading..."<<std::endl;

    //**** 1 ui界面和游戏小窗基础设置
    //设置ui（ui完全不依赖资源）
    set_ui();
    set_gamewindow();
    std::cout<<"UI and Gamewindow Set"<<std::endl;

    //**** 2 各种资源包创建并初始化，同时创建好资源包需要的对象
    //初始化资源，资源包含各大manager和system的引用
    resource_=std::make_unique<Resource>(app,bulletmanager_,dropmanager_,bombmanager_,collisionsystem_,phasecontroller_);
    std::cout<<"Resource Set"<<std::endl;

    //创建并初始化玩家对象
    set_player();
    std::cout<<"Player Set"<<std::endl;

    //初始化黄页，黄页包含ui和玩家指针（此时所有需要被访问的对象已经创建并初始化）
    yellowpage_=std::make_unique<YellowPage>(player_.get(),high_score_line_,score_line_);
    std::cout<<"YellowPage Set"<<std::endl;

    //至此广泛意义上的资源创建完成。后续直接创建对象

    //**** 3 为GameState中本身存在底层对象资源绑定
    //在资源创建前已经被创建对象的资源绑定
    bundle_resource();
    std::cout<<"Resource and YellowPage Bundle"<<std::endl;

    //**** 4 创建游戏对象
    //创建并初始化行为对象
    set_behavior();
    std::cout<<"Behavior Create and Initialize"<<std::endl;
    
    //创建并初始化敌人/Boss对象
    set_entity();
    std::cout<<"Entity Create and Initialize"<<std::endl;

    //创建并初始化游戏阶段对象
    set_phase();
    std::cout<<"Phase Create and Initialize"<<std::endl;

    //**** 5 根据对象间运行信息流上下级绑定   
    bundle_leader_menber();
    std::cout<<"Leader and Member Bundle"<<std::endl;

    std::cout<<"Game Prepared"<<std::endl;
}

void GameState::set_ui()
{
    //初始化overlays
    curtain_.setPosition({0,0});
    
    //初始化设置固定ui
    difficulty_.setTextPosition({980,20});
    difficulty_.setTextText("Easy");
    difficulty_.setTextSize(50);

    high_score_line_.setLinePosition({865,130});
    high_score_line_.setLineText("High Score");
    high_score_line_.setCurrentNum(0);
    high_score_line_.setMaxNum(999999999);
    score_line_.setLinePosition({865,180});
    score_line_.setLineText("         Score");
    score_line_.setCurrentNum(0);
    score_line_.setMaxNum(999999999);
    life_line_.setLinePosition({865,250});
    life_line_.setLineText("Life");
    life_line_.setMaxNum(8);
    life_line_.setCurrentNum(2);
    bomb_line_.setLinePosition({865,300});
    bomb_line_.setLineText("Bomb");
    bomb_line_.setMaxNum(8);
    bomb_line_.setCurrentNum(3);
}

void GameState::set_gamewindow()
{
    //初始化设置游戏小窗
    window_sprite_.setTexture(game_window_.getTexture());
    window_sprite_.setScale({1.f,-1.f});
    window_sprite_.setPosition({75,30+900});
}

void GameState::bundle_resource()
{
    //行为对象资源绑定
    dropfactory_.set_Resourse(resource_.get());
    dropfactory_.set_YellowPage(yellowpage_.get());
    dropmanager_.set_resource(resource_.get());
    dropmanager_.set_yellowpage(yellowpage_.get());
    bombmanager_.set_Resource(resource_.get());
    bombfactory_.set_Resourse(resource_.get());
    bombfactory_.set_YellowPage(yellowpage_.get());
    collisionsystem_.set_resource(resource_.get());
    collisionsystem_.set_yellowpage(yellowpage_.get());
}

void GameState::set_player()
{
    //创建游戏对象并初始化
    player_=std::make_unique<Player>(app_.playerTexture_,outline1,resource_.get());
    player_->setPosition({385,450});
    player_->setResource(resource_.get());
}

void GameState::set_behavior()
{
    enemy1_drop_=std::make_unique<ScoreDrop1>(resource_.get(),yellowpage_.get());
    enemy1_move_=std::make_unique<MoveToRandom1>(resource_.get(),yellowpage_.get());
    enemy1_shoot_=std::make_unique<AimShoot1>(resource_.get(),yellowpage_.get()); 
    enemy2_drop_=std::make_unique<ScoreDrop1>(resource_.get(),yellowpage_.get());
    enemy2_move_=std::make_unique<MoveToRandom1>(resource_.get(),yellowpage_.get());
    enemy2_shoot_=std::make_unique<AimShoot1>(resource_.get(),yellowpage_.get()); 
    spell1_move_=std::make_unique<MoveToRandom1>(resource_.get(),yellowpage_.get());
    spell1_shoot_=std::make_unique<AimShoot1>(resource_.get(),yellowpage_.get()); 
}

void GameState::set_entity()
{
    enemy1_=std::make_unique<Enemy>(app_.enemyTexture_);
    enemy1_->setPosition({460,100});
    enemy1_->setHP(200);
    enemy1_->set_start_end(240,216000);
    enemy2_=std::make_unique<Enemy>(app_.enemyTexture_);
    enemy2_->setPosition({460,100});
    enemy2_->setHP(200);
    enemy2_->set_start_end(240,216000);
    boss1_=std::make_unique<Boss>(app_.playerTexture_,resource_.get());
    boss1_->setPosition({460,150});
    spell1_=std::make_unique<SpellPhase>(resource_.get(),yellowpage_.get(),360);
}

void GameState::set_phase()
{
    midphase1_=std::make_unique<MidPhase>(resource_.get(),yellowpage_.get(),600);
    voidphase1_=std::make_unique<VoidPhase>(resource_.get(),yellowpage_.get(),180);
    bossphase1_=std::make_unique<BossPhase>(resource_.get(),yellowpage_.get());
    voidphase2_=std::make_unique<VoidPhase>(resource_.get(),yellowpage_.get(),180);
}

void GameState::bundle_leader_menber()
{
    //****上级绑定下级****
    //敌人绑定行为
    //符卡绑定行为
    //Boss绑定符卡
    //游戏阶段绑定敌人/Boss
    //游戏阶段控制器绑定游戏阶段

    //****下级绑定上级****
    //行为绑定敌人/Boss
    //符卡绑定Boss
    
    //敌人与行为相互绑定
    enemy1_drop_->set_entity(enemy1_.get());
    enemy1_->addBehavior(enemy1_drop_.get());
    enemy1_move_->set_entity(enemy1_.get());
    enemy1_->addBehavior(enemy1_move_.get());
    enemy1_shoot_->set_entity(enemy1_.get());
    enemy1_->addBehavior(enemy1_shoot_.get());
    enemy2_drop_->set_entity(enemy2_.get());
    enemy2_->addBehavior(enemy2_drop_.get());
    enemy2_move_->set_entity(enemy2_.get());
    enemy2_->addBehavior(enemy2_move_.get());
    enemy2_shoot_->set_entity(enemy2_.get());
    enemy2_->addBehavior(enemy2_shoot_.get());

    //行为绑定Boss，符卡绑定行为，符卡绑定Boss，Boss绑定符卡
    spell1_move_->set_entity(boss1_.get());
    spell1_->addBehavior(spell1_move_.get());
    spell1_shoot_->set_entity(boss1_.get());
    spell1_->addBehavior(spell1_shoot_.get());
    spell1_->setBoss(boss1_.get());
    boss1_->add_phase(spell1_.get());
    
    //游戏阶段绑定敌人/Boss
    midphase1_->add_enemy(enemy1_.get());
    midphase1_->add_enemy(enemy2_.get());
    bossphase1_->setBoss(boss1_.get());

    //游戏阶段控制器绑定游戏阶段
    phasecontroller_.add_process(midphase1_.get());
    phasecontroller_.add_process(voidphase1_.get());
    phasecontroller_.add_process(bossphase1_.get());
    phasecontroller_.add_process(voidphase2_.get());
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
    //std::cout<<"phase update"<<std::endl;

    bulletmanager_.update();//后续需要把清理子弹放到帧末统一处理，以不影响碰撞检测
    //std::cout<<"enemy update"<<std::endl;
    dropmanager_.update();
    //std::cout<<"drop update"<<std::endl;
    bombmanager_.update();
    //std::cout<<"bomb update"<<std::endl;
    
    handlecollision();
    //std::cout<<"collision update"<<std::endl;

    bulletmanager_.clear();
    //std::cout<<"bullet clear"<<std::endl;
    dropmanager_.clear_dead();
    //std::cout<<"enemy clear"<<std::endl;
    bombmanager_.clear_dead();
    //std::cout<<"bomb clear"<<std::endl;

    life_line_.setCurrentNum(player_->getLifeNum());
    bomb_line_.setCurrentNum(player_->getBombNum());

    clock_update();

    frame_++;
}

void GameState::Render(sf::RenderWindow& window)
{
    game_window_.clear();

    outline1.drawwindow(window);

    //player_->drawwindow(window);
    player_->drawtexture(game_window_);

    //phasecontroller_.render(window);
    phasecontroller_.render(game_window_);

    if(!phasecontroller_.apply_change())
    {
        std::cout<<"Game Over"<<std::endl;
        app_.stack_.pushRequest(std::make_unique<PauseState>(app_));
    }

    dropmanager_.render(game_window_);
    bulletmanager_.render(game_window_);
    bombmanager_.render(game_window_);

    window_sprite_.setTexture(game_window_.getTexture());
    window.draw(window_sprite_);

    difficulty_.DrawText(window);

    high_score_line_.render(window);
    score_line_.render(window);
    life_line_.render(window);
    bomb_line_.render(window);

    curtain_.render(window);
}

void GameState::clock_update()
{
    player_->clock_count();
}

void GameState::handlecollision()
{
    bombmanager_.ProcessCollision();
    resource_->collisionsystem_.ProcessCollision(yellowpage_->player_);
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