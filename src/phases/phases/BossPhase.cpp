#include "phases/phases/BossPhase.h"
#include "entities/Player.h"

BossPhase::BossPhase(std::shared_ptr<Resourse> resourse,std::shared_ptr<Boss> boss):
    EventPhase(resourse),boss_(boss)
{
    ;
}

BossPhase::BossPhase(std::shared_ptr<Resourse> resourse):
    EventPhase(resourse)
{
    ;
}

void BossPhase::update()
//对于update，所有中间的阶层都只是传递update消息而已，具体工作交给最小单位做
{
    boss_->update();
    
    if(boss_->isBeaten())
    {
        change_=true;
    }
}

void BossPhase::render(sf::RenderWindow& window)
{
    boss_->render(window);
}

void BossPhase::setBoss(std::shared_ptr<Boss> boss)
{
    boss_=std::move(boss);
}

void BossPhase::be_damage(float damage)
{
    boss_->be_damage(damage);
}

void BossPhase::ProcessCollision()
{
    boss_->ProcessCollision();
}