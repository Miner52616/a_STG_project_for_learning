#pragma once
#include <memory>
#include <vector>
#include "packages/EffectConfig.h"

class Effect;

class EffectFactory
{
public:
    std::unique_ptr<Effect> create(EffectConfig* effectconfig);
};