#include "entities/Enemy.h"

Enemy::Enemy(application &app,const sf::Texture &texture):
    Entity(app,texture),exist_(false),startframe_(0),endframe_(216000)
{
    ;
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

void Enemy::drawwindow(sf::RenderWindow& window)
{
    if(exist_)
    {
        window.draw(picture_);
    }
}