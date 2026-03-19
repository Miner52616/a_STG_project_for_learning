#include "manager/BombManager.h"
#include "manager/CollisionSystem.h"
#include "entities/Bomb.h"
#include <iostream>

BombManager::BombManager(std::vector<std::unique_ptr<Bomb>> &bomblist_,BombFactory &bombfactory):
    bomblist_(bomblist_),bombfactory_(bombfactory)
{
    ;
}

void BombManager::add_process(BombConfig* bombconfig)
{
    bomblist_.emplace_back(bombfactory_.create(bombconfig));
    std::cout<<"3"<<std::endl;
}

void BombManager::update()
{
    for(auto it=bomblist_.begin();it!=bomblist_.end();++it)
    {
        (*it)->update();
    }
}

void BombManager::clear_dead()
{
    bomblist_.erase
    (
        std::remove_if
        (
            bomblist_.begin(),bomblist_.end(),
            [this](const std::unique_ptr<Bomb>& bomb)
            {
                if(bomb->isDead())
                {
                    return true;
                }
                else
                {
                    return false;    
                }
            }
        ),bomblist_.end()
    );
}

void BombManager::render(sf::RenderTexture& texture)
{
    for(auto it=bomblist_.begin();it!=bomblist_.end();++it)
    {
        (*it)->drawtexture(texture);
    }
}

void BombManager::ProcessCollision()
{
    for(auto it=bomblist_.begin();it!=bomblist_.end();++it)
    {
        resource_->collisionsystem_.ProcessCollision(it->get());
    }
}

void BombManager::set_Resource(Resource* resource)
{
    resource_=resource;
}