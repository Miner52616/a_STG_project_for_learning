#include "collision/CollisionCheck.h"
#include "mathematics/mathematics.h"
#include "entities/Entity.h"
#include "entities/Drop.h"
#include <iostream>

bool isCollision(Entity &a,Entity &b)
{
    sf::Vector2f a1=a.getprevPosition();
    sf::Vector2f a2=a.getPosition();
    int ra=a.getHitbox_r();
    sf::Vector2f b1=b.getprevPosition();
    sf::Vector2f b2=b.getPosition();
    int rb=b.getHitbox_r();

    sf::Vector2f a1a2=a2-a1;
    sf::Vector2f b1b2=b2-b1;
    
    float closest=distancePointToSegment(a1,b1,b1+b1b2-a1a2);
    
    if(closest<ra+rb)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isGet(Entity &a,Drop &b)
{
    sf::Vector2f a1=a.getprevPosition();
    sf::Vector2f a2=a.getPosition();
    int ra=a.getHitbox_r();
    sf::Vector2f b1=b.getprevPosition();
    sf::Vector2f b2=b.getPosition();
    int rb=b.getGetbox_r();

    sf::Vector2f a1a2=a2-a1;
    sf::Vector2f b1b2=b2-b1;
    
    float closest=distancePointToSegment(a1,b1,b1+b1b2-a1a2);
    
    if(closest<ra+rb)
    {
        return true;
    }
    else
    {
        return false;
    }
}