#include "core/StateStack.h"
#include "states/MenuState.h"
//#include "state.h"
#include <iostream>

StateStack::StateStack(application &app):
    app_(app)
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

void StateStack::clear()
{
    stack_.clear();
}

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

void StateStack::pushRequest(std::unique_ptr<State> state)
{
    changestate_.action=Action::Push;
    changestate_.state=std::move(state);
    std::cout<<"wait for push success\n";
}

void StateStack::popRequest()
{
    changestate_.action=Action::Pop;
}

void StateStack::clearRequest()
{
    changestate_.action=Action::Clear;
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
        case Action::Clear:
        {
            clear();
            push(std::make_unique<MenuState>(app_));
        }
        default:
        {
            break;
        }
    }

    changestate_.action=Action::Maintain;
}