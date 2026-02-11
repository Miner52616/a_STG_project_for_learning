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
    bulletmanager_(app,bulletlist_),
    collisionsystem_(bulletlist_),
    phasecontroller_(app,bulletmanager_,phaselist_)
//    player_(app,app.playerTexture_,outline1,bulletmanager_)
//    boss1_(app,app.playerTexture_,bulletmanager_)
{
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

    player_=std::make_shared<Player>(app.playerTexture_,outline1,resource_);
    player_->setPosition({640,480});

    //resource和player互相持有对方指针。先创建的需要在后创建的创建后重新获取指针
    resource_=std::make_shared<Resource>(app,bulletmanager_,collisionsystem_,player_);
    player_->setResource(resource_);

    enemy1_move_=std::make_shared<MoveToRandom1>();
    enemy1_shoot_=std::make_shared<AimShoot1>(); 
    enemy2_move_=std::make_shared<MoveToRandom1>();
    enemy2_shoot_=std::make_shared<AimShoot1>(); 
    spell1_move_=std::make_shared<MoveToRandom1>();
    spell1_shoot_=std::make_shared<AimShoot1>(); 
    
    enemy1_=std::make_shared<Enemy>(app.enemyTexture_);
    enemy1_->setPosition({460,100});
    enemy1_->setHP(200);
    enemy1_->set_start_end(240,216000);
    enemy2_=std::make_shared<Enemy>(app.enemyTexture_);
    enemy2_->setPosition({460,100});
    enemy2_->setHP(200);
    enemy2_->set_start_end(240,216000);
    boss1_=std::make_shared<Boss>(app.playerTexture_,resource_);
    spell1_=std::make_shared<SpellPhase>(resource_,360);
    
    enemy1_move_->set_resource(resource_);
    enemy1_shoot_->set_resource(resource_);
    enemy2_move_->set_resource(resource_);
    enemy2_shoot_->set_resource(resource_);
    spell1_move_->set_resource(resource_);
    spell1_shoot_->set_resource(resource_);

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
    
    std::shared_ptr<MidPhase> a1=std::make_shared<MidPhase>(resource_,600);
    a1->add_enemy(enemy1_);
    a1->add_enemy(enemy2_);
    phasecontroller_.add_process(a1);
//    phasecontroller_.add_process(std::make_shared<MidPhase>(app_,bulletmanager_,collisionsystem_,600,player_));
    phasecontroller_.add_process(std::make_shared<VoidPhase>(resource_,180));
    std::shared_ptr<BossPhase> a=std::make_shared<BossPhase>(resource_,boss1_);
    phasecontroller_.add_process(std::move(a));
    phasecontroller_.add_process(std::make_shared<VoidPhase>(resource_,180));

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