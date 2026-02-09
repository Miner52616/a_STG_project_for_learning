#include "phases/phases/SpellPhase.h"
#include "manager/BulletManager.h"
#include "mathematics/mathematics.h"
#include "bullets/LinearBullet.h"
#include "entities/Boss.h"

SpellPhase::SpellPhase(application &app,BulletManager &bulletmanager,int target_frame,Player &player):
    TimePhase(app,bulletmanager,target_frame),player_(player),boss_(NULL),moveclock_(240),shootclock_(60),nextposition_(460,200)
{
    ;
}

void SpellPhase::update()
{
    boss_->store_position();
    boss_->setPosition((nextposition_-boss_->getPosition())*0.01f+boss_->getPosition());
    if(moveclock_.get_condition())
    {
        nextposition_={getRandomNum(125,795),getRandomNum(20,300)};
        moveclock_.reset();
    }

    bulletmanager_.update();
    if(shootclock_.get_condition())
    {
        bulletmanager_.add_process(std::make_unique<LinearBullet>(app_,app_.bulletTexture_,boss_->getPosition(),player_.getPosition(),0.06,6));
        shootclock_.reset();
    }

    moveclock_.count();
    shootclock_.count();
    frame_++;

    if(isTimeup())
    {
        change_=true;
    }
}

void SpellPhase::render(sf::RenderWindow& window)
{
    boss_->drawwindow(window);
    bulletmanager_.render(window);
}

void SpellPhase::setBoss(Boss *boss)
{
    boss_=boss;
}