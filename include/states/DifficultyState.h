#pragma  once
#include "basicstates/ButtonState.h"

constexpr int DifButtonNum=4;

class DifficultyState:public ButtonState<DifficultyState>
{
public:
    using ButtonState<DifficultyState>::HandleEvent;
    DifficultyState(application &app);
    void HandleEvent(sf::RenderWindow& window,const sf::Event::KeyPressed&);
};