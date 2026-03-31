#include "packages/YellowPage.h"

YellowPage::YellowPage(Player* player,NumLine1 &high_score_line,NumLine1 &score_line,NumLine1 &power_line,NumLine1 &graze_line):
    player_(player),high_score_line_(high_score_line),score_line_(score_line),power_line_(power_line),graze_line_(graze_line)
{
    ;
}

void YellowPage::setPlayer(Player* player)
{
    player_=player;
}