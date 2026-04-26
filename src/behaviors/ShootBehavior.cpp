#include "behaviors/ShootBehavior.h"
#include "core/application.h"

ShootBehavior::ShootBehavior(Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),effectconfig_(resource->app_.effectsheetTexture_)
{
    setEffectConfig();
}

ShootBehavior::ShootBehavior(Resource* resource,YellowPage* yellowpage,long long int target_frame):
    Behavior(resource,yellowpage,target_frame),effectconfig_(resource->app_.effectsheetTexture_)
{
    setEffectConfig();
}

void ShootBehavior::setEffectConfig()
{
    effectconfig_.effect_index_={1,1};
    effectconfig_.effecttype_=Bullet_Air;
    effectconfig_.random_rotate_=true;
    effectconfig_.texturelist_size_=8;
    effectconfig_.current_texture_num_=0;
    effectconfig_.time_=32;
}