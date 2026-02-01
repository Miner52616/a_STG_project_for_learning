#include "manager/BulletManager.h"
#include "core/Clock.h"

BulletManager::BulletManager(application &app,Player &player):
    app_(app),player_(player)
{
    ;
}

void BulletManager::update()
{
    playerbulletlist_update();
}

void BulletManager::render(sf::RenderWindow& window)
{
    playerbulletlist_render(window);
}

void BulletManager::playerbulletlist_add()
{
    if(player_.Handle_shoot_request())
    {    
        playerbulletlist_.emplace_back(std::make_unique<Bullet>(app_.bulletTexture_,player_.getPosition()));
    }
}

void BulletManager::playerbulletlist_update()
{
    playerbulletlist_clear();
    playerbulletlist_move();
    playerbulletlist_add();
}

void BulletManager::playerbulletlist_render(sf::RenderWindow& window)
{
    for(auto it=playerbulletlist_.begin();it!=playerbulletlist_.end();++it)
    {
        (*it)->drawwindow(window);
    }
}

void BulletManager::playerbulletlist_clear()
{
    playerbulletlist_.erase
    (
        std::remove_if
        (
            playerbulletlist_.begin(),playerbulletlist_.end(),
            [](const std::unique_ptr<Bullet>& bullet)
            {
                if((bullet->getPosition().x<0)||(bullet->getPosition().y<0)||(bullet->getPosition().x>1280)||(bullet->getPosition().y>960))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        ),
        playerbulletlist_.end()
    );
}

void BulletManager::playerbulletlist_move()
{
    for(auto it=playerbulletlist_.begin();it!=playerbulletlist_.end();++it)
    {
        (*it)->setPosition({(*it)->getPosition().x,(*it)->getPosition().y-12});
    }
}