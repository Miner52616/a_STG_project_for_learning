#include "behaviors/behaviors/MarkDead.h"
#include "overlays/Overlay.h"

MarkDead::MarkDead(Overlay* overlay):
    overlay_(overlay),delay_time_(120)
{
    delay_time_.reset();
}

void MarkDead::update()
{
    if(delay_time_.get_condition())
    {
        overlay_->markDead();
    }
    delay_time_.count();
}

void MarkDead::setTargetTime(int time)
{
    delay_time_.set_target(time);
}