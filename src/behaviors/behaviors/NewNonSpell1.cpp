#include "behaviors/behaviors/NewNonSpell1.h"
#include "packages/BulletConfig.h"
#include "mathematics/mathematics.h"
#include "core/application.h"
#include "entities/Entity.h"
#include "manager/BulletManager.h"

NewNonSpell1::NewNonSpell1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),shoot_clock_(20),start_clock_(30),bulletconfig_(resource->app_.bulletsheetTexture_)
{
    start_clock_.reset();
    bullet_num_=15;
    bullet_direction_={0,1};
    gap_=2;
    left_right_.push_back(1);
    left_right_.push_back(0);

    setBulletConfig();
}

void NewNonSpell1::setBulletConfig()
{
    bulletconfig_.r_=5;
    bulletconfig_.bulletbehavior_=Fix;
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
    bulletconfig_.bulletsize_=Small;
    bulletconfig_.bullet_index_={7,4};
}

void NewNonSpell1::update()
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
                    resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
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