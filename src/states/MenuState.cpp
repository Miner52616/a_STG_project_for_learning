#include "states/MenuState.h"
#include "states/DifficultyState.h"
#include "states/GameState.h"
#include "states/ManualState.h"
#include "core/application.h"
#include <iostream>

MenuState::MenuState(application &app):
    ButtonState(app,MenuButtonNum),current_phase_(1),clock_(30),
    title_(app.mainFont_),
    text1_(app.mainFont_),
    text2_(app.mainFont_),
    text3_(app.mainFont_),
    text4_(app.mainFont_),
    star_curtain2_(app.curtain_texture1_,app.color_flip_)
    //star_curtain_(app.curtain_texture1_)
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

    title_.setTextText("界面操作方法");
    title_.setTextSize(30);
    text1_.setTextText("↑ ↓ ← → ：选择按钮");
    text2_.setTextText("Z ：确定");
    text3_.setTextText("ESC / X ：返回");
    text4_.setTextText("第一次游玩请务必阅读Manual！");
    text4_.setTextSize(35);
    
    title_.setTextPosition({900,680});
    text1_.setTextPosition({900,730});
    text2_.setTextPosition({900,780});
    text3_.setTextPosition({900,830});
    text4_.setTextPosition({750,880});

    Star star1;
    star1.setR(100);
    star1.setAngle(-18);
    sf::Vector2f position1={50,920};
    star1.setPosition(position1);
    star1.getConfig()->clock_.set_target(0);
    star1.getConfig()->target_r_=740;
    star1.getConfig()->target_angle_=108;
    star1.getConfig()->target_position_=position1;

    Star star2;
    star2.setR(0);
    star2.setAngle(-80);
    sf::Vector2f position2={240,200};
    star2.setPosition(position2);
    star2.getConfig()->clock_.set_target(24);
    star2.getConfig()->target_r_=600;
    star2.getConfig()->target_angle_=0;
    star2.getConfig()->target_position_=position2;

    Star star3;
    star3.setR(0);
    star3.setAngle(-60);
    sf::Vector2f position3={960,192};
    star3.setPosition(position3);
    star3.getConfig()->clock_.set_target(48);
    star3.getConfig()->target_r_=580;
    star3.getConfig()->target_angle_=25;
    star3.getConfig()->target_position_=position3;

    Star star4;
    star4.setR(0);
    star4.setAngle(-112);
    sf::Vector2f position4={700,500};
    star4.setPosition(position4);
    star4.getConfig()->clock_.set_target(72);
    star4.getConfig()->target_r_=720;
    star4.getConfig()->target_angle_=1;
    star4.getConfig()->target_position_=position4;

    Star star5;
    star5.setR(0);
    star5.setAngle(-147);
    sf::Vector2f position5={999,822};
    star5.setPosition(position5);
    star5.getConfig()->clock_.set_target(96);
    star5.getConfig()->target_r_=600;
    star5.getConfig()->target_angle_=36;
    star5.getConfig()->target_position_=position5;

    star_curtain2_.add_star(star1);
    star_curtain2_.add_star(star2);
    star_curtain2_.add_star(star3);
    star_curtain2_.add_star(star4);
    star_curtain2_.add_star(star5);
    /*
    int num_x=14;
    int num_y=12;
    star_curtain_.setNum(num_x,num_y);
    star_curtain_.setStart_Target({640,-150},{1280-0.5*((float)1280/num_x),960-0.5*((float)960/num_y)},180);
    */

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
    //star_curtain_.update();
    star_curtain2_.update();

    switch (current_phase_)
    {
    case 2:
        {
            star_curtain2_.setEnable(true);
            if(star_curtain2_.isFinished())
            {
                current_phase_=3;
            }
            /*
            curtain_.update();
            if(curtain_.getPosition().x>=0)
            {
                current_phase_=3;
            }
                */
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

    title_.DrawText(window);
    text1_.DrawText(window);
    text2_.DrawText(window);
    text3_.DrawText(window);
    text4_.DrawText(window);

    star_curtain2_.render(window);
    //star_curtain_.render(window);
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