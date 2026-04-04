#include "collision/CollisionCheck.h"
#include "mathematics/mathematics.h"
#include "entities/Entity.h"
#include "entities/Drop.h"
#include "entities/Player.h"
#include "entities/Bullet.h"
#include "entities/LeiTan.h"
#include "entities/Bomb.h"
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
    
    float closest=distancePointToSegment2(a1,b1,b1+b1b2-a1a2);
    
    if(closest<(ra+rb)*(ra+rb))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isCollisionSimple(Entity &a,Entity &b)
{
    sf::Vector2f pa=a.getPosition();
    int ra=a.getHitbox_r();
    sf::Vector2f pb=b.getPosition();
    int rb=b.getHitbox_r();

    sf::Vector2f vec=pb-pa;
    float length2=(vec.x)*(vec.x)+(vec.y)*(vec.y);

    float error=70;
    if(length2<(ra+rb+error)*(ra+rb+error))
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

bool isGetSimple(Entity &a,Drop &b)
{
    sf::Vector2f pa=a.getPosition();
    int ra=a.getHitbox_r();
    sf::Vector2f pb=b.getPosition();
    int rb=b.getGetbox_r();

    sf::Vector2f vec=pb-pa;
    float length2=(vec.x)*(vec.x)+(vec.y)*(vec.y);

    float error=30;
    if(length2<(ra+rb+error)*(ra+rb+error))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isBomb(Entity &a,Bomb &b)
{
    sf::Vector2f a1=a.getprevPosition();
    sf::Vector2f a2=a.getPosition();
    int ra=a.getHitbox_r();
    sf::Vector2f b1=b.getprevPosition();
    sf::Vector2f b2=b.getPosition();
    int rb=b.getBombbox_r();

    sf::Vector2f a1a2=a2-a1;
    sf::Vector2f b1b2=b2-b1;
    
    float closest=distancePointToSegment2(a1,b1,b1+b1b2-a1a2);
    
    if(closest<(ra+rb)*(ra+rb))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isGraze(Player &a,Bullet &b)
{
    sf::Vector2f vec=a.getPosition()-b.getPosition();
    float length=vec.x*vec.x+vec.y*vec.y;
    float graze_length=a.getGrazebox_r()*a.getGrazebox_r()+b.getHitbox_r()*b.getHitbox_r();
    if(length<=graze_length)
    {
        return true;
    }
    else
    {
        return false;
    }
}