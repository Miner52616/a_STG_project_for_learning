#include "manager/EffectFactory.h"
#include "effects/Effect.h"
#include "effects/effects/LeiTan_Air.h"

std::unique_ptr<Effect> EffectFactory::create(EffectConfig* effectconfig)
{
    std::unique_ptr<Effect> effect;
    switch (effectconfig->effecttype_)
    {
    case EffectType::LeiTan_Air:
        effect=std::make_unique<LeiTan_Air>(effectconfig->texture_,effectconfig->spawn_point_,effectconfig->time_,effectconfig->direction_,effectconfig->v_);
        return std::move(effect);
        break;
    
    default:
        effect=std::make_unique<LeiTan_Air>(effectconfig->texture_,effectconfig->spawn_point_,effectconfig->time_,effectconfig->direction_,effectconfig->v_);
        return std::move(effect);
        break;
    }
}