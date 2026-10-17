#include "behaviors/behaviors/DivideSea.h"
#include "core/Application.h"
#include "batch/Batch.h"
#include "manager/BatchManager.h"
#include "manager/BulletManager.h"
#include "mathematics/mathematics.h"

DivideSea1::DivideSea1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),
    bulletconfig_(resource->app_.bulletsheetTexture2_),
    create_batch_(false),close_batch_(false),
    bullet_num_(12),
    shoot_clock_(5),line_(1)
{
    setBatchConfig();
    setBulletConfig();
}

void DivideSea1::setBulletConfig()
{
    bulletconfig_.r_=15;
    bulletconfig_.bulletclass_=BulletClasses::VoidUpdate;
    bulletconfig_.bulletbehavior_=BulletBehavior::Fix;
    bulletconfig_.bulletsize_=BulletSize::Large;
    bulletconfig_.bullet_index_={2,1};

    bulletconfig_.specialized_update_func_=UpdateSpecialLibrary::divide_sea1;

    bulletconfig_.v_=0.08;
    bulletconfig_.v2_=0;
    bulletconfig_.a_=0.1;
}

void DivideSea1::setBatchConfig()
{
    batchconfig_.target_time_=120;
    batchconfig_.target_time2_=60;
    batchconfig_.target_time3_=90;
    batchconfig_.update_func_=
    [](Batch* batch)
    {
        if(batch->clock_.get_condition())
        {
            switch (batch->phase_)
            {
            case 1:
                {
                    batch->clock_.reset();
                    batch->clock_.set_target(batch->batchconfig_.target_time2_);
                    break;
                }

            case 2:
                {
                    batch->clock_.reset();
                    batch->clock_.set_target(batch->batchconfig_.target_time3_);
                    break;
                }

            case 3:
                {
                    batch->clock_.reset();
                    batch->clock_.set_target(9999);
                    break;
                }
            
            default:
                break;
            }
            batch->phase_++;
        }
        batch->clock_.count();
    };
}

void DivideSea1::update()
{
    int bullet_num=bullet_num_;
    float gap=((float)770)/bullet_num;
    int line_num=(900/gap)+1;

    if(!create_batch_)
    {
        batch_=resource_->batchmanager_.add_process(&batchconfig_);
        batch_->bundle_config(&bulletconfig_);
        create_batch_=true;
    }
    if(line_<=line_num)
    {
        if(shoot_clock_.get_condition())
        {
            shoot_clock_.reset();
            float target_y=gap/2+((float)(line_-1))*gap;
            bulletconfig_.clock1_.set_target(target_y/20);
            for(int i=1;i<=bullet_num;i++)
            {
                float target_x=gap/2+((float)(i-1))*gap;
                bulletconfig_.spawn_point_={target_x,0};
                bulletconfig_.target_point_={target_x,target_y};
                if(target_x<=385)
                {
                    bulletconfig_.target_point2_={target_x*(float)0.95,target_y};
                    bulletconfig_.target_point3_={target_x*(float)0.5,target_y};
                }
                else
                {
                    bulletconfig_.target_point2_={770-(770-target_x)*(float)0.95,target_y};
                    bulletconfig_.target_point3_={770-(770-target_x)*(float)0.5,target_y};
                }
                resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
            }
            line_++;
        }
        shoot_clock_.count();
    }
    else
    {
        if(!close_batch_)
        {
            batch_->set_add_finished();
            close_batch_=true;
        }
    }
}

/************************************************ */

DivideSea2::DivideSea2(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),
    bulletconfig_(resource->app_.bulletsheetTexture2_),
    shoot_clock_(1),
    current_frame_(0)
{
    setBulletConfig();
}

void DivideSea2::setBulletConfig()
{
    bulletconfig_.r_=15;
    bulletconfig_.bulletclass_=BulletClasses::VoidUpdate;
    bulletconfig_.bulletbehavior_=BulletBehavior::Fix;
    bulletconfig_.bulletsize_=BulletSize::Large;
    bulletconfig_.bullet_index_={2,1};
    bulletconfig_.spawn_point_.x=-10;

    bulletconfig_.specialized_update_func_=UpdateSpecialLibrary::divide_sea2;
    
    bulletconfig_.v_=0.12;
    bulletconfig_.v2_=0;
    bulletconfig_.a_=0.1;
}

