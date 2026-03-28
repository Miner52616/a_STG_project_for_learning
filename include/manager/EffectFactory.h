#pragma once
#include <memory>
#include <vector>
#include "packages/EffectConfig.h"

class Effect;
class Overlay;

class EffectFactory
{
public:
    std::unique_ptr<Overlay> create(OverlayConfig* overlayconfig);
    std::unique_ptr<Effect> create(EffectConfig* effectconfig);
};