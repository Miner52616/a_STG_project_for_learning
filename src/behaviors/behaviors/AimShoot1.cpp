#include "behaviors/behaviors/AimShoot.h"
#include "manager/BulletManager.h"
#include "bullets/LinearBullet.h"
#include <iostream>

AimShoot1::AimShoot1(std::shared_ptr<Entity> entity):
    entity_(entity)
{
    ;   
}

AimShoot1::AimShoot1()
{
    ;
}

void AimShoot1::update()
{
    if(resource_==NULL)
    {
        std::cout<<"No Resource!"<<std::endl;
        return;
    }
    if(clock_.get_condition())
    {
        resource_->bulletmanager_.add_process(std::make_unique<LinearBullet>(resource_->app_.bulletTexture_,entity_->getPosition(),resource_->player_->getPosition(),0.06,6));
        clock_.reset();
    }
    clock_.count();
}

void AimShoot1::set_entity(std::shared_ptr<Entity> entity)
{
    entity_=std::move(entity);
}