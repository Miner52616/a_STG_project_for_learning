#include "behaviors/behaviors/BreezyBlossom1.h"
#include "core/application.h"
#include "manager/BulletManager.h"
#include "mathematics/mathematics.h"
#include "entities/Player.h"

BreezyBlossom1::BreezyBlossom1(Entity* entity,Resource* resource,YellowPage* yellowpage):
    entity_(entity),Behavior(resource,yellowpage),shoot_clock_(240),set_bullet_clock_(2),bullet_num_clock_(40),delay_time_(180),bulletconfig_(resource->app_.blossom_small_bulletTexture)
{
    shoot_clock_.reset();
    set_bullet_clock_.reset();
    bullet_num_clock_.reset();    
    setBulletConfig();
}

void BreezyBlossom1::update()
{
    if(shoot_clock_.get_condition())
    {
        if(bullet_num_clock_.get_condition())
        {
            shoot_clock_.reset();
            bullet_num_clock_.reset();
            set_bullet_clock_.reset();
        }
        else
        {
            if(set_bullet_clock_.get_condition())
            {
                set_bullet_clock_.reset();

                bulletconfig_.setClock1(delay_time_);
                for(int i=1;i<=20;i++)
                {   
                    sf::Vector2f shoot_position_copy=shoot_position_;
                    shoot_position_copy=roundwithCenter({0,0},shoot_position_copy,18*(i-1));
                    sf::Vector2f spawn_position=center_position_+shoot_position_copy;
                    bulletconfig_.spawn_point_=spawn_position;
                
                    bullet_direction_=spawn_position-center_position_;
                    bulletconfig_.direction_=bullet_direction_;

                    resource_->bulletmanager_.add_process(&bulletconfig_);
                }

                delay_time_=delay_time_+15;
                shoot_position_=shoot_position_+shoot_direction_;
                shoot_direction_=roundwithCenter({0,0},shoot_direction_,2);
            }
            set_bullet_clock_.count();

            bullet_num_clock_.count();
        }
    }
    else
    {
        reset();
        shoot_clock_.count();
    }
}

void BreezyBlossom1::set_entity(Entity* entity)
{
    entity_=entity;
}

void BreezyBlossom1::setBulletConfig()
{
    bulletconfig_.v_=0.2;
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet2;
    bulletconfig_.r_=2;
    bulletconfig_.a_=0.1;
    bulletconfig_.v2_=6;
}

void BreezyBlossom1::reset()
{
    center_position_=entity_->getPosition();
    shoot_position_={0,30};
    shoot_direction_={0,30};
    delay_time_=180;
}