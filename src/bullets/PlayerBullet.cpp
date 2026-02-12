#include "bullets/PlayerBullet.h"
#include "core/application.h"
#include "ui/Frame.h"

PlayerBullet::PlayerBullet(const sf::Texture &texture,sf::Vector2f position):
    Bullet(texture,position)
{
    hitbox_r_=10;
}

void PlayerBullet::update()
{
    prev_position_=position_;

    setPosition({getPosition().x,getPosition().y-12});

    if((getPosition().x<75)||(getPosition().y<-50)||(getPosition().x>845)||(getPosition().y>930))
    {
        dead_=true;
    }
}