#include "entities/Enemy.h"
#include "packages/DropConfig.h"
#include "manager/BulletManager.h"

Enemy::Enemy(const sf::Texture &texture):
    Entity(texture),exist_(false),startframe_(0),endframe_(216000),HP_(500),dead_(false)
{
    hitbox_r_=15;
}

void Enemy::set_exist(bool set)
{
    exist_=set;
}

void Enemy::set_exist(long long int frame)
{
    if((frame>=startframe_)&&(frame<endframe_))
    {
        exist_=true;
    }
    else
    {
        exist_=false;
    }
}

void Enemy::set_start_end(long long int start,long long int end)
{
    startframe_=start;
    endframe_=end;
}

bool Enemy::isExist()
{
    return exist_;
}

long long int Enemy::getStartFrame()
{
    return startframe_;
}

long long int Enemy::getEndFrame()
{
    return endframe_;
}

void Enemy::setHP(float HP)
{
    HP_=HP;
}

void Enemy::be_damage(float damage)
{
    HP_=HP_-damage;
}

void Enemy::markDead()
{
    dead_=true;
}

bool Enemy::isDead()
{
    return dead_;
}

void Enemy::addBehavior(std::shared_ptr<Behavior> behavior)
{
    behaviorlist_.emplace_back(std::move(behavior));
}

void Enemy::update(long long int frame)
{
    set_exist(frame);
    if(isExist())
    {
        if(HP_<=0)
        {
            markDead();
        }
        for(auto it=behaviorlist_.begin();it!=behaviorlist_.end();++it)
        {
            (*it)->update();
        }
    }
}

/*
void Enemy::addDrop(std::shared_ptr<DropConfig> dropconfig)
{
    droplist_.emplace_back(std::move(dropconfig));
}
*/

void Enemy::drawwindow(sf::RenderWindow& window)
{
    if(exist_)
    {
        window.draw(picture_);
    }
}

void Enemy::drawtexture(sf::RenderTexture& texture)
{
    if(exist_)
    {
        texture.draw(picture_);
    }
}

void Enemy::clock_count()
{
    ;
}