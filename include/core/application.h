#pragma once

#include <SFML/Graphics.hpp>
#include "core/StateStack.h"

//应用，整个游戏就是一个应用的实例
class application
{
public:
    //窗口资源需要作为参数传入使用，以明确窗口
    sf::RenderWindow window_;

public:
    //其它资源通过application指针或者引用使用
    sf::Font mainFont_;
    sf::Texture playerTexture_;
    sf::Texture enemyTexture_;
    sf::Texture bulletTexture_;

public:
    StateStack stack_;

public:
    application();  //初始化窗口属性，初始化资源加载，初始化状态栈
    bool IsRunning() const;  //窗口是否还在打开着
    void ProcessEvent();  //处理产生的所有事件
    void Update();  //统一更新属性
    void Render();  //统一渲染至屏幕
    void End_operation();  //一套流程中最后的操作
};