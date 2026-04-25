#include "behaviors/behaviors/NonSpell2.h"
#include "packages/BulletConfig.h"
#include "mathematics/mathematics.h"
#include "core/application.h"
#include "entities/Entity.h"
#include "manager/BulletManager.h"

NonSpell2_1::NonSpell2_1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),entity_(entity),shoot_clock_(90),start_clock_(300),bulletconfig_(resource->app_.deep_blue_light_bulletTexture_)
{
    start_clock_.reset();
    bullet_num_=13;
    bullet_direction_={0,1};
    gap_=20;

    setBulletConfig();
}

void NonSpell2_1::setBulletConfig()
{
    bulletconfig_.r_=3;
    bulletconfig_.v_=0.5;
    bulletconfig_.a_=0.05;
    bulletconfig_.v2_=4;
    bulletconfig_.clock1_.set_target(30);
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet2;
    bulletconfig_.bulletbehavior_=BulletBehavior::Rotate;
}

void NonSpell2_1::update()
{
    if(start_clock_.get_condition())
    {
        if(shoot_clock_.get_condition())
        {
            shoot_clock_.reset();

            start_position_={getRandomNum(200,570),getRandomNum(100,300)};
            set_direction_=roundwithCenter({0,0},{0,1},getRandomNum(0,360));
            bullet_direction_=roundwithCenter({0,0},set_direction_,-18);
            for(int j=1;j<=5;j++)
            {
                for(int i=1;i<=bullet_num_;i++)
                {
                    bulletconfig_.spawn_point_=start_position_+(i-1)*gap_*set_direction_;
                    bulletconfig_.direction_=bullet_direction_;
                    resource_->bulletmanager_.add_process(&bulletconfig_);
                    bullet_direction_=roundwithCenter({0,0},bullet_direction_,3);
                }
                start_position_=start_position_+(float)(bullet_num_-1)*gap_*set_direction_;
                set_direction_=roundwithCenter({0,0},set_direction_,144);
                bullet_direction_=roundwithCenter({0,0},set_direction_,-18);
            }
        }
        shoot_clock_.count();
    }
    else
    {
        start_clock_.count();
    }
}

/*********************************************************** */

NonSpell2_2::NonSpell2_2(Entity* entity,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),entity_(entity),shoot_clock_(1),shoot_num_(75),shoot_num2_(15),bulletconfig_(resource->app_.bulletsheetTexture_)
{
    shoot_num_.reset();
    shoot_num2_.reset();
    get_center=false;
    bullet_num_=13;
    group_num_=10;
    gap_=15;
    rotate_degree_=3;
    shoot_num2_.set_target(bullet_num_);
    shoot_num_.set_target(5*bullet_num_);
    delaytime_=90;
    bullet_direction_={0,1};
    bullet_direction2_={0,1};
    direction_list.resize(group_num_);
    for(int i=1;i<=group_num_;i++)
    {
        direction_list[i-1]=roundwithCenter({0,0},{0,1},i*360/group_num_);
    }

    start_position_={385,200};
    set_direction_=roundwithCenter({0,0},{0,1},18);
    bullet_direction_=roundwithCenter({0,0},set_direction_,-18);
    bullet_direction2_=roundwithCenter({0,0},set_direction_,-162+(-rotate_degree_*(bullet_num_-1)));

    setBulletConfig();
}

void NonSpell2_2::setBulletConfig()
{
    bulletconfig_.r_=3;
    bulletconfig_.v_=0.5;
    bulletconfig_.a_=0.05;
    bulletconfig_.v2_=4;
    bulletconfig_.a2_=-0.08;
    bulletconfig_.v3_=6.4;
    bulletconfig_.direction2_={0,1};
    bulletconfig_.clock1_.set_target(30);
    bulletconfig_.clock2_.set_target(80);
    bulletconfig_.bullet_index_={6,8};
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet3;
    bulletconfig_.bulletbehavior_=BulletBehavior::Rotate;
}

void NonSpell2_2::reset()
{
    shoot_num_.reset();
    shoot_num2_.reset();
    get_center=false;

    shoot_num2_.set_target(bullet_num_);
    shoot_num_.set_target(5*bullet_num_);
    delaytime_=90;
    bullet_direction_={0,1};
    bullet_direction2_={0,1};
    direction_list.resize(group_num_);
    for(int i=1;i<=group_num_;i++)
    {
        direction_list[i-1]=roundwithCenter({0,0},{0,1},i*360/group_num_);
    }

    start_position_={385,200};
    set_direction_=roundwithCenter({0,0},{0,1},18);
    bullet_direction_=roundwithCenter({0,0},set_direction_,-18);
    bullet_direction2_=roundwithCenter({0,0},set_direction_,-162+(-rotate_degree_*(bullet_num_-1)));

    setBulletConfig();
}

