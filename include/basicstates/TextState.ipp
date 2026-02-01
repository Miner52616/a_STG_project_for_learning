#include "core/application.h"
#include <iostream>

template<typename Derived>
TextState<Derived>::TextState(application &app,int PageNum):
    State(app),focus_(1)
{
    //pagelist_.resize(PageNum);
    setPagelistLength(PageNum);
}

template<typename Derived>
void TextState<Derived>::setPagelistLength(int length)
{
    for(;pagelist_.size()<length;)
    {
        pagelist_.emplace_back(font_);
    }
}

template<typename Derived>
void TextState<Derived>::ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event)
{
    event->visit
    (
        [this,&window](const auto event)
        {
            static_cast<Derived*>(this)->HandleEvent(window,event);
        }
    );
    //std::cout<<"process event success\n";
}

template<typename Derived>
void TextState<Derived>::Update()
{
    //std::cout<<"update success\n";
}

template<typename Derived>
void TextState<Derived>::Render(sf::RenderWindow& window)
{
    if (focus_ < 1 || focus_ > static_cast<int>(pagelist_.size()))
    {
        std::cout << "invalid focus_: " << focus_ << "\n";
        return;
    }

    //window.clear();
    pagelist_[focus_-1].Render(window);
    //window.display();
    //std::cout<<"render success\n";
}

template<typename Derived>
void TextState<Derived>::HandleEvent(sf::RenderWindow& window,const sf::Event::Closed&)
{
    window.close();
    std::cout<<"window closed\n";
}

template<typename Derived>
void TextState<Derived>::HandleEvent(sf::RenderWindow& window,const sf::Event::Resized&)
{
    app_.applyLetterBox();
    app_.window_.setView(app_.gameview_);
}