#include "manager/EffectManager.h"
#include <iostream>

EffectManager::EffectManager(std::vector<Effect*>& effectlist,std::vector<std::unique_ptr<Overlay>> &overlaylist,EffectFactory& effectfactory):
    effectlist_(effectlist),overlaylist_(overlaylist),effectfactory_(effectfactory)
{
    ;
}

void EffectManager::add_process(EffectConfig* effectconfig)
{
    effectlist_.emplace_back(effectfactory_.create(effectconfig));
}

void EffectManager::add_process(OverlayConfig* overlayconfig)
{
    overlaylist_.emplace_back(effectfactory_.create(overlayconfig));
    //std::cout<<"add"<<std::endl;
}

void EffectManager::update()
{
    for(auto it=overlaylist_.begin();it!=overlaylist_.end();++it)
    {
        (*it)->update();
        //std::cout<<"update"<<std::endl;
    }

    for(auto it=effectlist_.begin();it!=effectlist_.end();++it)
    {
        (*it)->update();
    }
}

void EffectManager::clear_dead()
{
    for(auto it=effectlist_.begin();it!=effectlist_.end();++it)
    {
        if((*it)->isDead())
        effectfactory_.destroy(*it);
    }

    effectlist_.erase
    (
        std::remove_if
        (
            effectlist_.begin(),effectlist_.end(),
            [this](Effect*& effect)
            {
                if(effect->isDead())
                {
                    //std::cout<<"dead"<<std::endl;
                    //std::cout<<effect->getPosition().x<<" "<<effect->getPosition().y<<std::endl;
                    return true;
                }
                else
                {
                    return false;    
                }
            }
        ),effectlist_.end()
    );

    overlaylist_.erase
    (
        std::remove_if
        (
            overlaylist_.begin(),overlaylist_.end(),
            [this](const std::unique_ptr<Overlay>& effect)
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
        ),overlaylist_.end()
    );
}

void EffectManager::render(sf::RenderTexture& texture)
{
    for(auto it=overlaylist_.begin();it!=overlaylist_.end();++it)
    {
        (*it)->render(texture);
        //std::cout<<"render"<<std::endl;
    }

    for(auto it=effectlist_.begin();it!=effectlist_.end();++it)
    {
        (*it)->drawtexture(texture);
    }
}