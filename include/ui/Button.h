#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "core/Clock.h"

constexpr int befocused=1;
constexpr int not_befocused=0;

constexpr int locked=1;
constexpr int unlocked=0;

constexpr int shining=1;
constexpr int not_shining=0;

class Button
{
private:
    int focused_;
    int locked_;
    int shining_;
    Clock shine_clock_;
    const sf::Font &font_;
    sf::Text text_;
public:
    Button(const sf::Font &font);  //默认按钮设置

public:
    sf::Text getButtonText_();  //获取按钮文字
    int getButtonLocked();  //获取按钮锁定状态
    sf::Vector2f getButtonPosition();
    void setButtonText(const std::string text);  //设置按钮文字
    void setButtonPosition(sf::Vector2f position);  //设置按钮位置
    void setButtonFocused(int focus);  //设置按钮选中状态
    void setButtonShining(int shining);
    void setButtonLock(int lock);  //设置按钮锁定状态
    void updateButton();  //更新按钮属性
};