void NonSpell2_2::update()
{
    if(!shoot_num_.get_condition())
    {
        if(!get_center)
        {
            center_=entity_->getPosition();
            sf::Vector2f direction=roundwithCenter({0,0},{1,0},-54);
            start_position_=center_+(float)((gap_*(bullet_num_-1)/2)/0.95106)*direction;

            get_center=true;
        }

        if(shoot_clock_.get_condition())
        {
            if(shoot_num2_.get_condition())
            {
                shoot_num2_.reset();

                set_direction_=roundwithCenter({0,0},set_direction_,144);
                bullet_direction_=roundwithCenter({0,0},set_direction_,-18);
                bullet_direction2_=roundwithCenter({0,0},set_direction_,-162+(-rotate_degree_*(bullet_num_-1)));
            }

            shoot_clock_.reset();
            bulletconfig_.spawn_point_=start_position_;

            bulletconfig_.clock3_.set_target(delaytime_);
            for(int i=1;i<=group_num_/2;i++)
            {
                bulletconfig_.direction2_=direction_list[2*i-1];
                bulletconfig_.direction_=bullet_direction_;
                resource_->bulletmanager_.add_process(&bulletconfig_);
            }
            for(int i=1;i<=group_num_/2;i++)
            {
                bulletconfig_.direction2_=direction_list[2*i-2];
                bulletconfig_.direction_=bullet_direction2_;
                resource_->bulletmanager_.add_process(&bulletconfig_);
            }

            //resource_->bulletmanager_.add_process(&bulletconfig_);

            bullet_direction_=roundwithCenter({0,0},bullet_direction_,rotate_degree_);
            bullet_direction2_=roundwithCenter({0,0},bullet_direction2_,rotate_degree_);
            start_position_=start_position_+gap_*set_direction_;

            shoot_num_.count();
            shoot_num2_.count();
            delaytime_=delaytime_-shoot_clock_.get_target();
        }
        shoot_clock_.count();
    }
}

NonSpell2_2_1::NonSpell2_2_1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    NonSpell2_2(entity,resource,yellowpage)
{
    bullet_num_=13;
    group_num_=10;
    gap_=15;
    rotate_degree_=3;

    reset();
}

void NonSpell2_2_1::update()
{
    NonSpell2_2::update();
}

NonSpell2_2_2::NonSpell2_2_2(Entity* entity,Resource* resource,YellowPage* yellowpage):
    NonSpell2_2(entity,resource,yellowpage),start_clock_(120)
{
    start_clock_.reset();
    bullet_num_=11;
    group_num_=8;
    gap_=15;
    rotate_degree_=3;

    bulletconfig_.v3_=4;
    bulletconfig_.a2_=-0.05;
    
    reset();
}

void NonSpell2_2_2::update()
{
    if(start_clock_.get_condition())
    {
        NonSpell2_2::update();
    }
    else
    {
        start_clock_.count();
    }
}

//***************************************************************** */

NonSpell2_3::NonSpell2_3(Entity* entity,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),entity_(entity),shoot_clock_(20),start_clock_(300),bulletconfig_(resource->app_.blue_light_bulletTexture_)
{
    start_clock_.reset();
    bullet_num_=15;
    bullet_direction_={0,1};
    gap_=2;
    left_right_.push_back(1);
    left_right_.push_back(0);

    setBulletConfig();
}

void NonSpell2_3::setBulletConfig()
{
    bulletconfig_.r_=3;
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
}

void NonSpell2_3::update()
{
    if(start_clock_.get_condition())
    {
        if(shoot_clock_.get_condition())
        {
            shoot_clock_.reset();

            for(int j=1;j<=3;j++)
            {
                start_position_={getRandomNum(200,570),getRandomNum(100,300)};
                set_direction_=roundwithCenter({0,0},{0,1},getRandomNum(0,360));
                int chiral=get_random_from<int>(left_right_);
                if(chiral)
                {
                    bullet_direction_=roundwithCenter({0,0},set_direction_,-18);
                }
                else
                {
                    bullet_direction_=roundwithCenter({0,0},set_direction_,18);
                }

                for(int i=1;i<=bullet_num_;i++)
                {
                    bulletconfig_.spawn_point_=start_position_+(i-1)*gap_*set_direction_;
                    bulletconfig_.direction_=bullet_direction_;
                    if(chiral)
                    {
                        bulletconfig_.v_=2+i*0.2;
                    }
                    else
                    {
                        bulletconfig_.v_=2+0.2*(bullet_num_+1-i);
                    }
                    resource_->bulletmanager_.add_process(&bulletconfig_);
                    bullet_direction_=roundwithCenter({0,0},bullet_direction_,2);
                }
            }
        }
        shoot_clock_.count();
    }
    else
    {
        start_clock_.count();
    }
}

/************************************************************ */

NonSpell2::NonSpell2(Entity* entity,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),nonspell2_1(entity,resource,yellowpage),nonspell2_2_1(entity,resource,yellowpage),nonspell2_2_2(entity,resource,yellowpage),nonspell2_3(entity,resource,yellowpage)
{
    ;
}

void NonSpell2::update()
{
    nonspell2_1.update();
    nonspell2_2_1.update();
    nonspell2_2_2.update();
    nonspell2_3.update();
}