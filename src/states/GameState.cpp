#include "states/GameState.h"
#include "states/PauseState.h"
#include "states/EndState.h"
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
    power_line_(app_.mainFont_),
    graze_line_(app_.mainFont_),
    bullet_line_(app_.mainFont_),
    effect_line_(app_.mainFont_),
    fps_line_(app_.mainFont_),
    life_line_(app_.mainFont_,app_.lifeUI_),
    bomb_line_(app_.mainFont_,app_.bombUI_),
    outline1({75,30},{845,930},5,sf::Color::Black,sf::Color(128,128,128)),
    window_sprite_(game_window_.getTexture()),
    //origin_window_sprite_(origin_window_.getTexture()),
    star_curtain1_(app_.curtain_texture1_),
    star_curtain2_(app_.curtain_texture1_,app_.color_flip_),
    star_curtain3_(app_.curtain_texture1_,app_.color_flip_),
    bulletfactory_(app),
    effectfactory_(app),
    bulletmanager_(app,bulletlist_,bulletfactory_),
    batchmanager_(batchlist_,batchfactory_),
    dropmanager_(droplist_,dropfactory_),
    bombmanager_(bomblist_,bombfactory_),
    effectmanager_(effectlist_,overlaylist_,effectfactory_),
    collisionsystem_(bulletlist_,droplist_,bomblist_),
    phasecontroller_(app,phaselist_),
    scriptloader_(app_.lua_)
{
    std::cout<<"/////////////////////////////////////////////////////////////"<<std::endl;
    std::cout<<"Game Loading..."<<std::endl;

    //**** 1 ui界面和游戏小窗基础设置
    //设置ui（ui完全不依赖资源）
    set_ui();
    set_gamewindow();
    std::cout<<"UI and Gamewindow Set"<<std::endl;

    //**** 2 各种资源包创建并初始化，同时创建好资源包需要的对象
    //初始化资源，资源包含各大manager和system的引用
    resource_=std::make_unique<Resource>(app,bulletmanager_,dropmanager_,bombmanager_,effectmanager_,batchmanager_,collisionsystem_,phasecontroller_);
    std::cout<<"Resource Set"<<std::endl;

    //创建并初始化玩家对象
    set_player();
    std::cout<<"Player Set"<<std::endl;

    //初始化黄页，黄页包含ui和玩家指针（此时所有需要被访问的对象已经创建并初始化）
    yellowpage_=std::make_unique<YellowPage>(player_.get(),high_score_line_,score_line_,power_line_,graze_line_);
    player_->setYellowPage(yellowpage_.get());
    std::cout<<"YellowPage Set"<<std::endl;

    //至此广泛意义上的资源创建完成。后续直接创建对象

    //**** 3 为GameState中本身存在底层对象资源绑定
    //在资源创建前已经被创建对象的资源绑定
    bundle_resource();
    std::cout<<"Resource and YellowPage Bundle"<<std::endl;

    //**** 4 创建游戏对象。这部分是对象是写死在.cpp中而非通过脚本阅读创建的。现已不再使用
    //创建并初始化行为对象
    set_behavior();
    std::cout<<"Behavior Create and Initialize"<<std::endl;
    
    //创建并初始化敌人/Boss对象
    set_entity();
    std::cout<<"Entity Create and Initialize"<<std::endl;

    //创建并初始化游戏阶段对象
    set_phase();
    std::cout<<"Phase Create and Initialize"<<std::endl;

    //**** 5 根据对象间运行信息流上下级绑定。这部分针对写死在.cpp中的对象。现已不再使用
    bundle_leader_menber();
    std::cout<<"Leader and Member Bundle"<<std::endl;

    //**** 6 阅读脚本创建对象并且绑定上下级关系
    read_script();
    std::cout<<"Script Loaded"<<std::endl;

    std::cout<<"Game Prepared!"<<std::endl;
    std::cout<<"/////////////////////////////////////////////////////////////"<<std::endl;
}

