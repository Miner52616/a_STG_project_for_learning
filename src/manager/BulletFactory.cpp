#include "manager/BulletFactory.h"
#include <iostream>

std::unique_ptr<Bullet> BulletFactory::create(std::shared_ptr<BulletConfig> bulletconfig)
{
    switch(bulletconfig->bulletclass_)
    {
        case BulletClasses::LinearBullet:
        {
            return std::make_unique<LinearBullet>(bulletconfig->texture_,bulletconfig->spawn_point_,bulletconfig->target_point_,bulletconfig->v_,bulletconfig->r_);
        }
        case BulletClasses::PlayerBullet:
        {
            return std::make_unique<PlayerBullet>(bulletconfig->texture_,bulletconfig->spawn_point_);
        }
        default:
        {
            std::cout<<"Bullet Create Type ERROR"<<std::endl;
            return std::make_unique<PlayerBullet>(bulletconfig->texture_,bulletconfig->spawn_point_);
        }
    }
}