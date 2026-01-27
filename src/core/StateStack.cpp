#include "core/StateStack.h"
#include <iostream>

StateStack::StateStack()
{
    changestate_.action=Action::Maintain;
}

void StateStack::push(std::unique_ptr<State> state)
{
    stack_.push_back(std::move(state));
    std::cout<<"push success\n";
}

void StateStack::pop()
{
    if(!stack_.empty())
    {
        stack_.pop_back();
        std::cout<<"pop success\n";
    }
}

/*
void StateStack::HandleEvent(sf::RenderWindow& window,const auto& event)
{
    for(auto it=stack_.rbegin();it!=stack_.rend();++it)
    {
        (*it)->HandleEvent(window,event);
        if((*it)->blocksUpdate())
            break;
    }
}
    */

void StateStack::Update()
{
    for (auto it = stack_.rbegin(); it != stack_.rend(); ++it)
    {
        (*it)->Update();
        if ((*it)->blocksUpdate())
            break;
    }
}

void StateStack::Render(sf::RenderWindow& window)
{
    for (auto it = stack_.rbegin(); it != stack_.rend(); ++it) 
    {
        (*it)->Render(window);
        if ((*it)->blocksRender())
            break;
    }
}

void StateStack::pushState(std::unique_ptr<State> state)
{
    changestate_.action=Action::Push;
    changestate_.state=std::move(state);
    std::cout<<"wait for push success\n";
}

void StateStack::popState()
{
    changestate_.action=Action::Pop;
}

void StateStack::applyStateChanges()
{
    switch(changestate_.action)
    {
        case Action::Push:
        {
            push(std::move(changestate_.state));
            break;
        }
        case Action::Pop:
        {
            if(!stack_.empty())
            {
                pop();
            }
            break;
        }
        case Action::Maintain:
        {
            break;
        }
        default:
        {
            break;
        }
    }

    changestate_.action=Action::Maintain;
}