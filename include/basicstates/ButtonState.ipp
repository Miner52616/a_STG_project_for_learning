#include "core/application.h"
#include "ui/Button.h"
#include <iostream>

template<typename Derived>
ButtonState<Derived>::ButtonState(application &app,int ButtonNum):
    State(app),focus_(1)
{
    //buttonlist_.resize(ButtonNum);
    setbuttonlistLength(ButtonNum);
}

template<typename Derived>
void ButtonState<Derived>::setbuttonlistLength(int length)
{
    for(;buttonlist_.size()<length;)
    {
        buttonlist_.emplace_back(font_);
    }
}

template<typename Derived>
void ButtonState<Derived>::HandleEvent(sf::RenderWindow& window,const sf::Event::Closed&)
{
    window.close();
    std::cout<<"window closed\n";
}

template<typename Derived>
void ButtonState<Derived>::HandleEvent(sf::RenderWindow& window,const sf::Event::Resized&)
{
    app_.applyLetterBox();
    app_.window_.setView(app_.gameview_);
}

template<typename Derived>
void ButtonState<Derived>::DrawButton_(sf::RenderWindow& window)
{
    for(int i=1;i<=buttonlist_.size();i++)
    {
        window.draw(buttonlist_[i-1].getButtonText_());
    }
}

template<typename Derived>
void ButtonState<Derived>::ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event)
{
    event->visit
    (
        [this,&window](const auto event)
        {
            static_cast<Derived*>(this)->HandleEvent(window,event);
        }
    );
}

template<typename Derived>
void ButtonState<Derived>::Update()
{
    for(int i=1;i<=buttonlist_.size();i++)
    {
        buttonlist_[i-1].setButtonFocused(not_befocused);
    }
    buttonlist_[focus_-1].setButtonFocused(befocused);

    updatebuttonlist_();
}

template<typename Derived>
void ButtonState<Derived>::updatebuttonlist_()
{
    for(int i=1;i<=buttonlist_.size();i++)
    {
        buttonlist_[i-1].updateButton();
    }
}

template<typename Derived>
void ButtonState<Derived>::Render(sf::RenderWindow& window)
{
    //window.clear();
    DrawButton_(window);
    //window.display();
}

/*
void ButtonState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
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