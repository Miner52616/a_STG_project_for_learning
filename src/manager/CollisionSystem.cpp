#include "manager/CollisionSystem.h"
#include "collision/CollisionCheck.h"
#include "entities/Entity.h"
#include "entities/Boss.h"
#include "entities/Enemy.h"
#include "entities/Player.h"
#include "entities/Bullet.h"
#include "entities/Drop.h"
#include "entities/Bomb.h"
#include "ui/NumLine1.h"
#include "mathematics/mathematics.h"

CollisionSystem::CollisionSystem(std::vector<std::unique_ptr<Bullet>> &bulletlist,std::vector<std::unique_ptr<Drop>> &droplist):
    bulletlist_(bulletlist),droplist_(droplist)
{
    ;
}

void CollisionSystem::set_resource(Resource* resource)
{
    resource_=resource;
}

void CollisionSystem::set_yellowpage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
}

void CollisionSystem::HandleCollision(Boss* boss,Bullet *bullet)
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

void CollisionSystem::HandleCollision(Enemy* enemy,Bullet *bullet)
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

void CollisionSystem::HandleCollision(Player* player,Bullet *bullet)
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

void CollisionSystem::HandleCollision(Player* player,Drop *drop)
{
    if(isCollision(*player,*drop))
    {
        drop->markDead();
        yellowpage_->score_line_.setCurrentNum(yellowpage_->score_line_.getCurrentNum()+the_min(500,750*((900-drop->getPosition().y)/900))+500);
    }
}

void CollisionSystem::HandleBeGet(Player* player,Drop *drop)
{
    if(isGet(*player,*drop))
    {
        drop->setPhase(2);
    }
}

void CollisionSystem::HandleCollision(Bomb* bomb,Bullet *bullet)
{
    if(!bullet->isPlayer())
    {
        if(isCollision(*bomb,*bullet))
        {
            bullet->markDead();
        }
    }
}

void CollisionSystem::ProcessCollision(Boss* boss)
{
    for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
    {
        HandleCollision(boss,it->get());
    }
}

void CollisionSystem::ProcessCollision(Enemy* enemy)
{
    for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
    {
        HandleCollision(enemy,it->get());
    }
}

void CollisionSystem::ProcessCollision(Player* player)
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

void CollisionSystem::ProcessCollision(Bomb* bomb)
{
    for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
    {
        HandleCollision(bomb,it->get());
    }
}