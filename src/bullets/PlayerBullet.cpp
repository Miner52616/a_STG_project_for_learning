#include "bullets/PlayerBullet.h"
#include "core/application.h"
#include "ui/Frame.h"

PlayerBullet::PlayerBullet(const sf::Texture &texture,sf::Vector2f position,Frame &outline):
    Bullet(texture,position),outline_(outline)
{
    hitbox_r_=10;
}

void PlayerBullet::update()
{
    prev_position_=position_;

    setPosition({getPosition().x,getPosition().y-12});

    if((getPosition().x<outline_.getBounds_left())||(getPosition().y<-50)||(getPosition().x>outline_.getBounds_right())||(getPosition().y>outline_.getBounds_bottom()))
    {
        dead_=true;
    }
}