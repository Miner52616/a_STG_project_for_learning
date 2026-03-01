#include "manager/CollisionSystem.h"
#include "collision/CollisionCheck.h"
#include "entities/Entity.h"
#include "entities/Boss.h"
#include "entities/Enemy.h"
#include "entities/Player.h"
#include "entities/Bullet.h"
#include "entities/Drop.h"

CollisionSystem::CollisionSystem(std::vector<std::unique_ptr<Bullet>> &bulletlist,std::vector<std::unique_ptr<Drop>> &droplist):
    bulletlist_(bulletlist),droplist_(droplist)
{
    ;
}

void CollisionSystem::HandleCollision(std::shared_ptr<Boss> boss,Bullet *bullet)
{
    if(bullet->isPlayer())
    {
        if(isCollision(*boss,*bullet))
        {
            bullet->markDead();
            boss->be_damage(bullet->getDamage());
        }
    }
}

void CollisionSystem::HandleCollision(std::shared_ptr<Enemy> enemy,Bullet *bullet)
{
    if((bullet->isPlayer())&&(enemy->isExist()))
    {
        if(isCollision(*enemy,*bullet))
        {
            bullet->markDead();
            enemy->be_damage(bullet->getDamage());
        }
    }
}

void CollisionSystem::HandleCollision(std::shared_ptr<Player> player,Bullet *bullet)
{
    if(!bullet->isPlayer())
    {
        if(isCollision(*player,*bullet))
        {
            bullet->markDead();
            player->be_damage();
        }
    }
}

void CollisionSystem::HandleCollision(std::shared_ptr<Player> player,Drop *drop)
{
    if(isCollision(*player,*drop))
    {
        drop->markDead();
    }
}

void CollisionSystem::HandleBeGet(std::shared_ptr<Player> player,Drop *drop)
{
    if(isGet(*player,*drop))
    {
        drop->setPhase(2);
    }
}

void CollisionSystem::ProcessCollision(std::shared_ptr<Boss> boss)
{
    for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
    {
        HandleCollision(boss,it->get());
    }
}

void CollisionSystem::ProcessCollision(std::shared_ptr<Enemy> enemy)
{
    for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
    {
        HandleCollision(enemy,it->get());
    }
}

void CollisionSystem::ProcessCollision(std::shared_ptr<Player> player)
{
    for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
    {
        HandleCollision(player,it->get());
    }
    for(auto it=droplist_.begin();it!=droplist_.end();++it)
    {
        HandleCollision(player,it->get());
        HandleBeGet(player,it->get());
    }
}