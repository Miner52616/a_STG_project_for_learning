#include "manager/BombFactory.h"
#include "entities/LeiTan.h"
#include "packages/YellowPage.h"
#include "entities/Player.h"
#include <iostream>

void BombFactory::set_Resourse(Resource* resource)
{
    resource_=resource;
}

void BombFactory::set_YellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
    yellowpage_->player_->getPosition();
}

std::unique_ptr<Bomb> BombFactory::create(BombConfig* bombconfig)
{
    std::unique_ptr<Bomb> bomb;
    yellowpage_->player_->getPosition();
    switch(bombconfig->bombtype_)
    {
        case BombType::LeiTan:
            bomb=std::make_unique<LeiTan>(bombconfig->texture_,bombconfig->spawn_point_,bombconfig->direction_,bombconfig->damage_,bombconfig->v_,yellowpage_);
            break;
        default:
            break;
    }
    //std::cout<<"create success"<<std::endl;
    return std::move(bomb);
}