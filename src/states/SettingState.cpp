#include "states/SettingState.h"
#include "mathematics/mathematics.h"
#include <fstream>

SettingState::SettingState(Application& app):
    ButtonState(app,1),title_(app_.assets_resource_.mainFont_)
{
    title_.setTextText("Option ~ 游戏设置");
    title_.setTextSize(40);
    title_.setTextPosition({120,30});

    LuaManager& lua=app_.lua_;
    lua.loadScript("lua_files/setting.lua");

    sol::table setting_state=lua.lua()["setting"];
    int setting_state_size=setting_state.size();
    button_num_=setting_state_size+1;

    setbuttonlistLength(button_num_);
    type_list_.reserve(setting_state_size);
    switch_list_.reserve(setting_state_size);
    for(;switch_list_.size()<setting_state_size;)
    {
        switch_list_.emplace_back(app_);
        switch_list_.back().setPosition({-500,-500});
    }
    
    for(int i=1;i<=setting_state_size;i++)
    {
        sol::table setting=setting_state[i];
        buttonlist_[i-1].setButtonText(setting["name"]);
        buttonlist_[i-1].setButtonPosition({300,i*80+70});
        buttonlist_[i-1].setButtonSize(25);
        if(setting["type"].get<std::string>()=="switch")
        {
            type_list_.emplace_back("switch");
            switch_list_[i-1].setPosition({900,i*80+70});
            switch_list_[i-1].setScale({0.5,0.5});
            bool state=setting["state"];
            switch_list_[i-1].setState(state);
        }
    }

    buttonlist_[button_num_-1].setButtonPosition({300,850});
    buttonlist_[button_num_-1].setButtonText("保存并退出");

    for(int i=1;i<=button_num_;i++)
    {
        buttonlist_[i-1].setButtonShake(5,15);
    }
}

void SettingState::update()
{
    ButtonState::update();
    for(auto it=switch_list_.begin();it!=switch_list_.end();++it)
    {
        it->update();
    }
}

void SettingState::render(sf::RenderWindow& window)
{
    ButtonState::render(window);
    for(auto it=switch_list_.begin();it!=switch_list_.end();++it)
    {
        it->render(window);
    }
    title_.DrawText(window);
}

void SettingState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if(key.code==sf::Keyboard::Key::Down)
    {
        do
        {
            focus_=(focus_%button_num_)+1;
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
                focus_=focus_+button_num_;
            }
        }while(buttonlist_[focus_-1].getButtonLocked()==locked);
        buttonlist_[focus_-1].shake();
    }

    if(key.code==sf::Keyboard::Key::Escape)
    {
        app_.stack_.popRequest();
    }

    if(key.code==sf::Keyboard::Key::X)
    {
        focus_=button_num_;
        buttonlist_[focus_-1].shake();
    }

    if(key.code==sf::Keyboard::Key::Z)
    {
        if(focus_==button_num_)
        {
            saveSetting();
            app_.stack_.popRequest();
        }
        else
        {
            if(type_list_[focus_-1]=="switch")
            {
                switch_list_[focus_-1].setState(!(switch_list_[focus_-1].getState()));
            }
        }
    }
}

void SettingState::saveSetting()
{
    std::ofstream file("lua_files/setting.lua");
    if (!file.is_open())
    {
        std::cout<<"无法写入setting.lua"<<std::endl;
        return;
    }

    int setting_state_size=button_num_-1;

    file<<std::boolalpha;

    file<<"setting=\n";
    file<<"{\n";
    for(int i=1;i<=setting_state_size;i++)
    {
        file<<"    {\n";
        file<<"        name=\""<<toStdString(buttonlist_[i-1].getButtonText_().getString())<<"\",\n";
        file<<"        type=\""<<type_list_[i-1]<<"\",\n";
        if(type_list_[i-1]=="switch")
        {
            file<<"        state="<<switch_list_[i-1].getState()<<"\n";
        }
        file<<"    },\n";

        app_.setting_[toStdString(buttonlist_[i-1].getButtonText_().getString())]=switch_list_[i-1].getState();
    }
    file<<"}\n";
}