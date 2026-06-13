#pragma once
#include "behaviors/Behavior.h"
#include "packages/EffectConfig.h"

class ShootBehavior:public Behavior
{
protected:
    EffectConfig effectconfig_;

    virtual void setEffectConfig();//特效的固定属性设置
    virtual void setBulletConfig()=0;//子弹的固定属性设置

public:
    ShootBehavior(Resource* resource,YellowPage* yellowpage);
    ShootBehavior(Resource* resource,YellowPage* yellowpage,long long int target_frame);
};