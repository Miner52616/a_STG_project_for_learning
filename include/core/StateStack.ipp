void StateStack::ProcessEvent(sf::RenderWindow& window,const auto& event)
    {
        for(auto it=stack_.rbegin();it!=stack_.rend();++it)
        {
            (*it)->ProcessEvent(window,event);
            if((*it)->blocksUpdate())
                break;
        }
    }