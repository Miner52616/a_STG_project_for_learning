#include "entities/LeiTan.h"
#include "behaviors/behaviors/RoundMove1.h"
#include "entities/Player.h"
#include "mathematics/mathematics.h"
#include <vector>

LeiTan::LeiTan(const sf::Texture &texture,sf::Vector2f position,YellowPage* yellowpage):
    Bomb(texture,position), yellowpage_(yellowpage)
{
    hitbox_r_=80;

    roundmove1_=std::make_unique<RoundMove1>(sf::Vector2f{100,0},(float)3,120,this);
    roundmove1_->set_center(yellowpage_->player_);
    aimmove2_=std::make_unique<AimMove2>(sf::Vector2f{0,0},3,this,180,resource_);

    behaviorlist_.emplace_back(roundmove1_.get());
}

LeiTan::LeiTan(const sf::Texture &texture,sf::Vector2f position,float damage,YellowPage* yellowpage):
    Bomb(texture,position,damage), yellowpage_(yellowpage)
{
    hitbox_r_=80;

    roundmove1_=std::make_unique<RoundMove1>(sf::Vector2f{100,0},(float)3,120,this);
    roundmove1_->set_entity(this);
    aimmove2_=std::make_unique<AimMove2>(sf::Vector2f{0,0},3,this,180,resource_);

    yellowpage_->player_->getPosition();
    roundmove1_->set_center(yellowpage_->player_);
    behaviorlist_.emplace_back(roundmove1_.get());
}

LeiTan::LeiTan(const sf::Texture &texture,sf::Vector2f position,sf::Vector2f direction,float damage,float v,YellowPage* yellowpage,Resource* resource):
    Bomb(texture,position,damage), yellowpage_(yellowpage),resource_(resource)
{
    hitbox_r_=80;

    roundmove1_=std::make_unique<RoundMove1>(direction,(float)v,120,this);
    roundmove1_->set_entity(this);
    aimmove2_=std::make_unique<AimMove2>(sf::Vector2f{0,0},3,this,180,resource);

    yellowpage_->player_->getPosition();
    roundmove1_->set_center(yellowpage_->player_);
    behaviorlist_.emplace_back(roundmove1_.get());
}

void LeiTan::update()
{
    switch (phase_)
    {
    case 1:
        roundmove1_->update();
        if(roundmove1_->isDone())
        {
            phase_change();
        }
        break;

    case 2:
        aimmove2_->update();
        if(aimmove2_->isDone())
        {
            phase_change();
        }
        break;
    
    default:
        markDead();
        break;
    }
}

void LeiTan::phase_change()
{
    switch (phase_)
    {
    case 1:
        phase_=2;
        aimmove2_->set_startposition(getPosition());
        aimmove2_->set_v(getPosition()-getprevPosition());
        break;

    case 2:
        phase_=3;
        markDead();
        break;
    
    default:
        markDead();
        break;
    }
}