#include "packages/Resource.h"

Resource::Resource(AssetsResource &app,Debug &debug,BulletManager &bulletmanager,DropManager &dropmanager,BombManager &bombmanager,EffectManager &effectmanager,BatchManager& batchmanager,CollisionSystem &collisionsystem,PhaseController &phasecontroller,Keys &keys):
    app_(app),
    debug_(debug),
    bulletmanager_(bulletmanager),
    dropmanager_(dropmanager),
    bombmanager_(bombmanager),
    effectmanager_(effectmanager),
    batchmanager_(batchmanager),
    collisionsystem_(collisionsystem),
    phasecontroller_(phasecontroller),
    keys_(keys)
{
    ;
}