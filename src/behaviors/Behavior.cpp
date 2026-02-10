#include "behaviors/Behavior.h"

Behavior::Behavior():
    clock_(180),resourse_(NULL)
{
    ;
}

void Behavior::set_target(long long int target_frame)
{
    clock_.set_target(target_frame);
}

void Behavior::set_resourse(std::shared_ptr<Resourse> resourse)
{
    resourse_=resourse;
}