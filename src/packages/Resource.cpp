#include "packages/Resource.h"

Resource::Resource(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,std::shared_ptr<Player> player):
    app_(app),bulletmanager_(bulletmanager),collisionsystem_(collisionsystem),player_(player)
{
    ;
}

void Resource::setPlayer(std::shared_ptr<Player> player)
{
    player_=std::move(player);
}