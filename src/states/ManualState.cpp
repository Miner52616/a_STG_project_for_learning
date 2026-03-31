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

    for(;buttonlist_.size()<ManPageNum;)
    {
        buttonlist_.emplace_back(font_);
    }
    buttonlist_[0].setButtonText("游戏的进行方式");

    buttonlist_[1].setButtonText("前情提要");

    buttonlist_[2].setButtonText("游戏的操作");

    buttonlist_[3].setButtonText("游戏界面");

    buttonlist_[4].setButtonText("掉落道具");

    buttonlist_[5].setButtonText("自机性能");

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

/*
    pagelist_[0].setTextlistLength(6);
    pagelist_[0].setTextText(1,"1、游戏的进行方式");
    pagelist_[0].setTextText(2,"    躲避子弹，清理道中看见的妖精。然后每一关的");
    pagelist_[0].setTextText(3,"关底有一个Boss，把她击败，这一关就通过了。");
    pagelist_[0].setTextText(4,"    把每一关都通过，游戏就通关了。");
    pagelist_[0].setTextText(5,"    是的，总的来说，就是尽量不中弹，坚持到游戏");
    pagelist_[0].setTextText(6,"通关。");

    pagelist_[0].setTextPosition(1,{400,120});
    pagelist_[0].setTextSize(1,50);
    for(int i=2;i<=6;i++)
    {
        pagelist_[0].setTextPosition(i,{400,220+float(i-2)*60});
        pagelist_[0].setTextSize(i,35);
    }

    pagelist_[1].setTextlistLength(2);
    pagelist_[1].setTextText(1,"2、前情提要");
    pagelist_[1].setTextText(2,"（暂缺）");

    pagelist_[1].setTextPosition(1,{400,120});
    pagelist_[1].setTextSize(1,50);
    for(int i=2;i<=2;i++)
    {
        pagelist_[1].setTextPosition(i,{400,220+float(i-2)*60});
        pagelist_[1].setTextSize(i,35);
    }

    pagelist_[2].setTextlistLength(5);
    pagelist_[2].setTextText(1,"3、游戏的操作");
    pagelist_[2].setTextText(2,"↑ ↓ ← → ：控制自机移动");
    pagelist_[2].setTextText(3,"Z ：射击");
    pagelist_[2].setTextText(4,"X ：使用符卡");
    pagelist_[2].setTextText(5,"LShift ： 按下时低速移动并显示自机判定点");
    
    pagelist_[2].setTextPosition(1,{400,120});
    pagelist_[2].setTextSize(1,50);
    for(int i=2;i<=5;i++)
    {
        pagelist_[2].setTextPosition(i,{400,220+float(i-2)*60});
        pagelist_[2].setTextSize(i,35);
    }

    pagelist_[3].setTextlistLength(2);
    pagelist_[3].setTextText(1,"4、游戏界面");
    pagelist_[3].setTextText(2,"manual 4");
    pagelist_[3].setTextPosition(1,{640,150});
    pagelist_[3].setTextPosition(2,{640,480});

    pagelist_[4].setTextlistLength(2);
    pagelist_[4].setTextText(1,"5、掉落道具");
    pagelist_[4].setTextText(2,"manual 5");
    pagelist_[4].setTextPosition(1,{640,150});
    pagelist_[4].setTextPosition(2,{640,480});

    pagelist_[5].setTextlistLength(2);
    pagelist_[5].setTextText(1,"6、自机性能");
    pagelist_[5].setTextText(2,"manual 5");
    pagelist_[5].setTextPosition(1,{640,150});
    pagelist_[5].setTextPosition(2,{640,480});
    */