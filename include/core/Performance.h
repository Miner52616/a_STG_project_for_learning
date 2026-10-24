#pragma once
#include <SFML/Graphics.hpp>
#include "ui/NumLine1.h"

enum class Clock_List
{
    UPDATE_CLOCK=0,
    RENDER_CLOCK1=1,
    DISPLAY_CLOCK1=2,
    RENDER_CLOCK2=3,
    DISPLAY_CLOCK2=4
};

class Performance
{
//debug参数
private:
    bool debug_information=false;
private:
    const sf::Font& font_;
    NumLine1 worktime_line_;
    std::vector<std::vector<int>> lists_;

    int frame_count_;
    float worktime_;
    sf::Clock clock_list[8];

private:
    void reset(int num);
    sf::Time getTime(int num);
public:
    Performance(const sf::Font& font);
    void setActive(bool active);
    void render(sf::RenderWindow& window);
    void calculate_worktime();

    void startWorktime(Clock_List clock);
    void endWorktime(Clock_List clock);
    void save();
};