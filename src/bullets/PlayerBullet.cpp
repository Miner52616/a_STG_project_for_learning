#include "bullets/PlayerBullet.h"
#include "core/application.h"
#include "ui/Frame.h"

PlayerBullet::PlayerBullet(sf::Texture &texture,sf::Vector2f position):
    Bullet(texture,position)
{
    hitbox_r_=10;
}

PlayerBullet::PlayerBullet(sf::Texture &texture,sf::Vector2f position,float damage):
    Bullet(texture,position,damage)
{
    hitbox_r_=10;
}

void PlayerBullet::setv(float v)
{
    v_=v;
}

void PlayerBullet::update()
{
    prev_position_=position_;

    setPosition({getPosition().x,getPosition().y-v_});

    if((getPosition().x<0)||(getPosition().y<-50)||(getPosition().x>770)||(getPosition().y>900))
    {
        dead_=true;
    }
}