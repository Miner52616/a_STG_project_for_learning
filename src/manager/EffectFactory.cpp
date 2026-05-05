#include "manager/EffectFactory.h"
#include "core/application.h"
#include "effects/Effect.h"
#include "effects/effects/LeiTan_Air.h"
#include "overlays/overlays/PictureOverlay.h"
#include "overlays/overlays/TextOverlay.h"
#include "behaviors/behaviors/MarkDead.h"
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

    copyconfig(effect->getEffectConfig(),effectconfig);

    //重新初始化特效，特别单独处理texture的更换
    effect->rebuild(*(effectconfig->texture_),effectconfig->spawn_point_);
    effect->setTime(effectconfig->time_);

    return effect;
}

std::unique_ptr<Overlay> EffectFactory::create(OverlayConfig* overlayconfig)
{
    std::unique_ptr<Overlay> overlay;

    std::unique_ptr<MarkDead> behavior;

    std::unique_ptr<PictureOverlay> pictureoverlay;
    std::unique_ptr<TextOverlay> textoverlay;
    switch (overlayconfig->overlaytype_)
    {
    case OverlayType::Picture_Overlay:
        pictureoverlay=std::make_unique<PictureOverlay>(overlayconfig->texture_);
        pictureoverlay->setPosition(overlayconfig->spawn_position_);
        pictureoverlay->setTargetPosition(overlayconfig->target_position_);
        pictureoverlay->setV(overlayconfig->v1_,overlayconfig->v2_);
        return std::move(pictureoverlay);
        break;

    case OverlayType::Text_Overlay:
        textoverlay=std::make_unique<TextOverlay>(app_.mainFont_);
        textoverlay->setTextText(overlayconfig->text_);
        textoverlay->setTextSize(overlayconfig->text_size_);
        textoverlay->setTextColor(sf::Color{255,255,255,overlayconfig->color_alpha_});
        textoverlay->changeOrigin(overlayconfig->change_origin_);
        textoverlay->setPosition(overlayconfig->spawn_position_);
        behavior=std::make_unique<MarkDead>(textoverlay.get());
        behavior->setTargetTime(overlayconfig->time_);

        textoverlay->addBehavior(std::move(behavior));
        return std::move(textoverlay);
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
    copy->texture_=origin->texture_;
    copy->spawn_point_=origin->spawn_point_;
    copy->effecttype_=origin->effecttype_;
    copy->time_=origin->time_;
    copy->v_=origin->v_;
    copy->a_=origin->a_;
    copy->v2_=origin->v2_;
    copy->direction_=origin->direction_;
    //copy->texturelist_=origin->texturelist_;
    copy->texturelist_size_=origin->texturelist_size_;
    copy->current_texture_num_=origin->current_texture_num_;
    copy->effect_index_=origin->effect_index_;
    copy->random_rotate_=origin->random_rotate_;
    copy->color_alpha_=origin->color_alpha_;
}