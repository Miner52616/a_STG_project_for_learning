#include "phases/phases/VoidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "manager/CollisionSystem.h"
#include "entities/Player.h"

VoidPhase::VoidPhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,int target_frame,std::shared_ptr<Player> player):
    TimePhase(app,bulletmanager,collisionsystem,target_frame),player_(player)
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
    collisionsystem_.ProcessCollision(player_);
}