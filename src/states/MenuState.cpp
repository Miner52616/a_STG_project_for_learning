#include "states/MenuState.h"
#include "states/DifficultyState.h"
#include "states/ManualState.h"
#include "core/application.h"
#include <iostream>

MenuState::MenuState(application &app):
    ButtonState(app,MenuButtonNum)
{
    buttonlist_[0].setButtonText("Start");
    buttonlist_[0].setButtonPosition({100,100});

    buttonlist_[1].setButtonText("Extra Start");
    buttonlist_[1].setButtonPosition({100,200});
    buttonlist_[1].setButtonLock(locked);

    buttonlist_[2].setButtonText("Manual");
    buttonlist_[2].setButtonPosition({100,300});

    buttonlist_[3].setButtonText("Quit");
    buttonlist_[3].setButtonPosition({100,400});
}

void MenuState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if(key.code==sf::Keyboard::Key::Down)
    {
       do
       {
            focus_=(focus_%MenuButtonNum)+1;
       }while(buttonlist_[focus_-1].getButtonLocked()==locked);
    }

    if(key.code==sf::Keyboard::Key::Up)
    {
       do
       {
            focus_--;
            if(focus_<1)
            {
                focus_=focus_+MenuButtonNum;
            }
       }while(buttonlist_[focus_-1].getButtonLocked()==locked);
    }
    
    if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
    {
        focus_=MenuButtonNum;
    }

    if(key.code==sf::Keyboard::Key::Z)
    {
        switch (focus_)
        {
            case 4:
            {
                window.close();
                std::cout<<"window closed\n";
                break;
            }
        
            case 1:
            {
                std::cout<<"choose difficulty\n";
                app_.stack_.pushState(std::make_unique<DifficultyState>(app_));
                break;
            }

            case 3:
            {
                std::cout<<"manual for playing\n";
                app_.stack_.pushState(std::make_unique<ManualState>(app_));
                break;
            }
        
        default:
            break;
        }
    }
}


/*

#include "MenuState.h"
#include "application.h"
#include "Button.h"
#include <iostream>

MenuState::MenuState(application &app):
    State(app),focus(ButtonNum)
{
    buttonlist[0].setButtonText("Quit");
    buttonlist[0].setButtonPosition({100,400});

    buttonlist[1].setButtonText("Manual");
    buttonlist[1].setButtonPosition({100,300});

    buttonlist[2].setButtonText("Extra Start");
    buttonlist[2].setButtonPosition({100,200});
    buttonlist[2].setButtonLock(locked);

    buttonlist[3].setButtonText("Start");
    buttonlist[3].setButtonPosition({100,100});
}

void MenuState::HandleEvent(sf::RenderWindow& window,const sf::Event::Closed&)
{
    window.close();
    std::cout<<"window closed\n";
}

void MenuState::DrawButton(sf::RenderWindow& window)
{
    for(int i=1;i<=ButtonNum;i++)
    {
        window.draw(buttonlist[i-1].getButtonText_());
    }
}

void MenuState::ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event)
{
    event->visit([this,&window](const auto event){this->HandleEvent(window,event);});
}

void MenuState::Update()
{
    for(int i=1;i<=ButtonNum;i++)
    {
        buttonlist[i-1].setButtonFocused(not_befocused);
    }
    buttonlist[focus-1].setButtonFocused(befocused);

    updatebuttonlist();
}

void MenuState::updatebuttonlist()
{
    for(int i=1;i<=ButtonNum;i++)
    {
        buttonlist[i-1].updateButton();
    }
}

void MenuState::Render(sf::RenderWindow& window)
{
    window.clear();
    DrawButton(window);
    window.display();
}

void MenuState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if(key.code==sf::Keyboard::Key::Up)
    {
       do
       {
            focus=(focus%ButtonNum)+1;
       }while(buttonlist[focus-1].getButtonLocked()==locked);
    }

    if(key.code==sf::Keyboard::Key::Down)
    {
       do
       {
            focus--;
            if(focus<1)
            {
                focus=focus+ButtonNum;
            }
       }while(buttonlist[focus-1].getButtonLocked()==locked);
    }

    if(key.code==sf::Keyboard::Key::Z)
    {
        switch (focus)
        {
        case 1:
            {
                window.close();
                std::cout<<"window closed\n";
            }
            break;
        
        default:
            break;
        }
    }
}

*/