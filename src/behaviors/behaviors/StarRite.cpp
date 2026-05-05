#include "behaviors/behaviors/StarRite.h"
#include "packages/BulletConfig.h"
#include "mathematics/mathematics.h"
#include "core/application.h"
#include "entities/Entity.h"
#include "manager/BulletManager.h"

StarRite1::StarRite1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),bulletconfig_(resource->app_.bulletsheetTexture_),shoot_clock_(1),shoot_num_clock_(21),phase_clock_(120),trigger_clock_(90),trigger_delay_(150),
    shoot_clock2_(19),shoot2_delay_(28),shoot_times_clock2_(4)
{
    shoot_times_clock2_.reset();
    shoot2_delay_.reset();
    trigger_delay_.reset();
    trigger_clock_.reset();
    phase_clock_.reset();
    shoot_num_clock_.reset();
    phase_=1;
    trigger_=false;
    gap_=11;
    bullet_num_=27;
    center_={0,0};
    shoot_position_=roundwithCenter({0,0},(float)(gap_*(bullet_num_-1)/(2*0.95105))*sf::Vector2f{0,-1},216);
    position_move_direction_=normalize(roundwithCenter({0,0},shoot_position_,162));
    shoot_num_clock_.set_target(bullet_num_);
    center_initialize_=false;

    setBulletConfig();
}

void StarRite1::setBulletConfig()
{
    bulletconfig_.r_=5;
    bulletconfig_.r2_=5;
    //bulletconfig_.v_=0;
    bulletconfig_.a_=0.05;
    bulletconfig_.v2_=1.5;
    bulletconfig_.v3_=3;
    bulletconfig_.a2_=0.05;
    bulletconfig_.clock1_.set_target(30);
    bulletconfig_.bulletclass_=PhaseCenterRotateBullet1;
    bulletconfig_.bulletbehavior_=Rotate;
    bulletconfig_.bulletbehavior2_=Rotate;
    bulletconfig_.bulletsize_=Small;
    bulletconfig_.bullet_index_={7,11};
    bulletconfig_.bullet_index2_={7,11};
    bulletconfig_.random_son_direction_=true;
    bulletconfig_.not_clear_=true;
    
    bulletconfig_.shareconfig_.active_=true;
    bulletconfig_.shareconfig_.phase_=&phase_;
    bulletconfig_.shareconfig_.trigger_=&trigger_;
}

void StarRite1::update()
{
    if(!center_initialize_)
    {
        center_initialize_=true;
        center_=entity_->getPosition();
        bulletconfig_.center_point2_=entity_->getPosition();
    }

    if(!shoot_num_clock_.get_condition())
    {
        if(shoot_clock_.get_condition())
        {
            shoot_num_clock_.count();
            shoot_clock_.reset();
            //bulletconfig_.bulletclass_=PhaseCenterRotateBullet1;
            bulletconfig_.center_point_=center_;
            bulletconfig_.center_point2_=center_;
            bulletconfig_.v_=0;
            bulletconfig_.x_=9999;
            for(int i=1;i<=1;i++)
            {
                bulletconfig_.spawn_point_=center_+roundwithCenter({0,0},shoot_position_,(i-1)*72);
                resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
            }
            shoot_position_=shoot_position_+gap_*position_move_direction_;
        }
    }

    if(!shoot_times_clock2_.get_condition())
    {
        if(shoot2_delay_.get_condition())
        {
            if(shoot_clock2_.get_condition())
            {
                shoot_clock2_.reset();

                //position_move_direction_=roundwithCenter({0,0},position_move_direction_,144);
                bulletconfig_.center_point_=center_+shoot_position_-gap_*position_move_direction_;//因为在最后一颗星放完之后shootposition还会推进一次，所以需要偏移一个
                bulletconfig_.center_point2_=center_;
                bulletconfig_.x_=36;
                bulletconfig_.v_=-2;
                for(int i=1;i<=bullet_num_;i++)
                {
                    bulletconfig_.spawn_point_=center_+shoot_position_-gap_*i*position_move_direction_;
                    resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
                }
                shoot_position_=roundwithCenter({0,0},shoot_position_,144);
                position_move_direction_=roundwithCenter({0,0},position_move_direction_,144);
                shoot_times_clock2_.count();
            }
        }
    }

//*********************************************** */

    if(phase_clock_.get_condition())
    {
        phase_=2;    
    }

/************************************************** */

    if(trigger_==true)
    {
        trigger_=false;
    }
    if(trigger_delay_.get_condition())
    {
        if(trigger_clock_.get_condition())
        {
            trigger_clock_.reset();
            trigger_=true;
        }
    }

/************************************************** */
    
    shoot2_delay_.count();
    shoot_clock2_.count();
    phase_clock_.count();
    shoot_clock_.count();
    trigger_clock_.count();
    trigger_delay_.count();
}

StarRite::StarRite(Entity* entity,Resource* resource,YellowPage* yellowpage):
    Behavior(resource,yellowpage),starrite1_(entity,resource,yellowpage),starrite2_(entity,resource,yellowpage),delay_clock_(135)
{
    delay_clock_.reset();
}

void StarRite::update()
{
    starrite1_.update();
    if(delay_clock_.get_condition())
    {
        starrite2_.update();
    }
    delay_clock_.count();
}