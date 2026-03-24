#include "packages/Resource.h"

Resource::Resource(application &app,BulletManager &bulletmanager,DropManager &dropmanager,BombManager &bombmanager,EffectManager &effectmanager,CollisionSystem &collisionsystem,PhaseController &phasecontroller):
    app_(app),bulletmanager_(bulletmanager),dropmanager_(dropmanager),bombmanager_(bombmanager),effectmanager_(effectmanager),collisionsystem_(collisionsystem),phasecontroller_(phasecontroller)
{
    ;
}