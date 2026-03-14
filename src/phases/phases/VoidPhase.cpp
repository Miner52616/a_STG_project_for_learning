#include "phases/phases/VoidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "manager/CollisionSystem.h"
#include "entities/Player.h"

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
    resource_->collisionsystem_.ProcessCollision(yellowpage_->player_);
}