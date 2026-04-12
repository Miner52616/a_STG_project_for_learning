#include "behaviors/behaviors/BreezyBlossom2.h"
#include "core/application.h"
#include "manager/BulletManager.h"
#include "mathematics/mathematics.h"
#include "entities/Player.h"

BreezyBlossom2::BreezyBlossom2(Entity* entity,Resource* resource,YellowPage* yellowpage):
    entity_(entity),Behavior(resource,yellowpage),shoot_clock_(6),bulletconfig_(resource->app_.blossom_small_bulletTexture)
{
    shoot_clock_.reset();
    setBulletConfig();
}

void BreezyBlossom2::update()
{
    if(shoot_clock_.get_condition())
    {
        shoot_clock_.reset();

        sf::Vector2f direction=roundwithCenter({0,0},{0,1},getRandomNum(-10,10));
        sf::Vector2f spawnposition={getRandomNum(10,760),15};
        float v=getRandomNum(4,7);
        bulletconfig_.v_=v;
        bulletconfig_.direction_=direction;
        bulletconfig_.spawn_point_=spawnposition;

        resource_->bulletmanager_.add_process(&bulletconfig_);
    }

    shoot_clock_.count();
}

void BreezyBlossom2::setBulletConfig()
{
    bulletconfig_.bulletclass_=BulletClasses::DirectBullet1;
    bulletconfig_.r_=2;
}
