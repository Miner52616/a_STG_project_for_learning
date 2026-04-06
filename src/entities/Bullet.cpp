#include "entities/Bullet.h"
#include "behaviors/Behavior.h"
#include "mathematics/mathematics.h"
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
    
    update_table[bulletconfig_->bulletclass_](*this,yellowpage_);

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
    dead_=false;
    exist_=true;
    grazed_=false;
    ofplayer_=true;
}

void Bullet::setBulletConfig(std::unique_ptr<BulletConfig> bulletconfig)
{
    bulletconfig_=std::move(bulletconfig);
}

void Bullet::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
}

void Bullet::setDead(bool dead)
{
    dead_=dead;
}

void Bullet::setbelong(bool ofplayer)
{
    ofplayer_=ofplayer;
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

//************************************************************** */
void aim_move1(Bullet& bullet,YellowPage* yellowpage)
{
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*(bullet.bulletconfig_->target_point_-bullet.getPosition()));
}

void direct_move1(Bullet& bullet,YellowPage* yellowpage)
{
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*normalize(bullet.bulletconfig_->direction_));
}

UpdateFunc update_table[]=
{
    aim_move1,
    direct_move1
};