#include "states/EndState.h"
#include "core/application.h"
#include <iostream>

EndState::EndState(application &app):
    ButtonState(app,EndButtonNum)
{
    buttonlist_[0].setButtonText("Continue");
    buttonlist_[0].setButtonPosition({100,600});

    buttonlist_[1].setButtonText("Return to title with replay");
    buttonlist_[1].setButtonPosition({100,700});

    buttonlist_[2].setButtonText("Return to title");
    buttonlist_[2].setButtonPosition({100,800});
}

void EndState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if(key.code==sf::Keyboard::Key::Down)
    {
       do
       {
            focus_=(focus_%EndButtonNum)+1;
       }while(buttonlist_[focus_-1].getButtonLocked()==locked);
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
    }
    
    if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
    {
        focus_=EndButtonNum;
    }

    if(key.code==sf::Keyboard::Key::Z)
    {
        switch (focus_)
        {
            case 1:
            {
                ;
            }

            case 3:
            {
                app_.stack_.clearRequest();
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

