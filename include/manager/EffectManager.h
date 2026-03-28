#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "effects/Effect.h"
#include "overlays/Overlay.h"
#include "packages/EffectConfig.h"
#include "manager/EffectFactory.h"

class EffectManager
{
private:
    std::vector<std::unique_ptr<Effect>> &effectlist_;
    std::vector<std::unique_ptr<Overlay>> &overlaylist_;
    EffectFactory& effectfactory_;


public:
    EffectManager(std::vector<std::unique_ptr<Effect>> &effectlist,std::vector<std::unique_ptr<Overlay>> &overlaylist,EffectFactory& effectfactory);
    void add_process(EffectConfig* effectconfig);
    void add_process(OverlayConfig* overlayconfig);
    void update();
    void clear_dead();
    void render(sf::RenderTexture& texture);
};