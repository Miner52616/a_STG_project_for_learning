#include "phases/phases/VoidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "entities/Player.h"

VoidPhase::VoidPhase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager,EnemyManager &enemymanager,int target_frame):
    TimePhase(app,phasecontroller,bulletmanager,enemymanager,target_frame)
{
    ;
}