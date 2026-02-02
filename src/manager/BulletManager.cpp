#include "manager/BulletManager.h"
#include "ui/Frame.h"
#include "core/Clock.h"

BulletManager::BulletManager(application &app,std::vector<std::unique_ptr<Bullet>> &bulletlist):
    app_(app),bulletlist_(bulletlist)//,outline_(outline),player_(player)
{
    ;
}

void BulletManager::add_process(std::unique_ptr<Bullet> bullet)
{
    bulletlist_.emplace_back(std::move(bullet));
}

void BulletManager::update()
{
    bulletlist_update();
}

void BulletManager::clear()
{
    bulletlist_.erase
    (
        std::remove_if
        (
            bulletlist_.begin(),bulletlist_.end(),
            [this](const std::unique_ptr<Bullet>& bullet)
            {
                if(bullet->isDead())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        ),
        bulletlist_.end()
    );
}

void BulletManager::render(sf::RenderWindow& window)
{
    bulletlist_render(window);
}
/*
void BulletManager::playerbulletlist_add()
{
    if(player_.Handle_shoot_request())
    {    
        playerbulletlist_.emplace_back(std::make_unique<Bullet>(app_.bulletTexture_,player_.getPosition()));
    }
}
*/

void BulletManager::bulletlist_update()
{
    /*
    playerbulletlist_clear();
    playerbulletlist_move();
    playerbulletlist_add();
    */
   for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
   {
        (*it)->update();
   }
}

void BulletManager::bulletlist_render(sf::RenderWindow& window)
{
    for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
    {
        (*it)->drawwindow(window);
    }
}

/*
void BulletManager::playerbulletlist_clear()
{
    playerbulletlist_.erase
    (
        std::remove_if
        (
            playerbulletlist_.begin(),playerbulletlist_.end(),
            [this](const std::unique_ptr<Bullet>& bullet)
            {
                if((bullet->getPosition().x<outline_.getBounds_left())||(bullet->getPosition().y<-50)||(bullet->getPosition().x>outline_.getBounds_right())||(bullet->getPosition().y>outline_.getBounds_bottom()))
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
*/
/*
void BulletManager::playerbulletlist_move()
{
    for(auto it=playerbulletlist_.begin();it!=playerbulletlist_.end();++it)
    {
        (*it)->setPosition({(*it)->getPosition().x,(*it)->getPosition().y-12});
    }
}
*/