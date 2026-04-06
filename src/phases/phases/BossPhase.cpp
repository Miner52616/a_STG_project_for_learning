#include "phases/phases/BossPhase.h"
#include "entities/Player.h"

BossPhase::BossPhase(Resource* resource,YellowPage* yellowpage,std::unique_ptr<Boss> boss):
    EventPhase(resource,yellowpage),boss_(std::move(boss))
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

void BossPhase::setBoss(std::unique_ptr<Boss> boss)
{
    boss_=std::move(boss);
}

Boss* BossPhase::getBoss()
{
    return boss_.get();
}

void BossPhase::be_damage(float damage)
{
    boss_->be_damage(damage);
}

void BossPhase::ProcessCollision()
{
    boss_->ProcessCollision();
}

sf::Vector2f BossPhase::get_targetposition_for_LeiTan(AimMove2* move)
{
    return boss_->getPhaseController()->get_targetposition_for_LeiTan(move);
}