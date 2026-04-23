#include "behaviors/behaviors/DreamingShootingStar.h"
#include "core/application.h"

DreamingShootingStar1::DreamingShootingStar1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),entity_(entity),shoot_clock_(24),bulletconfig_(resource->app_.deep_blue_light_bulletTexture_)
{
    setBulletConfig();
}

void DreamingShootingStar1::setBulletConfig()
{
    ;
}

void DreamingShootingStar1::update()
{
    ;
}