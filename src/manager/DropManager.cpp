#include "manager/DropManager.h"
#include "entities/Player.h"
#include <iostream>

DropManager::DropManager(std::vector<std::unique_ptr<Drop>> &droplist,DropFactory &dropfactory):
    droplist_(droplist),dropfactory_(dropfactory)
{
    ;
}

void DropManager::add_process(std::shared_ptr<DropConfig> dropconfig)
{
    droplist_.emplace_back(std::move(dropfactory_.create(dropconfig)));
    //std::cout<<"add success"<<std::endl;
}

void DropManager::set_resource(std::shared_ptr<Resource> resource)
{
    resource_=std::move(resource);
}

void DropManager::update()
{
    if(resource_->player_->getPosition().y<=300)
    {
        for(auto it=droplist_.begin();it!=droplist_.end();++it)
        {
            (*it)->setPhase(2);
        }
    }
    for(auto it=droplist_.begin();it!=droplist_.end();++it)
    {
        (*it)->update();
    }
}

void DropManager::clear_dead()
{
    droplist_.erase
    (
        std::remove_if
        (
            droplist_.begin(),droplist_.end(),
            [this](const std::unique_ptr<Drop>& drop)
            {
                if(drop->isDead())
                {
                    return true;
                }
                else
                {
                    return false;    
                }
            }
        ),
        droplist_.end()
    );
    //std::cout<<"clear success"<<std::endl;
}

void DropManager::render(sf::RenderTexture& texture)
{
    for(auto it=droplist_.begin();it!=droplist_.end();++it)
    {
        (*it)->drawtexture(texture);
    }
    //std::cout<<"render success"<<std::endl;
}