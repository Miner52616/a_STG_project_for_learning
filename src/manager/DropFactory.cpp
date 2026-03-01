#include "manager/DropFactory.h"
#include "packages/DropConfig.h"
#include "entities/Drop.h"
#include <iostream>

void DropFactory::set_Resourse(std::shared_ptr<Resource> resource)
{
    resource_=std::move(resource);
}

std::unique_ptr<Drop> DropFactory::create(std::shared_ptr<DropConfig> dropconfig)
{
    std::unique_ptr<Drop> drop=std::make_unique<Drop>(dropconfig->texture_);
    drop->setResource(resource_);
    drop->setPosition(dropconfig->spawn_point_);
    drop->setType(dropconfig->droptype_);

    //std::cout<<"create success"<<std::endl;
    return std::move(drop);
}