void GameState::set_ui()
{
    //初始化overlays
    //curtain_.setPosition({0,0});

    int num_x1=6;
    int num_y1=5;
    star_curtain1_.setNum(num_x1,num_y1);
    star_curtain1_.setR(240);
    star_curtain1_.setStart_Target({1280-0.5f*((float)1280/num_x1),960-0.5f*((float)960/num_y1)},{1880,-250},210);
    star_curtain1_.setEnable(true);

    int num_x2=9;
    int num_y2=8;
    star_curtain2_.setNum(num_x2,num_y2);
    star_curtain2_.setR(185);
    star_curtain2_.setStart_Target({1280-0.5f*((float)1280/num_x2),960-0.5f*((float)960/num_y2)},{1880,-250},210);
    star_curtain2_.setEnable(true);

    int num_x3=12;
    int num_y3=11;
    star_curtain3_.setNum(num_x3,num_y3);
    star_curtain3_.setR(120);
    star_curtain3_.setStart_Target({1280-0.5f*((float)1280/num_x3),960-0.5f*((float)960/num_y3)},{1880,-250},210);
    star_curtain3_.setEnable(true);
    star_curtain3_.setFlip(true);

    //初始化设置固定ui
    difficulty_.setTextPosition({960,20});
    difficulty_.setTextText("Phantasm");
    difficulty_.setTextSize(50);

    bullet_line_.setLinePosition({865,910});
    bullet_line_.setLineText("Bullet Num");
    bullet_line_.setCurrentNum(0);
    bullet_line_.setMaxNum(999999999);
    effect_line_.setLinePosition({865,860});
    effect_line_.setLineText("Effect Num");
    effect_line_.setCurrentNum(0);
    effect_line_.setMaxNum(999999999);
    fps_line_.setLinePosition({865,810});
    fps_line_.setLineText("Fps");
    fps_line_.setCurrentNum(0);
    fps_line_.setMaxNum(999999999);

    high_score_line_.setLinePosition({865,130});
    high_score_line_.setLineText("High Score");
    high_score_line_.setMaxNum(999999999);
    //std::cout <<app_.history_data_.high_score_<<std::endl;
    //std::cout <<app_.history_data_.cleared_<<std::endl;
    high_score_line_.setCurrentNum(app_.history_data_.high_score_);
    score_line_.setLinePosition({865,180});
    score_line_.setLineText("     Score");
    score_line_.setCurrentNum(0);
    score_line_.setMaxNum(999999999);
    power_line_.setLinePosition({865,400});
    power_line_.setLineText("     Power");
    power_line_.setCurrentNum(0);
    power_line_.setMaxNum(400);
    graze_line_.setLinePosition({865,450});
    graze_line_.setLineText("     Graze");
    graze_line_.setCurrentNum(0);
    graze_line_.setMaxNum(999999999);
    life_line_.setLinePosition({865,250});
    life_line_.setLineText("Player");
    life_line_.setMaxNum(8);
    life_line_.setCurrentNum(3);
    bomb_line_.setLinePosition({865,300});
    bomb_line_.setLineText("Spell");
    bomb_line_.setMaxNum(8);
    bomb_line_.setCurrentNum(3);
}

void GameState::set_gamewindow()
{
    //初始化设置游戏小窗
    window_sprite_.setTexture(game_window_.getTexture());
    window_sprite_.setScale({1.f,-1.f});
    window_sprite_.setPosition({75,30+900});
    
    //origin_window_sprite_.setTexture(origin_window_.getTexture());
    //origin_window_sprite_.setScale({1.f,-1.f});
    //origin_window_sprite_.setPosition({0,960});
}

