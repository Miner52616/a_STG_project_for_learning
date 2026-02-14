#include "overlays/Overlay.h"

void Overlay::setBehavior(std::shared_ptr<Behavior> behavior)
{
    behavior_=std::move(behavior);
}