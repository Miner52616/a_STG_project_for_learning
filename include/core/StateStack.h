#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"
//#include "State.h"
#include <memory>
#include <vector>

class State;

enum class Action{Push,Pop,Clear,Maintain};

struct ChangeState
{
    Action action;
    std::unique_ptr<State> state;
};

class StateStack
{
public:
    void push(std::unique_ptr<State> state);
    void pop();

    void pushState(std::unique_ptr<State> state);
    void popState();
//    void clear();

    void applyStateChanges();

    void ProcessEvent(sf::RenderWindow& window,const auto& event)
    {
    for(auto it=stack_.rbegin();it!=stack_.rend();++it)
    {
        (*it)->ProcessEvent(window,event);
        if((*it)->blocksUpdate())
            break;
    }
    }
    void Update();
    void Render(sf::RenderWindow& window);

private:
    ChangeState changestate_;
    std::vector<std::unique_ptr<State>> stack_;
    

public:
    StateStack();
};