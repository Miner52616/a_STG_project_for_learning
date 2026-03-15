#include "packages/Resource.h"

Resource::Resource(application &app,BulletManager &bulletmanager,DropManager &dropmanager,CollisionSystem &collisionsystem):
    app_(app),bulletmanager_(bulletmanager),dropmanager_(dropmanager),collisionsystem_(collisionsystem)
{
    ;
}