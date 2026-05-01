#include "behaviors/behaviors/SuddenRain.h"
#include "mathematics/mathematics.h"
#include "core/application.h"
#include "entities/Entity.h"
#include "manager/BulletManager.h"

SuddenRain1::SuddenRain1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),bulletconfig_(resource->app_.bulletsheetTexture_),shoot_clock_(3)
{
    gap_=67;
    shoot_position_={50,50};
    shoot_move_direction_={1,0};

    shoot_direction_list_.resize(5);
    angle_list_.resize(5);
    for(int i=1;i<=5;i++)
    {
        shoot_direction_list_[i-1]=roundwithCenter({0,0},{0,-1},72*(i-1));
        angle_list_[i-1]=72*(i-1);
    }

    setBulletConfig();
}

void SuddenRain1::setBulletConfig()
{
    bulletconfig_.r_=3;
    //bulletconfig_.v_=0.3;
    //bulletconfig_.v2_=5.5;
    //bulletconfig_.a_=0.05;
    bulletconfig_.direction2_={0,1};
    bulletconfig_.bulletsize_=Small;
    bulletconfig_.bullet_index_={9,5};
    bulletconfig_.bulletclass_=GravityBullet;
    bulletconfig_.bulletbehavior_=BulletBehavior::Direct;
}

void SuddenRain1::update()
{
    if(shoot_clock_.get_condition())
    {
        shoot_clock_.reset();
        
        bulletconfig_.spawn_point_={shoot_position_.x,shoot_position_.y+getRandomNum(0,50)};
        for(int i=1;i<=5;i++)
        {
            bulletconfig_.v_=3+getRandomNum(0,1);
            bulletconfig_.v2_=5.5+getRandomNum(0,1);
            bulletconfig_.a_=0.05+getRandomNum(-0.05,0.05);

            float error=getRandomNum(-5,5);
            bulletconfig_.direction_=roundwithCenter({0,0},shoot_direction_list_[i-1],error);
            bulletconfig_.angle_=angle_list_[i-1]+error;
            
            resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
        }

        shoot_position_=shoot_position_+(gap_+getRandomNum(-10,10))*shoot_move_direction_;
        if(shoot_position_.x>=660)
        {
            shoot_move_direction_={-1,0};
        }
        if(shoot_position_.x<=60)
        {
            shoot_move_direction_={1,0};
        }
    }
    shoot_clock_.count();
}

//*************************************************************************** */

SuddenRain2::SuddenRain2(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),bulletconfig_(resource->app_.bulletsheetTexture2_),shoot_clock_(90),shoot_clock2_(4),bullet_num_clock_(6)
{
    direction_num_=8;
    error_=getRandomNum(0,60);
    bullet_num_clock_.reset();
    shoot_rotate_angle_=5;
    shoot_direction_list_.resize(direction_num_);
    for(int i=1;i<=direction_num_;i++)
    {
        shoot_direction_list_[i-1]=roundwithCenter({0,0},{0,1},(360/direction_num_)*(i-1));
    }

    setBulletConfig();
}

void SuddenRain2::setBulletConfig()
{
    bulletconfig_.r_=3;
    bulletconfig_.v_=9;
    bulletconfig_.rotate_angle_=1.4;
    bulletconfig_.rotate_angle2_=120;
    bulletconfig_.a_=0.5;
    bulletconfig_.bulletsize_=Big;
    bulletconfig_.bullet_index_={6,2};
    bulletconfig_.bulletclass_=RotateBullet1;
    bulletconfig_.bulletbehavior_=Fix;
}

void SuddenRain2::update()
{
    if(shoot_clock_.get_condition())
    {
        if(bullet_num_clock_.get_condition())
        {
            bullet_num_clock_.reset();
            shoot_clock_.reset();
            bulletconfig_.rotate_angle_=-bulletconfig_.rotate_angle_;
            error_=getRandomNum(0,60);
        }
        else
        {
            if(shoot_clock2_.get_condition())
            {
                shoot_clock2_.reset();

                bulletconfig_.spawn_point_=entity_->getPosition();
                for(int i=1;i<=direction_num_;i++)
                {
                    bulletconfig_.direction_=roundwithCenter({0,0},shoot_direction_list_[i-1],error_);
                    resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
                }

                bullet_num_clock_.count();
            }
        }
    }
    shoot_clock2_.count();
    shoot_clock_.count();
}

/****************************************************************************** */

SuddenRain::SuddenRain(Entity* entity,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),rain_(entity,resource,yellowpage),wind_(entity,resource,yellowpage)
{
    ;
}

void SuddenRain::update()
{
    rain_.update();
    wind_.update();
}