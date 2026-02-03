#include "entities/Boss.h"

Boss::Boss(application &app,const sf::Texture &texture,BulletManager &bulletmanager):
    Entity(app,texture),bulletmanager_(bulletmanager),phasecontroller_(app,bulletmanager_,phaselist_)
{
    ;
}

void Boss::update()
{
    phasecontroller_.update();
}