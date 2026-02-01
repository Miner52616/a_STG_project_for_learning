#include "states/GameState.h"
#include "states/PauseState.h"
#include "core/application.h"
#include <iostream>

GameState::GameState(application &app):
    State(app),
    frame_(0),
    outline1({75,30},{845,930},5,sf::Color::Black,sf::Color(128,128,128)),
    player_(app,app.playerTexture_,outline1,bulletmanager_),
    enemy1_(app,app.enemyTexture_),
    enemymanager_(enemylist_),
    bulletmanager_(app_)
{
    top_cover1.setPosition({0,0});
    top_cover1.setSize({1280,25});
    top_cover1.setFillColor(sf::Color::Black);
    top_cover2.setPosition({70,25});
    top_cover2.setSize({780,5});
    top_cover2.setFillColor(sf::Color(128,128,128));

    player_.setPosition({640,480});

    enemy1_.setPosition({640,100});
    enemy1_.set_start_end(480,216000);
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

    bulletmanager_.update();

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
}

void GameState::enemylist_add(Enemy* enemy)
{
    enemylist_.emplace_back(enemy);
}

void GameState::clock_update()
{
    player_.clock_count();
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