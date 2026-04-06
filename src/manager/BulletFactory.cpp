#include "manager/BulletFactory.h"
#include "core/application.h"
#include "behaviors/behaviors/DirectMove1.h"
#include "behaviors/behaviors/AimMove3.h"
#include <iostream>

BulletFactory::BulletFactory(application& app):
    app_(app)
{
    std::cout<<"build BulletFactory"<<std::endl;
    initialize(poolsize_);
    std::cout<<"success"<<std::endl;
}


void BulletFactory::setResource(Resource* resource)
{
    resource_=resource;
}

void BulletFactory::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
    for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
    {
        it->setYellowPage(yellowpage);
    }
}

int BulletFactory::getPoolSize()
{
    return poolsize_;
}

void BulletFactory::initialize(int size)
{
    bulletlist_.reserve(size);
    std::cout<<"bullet storage "<<size<<std::endl;
    for (int i=1;i<=size;i++)
    {
        bulletlist_.emplace_back(app_.bulletTexture_,sf::Vector2f{0,0});
        free_list_.push(i-1);
    }
}

Bullet* BulletFactory::getBullet()
{
    if(free_list_.empty())
    {
        std::cout<<"FULL!!!"<<std::endl;
        return nullptr;
    }

    int id=free_list_.front();
    free_list_.pop();

    Bullet* bullet=&bulletlist_[id];
    bullet->setActive(true);
    bullet->initialize();
    bullet->setDead(false);
    return bullet;
}

void BulletFactory::destroy(Bullet* bullet)
{
    bullet->setActive(false);
    //bullet->initialize();
    int id=bullet-&bulletlist_[0];
    std::cout<<"release "<<id<<std::endl;
    free_list_.push(id);
}


Bullet* BulletFactory::create(std::shared_ptr<BulletConfig> bulletconfig)
{
    Bullet* bullet=getBullet();
    bullet->rebuild(bulletconfig->texture_,bulletconfig->spawn_point_,bulletconfig->damage_);
    bullet->setBulletConfig(bulletconfig);
    
    if(bulletconfig->bulletclass_!=BulletClasses::PlayerBullet)
    {
        bullet->setbelong(false);
    }
    /*
    switch(bulletconfig->bulletclass_)
    {
        case BulletClasses::LinearBullet:
        {
            bullet->setbelong(false);
            return std::move(bullet);
        }
        case BulletClasses::PlayerBullet:
        {
            return std::move(bullet);
        }
        default:
        {
            std::cout<<"Bullet Create Type ERROR"<<std::endl;
            return NULL;
        }
    
    }
        */

    return bullet;
            
}