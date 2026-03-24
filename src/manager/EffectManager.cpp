#include "manager/EffectManager.h"

EffectManager::EffectManager(std::vector<std::unique_ptr<Effect>> &effectlist,EffectFactory& effectfactory):
    effectlist_(effectlist),effectfactory_(effectfactory)
{
    ;
}

void EffectManager::add_process(EffectConfig* effectconfig)
{
    effectlist_.emplace_back(effectfactory_.create(effectconfig));
}

void EffectManager::update()
{
    for(auto it=effectlist_.begin();it!=effectlist_.end();++it)
    {
        (*it)->update();
    }
}

void EffectManager::clear_dead()
{
    effectlist_.erase
    (
        std::remove_if
        (
            effectlist_.begin(),effectlist_.end(),
            [this](const std::unique_ptr<Effect>& effect)
            {
                if(effect->isDead())
                {
                    return true;
                }
                else
                {
                    return false;    
                }
            }
        ),effectlist_.end()
    );
}

void EffectManager::render(sf::RenderTexture& texture)
{
    for(auto it=effectlist_.begin();it!=effectlist_.end();++it)
    {
        (*it)->drawtexture(texture);
    }
}