void DivideSea2::update()
{
    if(shoot_clock_.get_condition())
    {
        float percentage=((float)current_frame_)/240;
        if(percentage>1)
        {
            percentage=1;
        }

        for(int i=1;i<=2;i++)
        {
            shoot_clock_.reset();
            float y=getRandomNum(0,900);
            bulletconfig_.spawn_point_.y=y;
            
            float target_x=0.5*385+percentage*100*sin(2*std::numbers::pi*(y/900+((float)current_frame_)/420));
            bulletconfig_.target_point_={target_x,y};
            resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
        }
    }
    shoot_clock_.count();
    current_frame_++;
}

/*************************************************************************** */

DivideSea3::DivideSea3(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),
    bulletconfig_(resource->app_.bulletsheetTexture2_),
    shoot_clock_(1),
    current_frame_(0)
{
    setBulletConfig();
}

void DivideSea3::setBulletConfig()
{
    bulletconfig_.r_=15;
    bulletconfig_.bulletclass_=BulletClasses::VoidUpdate;
    bulletconfig_.bulletbehavior_=BulletBehavior::Fix;
    bulletconfig_.bulletsize_=BulletSize::Large;
    bulletconfig_.bullet_index_={2,1};
    bulletconfig_.spawn_point_.x=780;

    bulletconfig_.specialized_update_func_=UpdateSpecialLibrary::divide_sea2;
    
    bulletconfig_.v_=0.12;
    bulletconfig_.v2_=0;
    bulletconfig_.a_=0.1;
}

void DivideSea3::update()
{
    if(shoot_clock_.get_condition())
    {
        shoot_clock_.reset();
        float percentage=((float)current_frame_)/240;
        if(percentage>1)
        {
            percentage=1;
        }

        for(int i=1;i<=2;i++)
        {
            float y=getRandomNum(0,900);
            bulletconfig_.spawn_point_.y=y;
            
            float target_x=770-0.5*385+percentage*100*sin(2*std::numbers::pi*(y/900+((float)current_frame_)/420));
            bulletconfig_.target_point_={target_x,y};
            resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
        }
    }
    shoot_clock_.count();
    current_frame_++;
}

/****************************************************** */

DivideSea4::DivideSea4(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),
    bulletconfig_(resource->app_.bulletsheetTexture_),
    shoot_clock_(3)
{
    setBulletConfig();
}

void DivideSea4::setBulletConfig()
{
    bulletconfig_.r_=3;
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
    bulletconfig_.bulletbehavior_=BulletBehavior::Direct;
    bulletconfig_.bulletsize_=BulletSize::Small;
    bulletconfig_.bullet_index_={10,7};
  
    //bulletconfig_.v_=4;
}

void DivideSea4::update()
{
    if(shoot_clock_.get_condition())
    {
        shoot_clock_.reset();
        bulletconfig_.v_=getRandomNum(5,8);
        float x=entity_->getPosition().x+getRandomNum(-80,80);
        float y=entity_->getPosition().y+getRandomNum(-100,0);
        bulletconfig_.spawn_point_={x,y};
        sf::Vector2f direction=yellowpage_->player_->getPosition()-entity_->getPosition();
        bulletconfig_.angle_=RadTransToDegree(atan2f(direction.y,direction.x))-90;
        bulletconfig_.direction_=normalize(direction);
        resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
    }
    shoot_clock_.count();
}

/********************************************************** */

DivideSea::DivideSea(Entity* entity,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),
    dividesea1_(entity,resource,yellowpage),
    dividesea2_(entity,resource,yellowpage),
    dividesea3_(entity,resource,yellowpage),
    dividesea4_(entity,resource,yellowpage),
    delay_(222)
{
    delay_.reset();
}

void DivideSea::update()
{
    dividesea1_.update();
    if(delay_.get_condition())
    {
        dividesea2_.update();
        dividesea3_.update();
        dividesea4_.update();
    }
    delay_.count();
}