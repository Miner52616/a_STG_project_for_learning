#pragma once
#include <memory>

class Player;
class NumLine1;

class YellowPage
{
public:
    Player* player_;
    NumLine1 &high_score_line_;
    NumLine1 &score_line_;
    NumLine1 &power_line_;

public:
    YellowPage(Player* player,NumLine1 &high_score_line,NumLine1 &score_line,NumLine1 &power_line);
    void setPlayer(Player* player);
};