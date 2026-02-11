#include "phases/phases/VoidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "manager/CollisionSystem.h"
#include "entities/Player.h"

VoidPhase::VoidPhase(std::shared_ptr<Resourse> resourse,int target_frame):
    TimePhase(resourse,target_frame)
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

void VoidPhase::be_damage(float damage)
{
    ;
}

void VoidPhase::ProcessCollision()
{
    resourse_->collisionsystem_.ProcessCollision(resourse_->player_);
}