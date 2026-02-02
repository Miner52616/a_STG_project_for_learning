#include "bullets/LinearBullet.h"

LinearBullet::LinearBullet(application &app,const sf::Texture &texture,sf::Vector2f position,sf::Vector2f targetposition,float v,int r):
    Bullet(app,texture,position),targetposition_(targetposition),v_(v)
{
    hitbox_r_=r;
    ofplayer_=false;
}

void LinearBullet::update()
{
    prev_position_=getPosition();
    setPosition((targetposition_-getPosition())*v_+getPosition());

    if(isOut())
    {
        dead_=true;
    }
}