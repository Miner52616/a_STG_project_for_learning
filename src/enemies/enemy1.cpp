#include "enemies/Enemy1.h"
#include "entities/Player.h"
#include "manager/BulletManager.h"
#include "bullets/LinearBullet.h"
#include "mathematics/mathematics.h"

Enemy1::Enemy1(application &app,const sf::Texture &texture,BulletManager &bulletmanager,Player &player):
    Enemy(app,texture,bulletmanager),player_(player),moveclock_(180),shootclock_(20),nextposition_({460,200})
{
    ;
}

void Enemy1::move()
{
    setPosition((nextposition_-position_)*0.01f+position_);
}

void Enemy1::update(long long int frame)
{
    set_exist(frame);
    if(isExist())
    {
        if(HP_<=0)
        {
            markDead();
        }
        store_position();

        move();

        if(moveclock_.get_condition())
        {
            nextposition_={getRandomNum(125,795),getRandomNum(20,300)};
            moveclock_.reset();
        }

        if(shootclock_.get_condition())
        {
            bulletmanager_.add_process(std::make_unique<LinearBullet>(app_,app_.bulletTexture_,getPosition(),player_.getPosition()+(player_.getPosition()-getPosition()),0.06,6));
            bulletmanager_.add_process(std::make_unique<LinearBullet>(app_,app_.bulletTexture_,getPosition(),player_.getPosition()+(player_.getPosition()-getPosition()),0.04,6));
            bulletmanager_.add_process(std::make_unique<LinearBullet>(app_,app_.bulletTexture_,getPosition(),player_.getPosition(),0.06,6));
            shootclock_.reset();
        }

        clock_count();
    }
}

void Enemy1::clock_count()
{
    moveclock_.count();
    shootclock_.count();
}