#include "core/Performance.h"

Performance::Performance(const sf::Font& font):
    font_(font),worktime_line_(font_)
{
    worktime_line_.setLinePosition({1000,910});
    worktime_line_.setLineText("Work Time");
    worktime_line_.setCurrentNum(0);
    worktime_line_.setMaxNum(9999999);
}

void Performance::reset(int num)
{
    clock_list[num].restart();
}

sf::Time Performance::getTime(int num)
{
    return clock_list[num].getElapsedTime();
}

void Performance::render(sf::RenderWindow& window)
{
    worktime_line_.render(window);
}

void Performance::startWorktime()
{
    reset((int)Clock_List::FRAME_CLOCK);
}

void Performance::endWorktime()
{
    worktime_=getTime((int)Clock_List::FRAME_CLOCK).asMicroseconds();
    worktime_line_.setCurrentNum(worktime_);
}