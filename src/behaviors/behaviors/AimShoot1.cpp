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

void AimShoot1::setBulletConfig()
{
    bulletconfig_=std::make_shared<BulletConfig>(resource_->app_.bulletTexture_);
    //bulletconfig_->texture_=resource_->app_.bulletTexture_;
    bulletconfig_->bulletclass_=BulletClasses::LinearBullet;
    bulletconfig_->damage_=100;
    //bulletconfig_->spawn_point_=entity_->getPosition();
    //bulletconfig_->target_point_=resource_->player_->getPosition();
    bulletconfig_->v_=0.06;
    bulletconfig_->r_=3;
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
        bulletconfig_->spawn_point_=entity_->getPosition();
        bulletconfig_->target_point_=resource_->player_->getPosition();
        resource_->bulletmanager_.add_process(bulletconfig_);//(std::make_unique<LinearBullet>(resource_->app_.bulletTexture_,entity_->getPosition(),resource_->player_->getPosition(),0.06,6));
        clock_.reset();
    }
    clock_.count();
}

void AimShoot1::set_entity(std::shared_ptr<Entity> entity)
{
    entity_=std::move(entity);
}