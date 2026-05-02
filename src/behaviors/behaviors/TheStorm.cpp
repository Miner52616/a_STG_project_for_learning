#include "behaviors/behaviors/TheStorm.h"
#include "packages/BulletConfig.h"
#include "mathematics/mathematics.h"
#include "core/application.h"
#include "entities/Entity.h"
#include "manager/BulletManager.h"

TheStorm1::TheStorm1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),bulletconfig_(resource->app_.bulletsheetTexture_),shoot_clock_(720),shoot_clock2_(2),shoot_num_clock_(30)
{
    shoot_num_clock_.reset();
    translation_={-100,0};
    initial_delay_time_=40;
    delay_time_=initial_angle_;
    initial_radius_=roundwithCenter({0,0},{0,50},135);
    radius_=initial_radius_;
    direction_=normalize(roundwithCenter({0,0},radius_,-90));
    initial_angle_=-2;
    rotate_angle_=initial_angle_;

    setBulletConfig();
}

void TheStorm1::setBulletConfig()
{
    bulletconfig_.r_=3;
    bulletconfig_.v2_=1.5;
    bulletconfig_.angle2_=0;
    bulletconfig_.bullet_num_=5;
    //bulletconfig_.v_=0.5;
    //bulletconfig_.a_=0.05;
    //bulletconfig_.v2_=4;
    bulletconfig_.clock1_.set_target(initial_delay_time_);
    bulletconfig_.clock1_.reset();
    bulletconfig_.bulletsize_=Small;
    bulletconfig_.bullet_index_={11,3};
    bulletconfig_.bullet_index2_={11,5};
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
    bulletconfig_.bulletbehavior_=BulletBehavior::Fix;
}

void TheStorm1::update()
{
    if(shoot_clock_.get_condition())
    {
        if((shoot_num_clock_.get_condition()))
        {
            shoot_clock_.reset();

            shoot_num_clock_.reset();
            rotate_angle_=initial_angle_;
            radius_=roundwithCenter({0,0},initial_radius_,getRandomNum(-5,5));
            direction_=normalize(roundwithCenter({0,0},radius_,-90));
            bulletconfig_.clock1_.set_target(initial_delay_time_);
        }
        else
        {
            if(shoot_clock2_.get_condition())
            {
                shoot_clock2_.reset();

                sf::Vector2f position=entity_->getPosition();
                bulletconfig_.spawn_point_=position+translation_+radius_;
                bulletconfig_.direction_=direction_;
                bulletconfig_.angle2_=getRandomNum(0,72);
                for(int i=1;i<=25;i++)
                {
                    if(i==1)
                    {
                        bulletconfig_.bulletclass_=Behavior_DirectBullet1;
                    }
                    else
                    {
                        bulletconfig_.bulletclass_=DirectBullet1;
                    }
                    bulletconfig_.v_=(float)3+(float)i*4/25;
                    resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
                }

                bulletconfig_.clock1_.set_target(bulletconfig_.clock1_.get_target()+3);
                radius_=roundwithCenter({0,0},radius_,rotate_angle_);
                direction_=roundwithCenter({0,0},direction_,rotate_angle_);
                rotate_angle_=rotate_angle_+getRandomNum(-0.4,-0.2);
                
                shoot_num_clock_.count();
            }
        }
    }
    shoot_clock_.count();
    shoot_clock2_.count();
}

/********************************************************* */

TheStorm2::TheStorm2(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),bulletconfig_(resource->app_.bulletsheetTexture_),shoot_clock_(720),shoot_clock2_(2),shoot_num_clock_(30),start_clock_(180)
{
    start_clock_.reset();
    shoot_num_clock_.reset();
    translation_={100,0};
    initial_delay_time_=40;
    delay_time_=initial_angle_;
    initial_radius_=roundwithCenter({0,0},{0,50},-135);
    radius_=initial_radius_;
    direction_=normalize(roundwithCenter({0,0},radius_,90));
    initial_angle_=2;
    rotate_angle_=initial_angle_;

    setBulletConfig();
}

