#pragma once
#include "behaviors/Behavior.h"
#include "packages/EffectConfig.h"

class ShootBehavior:public Behavior
{
protected:
    EffectConfig effectconfig_;

    void setEffectConfig();
    virtual void setBulletConfig()=0;

public:
    ShootBehavior(Resource* resource,YellowPage* yellowpage);
    ShootBehavior(Resource* resource,YellowPage* yellowpage,long long int target_frame);
};