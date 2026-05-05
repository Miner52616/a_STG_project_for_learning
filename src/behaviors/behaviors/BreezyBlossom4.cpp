#include "behaviors/behaviors/BreezyBlossom4.h"
#include "core/application.h"
#include "manager/BulletManager.h"
#include "mathematics/mathematics.h"
#include "entities/Player.h"

BreezyBlossom4::BreezyBlossom4(Entity* entity,Resource* resource,YellowPage* yellowpage):
    entity_(entity),ShootBehavior(resource,yellowpage),shoot_clock_(90),bulletconfig_(resource->app_.bulletsheetTexture2_)
{
    shoot_clock_.reset();
    setBulletConfig();
}

void BreezyBlossom4::update()
{
    if(shoot_clock_.get_condition())
    {
        shoot_clock_.reset();

        sf::Vector2f direction=roundwithCenter({0,0},{0,1},getRandomNum(-10,10));
        sf::Vector2f spawnposition=entity_->getPosition();
        bulletconfig_.spawn_point_=spawnposition;

        for(int i=1;i<=30;i++)
        {
            bulletconfig_.direction_=direction;
            resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);

            direction=roundwithCenter({0,0},direction,12);
        }

        resource_->bulletmanager_.add_process(&bulletconfig_,&effectconfig_);
    }

    shoot_clock_.count();
}

void BreezyBlossom4::setBulletConfig()
{
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
    bulletconfig_.bulletsize_=Large;
    bulletconfig_.r_=18;
    bulletconfig_.v_=8;
    bulletconfig_.bullet_index_={1,1};
}
