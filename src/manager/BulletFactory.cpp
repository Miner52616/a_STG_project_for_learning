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
    for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
    {
        it->setResource(resource);
    }
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
        bulletlist_.emplace_back(app_.bulletsheetTexture_,sf::Vector2f{0,0});
        free_list_.push_back(i-1);
    }
}

Bullet* BulletFactory::getBullet()
{
    if(free_list_.empty())
    {
        std::cout<<"BULLET FULL!!!"<<std::endl;
        return nullptr;
    }

    int id=free_list_.back();
    free_list_.pop_back();

    Bullet* bullet=&bulletlist_[id];
    bullet->setActive(true);
    bullet->initialize();
    bullet->setDead(false);
    return bullet;
}

void BulletFactory::destroy(Bullet* bullet)
{
    bullet->setActive(false);
    int id=bullet-&bulletlist_[0];
    //std::cout<<"release "<<id<<std::endl;
    free_list_.push_back(id);
}


Bullet* BulletFactory::create(BulletConfig* bulletconfig)
{
    Bullet* bullet=getBullet();

    //子弹其它可选用属性，通过bulletconfig传递
    copyconfig(bullet->getBulletConfig(),bulletconfig);

    //重新初始化和设置子弹核心属性，特别单独处理texture的更换
    bullet->rebuild(bulletconfig->texture_,bulletconfig->spawn_point_,bulletconfig->damage_);
    bullet->setHitbox_r(bulletconfig->r_);
    if
    (
        (bulletconfig->bulletclass_==BulletClasses::PlayerBullet)
        ||((bulletconfig->bulletclass_==BulletClasses::PlayerAimBullet))
    )
    {
        bullet->setbelong(true);
    }
    else
    {
        bullet->setbelong(false);
    }

    return bullet;
}

void copyconfig(BulletConfig* copy,BulletConfig* origin)
{
    //提供的时钟默认先reset
    copy->clock1_.reset();
    copy->clock2_.reset();
    copy->clock3_.reset();

    //除了图片之外的所有子弹信息全部拷贝（引用对象无法改引用，图片设置非子弹信息，单独处理）
    copy->bulletclass_=origin->bulletclass_;
    copy->damage_=origin->damage_;
    copy->direction_=origin->direction_;
    copy->r_=origin->r_;
    copy->spawn_point_=origin->spawn_point_;
    copy->target_point_=origin->target_point_;
    copy->v_=origin->v_;
    copy->a_=origin->a_;
    copy->clock1_.set_target(origin->clock1_.get_target());
    copy->v2_=origin->v2_;
    copy->a2_=origin->a2_;
    copy->v3_=origin->v3_;
    copy->direction2_=origin->direction2_;
    copy->clock2_.set_target(origin->clock2_.get_target());
    copy->clock3_.set_target(origin->clock3_.get_target());
    copy->bulletbehavior_=origin->bulletbehavior_;
    copy->angle_=origin->angle_;
    copy->bullet_index_=origin->bullet_index_;
    copy->bulletsize_=origin->bulletsize_;
}