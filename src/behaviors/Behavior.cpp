#include "behaviors/Behavior.h"

Behavior::Behavior():
    clock_(180),resource_(NULL)
{
    ;
}

Behavior::Behavior(Resource* resource,YellowPage* yellowpage):
    clock_(180),resource_(resource),yellowpage_(yellowpage)
{
    ;
}

Behavior::Behavior(Resource* resource,YellowPage* yellowpage,long long int target_frame):
    clock_(target_frame),resource_(resource),yellowpage_(yellowpage)
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