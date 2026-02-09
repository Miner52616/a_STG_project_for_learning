#include "phases/phases/SpellPhase.h"
#include "manager/BulletManager.h"
#include "manager/CollisionSystem.h"
#include "mathematics/mathematics.h"
#include "bullets/LinearBullet.h"
#include "entities/Boss.h"

SpellPhase::SpellPhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,int target_frame,Player &player):
    TimePhase(app,bulletmanager,collisionsystem,target_frame),player_(player),boss_(NULL),moveclock_(240),shootclock_(60),nextposition_(460,200),fullHP_(1000),HP_(1000)
{
    HPline_.setFillColor(sf::Color::White);
    HPline_.setPosition({80,35});
    HPline_.setSize({760,8});
}

void SpellPhase::update()
{
    HPline_.setSize({(760*HP_)/fullHP_,8});

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
    window.draw(HPline_);
    bulletmanager_.render(window);
}

void SpellPhase::be_damage(float damage)
{
    HP_=HP_-damage;
}

void SpellPhase::ProcessCollision()
{
    collisionsystem_.ProcessCollision(boss_);
    collisionsystem_.ProcessCollision(&player_);
}

void SpellPhase::setBoss(Boss *boss)
{
    boss_=boss;
}