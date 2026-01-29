#pragma once
#include "Text.h"

class Page
{
private:
    const sf::Font &font_;
    std::vector<Text> textlist_;

private:
    void addText();

public:
    Page(const sf::Font &font);  //默认页面设置，初始化资源引用

public:
    void Render(sf::RenderWindow& window);  //渲染页面至屏幕

    void setTextlistLength(int num);  //设置页面文字组件数（设置文字数组大小）
    void setTextText(int num,const std::string text);  //设置页面的文字组件的文字
    void setTextPosition(int num,sf::Vector2f position);  //设置页面的文字组件的位置
    void setTextSize(int num,int size);  //设置页面的文字组件的大小
    void setTextColor(int num,sf::Color color);  //设置页面的文字组件的颜色
};