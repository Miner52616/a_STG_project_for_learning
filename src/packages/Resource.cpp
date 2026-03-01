#include "packages/Resource.h"

Resource::Resource(application &app,BulletManager &bulletmanager,DropManager &dropmanager,CollisionSystem &collisionsystem,std::shared_ptr<Player> player,NumLine1 &high_score_line,NumLine1 &score_line):
    app_(app),bulletmanager_(bulletmanager),dropmanager_(dropmanager),collisionsystem_(collisionsystem),player_(player),high_score_line_(high_score_line),score_line_(score_line)
{
    ;
}

void Resource::setPlayer(std::shared_ptr<Player> player)
{
    player_=std::move(player);
}