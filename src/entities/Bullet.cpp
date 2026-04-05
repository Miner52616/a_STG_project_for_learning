#include "entities/Bullet.h"
#include "behaviors/Behavior.h"
#include <iostream>

Bullet::Bullet(sf::Texture &texture,sf::Vector2f position):
    Entity(texture),bullet_texture_(texture),exist_(true),dead_(false),active_(false),grazed_(false),ofplayer_(true),damage_(100)
{
    position_=position;
    hitbox_r_=10;
}

Bullet::Bullet(sf::Texture &texture,sf::Vector2f position,float damage):
    Entity(texture),bullet_texture_(texture),exist_(true),dead_(false),active_(false),grazed_(false),ofplayer_(true),damage_(damage)
{
    position_=position;
    hitbox_r_=10;
}

void Bullet::update()
{
    store_position();
    for(auto it=behaviorlist_.begin();it!=behaviorlist_.end();++it)
    {
        (*it)->update();
    }
    if(isOut())
    {
        markDead();
    }
}

bool Bullet::isDead() const
{
    return dead_;
}

bool Bullet::isAcitve()
{
    return active_;
}

bool Bullet::isGrazed()
{
    return grazed_;
}

bool Bullet::isPlayer()
{
    return ofplayer_;
}

bool Bullet::isOut()
{
    if(getPosition().x<=0||getPosition().y<=0||getPosition().x>=770||getPosition().y>=900)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Bullet::rebuild(sf::Texture &texture,sf::Vector2f position)
{
    bullet_texture_=texture;
    picture_.setTexture(bullet_texture_);
    position_=position;
    hitbox_r_=10;
}

void Bullet::rebuild(sf::Texture &texture,sf::Vector2f position,float damage)
{
    bullet_texture_=texture;
    picture_.setTexture(bullet_texture_);
    damage_=damage;
    position_=position;
    hitbox_r_=10;
}

void Bullet::initialize()
{
    behaviorlist_.clear();
    //dead_=false;
    exist_=true;
    grazed_=false;
    ofplayer_=true;
}

void Bullet::setDead(bool dead)
{
    dead_=dead;
}

void Bullet::setbelong(bool ofplayer)
{
    ofplayer_=ofplayer;
}

void Bullet::addBehavior(std::unique_ptr<Behavior> behavior)
{
    behaviorlist_.emplace_back(std::move(behavior));
}

void Bullet::markDead()
{
    dead_=true;
}

void Bullet::setActive(bool active)
{
    active_=active;
}

void Bullet::markGrazed()
{
    grazed_=true;
}

float Bullet::getDamage()
{
    return damage_;
}

/*
void Bullet::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
}
    */