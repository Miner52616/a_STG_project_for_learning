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

CollisionSystem::CollisionSystem(std::vector<std::unique_ptr<Bullet>> &bulletlist,std::vector<std::unique_ptr<Drop>> &droplist,std::vector<std::unique_ptr<Bomb>> &bomblist):
    bulletlist_(bulletlist),droplist_(droplist),bomblist_(bomblist)
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
        if(isGraze(*player,*bullet)&&(!bullet->isGrazed()))
        {
            bullet->markGrazed();
            yellowpage_->graze_line_.setCurrentNum(yellowpage_->graze_line_.getCurrentNum()+1);
        }
    }
}

void CollisionSystem::HandleCollision(Player* player,Drop *drop)
{
    if(isCollision(*player,*drop))
    {
        drop->markDead();
        switch (drop->getType())
        {
        case DropType::Score:
            yellowpage_->score_line_.setCurrentNum(yellowpage_->score_line_.getCurrentNum()+the_min(500,750*((900-drop->getPosition().y)/900))+500);
            break;
        
        case DropType::Power:
            yellowpage_->power_line_.setCurrentNum(yellowpage_->power_line_.getCurrentNum()+5);
            break;

        default:
            break;
        }
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

void CollisionSystem::HandleCollision(Enemy* enemy,Bomb* bomb)
{
    if(enemy->isExist()&&isCollision(*enemy,*bomb))
    {
        switch (bomb->getPhase())
        {
        case 1:
            enemy->be_damage(bomb->getDamage());
            break;

        case 2:
            enemy->be_damage(bomb->getDamage());
            bomb->phase_change();
            break;

        case 3:
            enemy->be_damage(bomb->getDamage());
            break;

        case 4:
            enemy->be_damage(bomb->getDamage());
            bomb->phase_change();

        default:
            break;
        }
    }
}

void CollisionSystem::HandleCollision(Boss* boss,Bomb* bomb)
{
    if(isCollision(*boss,*bomb))
    {
        switch (bomb->getPhase())
        {
        case 1:
            boss->be_damage(bomb->getDamage());
            break;

        case 2:
            boss->be_damage(bomb->getDamage());
            bomb->phase_change();
            break;

        case 3:
            boss->be_damage(bomb->getDamage());
            break;

        case 4:
            boss->be_damage(bomb->getDamage());
            bomb->phase_change();

        default:
            break;
        }
    }
}

void CollisionSystem::ProcessCollision(Boss* boss)
{
    for(auto it=bulletlist_.begin();it!=bulletlist_.end();++it)
    {
        HandleCollision(boss,it->get());
    }
    for(auto it=bomblist_.begin();it!=bomblist_.end();++it)
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
    for(auto it=bomblist_.begin();it!=bomblist_.end();++it)
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