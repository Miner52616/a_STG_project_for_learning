#include "entities/Drop.h"
#include "entities/Player.h"
#include "behaviors/behaviors/DropMove1.h"
#include "behaviors/behaviors/AimMove1.h"

Drop::Drop(const sf::Texture &texture):
    Entity(texture),getbox_r_(80),phase_(1),v1_(-20),v2_(30),a_(0.5)
{
    ;
}

void Drop::setResource(std::shared_ptr<Resource> resource)
{
    resource_=std::move(resource);
}

void Drop::setType(DropType type)
{
    type_=type;
}

void Drop::setPhase(int phase)
{
    phase_=phase;
}

void Drop::setMove(std::shared_ptr<Behavior> move1,std::shared_ptr<Behavior> move2)
{
    move1_=move1;
    move2_=move2;
}

void Drop::markDead()
{
    dead_=true;
}

bool Drop::isDead()
{
    return dead_;
}

void Drop::update()
{
    //std::cout<<phase_<<std::endl;
    switch(phase_)
    {
        case 1:
        {
            //move1_->update();//后续如果需要再加入可组合行为
            store_position();
            setPosition({getPosition().x,getPosition().y+v1_});
            v1_=v1_+a_;
            //std::cout<<"drop move success"<<std::endl;
            break;      
        }
        case 2:
        {
            //move2_->update();
            store_position();
            setPosition(getPosition()+v2_*((resource_->player_->getPosition()-getPosition())/((resource_->player_->getPosition()-getPosition()).length())));
            //std::cout<<"aim move success"<<std::endl;
            break;
        }
    }
    if(getPosition().y>=950)
    {
        markDead();
    }
    //std::cout<<"update success"<<std::endl;
}

void Drop::drawtexture(sf::RenderTexture& texture)
{
    texture.draw(picture_);
}