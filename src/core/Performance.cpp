#include "core/Performance.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Performance::Performance(const sf::Font& font):
    font_(font),worktime_line_(font_)
{
    worktime_line_.setLinePosition({1000,910});
    worktime_line_.setLineText("Work Time");
    worktime_line_.setCurrentNum(0);
    worktime_line_.setMaxNum(9999999);

    lists_.resize(8);
    for(auto it=lists_.begin();it!=lists_.end();++it)
    {
        it->reserve(8000);
    }
}

void Performance::setActive(bool active)
{
    debug_information=active;
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
    if(debug_information)
    {
        worktime_line_.render(window);
    }
}

void Performance::calculate_worktime()
{
    if(debug_information)
    {
        int num=0;
        for(int i=1;i<=5;i++)
        {
            num=num+lists_[i-1].back();
        }
        worktime_line_.setCurrentNum(num);
    }
}

void Performance::startWorktime(Clock_List clock)
{
    if(debug_information)
    {
        reset((int)clock);
    }
}

void Performance::endWorktime(Clock_List clock)
{
    if(debug_information)
    {
        worktime_=getTime((int)clock).asMicroseconds();
        lists_[(int)clock].emplace_back(worktime_);
    }
}

void Performance::save()
{
    if(debug_information)
    {
        const char* path = "worktime.txt";

        std::ofstream ofs(path, std::ios::out | std::ios::trunc);

        // 以最短的列表长度为上界
        std::size_t num=lists_[(int)Clock_List::UPDATE_CLOCK].size();
        num=std::min(num,lists_[(int)Clock_List::RENDER_CLOCK1].size());
        num=std::min(num,lists_[(int)Clock_List::DISPLAY_CLOCK1].size());
        num=std::min(num,lists_[(int)Clock_List::RENDER_CLOCK2].size());
        num=std::min(num,lists_[(int)Clock_List::DISPLAY_CLOCK2].size());

        for(std::size_t i=0;i<num;i++)
        {
            ofs<<lists_[(int)Clock_List::UPDATE_CLOCK][i]<<' '
            <<lists_[(int)Clock_List::RENDER_CLOCK1][i]<<' '
            <<lists_[(int)Clock_List::DISPLAY_CLOCK1][i]<<' '
            <<lists_[(int)Clock_List::UPDATE_CLOCK][i]+
            lists_[(int)Clock_List::RENDER_CLOCK1][i]+
            lists_[(int)Clock_List::DISPLAY_CLOCK1][i]<<' '
            <<lists_[(int)Clock_List::RENDER_CLOCK2][i]<<' '
            <<lists_[(int)Clock_List::DISPLAY_CLOCK2][i]<<' '
            <<lists_[(int)Clock_List::RENDER_CLOCK2][i]+
            lists_[(int)Clock_List::DISPLAY_CLOCK2][i]<<' '
            <<lists_[(int)Clock_List::UPDATE_CLOCK][i]+
            lists_[(int)Clock_List::RENDER_CLOCK1][i]+
            lists_[(int)Clock_List::DISPLAY_CLOCK1][i]+
            lists_[(int)Clock_List::RENDER_CLOCK2][i]+
            lists_[(int)Clock_List::DISPLAY_CLOCK2][i]
            << '\n';
        }

        ofs.close();
    }
}