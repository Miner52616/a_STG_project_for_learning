#include "states/ManualState.h"
#include "core/application.h"
#include <iostream>

ManualState::ManualState(application &app):
    TextState(app,ManPageNum)
{
    pagelist_[0].setTextlistLength(2);
    pagelist_[0].setTextText(1,"Title 1");
    pagelist_[0].setTextText(2,"manual 1");
    pagelist_[0].setTextPosition(1,{640,150});
    pagelist_[0].setTextPosition(2,{640,480});

    pagelist_[1].setTextlistLength(2);
    pagelist_[1].setTextText(1,"Title 2");
    pagelist_[1].setTextText(2,"manual 2");
    pagelist_[1].setTextPosition(1,{640,150});
    pagelist_[1].setTextPosition(2,{640,480});

    pagelist_[2].setTextlistLength(2);
    pagelist_[2].setTextText(1,"Title 3");
    pagelist_[2].setTextText(2,"manual 3");
    pagelist_[2].setTextPosition(1,{640,150});
    pagelist_[2].setTextPosition(2,{640,480});

    pagelist_[3].setTextlistLength(2);
    pagelist_[3].setTextText(1,"Title 4");
    pagelist_[3].setTextText(2,"manual 4");
    pagelist_[3].setTextPosition(1,{640,150});
    pagelist_[3].setTextPosition(2,{640,480});

    pagelist_[4].setTextlistLength(2);
    pagelist_[4].setTextText(1,"Title 5");
    pagelist_[4].setTextText(2,"manual 5");
    pagelist_[4].setTextPosition(1,{640,150});
    pagelist_[4].setTextPosition(2,{640,480});
}

void ManualState::HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed& key)
{
    if(key.code==sf::Keyboard::Key::Right)
    {
        focus_=(focus_%ManPageNum)+1;
    }

    if(key.code==sf::Keyboard::Key::Left)
    {
        focus_--;
        if(focus_<1)
        {
            focus_=focus_+ManPageNum;
        }
    }

    if((key.code==sf::Keyboard::Key::X)||(key.code==sf::Keyboard::Key::Escape))
    {
        app_.stack_.popState();
    }
}