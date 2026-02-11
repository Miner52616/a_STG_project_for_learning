#include "phases/phases/SpellPhase.h"
#include "manager/BulletManager.h"
#include "manager/CollisionSystem.h"
#include "mathematics/mathematics.h"
#include "bullets/LinearBullet.h"
#include "entities/Boss.h"

SpellPhase::SpellPhase(std::shared_ptr<Resourse> resourse,int target_frame):
    TimePhase(resourse,target_frame),boss_(NULL),moveclock_(240),shootclock_(60),nextposition_(460,200),fullHP_(1000),HP_(1000)
{
    setHP(600);
    HPline_.setFillColor(sf::Color::White);
    HPline_.setPosition({80,35});
    HPline_.setSize({760,8});
}

void SpellPhase::update()
{
    HPline_.setSize({(760*HP_)/fullHP_,8});

    for(auto it=behaviorlist_.begin();it!=behaviorlist_.end();++it)
    {
        (*it)->update();
    }
    /*
    boss_->store_position();
    boss_->setPosition((nextposition_-boss_->getPosition())*0.01f+boss_->getPosition());
    if(moveclock_.get_condition())
    {
        nextposition_={getRandomNum(125,795),getRandomNum(20,300)};
        moveclock_.reset();
    }

    if(shootclock_.get_condition())
    {
        bulletmanager_.add_process(std::make_unique<LinearBullet>(app_,app_.bulletTexture_,boss_->getPosition(),player_->getPosition(),0.06,6));
        shootclock_.reset();
    }
*/
    moveclock_.count();
    shootclock_.count();
    frame_++;

    if(isTimeup()||HP_<=0)
    {
        change_=true;
    }
}

void SpellPhase::render(sf::RenderWindow& window)
{
    boss_->drawwindow(window);
    window.draw(HPline_);
}

void SpellPhase::addBehavior(std::shared_ptr<Behavior> behavior)
{
    behaviorlist_.emplace_back(std::move(behavior));
}

void SpellPhase::setHP(float HP)
{
    fullHP_=HP;
    HP_=HP;
}

void SpellPhase::be_damage(float damage)
{
    HP_=HP_-damage;
}

void SpellPhase::ProcessCollision()
{
    resourse_->collisionsystem_.ProcessCollision(boss_);
    resourse_->collisionsystem_.ProcessCollision(resourse_->player_);
}

void SpellPhase::setBoss(std::shared_ptr<Boss> boss)
{
    boss_=boss;
}