#pragma once

#include <SFML/Graphics.hpp>
//#include "Menustate.h"
#include "StateStack.h"

//class StateStack;

class application
{
private:
    //窗口资源需要作为参数传入使用，以明确窗口
    sf::RenderWindow window_;

public:
    //其它资源通过application指针或者引用使用即可
    sf::Font mainFont_;
    sf::Texture playerTexture_;
    sf::Texture enemyTexture_;
    sf::Texture bulletTexture_;

public:
    StateStack stack_;
//    std::unique_ptr<State> current_state_=std::make_unique<MenuState>();

public:
    application();
    bool IsRunning() const;
    void ProcessEvent();
    void Update();
    void Render();
};