#include "packages/Resource.h"

Resource::Resource(application &app,BulletManager &bulletmanager,DropManager &dropmanager,CollisionSystem &collisionsystem,std::shared_ptr<Player> player):
    app_(app),bulletmanager_(bulletmanager),dropmanager_(dropmanager),collisionsystem_(collisionsystem),player_(player)
{
    ;
}

void Resource::setPlayer(std::shared_ptr<Player> player)
{
    player_=std::move(player);
}