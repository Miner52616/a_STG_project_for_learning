#include "states/EndStoryState.h"
#include "core/application.h"
#include "core/LuaManager.h"
#include <iostream>

PackText::PackText(const sf::Font& font):
    text_(font),
    show_next_(false)
{
    ;
}

void PackText::render(sf::RenderWindow& window)
{
    text_.DrawText(window);
}

Text& PackText::getText()
{
    return text_;
}

void PackText::setShowNext(bool show_next)
{
    show_next_=show_next;
}

bool PackText::isShowNext()
{
    return show_next_;
}

/*********************************************** */

EndStoryState::EndStoryState(application &app):
    State(app),
    current_page_(1),current_text_(0),
    ispressing_(false)
{
    ;
}

void EndStoryState::Load(const std::string& path)
{
    LuaManager& lua=app_.lua_;
    lua.loadScript(path);

    sol::table pages=lua.lua_["pages"];
    int page_num=pages.size();
    
    for(int i=1;i<=page_num;i++)
    {
        sol::table page=pages[i];
        int text_num=page.size();
        
        std::vector<PackText> page_main;
        std::vector<PackText> page_name;
        for(int j=1;j<=text_num;j++)
        {
            sol::table text=page[j];
            sol::table color=text["RGB"];
            int r=color["R"];
            int g=color["G"];
            int b=color["B"];

            PackText packtext_main=PackText(app_.mainFont_);
            PackText packtext_name=PackText(app_.mainFont_);

            packtext_main.getText().setTextSize(27);
            packtext_name.getText().setTextSize(27);
            packtext_main.getText().setTextText(text["text"]);
            packtext_name.getText().setTextText(text["name"]);
            packtext_main.getText().setTextColor(sf::Color{r,g,b});
            packtext_name.getText().setTextColor(sf::Color{r,g,b});
            bool aside=text["aside"];
            if(aside)
            {
                packtext_main.getText().setTextPosition({200,float(760+30*(j-1))});
                packtext_name.getText().setTextPosition({-500,-500});
            }
            else
            {
                packtext_main.getText().setTextPosition({250,float(760+30*(j-1))});
                packtext_name.getText().setTextPosition({170,float(760+30*(j-1))});
            }

            bool show_next=text["show_next"];
            packtext_main.setShowNext(show_next);
            packtext_name.setShowNext(show_next);

            page_main.emplace_back(packtext_main);
            page_name.emplace_back(packtext_name);
        }

        pages_main_.emplace_back(page_main);
        pages_name_.emplace_back(page_name);
    }
}

void EndStoryState::Update()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        if(!ispressing_)
        {
            do
            {
                current_text_++;
                if(current_text_>pages_main_[current_page_-1].size())
                {
                    current_text_=1;
                    current_page_++;
                    if(current_page_>pages_main_.size())
                    {
                        current_page_=pages_main_.size();
                        app_.stack_.clearRequest();
                    }
                    break;
                }
            }
            while(pages_main_[current_page_-1][current_text_-1].isShowNext());
        }
        ispressing_=true;
    }
    else
    {
        ispressing_=false;
    }
}

void EndStoryState::Render(sf::RenderWindow& window)
{
    for(int i=1;i<=current_text_;i++)
    {
        pages_main_[current_page_-1][i-1].render(window);
        pages_name_[current_page_-1][i-1].render(window);
    }
}

void EndStoryState::ProcessEvent(sf::RenderWindow& window,const std::optional<sf::Event> event)
{
    event->visit
    (
        [this,&window](const auto event)
        {
            this->HandleEvent(window,event);
        }
    );
}

void EndStoryState::HandleEvent(sf::RenderWindow& window,const sf::Event::Closed)
{
    window.close();
    std::cout<<"window closed";
}

void EndStoryState::HandleEvent(sf::RenderWindow& window,const sf::Event::Resized&)
{
    app_.applyLetterBox();
    app_.window_.setView(app_.gameview_);
}

