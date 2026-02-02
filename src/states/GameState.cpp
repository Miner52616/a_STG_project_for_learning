#include "states/GameState.h"
#include "states/PauseState.h"
#include "core/application.h"
#include "collision/CollisionCheck.h"
#include <iostream>

GameState::GameState(application &app):
    State(app),
    frame_(0),
    outline1({75,30},{845,930},5,sf::Color::Black,sf::Color(128,128,128)),
    bulletmanager_(app,bulletlist_),
    player_(app,app.playerTexture_,outline1,bulletmanager_),
    enemy1_(app,app.enemyTexture_,bulletmanager_,player_),
    enemymanager_(enemylist_)
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

    player_.setPosition({640,480});

    enemy1_.setPosition({640,100});
    enemy1_.set_start_end(240,216000);
    enemylist_add(&enemy1_);
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
    player_.Player_update();

    enemymanager_.update(frame_);

    bulletmanager_.update();//后续需要把清理子弹放到帧末统一处理，以不影响碰撞检测

    handlecollision();

    bulletmanager_.clear();

    clock_update();

    frame_++;
}

void GameState::Render(sf::RenderWindow& window)
{
    outline1.drawwindow(window);

    player_.drawwindow(window);

    enemymanager_.render(window);

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

void GameState::enemylist_add(Enemy* enemy)
{
    enemylist_.emplace_back(enemy);
}

void GameState::clock_update()
{
    player_.clock_count();
}

void GameState::handlecollision()
{
    handleplayerbulletcollision();
}

void GameState::handleplayerbulletcollision()
{
    for(auto it1=bulletlist_.begin();it1!=bulletlist_.end();++it1)
    {
        if((*it1)->isPlayer())
        {
            for(auto it2=enemylist_.begin();it2!=enemylist_.end();++it2)
            {
                if(isCollision(*(*it2),*(*it1))&&((*it2)->isExist()))
                {
                    (*it1)->markDead();
                    //std::cout<<"hit!"<<std::endl;
                }
            }
        }
        else
        {
            if(isCollision(player_,*(*it1)))
            {
                (*it1)->markDead();
                std::cout<<"be hit"<<std::endl;
            }
        }
    }
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