void TheStorm2::setBulletConfig()
{
    bulletconfig_.r_=3;
    bulletconfig_.v2_=1.5;
    bulletconfig_.angle2_=0;
    bulletconfig_.bullet_num_=5;
    //bulletconfig_.v_=0.5;
    //bulletconfig_.a_=0.05;
    //bulletconfig_.v2_=4;
    bulletconfig_.clock1_.set_target(initial_delay_time_);
    bulletconfig_.clock1_.reset();
    bulletconfig_.bulletsize_=Small;
    bulletconfig_.bullet_index_={11,3};
    bulletconfig_.bullet_index2_={11,5};
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
    bulletconfig_.bulletbehavior_=BulletBehavior::Fix;
}

void TheStorm2::update()
{
    if(start_clock_.get_condition())
    {
        if(shoot_clock_.get_condition())
        {
            if((shoot_num_clock_.get_condition()))
            {
                shoot_clock_.reset();

                shoot_num_clock_.reset();
                rotate_angle_=initial_angle_;
                radius_=roundwithCenter({0,0},initial_radius_,getRandomNum(-5,5));
                direction_=normalize(roundwithCenter({0,0},radius_,90));
                bulletconfig_.clock1_.set_target(initial_delay_time_);
            }
            else
            {
                if(shoot_clock2_.get_condition())
                {
                    shoot_clock2_.reset();

                    sf::Vector2f position=entity_->getPosition();
                    bulletconfig_.spawn_point_=position+translation_+radius_;
                    bulletconfig_.direction_=direction_;
                    bulletconfig_.angle2_=getRandomNum(0,72);
                    for(int i=1;i<=25;i++)
                    {
                        if(i==1)
                        {
                            bulletconfig_.bulletclass_=Behavior_DirectBullet1;
                        }
                        else
                        {
                            bulletconfig_.bulletclass_=DirectBullet1;
                        }
                        bulletconfig_.v_=(float)3+(float)i*4/25;
                        resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
                    }

                    bulletconfig_.clock1_.set_target(bulletconfig_.clock1_.get_target()+3);
                    radius_=roundwithCenter({0,0},radius_,rotate_angle_);
                    direction_=roundwithCenter({0,0},direction_,rotate_angle_);
                    rotate_angle_=rotate_angle_+getRandomNum(0.2,0.4);
                    
                    shoot_num_clock_.count();
                }
            }
        }
    }
    start_clock_.count();
    shoot_clock_.count();
    shoot_clock2_.count();
}

/********************************************* */

TheStorm3::TheStorm3(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),bulletconfig_(resource->app_.bulletsheetTexture_),shoot_clock_(580),shoot_clock2_(4),shoot_num_clock_(50),start_clock_(360)
{
    start_clock_.reset();
    shoot_num_clock_.reset();
    initial_translation_={100,-50};
    translation_=initial_translation_;
    initial_delay_time_=40;
    delay_time_=initial_angle_;
    initial_radius_=roundwithCenter({0,0},{0,50},135);
    radius_=initial_radius_;
    direction_=normalize(roundwithCenter({0,0},radius_,-90));
    initial_angle_=-4;
    rotate_angle_=initial_angle_;

    setBulletConfig();
}

void TheStorm3::setBulletConfig()
{
    bulletconfig_.r_=3;
    //bulletconfig_.v_=0.5;
    //bulletconfig_.a_=0.05;
    //bulletconfig_.v2_=4;
    bulletconfig_.clock1_.set_target(initial_delay_time_);
    bulletconfig_.clock1_.reset();
    bulletconfig_.bulletsize_=Small;
    bulletconfig_.bullet_index_={11,3};
    bulletconfig_.bullet_index2_={11,5};
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
    bulletconfig_.bulletbehavior_=BulletBehavior::Fix;
}

