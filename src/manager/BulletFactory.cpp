#include "manager/BulletFactory.h"
#include "behaviors/behaviors/DirectMove1.h"
#include "behaviors/behaviors/AimMove3.h"
#include <iostream>

BulletFactory::BulletFactory()
{
    //initialize(1500);
}

/*
void BulletFactory::initialize(int size)
{
    bulletlist_.resize(size);
    for (int i = 0; i < size; ++i)
        free_list_.push(i);
}

Bullet* BulletFactory::getBullet()
{
    if(free_list_.empty())
    {
        return nullptr;
    }

    int id=free_list_.front();
    free_list_.pop();

    Bullet* bullet=&bulletlist_[id];
    bullet->setActive(true);
    return bullet;
}

void BulletFactory::destory(Bullet* bullet)
{
    bullet->setActive(false);
    int id=bullet-&bulletlist_[0];
    free_list_.push(id);
}
*/

std::unique_ptr<Bullet> BulletFactory::create(std::shared_ptr<BulletConfig> bulletconfig)
{
    std::unique_ptr<Bullet> bullet=std::make_unique<Bullet>(bulletconfig->texture_,bulletconfig->spawn_point_,bulletconfig->damage_);
    switch(bulletconfig->bulletclass_)
    {
        case BulletClasses::LinearBullet:
        {
            bullet->setbelong(false);
            std::unique_ptr<Behavior> aimbulletbehavior=std::make_unique<AimMove3>(bullet.get(),bulletconfig->v_,bulletconfig->target_point_);
            bullet->addBehavior(std::move(aimbulletbehavior));
            //return std::make_unique<LinearBullet>(bulletconfig->texture_,bulletconfig->spawn_point_,bulletconfig->target_point_,bulletconfig->v_,bulletconfig->r_);
            return std::move(bullet);
        }
        case BulletClasses::PlayerBullet:
        {
            std::unique_ptr<Behavior> playerbulletbehavior=std::make_unique<DirectMove1>(bullet.get(),bulletconfig->v_,sf::Vector2f{0,-1});
            bullet->addBehavior(std::move(playerbulletbehavior));
            return std::move(bullet);
        }
        default:
        {
            std::cout<<"Bullet Create Type ERROR"<<std::endl;
            return std::make_unique<PlayerBullet>(bulletconfig->texture_,bulletconfig->spawn_point_);
        }
    }
}