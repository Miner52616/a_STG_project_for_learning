#include "states/EndState.h"
#include "core/application.h"
#include "states/GameState.h"
#include <iostream>

EndState::EndState(application &app,GameState& gamestate):
    ButtonState(app,EndButtonNum),gamestate_(gamestate),title_(app.mainFont_),title2_(app.mainFont_)
{
    title_.setTextText("满身疮痍！");
    title_.setTextSize(60);
    title_.setTextPosition({100,600});
    title2_.setTextText("Game Over");
    title2_.setTextSize(30);
    title2_.setTextPosition({350,660});

    buttonlist_[0].setButtonText("Continue");
    buttonlist_[0].setButtonPosition({100,700});

    //buttonlist_[1].setButtonText("Return to title with replay");
    //buttonlist_[1].setButtonPosition({100,700});

    buttonlist_[1].setButtonText("Return to title");
    buttonlist_[1].setButtonPosition({100,800});
    
    for(int i=1;i<=EndButtonNum;i++)
    {
        buttonlist_[i-1].setButtonShake(5,15);
    }

    if(gamestate_.getLife()<0)
    {
        buttonlist_[0].setButtonLock(unlocked);
    }
    else
    {
        buttonlist_[0].setButtonLock(locked);
        focus_=2;
        title_.setTextText("游戏通关！");
        title2_.setTextText("Game Clear");
    }
}

void EndState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    
    if(gamestate_.getLife()<0)
    {
        buttonlist_[0].setButtonLock(unlocked);
    }
    else
    {
        buttonlist_[0].setButtonLock(locked);
        title_.setTextText("游戏通关！");
        title2_.setTextText("Game Clear");
    }

    if(key.code==sf::Keyboard::Key::Down)
    {
       do
       {
            focus_=(focus_%EndButtonNum)+1;
       }while(buttonlist_[focus_-1].getButtonLocked()==locked);
       buttonlist_[focus_-1].shake();
    }

    if(key.code==sf::Keyboard::Key::Up)
    {
       do
       {
            focus_--;
            if(focus_<1)
            {
                focus_=focus_+EndButtonNum;
            }
       }while(buttonlist_[focus_-1].getButtonLocked()==locked);
       buttonlist_[focus_-1].shake();
    }
    
    if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
    {
        focus_=EndButtonNum;
        buttonlist_[focus_-1].shake();
    }

    if(key.code==sf::Keyboard::Key::Z)
    {
        switch (focus_)
        {
            case 1:
            {
                gamestate_.setLife(2);
                app_.stack_.popRequest();
                break;
            }
            
            case 2:
            {
                app_.stack_.clearRequest();
                break;
            }
        default:
            break;
        }
    }
}

void EndState::Render(sf::RenderWindow& window)
{
    ButtonState::Render(window);
    title_.DrawText(window);
    title2_.DrawText(window);
}