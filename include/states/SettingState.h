#pragma once
#include "basicstates/ButtonState.h"
#include "ui/Switch.h"
#include "ui/Text.h"

class SettingState:public ButtonState<SettingState>
{
private:
    int button_num_=1;

    Text title_;

    std::vector<std::string> type_list_;
    std::vector<Switch> switch_list_;

private:
    void saveSetting();
public:
    using ButtonState<SettingState>::HandleEvent;
    SettingState(Application &app);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);  //处理“按钮按下”事件
};