#include "states/ManualState.h"
#include "core/application.h"
#include <iostream>
#include <sol/sol.hpp>

ManualState::ManualState(application &app):
    TextState(app,ManPageNum)
{  
    auto& lua=app_.lua_;
    lua.loadScript("include/luas/manual.lua");
    
    sol::table manual=lua.lua_["manual"];

    setPagelistLength(manual.size());

    for(;buttonlist_.size()<manual.size();)
    {
        buttonlist_.emplace_back(font_);
    }
    for(int i=1;i<=manual.size();i++)
    {
        sol::table page=manual[i];
        buttonlist_[i-1].setButtonText(page["button"]);
    }

    for(int i=1;i<=ManPageNum;i++)
    {
        buttonlist_[i-1].setButtonPosition({30,150+i*50});
        buttonlist_[i-1].setButtonSize(30);
        buttonlist_[i-1].setButtonShake(5,15);
    }

    for(int i=1;i<=manual.size();i++)
    {
        sol::table page=manual[i];
        sol::table texts=page["texts"];

        pagelist_[i-1].setTextlistLength(texts.size()+1);
        pagelist_[i-1].setTextText(1,page["title"]);
        pagelist_[i-1].setTextPosition(1,{400,120});
        pagelist_[i-1].setTextSize(1,50);

        for(int j=1;j<=texts.size();j++)
        {
            pagelist_[i-1].setTextText(j+1,texts[j]);
            pagelist_[i-1].setTextPosition(j+1,{400,220+float(j-1)*60});
            pagelist_[i-1].setTextSize(j+1,35);
        }
    }
}

void ManualState::Update()
{
    TextState::Update();
    for(int i=1;i<=buttonlist_.size();i++)
    {
        buttonlist_[i-1].setButtonFocused(not_befocused);
    }
    buttonlist_[focus_-1].setButtonFocused(befocused);
    for(int i=1;i<=buttonlist_.size();i++)
    {
        buttonlist_[i-1].update();
    }
}

void ManualState::Render(sf::RenderWindow& window)
{
    TextState::Render(window);
    for(int i=1;i<=buttonlist_.size();i++)
    {
        window.draw(buttonlist_[i-1].getButtonText_());
    }
}

void ManualState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if(key.code==sf::Keyboard::Key::Down)
    {
        focus_=(focus_%ManPageNum)+1;
        buttonlist_[focus_-1].shake();
    }

    if(key.code==sf::Keyboard::Key::Up)
    {
        focus_--;
        if(focus_<1)
        {
            focus_=focus_+ManPageNum;
        }
        buttonlist_[focus_-1].shake();
    }

    if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
    {
        app_.stack_.popRequest();
    }
}