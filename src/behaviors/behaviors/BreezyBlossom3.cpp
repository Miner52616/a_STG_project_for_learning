#include "behaviors/behaviors/BreezyBlossom3.h"
#include "core/application.h"
#include "manager/BulletManager.h"
#include "mathematics/mathematics.h"
#include "entities/Player.h"

BreezyBlossom3::BreezyBlossom3(Entity* entity,Resource* resource,YellowPage* yellowpage):
    entity_(entity),Behavior(resource,yellowpage),shoot_clock_(24),bulletconfig_(resource->app_.blossom_small_bulletTexture)
{
    shoot_clock_.reset();
    setBulletConfig();
}

void BreezyBlossom3::update()
{
    if(shoot_clock_.get_condition())
    {
        shoot_clock_.reset();

        sf::Vector2f direction=normalize(yellowpage_->player_->getPosition()-entity_->getPosition());
        direction=roundwithCenter({0,0},direction,getRandomNum(-10,10));
        sf::Vector2f spawnposition=entity_->getPosition();
        float v=getRandomNum(1.7,2);
        bulletconfig_.v_=v;
        bulletconfig_.spawn_point_=spawnposition;
        
        //std::cout<<spawnposition.x<<" "<<spawnposition.y<<std::endl;
        for(int i=1;i<=6;i++)
        {
            bulletconfig_.direction_=direction;
            resource_->bulletmanager_.add_process(&bulletconfig_);

            direction=roundwithCenter({0,0},direction,60);
        }
    }

    shoot_clock_.count();
}

void BreezyBlossom3::setBulletConfig()
{
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
    bulletconfig_.r_=2;
}
