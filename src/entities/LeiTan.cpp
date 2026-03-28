#include "entities/LeiTan.h"
#include "behaviors/behaviors/RoundMove1.h"
#include "entities/Player.h"
#include "mathematics/mathematics.h"
#include "core/application.h"
#include "manager/EffectManager.h"
#include <vector>

LeiTan::LeiTan(const sf::Texture &texture,sf::Vector2f position,YellowPage* yellowpage,Resource* resource):
    Bomb(texture,position), yellowpage_(yellowpage),resource_(resource),clock_(15)
{
    effectconfig_=std::make_unique<EffectConfig>(resource_->app_.LeiTan_AirTexture_);
    hitbox_r_=80;
    clock_.reset();

    roundmove1_=std::make_unique<RoundMove1>(sf::Vector2f{100,0},(float)3,120,this);
    roundmove1_->set_center(yellowpage_->player_);
    aimmove2_=std::make_unique<AimMove2>(sf::Vector2f{0,0},3,this,180,resource_);

    behaviorlist_.emplace_back(roundmove1_.get());
}

LeiTan::LeiTan(const sf::Texture &texture,sf::Vector2f position,float damage,YellowPage* yellowpage,Resource* resource):
    Bomb(texture,position,damage), yellowpage_(yellowpage),resource_(resource),clock_(15)
{
    effectconfig_=std::make_unique<EffectConfig>(resource_->app_.LeiTan_AirTexture_);
    hitbox_r_=80;
    clock_.reset();

    roundmove1_=std::make_unique<RoundMove1>(sf::Vector2f{100,0},(float)3,120,this);
    roundmove1_->set_entity(this);
    aimmove2_=std::make_unique<AimMove2>(sf::Vector2f{0,0},3,this,180,resource_);

    yellowpage_->player_->getPosition();
    roundmove1_->set_center(yellowpage_->player_);
    behaviorlist_.emplace_back(roundmove1_.get());
}

LeiTan::LeiTan(const sf::Texture &texture,sf::Vector2f position,sf::Vector2f direction,float damage1,float damage2,float v,YellowPage* yellowpage,Resource* resource):
    Bomb(texture,position,damage1), yellowpage_(yellowpage),resource_(resource),clock_(15),damage1_(damage1),damage2_(damage2)
{
    effectconfig_=std::make_unique<EffectConfig>(resource_->app_.LeiTan_AirTexture_);
    hitbox_r_=80;
    clock_.reset();

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

    case 3:
        aimmove2_->update();
        clock_.count();
        if(clock_.get_condition())
        {
            phase_change();
        }
        break;
    
    case 4:
        aimmove2_->update();
        phase_change();
        break;
    
    default:
        for(int i=1;i<=8;i++)
        {
            float x=getRandomNum(-1,1);
            float y=getRandomNum(-1,1);
            float length=getRandomNum(0,100);
            sf::Vector2f direction={x,y};
            direction=length*normalize(direction);
            effectconfig_->direction_=direction;
            effectconfig_->spawn_point_=getPosition();
            effectconfig_->time_=getRandomNum(30,60);
            resource_->effectmanager_.add_process(effectconfig_.get());
        }
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
        break;

    case 3:
        phase_=4;
        break;
    
    case 4:
        phase_=5;
        break;
    
    default:
        markDead();
        break;
    }
}

int LeiTan::getPhase()
{
    return phase_;
}

float LeiTan::getDamage()
{
    switch (phase_)
    {
    case 1:
        return damage1_;
        break;
    
    case 2:
        return damage1_;
        break;

    case 3:
        return damage1_;
        break;

    case 4:
        return damage2_;
        break;

    default:
        return 0;
        break;
    }
}