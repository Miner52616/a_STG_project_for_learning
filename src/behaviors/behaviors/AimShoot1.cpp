#include "behaviors/behaviors/AimShoot.h"
#include "manager/BulletManager.h"
#include "bullets/LinearBullet.h"
#include <iostream>

AimShoot1::AimShoot1(std::shared_ptr<Entity> entity,BulletManager &bulletmanager):
    entity_(entity),bulletmanager_(bulletmanager)
{
    ;   
}

AimShoot1::AimShoot1(BulletManager &bulletmanager):
    bulletmanager_(bulletmanager)
{
    ;
}

void AimShoot1::update()
{
    if(resourse_==NULL)
    {
        std::cout<<"No Resourse!"<<std::endl;
        return;
    }
    if(clock_.get_condition())
    {
        bulletmanager_.add_process(std::make_unique<LinearBullet>(resourse_->app_,resourse_->app_.bulletTexture_,entity_->getPosition(),resourse_->player_->getPosition(),0.06,6));
        clock_.reset();
    }
}

void AimShoot1::set_entity(std::shared_ptr<Entity> entity)
{
    entity_=std::move(entity);
}