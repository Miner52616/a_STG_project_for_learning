#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"
#include <memory>
#include <vector>

class State;

enum class Action{Push,Pop,Clear,Maintain};

//用于记录push/pop申请的结构类型
struct ChangeState
{
    Action action;  //申请操作
    std::unique_ptr<State> state;  //如果是push申请，记录将要push的状态
};

//状态栈，用于管理所有页面
class StateStack
{
public:
    void push(std::unique_ptr<State> state);  //push一个状态
    void pop();  //pop一个状态

    void pushRequest(std::unique_ptr<State> state);  //发送push申请
    void popRequest();  //发送pop申请
//    void clear();

    void applyStateChanges(); //响应push/pop申请

    void ProcessEvent(sf::RenderWindow& window,const auto& event);  //处理被分发到的事件
    void Update();  //统一更新属性
    void Render(sf::RenderWindow& window);  //统一渲染至屏幕

private:
    ChangeState changestate_;
    std::vector<std::unique_ptr<State>> stack_;
    

public:
    StateStack(); //初始化申请为“保持”状态
};

#include "core/StateStack.ipp"