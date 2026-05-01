#include "behaviors/behaviors/NonSpell1.h"
#include "packages/BulletConfig.h"
#include "mathematics/mathematics.h"
#include "core/application.h"
#include "entities/Entity.h"
#include "manager/BulletManager.h"

NonSpell1_1::NonSpell1_1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),shoot_clock_(2),bulletconfig_(resource->app_.red_light_bulletTexture_)
{
    bullet_direction_={0,1};
    for(int i=1;i<=4;i++)
    {
        direction_list_.push_back({0,0});
    }
    setBulletConfig();
    rotate();
}

void NonSpell1_1::setBulletConfig()
{
    bulletconfig_.r_=3;
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
}

void NonSpell1_1::rotate()
{
    bullet_direction_=roundwithCenter({0,0},bullet_direction_,9);//40次发弹转一圈
    direction_list_[0]=bullet_direction_;
    direction_list_[1]={-bullet_direction_.y,bullet_direction_.x};
    direction_list_[2]=-bullet_direction_;
    direction_list_[3]={bullet_direction_.y,-bullet_direction_.x};
}

void NonSpell1_1::update()
{
    if(shoot_clock_.get_condition())
    {
        shoot_clock_.reset();

        bulletconfig_.spawn_point_=entity_->getPosition();

        bulletconfig_.v_=6;

        bulletconfig_.direction_=direction_list_[0];
        resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);

        bulletconfig_.direction_=direction_list_[2];
        resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);

        bulletconfig_.v_=3;

        bulletconfig_.direction_=direction_list_[1];
        resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);

        bulletconfig_.direction_=direction_list_[3];
        resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
    
        rotate();
    }
    shoot_clock_.count();
}

//**************************************************** */

NonSpell1_2::NonSpell1_2(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),shoot_clock_(72),bulletconfig_(resource->app_.red_light_bulletTexture_)
{
    bulletnum_=90;
    bullet_direction_={0,1};
    initial();
    setBulletConfig();
}

void NonSpell1_2::initial()
{
    for(int i=1;i<=bulletnum_;i++)
    {
        direction_list_.push_back(bullet_direction_);
        bullet_direction_=roundwithCenter({0,0},bullet_direction_,360/bulletnum_);
    }
    bullet_direction_={0,1};
}

void NonSpell1_2::setBulletConfig()
{
    bulletconfig_.r_=3;
    bulletconfig_.v_=4;
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
}

void NonSpell1_2::update()
{
    if(shoot_clock_.get_condition())
    {
        shoot_clock_.reset();
        sf::Vector2f center=entity_->getPosition();
        for(int i=1;i<=bulletnum_;i++)
        {
            bulletconfig_.direction_=direction_list_[i-1];
            if(i%2)
            {
                bulletconfig_.spawn_point_=center+(float)10*direction_list_[i-1];
                resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
                bulletconfig_.spawn_point_=center+(float)70*direction_list_[i-1];
                resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
            }
            else
            {
                bulletconfig_.spawn_point_=center+(float)40*direction_list_[i-1];
                resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
            }
            //std::cout<<direction_list_[i-1].x<<" "<<direction_list_[i-1].y<<std::endl;
        }
    }
    shoot_clock_.count();
}

//******************************* */
NonSpell1::NonSpell1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    entity_(entity),Behavior(resource,yellowpage),spell1(entity,resource,yellowpage),spell2(entity,resource,yellowpage)
{
    ;
}

void NonSpell1::update()
{
    spell1.update();
    spell2.update();
}