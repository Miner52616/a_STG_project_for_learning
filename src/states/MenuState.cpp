#include "states/MenuState.h"
#include "states/DifficultyState.h"
#include "states/GameState.h"
#include "states/ManualState.h"
#include "core/application.h"
#include <iostream>

MenuState::MenuState(application &app):
    ButtonState(app,MenuButtonNum),current_phase_(1),clock_(30)
{
    buttonlist_[0].setButtonText("Phantasm Start");
    buttonlist_[0].setButtonPosition({100,100});

    //buttonlist_[1].setButtonText("Extra Start");
    //buttonlist_[1].setButtonPosition({100,200});
    //buttonlist_[1].setButtonLock(locked);

    buttonlist_[1].setButtonText("Manual");
    buttonlist_[1].setButtonPosition({100,200});

    buttonlist_[2].setButtonText("Quit");
    buttonlist_[2].setButtonPosition({100,300});

    for(int i=1;i<=MenuButtonNum;i++)
    {
        buttonlist_[i-1].setButtonShake(5,15);
    }

    rec_.setspeed(0.1);
    rec_.setSize({500,80});

    clock_.reset();
}

void MenuState::ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event)
{
    if(current_phase_==1)
    {
        ButtonState<MenuState>::ProcessEvent(window,event);
    }
}

void MenuState::Update()
{
    rec_.setTargetPosition({50,buttonlist_[focus_-1].getButtonPosition().y});


    switch (current_phase_)
    {
    case 2:
        {
            curtain_.update();
            if(curtain_.getPosition().x>=0)
            {
                current_phase_=3;
            }
            break;
        }

    case 3:
        {
            if(buttonlist_[focus_-1].isDone())
            {
                buttonlist_[focus_-1].setDone(false);
                current_phase_=1;
                switch (focus_)
                {
                    case 1:
                    {
                        std::cout<<"Phantasm Start"<<std::endl;
                        app_.stack_.pushRequest(std::make_unique<GameState>(app_));
                        break;
                    }

                    case 2:
                    {
                        std::cout<<"manual for playing"<<std::endl;
                        app_.stack_.pushRequest(std::make_unique<ManualState>(app_));
                        break;
                    }   
                    
                default:
                    break;
                }
            }
            break;
        }
    
    default:
        break;
    }

    rec_.update();
    ButtonState<MenuState>::Update();
}

void MenuState::Render(sf::RenderWindow& window)
{
    rec_.render(window);
    ButtonState<MenuState>::Render(window);
    curtain_.render(window);
}

void MenuState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if(key.code==sf::Keyboard::Key::Down)
    {
       do
       {
            focus_=(focus_%MenuButtonNum)+1;
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
                focus_=focus_+MenuButtonNum;
            }
       }while(buttonlist_[focus_-1].getButtonLocked()==locked);
       buttonlist_[focus_-1].shake();
    }
    
    if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
    {
        focus_=MenuButtonNum;
        
        //std::cout<<a<<std::endl;
        buttonlist_[focus_-1].shake();
    }

    if(key.code==sf::Keyboard::Key::Z)
    {
        buttonlist_[focus_-1].setPhase(2);
        //current_phase_=2;
        
        switch (focus_)
        {
            case 1:
            {
                current_phase_=2;
                break;
            }

            case 2:
            {
                current_phase_=3;
                break;
            }

            case MenuButtonNum:
            {
                window.close();
                std::cout<<"window closed\n";
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
        buttonlist[i-1].update();
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