#include "manager/EffectFactory.h"
#include "effects/Effect.h"
#include "effects/effects/LeiTan_Air.h"
#include "overlays/overlays/PictureOverlay.h"

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

std::unique_ptr<Overlay> EffectFactory::create(OverlayConfig* overlayconfig)
{
    std::unique_ptr<Overlay> overlay;

    std::unique_ptr<PictureOverlay> pictureoverlay;
    switch (overlayconfig->overlaytype_)
    {
    case OverlayType::Picture_Overlay:
        pictureoverlay=std::make_unique<PictureOverlay>(overlayconfig->texture_);
        pictureoverlay->setPosition(overlayconfig->spawn_position_);
        pictureoverlay->setTargetPosition(overlayconfig->target_position_);
        pictureoverlay->setV(overlayconfig->v1_,overlayconfig->v2_);
        return std::move(pictureoverlay);
        break;
    
    default:
        overlay=std::make_unique<PictureOverlay>(overlayconfig->texture_);
        overlay->setPosition(overlayconfig->spawn_position_);

        return std::move(overlay);
        break;
    }
}
