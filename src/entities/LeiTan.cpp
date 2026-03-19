#include "entities/LeiTan.h"
#include "behaviors/behaviors/RoundMove1.h"
#include "entities/Player.h"

LeiTan::LeiTan(const sf::Texture &texture,sf::Vector2f position,YellowPage* yellowpage):
    Bomb(texture,position), yellowpage_(yellowpage),clock_(180)
{
    clock_.reset();
    roundmove1_=std::make_unique<RoundMove1>(sf::Vector2f{100,0},(float)3,this);
    roundmove1_->set_center(yellowpage_->player_);
    behaviorlist_.emplace_back(roundmove1_.get());
}

LeiTan::LeiTan(const sf::Texture &texture,sf::Vector2f position,float damage,YellowPage* yellowpage):
    Bomb(texture,position,damage), yellowpage_(yellowpage),clock_(180)
{
    hitbox_r_=80;
    clock_.reset();
    roundmove1_=std::make_unique<RoundMove1>(sf::Vector2f{100,0},(float)3,this);
    roundmove1_->set_entity(this);
    yellowpage_->player_->getPosition();
    roundmove1_->set_center(yellowpage_->player_);
    behaviorlist_.emplace_back(roundmove1_.get());
}

LeiTan::LeiTan(const sf::Texture &texture,sf::Vector2f position,sf::Vector2f direction,float damage,float v,YellowPage* yellowpage):
    Bomb(texture,position,damage), yellowpage_(yellowpage),clock_(180)
{
    hitbox_r_=80;
    clock_.reset();
    roundmove1_=std::make_unique<RoundMove1>(direction,(float)v,this);
    roundmove1_->set_entity(this);
    yellowpage_->player_->getPosition();
    roundmove1_->set_center(yellowpage_->player_);
    behaviorlist_.emplace_back(roundmove1_.get());
}

void LeiTan::update()
{
    clock_.count();
    if(clock_.get_condition())
    {
        markDead();
    }
    for(auto it=behaviorlist_.begin();it!=behaviorlist_.end();++it)
    {
        (*it)->update();
    }
}