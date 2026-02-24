#include "core/application.h"
//#include "core/StateStack.h"
#include "states/MenuState.h"
#include <iostream>

application::application():
    stack_(*(this)),
    window_(sf::VideoMode({1280,960}),"trytry window"),
    mainFont_("assets/fonts/abc.ttf"),
    playerTexture_("assets/textures/player.png"),
    enemyTexture_("assets/textures/enemy.png"),
    bulletTexture_("assets/textures/bullet.png"),
    lifeUI_("assets/textures/life.png"),
    bombUI_("assets/textures/bomb.png")
{
    window_.setFramerateLimit(60);
    gameview_.setSize({1280,960});
    gameview_.setCenter({640,480});
    applyLetterBox();
    window_.setView(gameview_);
    stack_.push(std::make_unique<MenuState>(*this));
}

bool application::IsRunning() const
{
    return window_.isOpen();
}

void application::ProcessEvent()
{
    //状态栈逐个处理事件
    while(const auto event=window_.pollEvent())
    {
        stack_.ProcessEvent(window_,event);
    }
}

void application::Update()
{
    stack_.Update();
}

void application::Render()
{
    window_.clear();
    stack_.Render(window_);
    window_.display();
}

void application::End_operation()
{
    stack_.applyStateChanges();
}

void application::applyLetterBox()
{
    float windowRatio =
        window_.getSize().x / static_cast<float>(window_.getSize().y);
    float viewRatio =
        gameview_.getSize().x / gameview_.getSize().y;

    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX = 0.f;
    float posY = 0.f;

    if (windowRatio > viewRatio)
    {
        sizeX = viewRatio / windowRatio;
        posX = (1.f - sizeX) / 2.f;
    }
    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1.f - sizeY) / 2.f;
    }

    gameview_.setViewport(sf::FloatRect({posX, posY},{sizeX, sizeY}));
}