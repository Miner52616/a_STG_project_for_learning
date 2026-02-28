#include "manager/DropManager.h"

DropManager::DropManager(std::vector<std::unique_ptr<Drop>> &droplist,DropFactory &dropfactory):
    droplist_(droplist),dropfactory_(dropfactory)
{
    ;
}

void DropManager::add_process(std::shared_ptr<DropConfig> dropconfig)
{
    droplist_.emplace_back(std::move(dropfactory_.create(dropconfig)));
}

void DropManager::update()
{
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
}

void DropManager::render(sf::RenderTexture& texture)
{
    for(auto it=droplist_.begin();it!=droplist_.end();++it)
    {
        (*it)->drawtexture(texture);
    }
}