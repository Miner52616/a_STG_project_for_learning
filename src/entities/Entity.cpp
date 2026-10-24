#include "entities/Entity.h"
#include "core/Application.h"
#include <iostream>

Entity::Entity(/*Application &app,*/const sf::Texture &texture):
    /*app_(app),*/texture_(texture),hitbox_r_(5),picture_(texture_),//middle_picture_(texture_),
    position_({0,0}),prev_position_({0,0})
{
    hitbox_.setRadius(hitbox_r_);

    hitbox_.setOrigin(hitbox_.getGlobalBounds().getCenter());
    picture_.setOrigin(picture_.getGlobalBounds().getCenter());
    for(int i=1;i<=picture_list_size_;i++)
    {
        middle_picture_list_.emplace_back(texture_);
        middle_position_list_.emplace_back(sf::Vector2f{0,0});
    }
    for(auto it=middle_picture_list_.begin();it!=middle_picture_list_.end();++it)
    {
        it->setOrigin(it->getGlobalBounds().getCenter());
    }
    //middle_picture_.setOrigin(middle_picture_.getGlobalBounds().getCenter());

    setPosition();
}

void Entity::setPosition()
{
    hitbox_.setPosition(position_);
    picture_.setPosition(position_);
}

void Entity::setPosition(sf::Vector2f position)
{
    position_=position;
    setPosition();
}

void Entity::setMiddlePosition()
{
    if(prev_position_==(sf::Vector2f{0,0}))
    {
        //middle_position_=position_;
        for(auto it=middle_position_list_.begin();it!=middle_position_list_.end();++it)
        {
            (*it)=position_;
        }
    }
    else
    {
        //middle_position_=0.5f*(prev_position_+position_);
        for(int i=1;i<=picture_list_size_;i++)
        {
            middle_position_list_[i-1]=(static_cast<float>(i)/static_cast<float>(picture_list_size_+1))*position_+(static_cast<float>(picture_list_size_+1-i)/static_cast<float>(picture_list_size_+1))*prev_position_;
        }
    }
    //middle_picture_.setPosition(middle_position_);
    for(int i=1;i<=picture_list_size_;i++)
    {
        middle_picture_list_[i-1].setPosition(middle_position_list_[i-1]);
    }
}

void Entity::store_position()
{
    prev_position_=position_;
}

sf::Vector2f Entity::getPosition()
{
    return position_;
}

sf::Vector2f Entity::getprevPosition()
{
    return prev_position_;
}

int Entity::getHitbox_r()
{
    return hitbox_r_;
}

void Entity::drawwindow(sf::RenderWindow& window)
{
    window.draw(picture_);
    //window.draw(hitbox_);
}

void Entity::drawtexture(sf::RenderTexture& texture)
{
    texture.draw(picture_);
    //texture.draw(hitbox_);
}

void Entity::drawwindow_mid(sf::RenderWindow& window,int num)
{
    window.draw(middle_picture_list_[num-1]);
    //window.draw(hitbox_);
}

void Entity::drawtexture_mid(sf::RenderTexture& texture,int num)
{
    texture.draw(middle_picture_list_[num-1]);
    //texture.draw(hitbox_);
}