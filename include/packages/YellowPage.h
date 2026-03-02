#pragma once
#include <memory>

class Player;
class NumLine1;

class YellowPage
{
public:
    std::shared_ptr<Player> player_;
    NumLine1 &high_score_line_;
    NumLine1 &score_line_;

public:
    YellowPage(std::shared_ptr<Player> player,NumLine1 &high_score_line,NumLine1 &score_line);
};