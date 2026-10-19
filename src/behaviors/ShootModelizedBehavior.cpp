#include "behaviors/ShootModelizedBehavior.h"

ShootModelizedBehavior::ShootModelizedBehavior(Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),
    delayclock_(180),loopclock_(30)
{
    delayclock_.reset();
}

void ShootModelizedBehavior::update()
{
    if(delayclock_.get_condition())
    {
        stateUpdate();
        if(loopclock_.get_condition())
        {
            loopclock_.reset();
            eventUpdate();
        }
        loopclock_.count();
    }
    delayclock_.count();
}