#pragma once
#include "core/state.h"
#include "ui/Text.h"
#include <vector>

class PackText
{
private:
    Text text_;
    bool show_next_;

public:
    PackText(const sf::Font& font);
    void render(sf::RenderWindow& window);
    Text& getText();
    void setShowNext(bool show_next);
    bool isShowNext();
};

class EndStoryState:public State
{
private:
    std::vector<std::vector<PackText>> pages_main_;
    std::vector<std::vector<PackText>> pages_name_;
    int current_page_;
    int current_text_;
    bool ispressing_;

public:
    EndStoryState(Application &app);

    void processEvent(sf::RenderWindow& window,const std::optional<sf::Event> event) override;  //处理被分发到的事件
    void update() override;  //统一更新属性
    void render(sf::RenderWindow& window) override;  //统一渲染至屏幕
    void Load(const std::string& path);

private:
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Closed);  //处理“关闭窗口”事件
    void HandleEvent(sf::RenderWindow& window,const sf::Event::Resized&);  //拉伸窗口时保证宽高比一致
    void HandleEvent(sf::RenderWindow& window,auto){};  //其它无反应事件
};