void TheStorm3::update()
{
    if(start_clock_.get_condition())
    {
        if(shoot_clock_.get_condition())
        {
            if((shoot_num_clock_.get_condition()))
            {
                shoot_clock_.reset();

                shoot_num_clock_.reset();
                rotate_angle_=initial_angle_;
                radius_=roundwithCenter({0,0},initial_radius_,getRandomNum(-5,5));
                direction_=normalize(roundwithCenter({0,0},radius_,-90));
                bulletconfig_.clock1_.set_target(initial_delay_time_);
                translation_=initial_translation_;
            }
            else
            {
                if(shoot_clock2_.get_condition())
                {
                    shoot_clock2_.reset();

                    sf::Vector2f position=entity_->getPosition();
                    bulletconfig_.spawn_point_=position+translation_+radius_;
                    bulletconfig_.direction_=direction_;
                    bulletconfig_.angle2_=getRandomNum(0,72);
                    for(int i=1;i<=15;i++)
                    {
                        bulletconfig_.v_=(float)2+(float)i*3.5/15;
                        resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
                    }

                    bulletconfig_.clock1_.set_target(bulletconfig_.clock1_.get_target()+3);
                    radius_=roundwithCenter({0,0},radius_,rotate_angle_);
                    direction_=roundwithCenter({0,0},direction_,rotate_angle_);
                    rotate_angle_=rotate_angle_+getRandomNum(-0.1,0);
                    translation_=translation_+sf::Vector2f{1,2};

                    shoot_num_clock_.count();
                }
            }
        }
    }
    start_clock_.count();
    shoot_clock_.count();
    shoot_clock2_.count();
}
//**************************************************** */

TheStorm4::TheStorm4(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),bulletconfig_(resource->app_.bulletsheetTexture_),shoot_clock_(580),shoot_clock2_(4),shoot_num_clock_(50),start_clock_(360)
{
    start_clock_.reset();
    shoot_num_clock_.reset();
    initial_translation_={-100,-50};
    translation_=initial_translation_;
    initial_delay_time_=40;
    delay_time_=initial_angle_;
    initial_radius_=roundwithCenter({0,0},{0,50},-135);
    radius_=initial_radius_;
    direction_=normalize(roundwithCenter({0,0},radius_,90));
    initial_angle_=4;
    rotate_angle_=initial_angle_;

    setBulletConfig();
}

void TheStorm4::setBulletConfig()
{
    bulletconfig_.r_=3;
    //bulletconfig_.v_=0.5;
    //bulletconfig_.a_=0.05;
    //bulletconfig_.v2_=4;
    bulletconfig_.clock1_.set_target(initial_delay_time_);
    bulletconfig_.clock1_.reset();
    bulletconfig_.bulletsize_=Small;
    bulletconfig_.bullet_index_={11,3};
    bulletconfig_.bullet_index2_={11,5};
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
    bulletconfig_.bulletbehavior_=BulletBehavior::Fix;
}

void TheStorm4::update()
{
    if(start_clock_.get_condition())
    {
        if(shoot_clock_.get_condition())
        {
            if((shoot_num_clock_.get_condition()))
            {
                shoot_clock_.reset();

                shoot_num_clock_.reset();
                rotate_angle_=initial_angle_;
                radius_=roundwithCenter({0,0},initial_radius_,getRandomNum(-5,5));
                direction_=normalize(roundwithCenter({0,0},radius_,90));
                bulletconfig_.clock1_.set_target(initial_delay_time_);
                translation_=initial_translation_;
            }
            else
            {
                if(shoot_clock2_.get_condition())
                {
                    shoot_clock2_.reset();

                    sf::Vector2f position=entity_->getPosition();
                    bulletconfig_.spawn_point_=position+translation_+radius_;
                    bulletconfig_.direction_=direction_;
                    bulletconfig_.angle2_=getRandomNum(0,72);
                    for(int i=1;i<=15;i++)
                    {
                        bulletconfig_.v_=(float)2+(float)i*3.5/15;
                        resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
                    }

                    bulletconfig_.clock1_.set_target(bulletconfig_.clock1_.get_target()+3);
                    radius_=roundwithCenter({0,0},radius_,rotate_angle_);
                    direction_=roundwithCenter({0,0},direction_,rotate_angle_);
                    rotate_angle_=rotate_angle_+getRandomNum(0,0.1);
                    translation_=translation_+sf::Vector2f{-1,2};

                    shoot_num_clock_.count();
                }
            }
        }
    }
    start_clock_.count();
    shoot_clock_.count();
    shoot_clock2_.count();
}

/********************************************************** */

TheStorm::TheStorm(Entity* entity,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),storm1_(entity,resource,yellowpage),storm2_(entity,resource,yellowpage),storm3_(entity,resource,yellowpage),storm4_(entity,resource,yellowpage)
{
    ;
}

void TheStorm::update()
{
    storm1_.update();
    storm2_.update();
    storm3_.update();
    storm4_.update();
}