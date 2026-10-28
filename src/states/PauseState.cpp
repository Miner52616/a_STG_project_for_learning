#include "states/PauseState.h"
#include "states/ManualState.h"
#include "states/ReplayState.h"
#include "states/GameState.h"
#include "core/Application.h" 
#include <iostream>

PauseState::PauseState(Application &app,GameState* game):
    ButtonState(app,PauButtonNum),
    game_(game),
    title_(app.assets_resource_.mainFont_),title2_(app.assets_resource_.mainFont_)
{
    title_.setTextText("一时停止");
    title_.setTextSize(60);
    title_.setTextPosition({100,600});
    title2_.setTextText("Game Pause");
    title2_.setTextSize(30);
    title2_.setTextPosition({350,660});

    buttonlist_[0].setButtonText("Return to Game");
    buttonlist_[0].setButtonPosition({100,700});

    //buttonlist_[1].setButtonText("Save Replay and Return to Title");
    //buttonlist_[1].setButtonPosition({100,700});

    buttonlist_[1].setButtonText("Manual");
    buttonlist_[1].setButtonPosition({100,760});

    buttonlist_[2].setButtonText("Save Replay");
    buttonlist_[2].setButtonPosition({100,820});

    buttonlist_[3].setButtonText("Return to Title");
    buttonlist_[3].setButtonPosition({100,880});

    for(int i=1;i<=PauButtonNum;i++)
    {
        buttonlist_[i-1].setButtonShake(5,15);
    }

    if(game->getReplayMode())
    {
        buttonlist_[2].setButtonLock(locked);
    }
}

void PauseState::render(sf::RenderWindow& window)
{
    ButtonState::render(window);
    title_.DrawText(window);
    title2_.DrawText(window);
}

void PauseState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if(key.code==sf::Keyboard::Key::Down)
    {
       do
       {
            focus_=(focus_%PauButtonNum)+1;
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
                focus_=focus_+PauButtonNum;
            }
       }while(buttonlist_[focus_-1].getButtonLocked()==locked);
       buttonlist_[focus_-1].shake();
    }
    
    if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
    {
        focus_=PauButtonNum;
        buttonlist_[focus_-1].shake();
    }

    if(key.code==sf::Keyboard::Key::Z)
    {
        switch (focus_)
        {
            case 3:
            {
                //app_.stack_.clearRequest();
                app_.stack_.pushRequest(std::make_unique<ReplayState>(app_,game_));
                break;
            }
        
            case 1:
            {
                app_.stack_.popRequest();
                break;
            }

            case 4:
            {
                //app_.stack_.pushRequest(std::make_unique<ManualState>(app_));
                app_.stack_.clearRequest();
                break;
            }
            
            case 2:
            {
                //app_.stack_.clearRequest();
                app_.stack_.pushRequest(std::make_unique<ManualState>(app_));
                break;
            }
        default:
            break;
        }
    }
}