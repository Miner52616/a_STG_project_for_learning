#include "effects/Effect.h"
#include "packages/EffectConfig.h"
#include "core/application.h"

Effect::Effect(sf::Texture &texture):
    texture_(&texture),picture_(texture),position_({0,0}),prev_position_({0,0}),dead_(false),clock_(48),effectconfig_(texture)
{
    clock_.reset();
}

Effect::Effect(sf::Texture &texture,sf::Vector2f position,long long int time):
    texture_(&texture),picture_(texture),position_(position),prev_position_({0,0}),dead_(false),clock_(time),effectconfig_(texture)
{
    clock_.reset();
}

void Effect::setPosition(sf::Vector2f position)
{
    position_=position;
    picture_.setPosition(position_);
}

void Effect::store_position()
{
    prev_position_=position_;
}

sf::Vector2f Effect::getPosition()
{
    return position_;
}

sf::Vector2f Effect::getprevPosition()
{
    return prev_position_;
}

void Effect::setResource(Resource* resource)
{
    resource_=resource;
}

bool Effect::isDead() const
{
    return dead_;
}


void Effect::markDead()
{
    dead_=true;
}

void Effect::addBehavior(std::unique_ptr<Behavior> behavior)
{
    behaviorlist_.emplace_back(std::move(behavior));
}

void Effect::update()
{
    store_position();
    /*
    for(auto it=behaviorlist_.begin();it!=behaviorlist_.end();++it)
    {
        (*it)->update();
    }*/
    effect_update_table[effectconfig_.effecttype_](*this);

    clock_.count();
    if(clock_.get_condition())
    {
        markDead();
    }
}

void Effect::setDead(bool dead)
{
    dead_=dead;
}

void Effect::initialize()
{
    dead_=false;
}

void Effect::setActive(bool active)
{
    active_=active;
}

void Effect::rebuild(sf::Texture &texture,sf::Vector2f position)
{
    texture_=&texture;
    picture_.setTexture(*texture_,true);
    prev_position_={0,0};
    dead_=false;
    clock_.set_target(48);

    setPosition(position);
    clock_.reset();
}

EffectConfig* Effect::getEffectConfig()
{
    return &effectconfig_;
}

void Effect::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
}

void Effect::drawtexture(sf::RenderTexture& texture)
{
    texture.draw(picture_);
}

void Effect::setTime(long long int time)
{
    clock_.set_target(time);
}

/******************************************************* */

//匀速直线运动
void direct_move1(Effect& effect)
{
    effect.setPosition(effect.getPosition()+effect.effectconfig_.v_*effect.effectconfig_.direction_);
}

//含加速度的减速至目标速度的减速运动
void direct_move2(Effect& effect)
{
    effect.setPosition(effect.getPosition()+effect.effectconfig_.v_*effect.effectconfig_.direction_);
    if(effect.effectconfig_.v_>effect.effectconfig_.v2_)
    {
        effect.effectconfig_.v_=effect.effectconfig_.v_-effect.effectconfig_.a_;
        if(effect.effectconfig_.v_<effect.effectconfig_.v2_)
        {
            effect.effectconfig_.v_=effect.effectconfig_.v2_;
        }
    }
}

EffectUpdateFunc effect_update_table[]=
{
    direct_move2
};