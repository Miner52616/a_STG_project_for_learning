#include "phases/phases/BossPhase.h"
#include "entities/Player.h"

BossPhase::BossPhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,Boss *boss,Player &player):
    EventPhase(app,bulletmanager,collisionsystem),boss_(boss),player_(player)
{
    boss_->setPosition({460,100});
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

void BossPhase::be_damage(float damage)
{
    boss_->be_damage(damage);
}

void BossPhase::ProcessCollision()
{
    boss_->ProcessCollision();
}