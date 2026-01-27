#include "core/application.h"
#include "core/StateStack.h"
#include "states/MenuState.h"
#include <iostream>

application::application():
//初始化窗口属性
    window_(sf::VideoMode({1280,960}),"trytry window"),
    mainFont_("assets/fonts/abc.ttf"),
    playerTexture_("assets/textures/player.png"),
    enemyTexture_("assets/textures/enemy.png"),
    bulletTexture_("assets/textures/bullet.png")
{
//    mainFont_.openFromFile("abc.ttf");
    window_.setFramerateLimit(60);
    stack_.push(std::make_unique<MenuState>(*this));
}

bool application::IsRunning() const
{
    return window_.isOpen();
}

void application::ProcessEvent()
{
    //处理循环中一帧中产生的所有事件
    while(const auto event=window_.pollEvent())
    {
//        current_state_->ProcessEvent(window_,event);
        stack_.ProcessEvent(window_,event);
    }
    stack_.applyStateChanges();
}

void application::Update()
{
//    current_state_->Update();
    stack_.Update();
}

void application::Render()
{
//    current_state_->Render(window_);
    window_.clear();
    stack_.Render(window_);
    window_.display();
}