#include "behaviors/Behavior.h"

Behavior::Behavior():
    clock_(180),resource_(NULL)
{
    ;
}

void Behavior::set_target(long long int target_frame)
{
    clock_.set_target(target_frame);
}

void Behavior::set_resource(Resource* resource)
{
    resource_=resource;
}

void Behavior::set_YellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
}