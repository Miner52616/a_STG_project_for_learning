#include "states/DifficultyState.h"
#include "core/application.h"
#include "states/GameState.h"
#include <iostream>

DifficultyState::DifficultyState(application &app):
    ButtonState(app,DifButtonNum)
{
    buttonlist_[0].setButtonText("Easy");
    buttonlist_[0].setButtonPosition({150,250});

    buttonlist_[1].setButtonText("Normal");
    buttonlist_[1].setButtonPosition({250,350});

    buttonlist_[2].setButtonText("Hard");
    buttonlist_[2].setButtonPosition({350,450});

    buttonlist_[3].setButtonText("Lunatic");
    buttonlist_[3].setButtonPosition({450,550});
}

void DifficultyState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if((key.code==sf::Keyboard::Key::Down)||(key.code==sf::Keyboard::Key::Right))
    {
       do
       {
            focus_=(focus_%DifButtonNum)+1;
       }while(buttonlist_[focus_-1].getButtonLocked()==locked);
    }

    if((key.code==sf::Keyboard::Key::Up)||(key.code==sf::Keyboard::Key::Left))
    {
       do
       {
            focus_--;
            if(focus_<1)
            {
                focus_=focus_+DifButtonNum;
            }
       }while(buttonlist_[focus_-1].getButtonLocked()==locked);
    }

    if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
    {
        app_.stack_.popRequest();
    }

    if(key.code==sf::Keyboard::Key::Z)
    {
        switch (focus_)
        {
            case 1:
            {
                std::cout<<"Easy mode\n";
                app_.stack_.pushRequest(std::make_unique<GameState>(app_));
                break;
            }
        
            case 2:
            {
                std::cout<<"Normal mode\n";
                break;
            }

            case 3:
            {
                std::cout<<"Hard mode\n";
                break;
            }

            case 4:
            {
                std::cout<<"Lunatic mode\n";
                break;
            }
        
        default:
            break;
        }
    }
}