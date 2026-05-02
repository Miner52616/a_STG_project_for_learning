#pragma once
#include <memory>
#include <vector>
#include "packages/EffectConfig.h"

class Effect;
class Overlay;
class application;

class EffectFactory
{
private:
    application& app_;

    int poolsize_=5000;
    std::vector<Effect> effectlist_;
    std::vector<int> free_list_;

    void initialize(int size);
    Effect* getEffect();

public:
    EffectFactory(application& app);
    std::unique_ptr<Overlay> create(OverlayConfig* overlayconfig);
    //std::unique_ptr<Effect> create(EffectConfig* effectconfig);
    Effect* create(EffectConfig* effectconfig);
    void destroy(Effect* effect);
};

void copyconfig(EffectConfig* copy,EffectConfig* origin);