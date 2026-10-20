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

void Performance::startWorktime(Clock_List clock)
{
    reset((int)clock);
}

void Performance::endWorktime(Clock_List clock)
{
    worktime_=getTime((int)clock).asMicroseconds();
    lists_[(int)clock].emplace_back(worktime_);
    //worktime_line_.setCurrentNum(worktime_);
}

void Performance::save()
{
    const char* path = "worktime.txt";

    std::ofstream ofs(path, std::ios::out | std::ios::trunc); // 打开即清空

    // 各时钟列表长度可能不一致（如 RENDER_CLOCK2 从未被 endWorktime），
    // 因此以最短的列表长度为上界，避免越界访问。
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