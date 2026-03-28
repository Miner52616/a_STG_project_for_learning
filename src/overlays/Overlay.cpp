#include "overlays/Overlay.h"

Overlay::Overlay():
    dead_(false)
{
    ;
}


void Overlay::setBehavior(std::shared_ptr<Behavior> behavior)
{
    behavior_=std::move(behavior);
}

void Overlay::update()
{
    for(auto it=behaviorlist_.begin();it!=behaviorlist_.end();++it)
    {
        (*it)->update();
    }
}

void Overlay::addBehavior(Behavior* behavior)
{
    behaviorlist_.emplace_back(behavior);
}

void Overlay::markDead()
{
    dead_=true;
}

bool Overlay::isDead()
{
    return dead_;
}