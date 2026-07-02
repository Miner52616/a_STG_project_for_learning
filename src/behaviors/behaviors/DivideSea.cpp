#include "behaviors/behaviors/DivideSea.h"
#include "core/application.h"

DivideSea1::DivideSea1(Entity* entity,Resource* resource,YellowPage* yellowpage)
    :ShootBehavior(resource,yellowpage),entity_(entity),bulletconfig_(resource->app_.bulletsheetTexture2_)
{
    setBulletConfig();
}

void DivideSea1::setBulletConfig()
{
    ;
}

void DivideSea1::update()
{
    ;
}