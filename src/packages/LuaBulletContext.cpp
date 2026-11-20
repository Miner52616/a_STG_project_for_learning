#include "packages/LuaBulletContext.h"
#include "entities/Entity.h"
#include "mathematics/mathematics.h"

LuaBulletContext::LuaBulletContext(Entity* entity,Resource* resource):
    entity_(entity),resource_(resource)
{
    ;
}

sf::Vector2f LuaBulletContext::getPosition()
{
    return entity_->getPosition();
}

void LuaBulletContext::spawnBullet(sol::table bulletconfig)
{
    ;
} 

float LuaBulletContext::random(float a,float b)
{
    return getRandomNum(a,b);
}