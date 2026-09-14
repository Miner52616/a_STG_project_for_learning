void StateStack::processEvent(sf::RenderWindow& window,const auto& event)
    {
        for(auto it=stack_.rbegin();it!=stack_.rend();++it)
        {
            (*it)->processEvent(window,event);
            if((*it)->blocksUpdate())
                break;
        }
    }