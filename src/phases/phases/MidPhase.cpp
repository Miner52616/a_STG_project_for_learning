#include "phases/phases/MidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "entities/Player.h"

MidPhase::MidPhase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager,EnemyManager &enemymanager,int target_frame,Player &player):
    TimePhase(app,phasecontroller,bulletmanager,enemymanager,target_frame),player_(player),enemy1_(app_,app_.enemyTexture_,bulletmanager_,player_)
{
    enemy1_.setPosition({460,100});
    enemy1_.set_start_end(240,216000);
    enemymanager_.add_process(&enemy1_);
}