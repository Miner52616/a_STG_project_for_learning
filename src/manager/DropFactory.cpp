#include "manager/DropFactory.h"
#include "packages/DropConfig.h"
#include "core/application.h"
#include "entities/Drop.h"
#include <iostream>

void DropFactory::set_Resourse(Resource* resource)
{
    resource_=resource;
}

void DropFactory::set_YellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
}

std::unique_ptr<Drop> DropFactory::create(DropConfig* dropconfig)
{
    std::unique_ptr<Drop> drop;
    switch (dropconfig->droptype_)
    {
    case DropType::Score:
        drop=std::make_unique<Drop>(resource_->app_.score_dropTexture_);
        drop->setResource(resource_);
        drop->setYellowPage(yellowpage_);
        drop->setPosition(dropconfig->spawn_point_);
        drop->setType(dropconfig->droptype_);

        //std::cout<<"create success"<<std::endl;
        return std::move(drop);
        break;

    case DropType::Power:
        drop=std::make_unique<Drop>(resource_->app_.power_dropTexture_);
        drop->setResource(resource_);
        drop->setYellowPage(yellowpage_);
        drop->setPosition(dropconfig->spawn_point_);
        drop->setType(dropconfig->droptype_);

        //std::cout<<"create success"<<std::endl;
        return std::move(drop);
        break;
    
    default:
        drop=std::make_unique<Drop>(resource_->app_.score_dropTexture_);
        drop->setResource(resource_);
        drop->setYellowPage(yellowpage_);
        drop->setPosition(dropconfig->spawn_point_);
        drop->setType(dropconfig->droptype_);

        //std::cout<<"create success"<<std::endl;
        return std::move(drop);
        break;
    }
    
}