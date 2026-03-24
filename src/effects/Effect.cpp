#include "effects/Effect.h"

Effect::Effect(const sf::Texture &texture):
    texture_(texture),picture_(texture_),position_({0,0}),prev_position_({0,0}),dead_(false),clock_(48)
{
    clock_.reset();
}

Effect::Effect(const sf::Texture &texture,sf::Vector2f position,long long int time):
    texture_(texture),picture_(texture_),position_(position),prev_position_({0,0}),dead_(false),clock_(time)
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
    for(auto it=behaviorlist_.begin();it!=behaviorlist_.end();++it)
    {
        (*it)->update();
    }
    clock_.count();
    if(clock_.get_condition())
    {
        markDead();
    }
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