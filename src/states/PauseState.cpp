#include "states/PauseState.h"
#include "states/ManualState.h"
#include "core/application.h" 
#include <iostream>

PauseState::PauseState(application &app):
    ButtonState(app,PauButtonNum)
{
    buttonlist_[0].setButtonText("Return to Game");
    buttonlist_[0].setButtonPosition({100,600});

    buttonlist_[1].setButtonText("Save Replay and Return to Title");
    buttonlist_[1].setButtonPosition({100,700});

    buttonlist_[2].setButtonText("Manual");
    buttonlist_[2].setButtonPosition({100,800});

    buttonlist_[3].setButtonText("Return to Title");
    buttonlist_[3].setButtonPosition({100,900});
}

void PauseState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if(key.code==sf::Keyboard::Key::Down)
    {
       do
       {
            focus_=(focus_%PauButtonNum)+1;
       }while(buttonlist_[focus_-1].getButtonLocked()==locked);
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
    }
    
    if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
    {
        focus_=PauButtonNum;
    }

    if(key.code==sf::Keyboard::Key::Z)
    {
        switch (focus_)
        {
            case 4:
            {
                app_.stack_.clearRequest();
                break;
            }
        
            case 1:
            {
                app_.stack_.popRequest();
                break;
            }

            case 3:
            {
                app_.stack_.pushRequest(std::make_unique<ManualState>(app_));
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