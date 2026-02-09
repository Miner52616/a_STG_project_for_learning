#include "entities/Enemy.h"
#include "manager/BulletManager.h"

Enemy::Enemy(application &app,const sf::Texture &texture,BulletManager &bulletmanager):
    Entity(app,texture),exist_(false),startframe_(0),endframe_(216000),HP_(500),bulletmanager_(bulletmanager)
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

void Enemy::be_damage(float damage)
{
    HP_=HP_-damage;
}

void Enemy::drawwindow(sf::RenderWindow& window)
{
    if(exist_)
    {
        window.draw(picture_);
    }
}