#include "entities/Bullet.h"
#include "behaviors/Behavior.h"
#include "mathematics/mathematics.h"
#include "manager/PhaseController.h"
#include <iostream>

Bullet::Bullet(sf::Texture &texture,sf::Vector2f position):
    Entity(texture),bullet_texture_(&texture),exist_(true),dead_(false),active_(false),grazed_(false),ofplayer_(true),damage_(100)
{
    bulletconfig_=std::make_unique<BulletConfig>(texture);
    position_=position;
    hitbox_r_=10;
    hitbox_draw_.setRadius(hitbox_r_);
    hitbox_draw_.setOrigin(hitbox_draw_.getLocalBounds().getCenter());
}

Bullet::Bullet(sf::Texture &texture,sf::Vector2f position,float damage):
    Entity(texture),bullet_texture_(&texture),exist_(true),dead_(false),active_(false),grazed_(false),ofplayer_(true),damage_(damage)
{
    bulletconfig_=std::make_unique<BulletConfig>(texture);
    position_=position;
    hitbox_r_=10;
    hitbox_draw_.setRadius(hitbox_r_);
    hitbox_draw_.setOrigin(hitbox_draw_.getLocalBounds().getCenter());
}

void Bullet::selfbehavior()
{
    switch (bulletconfig_->bulletbehavior_)
    {
    case BulletBehavior::Fix:
        {
            break;
        }
    
    case BulletBehavior::Rotate:
        {
            picture_.rotate(sf::degrees(3));
            break;
        }

    case BulletBehavior::Direct:
        {
            picture_.setRotation(sf::degrees(bulletconfig_->angle_));
            break;
        }
    
    default:
        break;
    }
}

void Bullet::update()
{
    store_position();
    
    update_table[bulletconfig_->bulletclass_](*this,yellowpage_,resource_);
    selfbehavior();

    if(isOut())
    {
        //std::cout<<getPosition().x<<" "<<getPosition().y<<std::endl;
        markDead();
    }
}

void Bullet::drawtexture(sf::RenderTexture& texture)
{
    texture.draw(picture_);
    if(show_hitbox_)
    {
        texture.draw(hitbox_draw_);
    }
}

void Bullet::setPosition(sf::Vector2f position)
{
    Entity::setPosition(position);
    hitbox_draw_.setPosition(position);
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
    if(getPosition().x<=-100||getPosition().y<=-100||getPosition().x>=870||getPosition().y>=1000)
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
    bullet_texture_=&texture;
    picture_.setTexture(*bullet_texture_,true);
    picture_.setScale({1.414,1.414});
    picture_.setOrigin(picture_.getLocalBounds().getCenter());
    position_=position;
    hitbox_r_=5;
    hitbox_draw_.setRadius(hitbox_r_);
    hitbox_draw_.setOrigin(hitbox_draw_.getLocalBounds().getCenter());
}

void Bullet::rebuild(sf::Texture &texture,sf::Vector2f position,float damage)
{
    bullet_texture_=&texture;
    picture_.setTexture(*bullet_texture_,true);
    picture_.setScale({1.414,1.414});
    picture_.setOrigin(picture_.getLocalBounds().getCenter());
    damage_=damage;
    position_=position;
    hitbox_r_=5;
    hitbox_draw_.setRadius(hitbox_r_);
    hitbox_draw_.setOrigin(hitbox_draw_.getLocalBounds().getCenter());
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

BulletConfig* Bullet::getBulletConfig()
{
    return bulletconfig_.get();
}


void Bullet::setYellowPage(YellowPage* yellowpage)
{
    yellowpage_=yellowpage;
}

void Bullet::setResource(Resource* resource)
{
    resource_=resource;
}

void Bullet::setDead(bool dead)
{
    dead_=dead;
}

void Bullet::setHitbox_r(int r)
{
    hitbox_r_=r;
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
void aim_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*(bullet.bulletconfig_->target_point_-bullet.getPosition()));
}

void aim_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    sf::Vector2f target=resource->phasecontroller_.get_closest_target(bullet.getPosition());
    if(target!=(sf::Vector2f{2500,2500}))
    {
        sf::Vector2f a_direction=target-bullet.getPosition();
        a_direction=bullet.bulletconfig_->a_*normalize(a_direction);
        sf::Vector2f direction=bullet.bulletconfig_->v_*bullet.bulletconfig_->direction_+a_direction;
        direction=normalize(direction);
        bullet.bulletconfig_->direction_=direction;
    }
    
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*bullet.bulletconfig_->direction_);
}

void direct_move1(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*normalize(bullet.bulletconfig_->direction_));
}

void direct_move2(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    if(!bullet.bulletconfig_->clock1_.get_condition())
    {
        bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*normalize(bullet.bulletconfig_->direction_));
    }
    else
    {
        bullet.bulletconfig_->v_=bullet.bulletconfig_->v_+bullet.bulletconfig_->a_;
        if(bullet.bulletconfig_->v_>bullet.bulletconfig_->v2_)
        {
            bullet.bulletconfig_->v_=bullet.bulletconfig_->v2_;
        }
        bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*normalize(bullet.bulletconfig_->direction_));
    }
    bullet.bulletconfig_->clock1_.count();
}

void direct_move3(Bullet& bullet,YellowPage* yellowpage,Resource* resource)
{
    if(!bullet.bulletconfig_->clock3_.get_condition())
    {
        bullet.setPosition(bullet.getPosition());
        bullet.bulletconfig_->clock3_.count();
    }
    else
    {
        if(!bullet.bulletconfig_->clock2_.get_condition())
        {
            bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v3_*bullet.bulletconfig_->direction2_);
            //std::cout<<bullet.bulletconfig_->direction2_.x<<" "<<bullet.bulletconfig_->direction2_.y<<std::endl;
            bullet.bulletconfig_->v3_=bullet.bulletconfig_->v3_+bullet.bulletconfig_->a2_;
            bullet.bulletconfig_->clock2_.count();
        }
        else
        {
            if(!bullet.bulletconfig_->clock1_.get_condition())
            {
                bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*normalize(bullet.bulletconfig_->direction_));
                bullet.bulletconfig_->clock1_.count();
            }
            else
            {
                bullet.bulletconfig_->v_=bullet.bulletconfig_->v_+bullet.bulletconfig_->a_;
                if(bullet.bulletconfig_->v_>bullet.bulletconfig_->v2_)
                {
                    bullet.bulletconfig_->v_=bullet.bulletconfig_->v2_;
                }
                bullet.setPosition(bullet.getPosition()+bullet.bulletconfig_->v_*normalize(bullet.bulletconfig_->direction_));
            }
        }
    }
}

UpdateFunc update_table[]=
{
    aim_move1,
    direct_move1,
    direct_move1,
    direct_move2,
    aim_move2,
    direct_move3
};