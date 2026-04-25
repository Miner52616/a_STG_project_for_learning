#include "manager/EffectFactory.h"
#include "core/application.h"
#include "effects/Effect.h"
#include "effects/effects/LeiTan_Air.h"
#include "overlays/overlays/PictureOverlay.h"
#include <iostream>

EffectFactory::EffectFactory(application& app):
    app_(app)
{
    initialize(poolsize_);
}

void EffectFactory::initialize(int size)
{
    effectlist_.reserve(size);
    std::cout<<"effect storage "<<size<<std::endl;
    for (int i=1;i<=size;i++)
    {
        effectlist_.emplace_back(app_.overlay1Texture_,sf::Vector2f{0,0},(long long int)60);
        free_list_.push_back(i-1);
    }
    std::cout<<"effect pool initialized"<<std::endl;
}

Effect* EffectFactory::getEffect()
{
    if(free_list_.empty())
    {
        std::cout<<"EFFECT FULL!!!"<<std::endl;
        return nullptr;
    }

    int id=free_list_.back();
    free_list_.pop_back();

    Effect* effect=&effectlist_[id];
    effect->setActive(true);
    effect->initialize();
    effect->setDead(false);
    return effect;
}

void EffectFactory::destroy(Effect* effect)
{
    effect->setActive(false);
    int id=effect-&effectlist_[0];
    //std::cout<<"release "<<id<<std::endl;
    free_list_.push_back(id);
}

/*
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
    */

Effect* EffectFactory::create(EffectConfig* effectconfig)
{
    Effect* effect=getEffect();

    //重新初始化特效，特别单独处理texture的更换
    effect->rebuild(effectconfig->texture_,effectconfig->spawn_point_);
    effect->setTime(effectconfig->time_);
    copyconfig(effect->getEffectConfig(),effectconfig);

    return effect;
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

void copyconfig(EffectConfig* copy,EffectConfig* origin)
{
    //除了texture引用外全员复制
    copy->spawn_point_=origin->spawn_point_;
    copy->effecttype_=origin->effecttype_;
    copy->time_=origin->time_;
    copy->v_=origin->v_;
    copy->direction_=origin->direction_;
}