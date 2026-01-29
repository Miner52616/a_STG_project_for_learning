#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Text
{
private:
    const sf::Font &font_;
    sf::Text text_;
public:
    Text(const sf::Font& font);  //默认设置，初始化资源引用

public:
    void setTextText(const std::string text);  //设置显示的文字
    void setTextPosition(sf::Vector2f position);  //设置文字位置
    void setTextSize(int size);  //设置文字大小
    void setTextColor(sf::Color color);  //设置文字颜色

    void DrawText(sf::RenderWindow& window);  //渲染文字至窗口
};