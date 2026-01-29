#include "core/application.h"
//#include "core/StateStack.h"
#include "states/MenuState.h"
#include <iostream>

application::application():
    window_(sf::VideoMode({1280,960}),"trytry window"),
    mainFont_("assets/fonts/abc.ttf"),
    playerTexture_("assets/textures/player.png"),
    enemyTexture_("assets/textures/enemy.png"),
    bulletTexture_("assets/textures/bullet.png")
{
    window_.setFramerateLimit(60);
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