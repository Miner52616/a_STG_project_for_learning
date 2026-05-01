#include "behaviors/behaviors/TheStorm.h"
#include "packages/BulletConfig.h"
#include "mathematics/mathematics.h"
#include "core/application.h"
#include "entities/Entity.h"
#include "manager/BulletManager.h"

TheStorm1::TheStorm1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),bulletconfig_(resource->app_.bulletsheetTexture_),bulletconfig2_(resource->app_.bulletsheetTexture_),shoot_clock_(180),shoot_clock2_(2),shoot_clock3_1_(48),shoot_clock3_2_(3),shoot_num_clock_(60),shoot_num_clock2_(60)
{
    shoot_clock3_1_.reset();
    shoot_num_clock_.reset();
    shoot_num_clock2_.reset();
    translation_={-100,0};
    initial_radius_=roundwithCenter({0,0},{0,50},135);
    radius_=initial_radius_;
    radius2_=initial_radius_;
    direction_=normalize(roundwithCenter({0,0},radius_,-90));
    direction2_=normalize(roundwithCenter({0,0},radius2_,-90));
    initial_angle_=-2;
    rotate_angle_=initial_angle_;
    rotate_angle2_=initial_angle_;

    shoot_direction_list_.resize(5);
    angle_list_.resize(5);
    for(int i=1;i<=5;i++)
    {
        shoot_direction_list_[i-1]=roundwithCenter({0,0},{0,-1},72*(i-1));
        angle_list_[i-1]=72*(i-1);
    }

    setBulletConfig();
}

void TheStorm1::setBulletConfig()
{
    bulletconfig_.r_=3;
    //bulletconfig_.v_=0.5;
    //bulletconfig_.a_=0.05;
    //bulletconfig_.v2_=4;
    //bulletconfig_.clock1_.set_target(30);
    bulletconfig_.bulletsize_=Small;
    bulletconfig_.bullet_index_={11,3};
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
    bulletconfig_.bulletbehavior_=BulletBehavior::Fix;

    bulletconfig2_.r_=3;
    bulletconfig2_.v_=0;
    bulletconfig2_.v2_=1.5;
    bulletconfig2_.a_=0.05;
    //bulletconfig2_.clock1_.set_target(24);
    bulletconfig2_.bulletsize_=Small;
    bulletconfig2_.bullet_index_={11,5};
    bulletconfig2_.bulletclass_=BulletClasses::DirectBullet2;
    bulletconfig2_.bulletbehavior_=BulletBehavior::Direct;
}

void TheStorm1::update()
{
    if(shoot_clock_.get_condition())
    {
        if((shoot_num_clock_.get_condition())&&(shoot_num_clock2_.get_condition()))
        {
            shoot_clock_.reset();
            shoot_clock3_1_.reset();

            shoot_num_clock_.reset();
            rotate_angle_=initial_angle_;
            radius_=roundwithCenter({0,0},initial_radius_,getRandomNum(-5,5));
            direction_=normalize(roundwithCenter({0,0},radius_,-90));

            shoot_num_clock2_.reset();
            rotate_angle2_=initial_angle_;
            radius2_=radius_;
            direction2_=direction_;
        }
        else
        {
            if(shoot_clock2_.get_condition())
            {
                shoot_clock2_.reset();

                sf::Vector2f position=entity_->getPosition();
                bulletconfig_.spawn_point_=position+translation_+radius_;
                bulletconfig_.direction_=direction_;
                for(int i=1;i<=25;i++)
                {
                    bulletconfig_.v_=(float)3+(float)i*4/25;
                    resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
                }

                radius_=roundwithCenter({0,0},radius_,rotate_angle_);
                direction_=roundwithCenter({0,0},direction_,rotate_angle_);
                rotate_angle_=rotate_angle_-0.3;
                
                shoot_num_clock_.count();
            }

            if(shoot_clock3_1_.get_condition())
            {
                if(shoot_clock3_2_.get_condition())
                {
                    shoot_clock3_2_.reset();

                    sf::Vector2f position=entity_->getPosition();
                    position=position+translation_+radius2_;
                    for(int i=1;i<=3;i++)
                    {
                        bulletconfig2_.clock1_.set_target(24+(i-1)*8);
                        bulletconfig2_.spawn_point_=position+(float)i*300*direction2_;
                        float error=getRandomNum(0,72);
                        for(int j=1;j<=5;j++)
                        {
                            bulletconfig2_.direction_=roundwithCenter({0,0},shoot_direction_list_[j-1],error);
                            bulletconfig2_.angle_=angle_list_[j-1]-90+error;
                            resource_->bulletmanager_.add_process(&bulletconfig2_,&effectconfig_);
                        }

                        radius2_=roundwithCenter({0,0},radius2_,rotate_angle_);
                        direction2_=roundwithCenter({0,0},direction2_,rotate_angle_);
                        rotate_angle2_=rotate_angle2_-0.3;
                    }

                    shoot_num_clock2_.count();
                }
            }
        }
        shoot_clock3_1_.count();
    }
    shoot_clock_.count();
    shoot_clock2_.count();
    shoot_clock3_2_.count();
}