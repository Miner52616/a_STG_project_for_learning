#include "phases/phases/BossPhase.h"
#include "entities/Player.h"

BossPhase::BossPhase(Resource* resource,YellowPage* yellowpage,Boss* boss):
    EventPhase(resource,yellowpage),boss_(boss)
{
    ;
}

BossPhase::BossPhase(Resource* resource,YellowPage* yellowpage):
    EventPhase(resource,yellowpage)
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

void BossPhase::render(sf::RenderTexture& texture)
{
    boss_->render(texture);
}

void BossPhase::setBoss(Boss* boss)
{
    boss_=boss;
}

void BossPhase::be_damage(float damage)
{
    boss_->be_damage(damage);
}

void BossPhase::ProcessCollision()
{
    boss_->ProcessCollision();
}