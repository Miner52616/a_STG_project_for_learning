#include "core/Clock.h"

Clock::Clock(long long int target_frame):
    target_frame_(target_frame),current_frame_(9999)
{
    ;
}

void Clock::count()
{
    current_frame_++;
}

void Clock::reset()
{
    current_frame_=0;
}

bool Clock::get_condition()
{
    if(current_frame_>=target_frame_)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Clock::set_target(long long int target_frame)
{
    target_frame_=target_frame;
}