#pragma once
#include <SFML/Graphics.hpp>
#include "ui/NumLine1.h"

enum class Clock_List
{
    FPS_CLOCK=0,
    FRAME_CLOCK=1
};

class Performance
{
private:
    const sf::Font& font_;
    NumLine1 worktime_line_;

    int frame_count_;
    float worktime_;
    sf::Clock clock_list[8];

public:
    Performance(const sf::Font& font);
    void reset(int num);
    sf::Time getTime(int num);
    void render(sf::RenderWindow& window);

    void startWorktime();
    void endWorktime();
};