void GameState::bundle_resource()
{
    //行为对象资源绑定
    bulletmanager_.setResource(resource_.get());
    bulletfactory_.setResource(resource_.get());
    bulletfactory_.setYellowPage(yellowpage_.get());
    dropfactory_.set_Resourse(resource_.get());
    dropfactory_.set_YellowPage(yellowpage_.get());
    dropmanager_.set_resource(resource_.get());
    dropmanager_.set_yellowpage(yellowpage_.get());
    bombmanager_.set_Resource(resource_.get());
    bombfactory_.set_Resourse(resource_.get());
    bombfactory_.set_YellowPage(yellowpage_.get());
    collisionsystem_.set_resource(resource_.get());
    collisionsystem_.set_yellowpage(yellowpage_.get());
    scriptloader_.setResource(resource_.get());
    scriptloader_.setYellowPage(yellowpage_.get());
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
    enemy1_drop_->setDropConfig(DropType::Power,20);
    enemy1_move_=std::make_unique<MoveToRandom1>(resource_.get(),yellowpage_.get());
    enemy1_shoot_=std::make_unique<AimShoot1>(resource_.get(),yellowpage_.get()); 
    enemy2_drop_=std::make_unique<ScoreDrop1>(resource_.get(),yellowpage_.get());
    enemy2_drop_->setDropConfig(DropType::Power,20);
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

void GameState::read_script()
{
    scriptloader_.loadPhase("include/luas/phases.lua");
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
    
    /*
    //敌人与行为相互绑定
    enemy1_drop_->set_entity(enemy1_.get());
    enemy1_->addBehavior(std::move(enemy1_drop_));
    enemy1_move_->set_entity(enemy1_.get());
    enemy1_->addBehavior(std::move(enemy1_move_));
    enemy1_shoot_->set_entity(enemy1_.get());
    enemy1_->addBehavior(std::move(enemy1_shoot_));
    enemy2_drop_->set_entity(enemy2_.get());
    enemy2_->addBehavior(std::move(enemy2_drop_));
    enemy2_move_->set_entity(enemy2_.get());
    enemy2_->addBehavior(std::move(enemy2_move_));
    enemy2_shoot_->set_entity(enemy2_.get());
    enemy2_->addBehavior(std::move(enemy2_shoot_));

    //行为绑定Boss，符卡绑定行为，符卡绑定Boss，Boss绑定符卡
    spell1_move_->set_entity(boss1_.get());
    spell1_->addBehavior(std::move(spell1_move_));
    spell1_shoot_->set_entity(boss1_.get());
    spell1_->addBehavior(std::move(spell1_shoot_));
    spell1_->setBoss(boss1_.get());
    boss1_->add_phase(std::move(spell1_));
    
    //游戏阶段绑定敌人/Boss
    midphase1_->add_enemy(std::move(enemy1_));
    midphase1_->add_enemy(std::move(enemy2_));
    bossphase1_->setBoss(std::move(boss1_));

    //游戏阶段控制器绑定游戏阶段
    phasecontroller_.add_process(std::move(midphase1_));
    phasecontroller_.add_process(std::move(voidphase1_));
    phasecontroller_.add_process(std::move(bossphase1_));
    phasecontroller_.add_process(std::move(voidphase2_));
    */
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
    //curtain_.update();
    star_curtain1_.update();
    star_curtain2_.update();
    star_curtain3_.update();

    continue_check();

    player_->Player_update();

    phasecontroller_.update();
    //std::cout<<"phase update"<<std::endl;

    batchmanager_.update();
    //std::cout<<"batch update"<<std::endl;
    bulletmanager_.update();//后续需要把清理子弹放到帧末统一处理，以不影响碰撞检测
    //std::cout<<"enemy update"<<std::endl;
    dropmanager_.update();
    //std::cout<<"drop update"<<std::endl;
    bombmanager_.update();
    //std::cout<<"bomb update"<<std::endl;
    effectmanager_.update();
    //std::cout<<"effect update"<<std::endl;
    
    handlecollision();
    //std::cout<<"collision update"<<std::endl;

    bulletmanager_.clear();
    //std::cout<<"bullet clear"<<std::endl;
    dropmanager_.clear_dead();
    //std::cout<<"enemy clear"<<std::endl;
    bombmanager_.clear_dead();
    //std::cout<<"bomb clear"<<std::endl;
    effectmanager_.clear_dead();
    //std::cout<<"effect clear"<<std::endl;
    batchmanager_.clear_empty();
    //std::cout<<"batch clear"<<std::endl;

    fps_update();

    fps_line_.setCurrentNum(fps_);
    bullet_line_.setCurrentNum(bulletlist_.size());
    effect_line_.setCurrentNum(effectlist_.size());
    life_line_.setCurrentNum(player_->getLifeNum());
    bomb_line_.setCurrentNum(player_->getBombNum());
    if((score_line_.getCurrentNum())>(high_score_line_.getCurrentNum()))
    {
        high_score_line_.setCurrentNum(score_line_.getCurrentNum());
    }

    if(!phasecontroller_.apply_change())
    {
        std::cout<<"Game Over"<<std::endl;
        SaveData data;
        if(player_->isContinued())
        {
            data.cleared_=app_.history_data_.cleared_;
        }
        else
        {
            data.cleared_=true;
        }
        data.high_score_=high_score_line_.getCurrentNum();
        app_.lua_.writeSave(data);
        app_.history_data_=app_.lua_.loadSave();
        app_.stack_.pushRequest(std::make_unique<EndState>(app_,*this));
    }

    clock_update();

    frame_++;
}

void GameState::Render(sf::RenderWindow& window)
{
    game_window_.clear();
    origin_window_.clear();

    outline1.drawwindow(window);
    outline1.drawTexture(origin_window_);

    //player_->drawwindow(window);
    player_->drawtexture(game_window_);

    dropmanager_.render(game_window_);
    bulletmanager_.render(game_window_);
    bombmanager_.render(game_window_);
    effectmanager_.render(game_window_);

    //phasecontroller_.render(window);
    phasecontroller_.render(game_window_);

    /*
    if(!phasecontroller_.apply_change())
    {
        std::cout<<"Game Over"<<std::endl;
        app_.stack_.pushRequest(std::make_unique<EndState>(app_,*this));
    }
        */

    

    window_sprite_.setTexture(game_window_.getTexture());
    window.draw(window_sprite_);
    origin_window_.draw(window_sprite_);

    difficulty_.DrawText(window);
    difficulty_.DrawText(origin_window_);

    high_score_line_.render(window);
    high_score_line_.render(origin_window_);
    score_line_.render(window);
    score_line_.render(origin_window_);
    power_line_.render(window);
    power_line_.render(origin_window_);
    graze_line_.render(window);
    graze_line_.render(origin_window_);

    bullet_line_.render(window);
    bullet_line_.render(origin_window_);
    effect_line_.render(window);
    effect_line_.render(origin_window_);
    fps_line_.render(window);
    fps_line_.render(origin_window_);

    life_line_.render(window);
    life_line_.render(origin_window_);
    bomb_line_.render(window);
    bomb_line_.render(origin_window_);

    //curtain_.render(window);
    star_curtain3_.setTexture(origin_window_.getTexture());
    
    star_curtain3_.render(window);
    star_curtain2_.render(window);
    star_curtain1_.render(window);
}

int GameState::getLife()
{
    return life_line_.getCurrentNum();
}

void GameState::setLife(int life)
{
    player_->setLifeNum(2);
}

void GameState::setScore(int score)
{
    score_line_.setCurrentNum(score);
}

bool GameState::isContinued()
{
    return player_->isContinued();
}

void GameState::fps_update()
{
    float dt=clock_.restart().asSeconds();
    elapsed_+=dt;
    frame_count_++;

    if(elapsed_>=1)
    {
        fps_=frame_count_/elapsed_;
        
        frame_count_=0;
        elapsed_=0;
    }
}

void GameState::clock_update()
{
    player_->clock_count();
}

void GameState::continue_check()
{
    if((player_->getLifeNum())==(-1))
    {
        app_.stack_.pushRequest(std::make_unique<EndState>(app_,*this));
        player_->setContinued(true);

        SaveData data;
        if(player_->isContinued())
        {
            data.cleared_=app_.history_data_.cleared_;
        }
        else
        {
            data.cleared_=true;
        }
        data.high_score_=high_score_line_.getCurrentNum();
        app_.lua_.writeSave(data);
        app_.history_data_=app_.lua_.loadSave();
    }
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