#include "phases/phases/VoidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "manager/CollisionSystem.h"
#include "entities/Player.h"
#include "mathematics/mathematics.h"
#include "behaviors/behaviors/AimMove2.h"

VoidPhase::VoidPhase(Resource* resource,YellowPage* yellowpage,int target_frame):
    TimePhase(resource,yellowpage,target_frame)
{
    ;
}

void VoidPhase::update()
{
    frame_forward();

    if(isTimeup())
    {
        change_=true;
    }
}

void VoidPhase::render(sf::RenderWindow& window)
{
    ;
}

void VoidPhase::render(sf::RenderTexture& texture)
{
    ;
}

void VoidPhase::be_damage(float damage)
{
    ;
}

void VoidPhase::ProcessCollision()
{
    ;
}

sf::Vector2f VoidPhase::get_targetposition_for_LeiTan(AimMove2* move)
{
    move->set_aimstate(AimState::LOCKED);
    return get_randomposition_for_LeiTan(move->get_v());
}