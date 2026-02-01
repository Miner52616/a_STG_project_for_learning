#include "states/GameState.h"
#include "states/PauseState.h"
#include "core/application.h"
#include <iostream>

GameState::GameState(application &app):
    State(app),
    frame_(0),
    player_(app.playerTexture_),
    enemy1_(app.enemyTexture_),
    outline1({75,30},{845,930},5,sf::Color::Black,sf::Color(128,128,128))
{
    player_.setPosition({640,480});
    enemy1_.setPosition({640,100});

    enemy1_.set_start_end(480,216000);
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

    enemy1_.set_exist(frame_);

    player_bulletlist_update();

    frame_++;
}

void GameState::Render(sf::RenderWindow& window)
{
    outline1.drawwindow(window);

    player_.drawwindow(window);

    enemy1_.drawwindow(window);

    player_bulletlist_drawwindow(window);
    
}

void GameState::player_bulletlist_update()
{
    player_bulletlist_move();
    player_bulletlist_clear();
    player_bulletlist_add();
}

void GameState::player_bulletlist_move()
{
    for(auto it=player_bulletlist.begin();it!=player_bulletlist.end();++it)
    {
        (*it)->setPosition({(*it)->getPosition().x,(*it)->getPosition().y-12});
    }
}

void GameState::player_bulletlist_clear()
{
    player_bulletlist.erase
    (
        std::remove_if
        (
            player_bulletlist.begin(),player_bulletlist.end(),
            [](const std::unique_ptr<Bullet>& bullet)
            {
                if((bullet->getPosition().x<0)||(bullet->getPosition().y<0)||(bullet->getPosition().x>1280)||(bullet->getPosition().y>960))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        ),
        player_bulletlist.end()
    );
}

void GameState::player_bulletlist_add()
{
    if(player_.Handle_shoot_request())
    {
        player_bulletlist.emplace_back(std::make_unique<Bullet>(app_.bulletTexture_,player_.getPosition()));
    }
}

void GameState::player_bulletlist_drawwindow(sf::RenderWindow& window)
{
    for(auto it=player_bulletlist.begin();it!=player_bulletlist.end();++it)
    {
        (*it)->drawwindow(window);
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