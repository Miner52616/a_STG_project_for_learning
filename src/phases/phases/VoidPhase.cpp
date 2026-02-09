#include "phases/phases/VoidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "entities/Player.h"

VoidPhase::VoidPhase(application &app,BulletManager &bulletmanager,int target_frame):
    TimePhase(app,bulletmanager,target_frame)
{
    ;
}

void VoidPhase::update()
{
    bulletmanager_.update();
    frame_forward();

    if(isTimeup())
    {
        change_=true;
    }
}

void VoidPhase::render(sf::RenderWindow& window)
{
    bulletmanager_.render(window);
}

void VoidPhase::be_damage(float damage)
{
    ;
}