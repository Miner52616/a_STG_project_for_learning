#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "effects/Effect.h"
#include "packages/EffectConfig.h"
#include "manager/EffectFactory.h"

class EffectManager
{
private:
    std::vector<std::unique_ptr<Effect>> &effectlist_;
    EffectFactory& effectfactory_;

public:
    EffectManager(std::vector<std::unique_ptr<Effect>> &effectlist,EffectFactory& effectfactory);
    void add_process(EffectConfig* effectconfig);
    void update();
    void clear_dead();
    void render(sf::RenderTexture& texture);
};