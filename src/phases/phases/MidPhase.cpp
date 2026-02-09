#include "phases/phases/MidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "entities/Player.h"

MidPhase::MidPhase(application &app,BulletManager &bulletmanager,int target_frame,Player &player):
    TimePhase(app,bulletmanager,target_frame),enemymanager_(enemylist_),player_(player),enemy1_(app_,app_.enemyTexture_,bulletmanager_,player_)
{
    enemy1_.setPosition({460,100});
    enemy1_.set_start_end(240,216000);
    enemymanager_.add_process(&enemy1_);
}

void MidPhase::update()
{
    enemymanager_.update(frame_);
    bulletmanager_.update();
    frame_++;

    if(frame_>=target_frame_)
    {
        enemymanager_.clear();
        change_=true;
    }
}

void MidPhase::render(sf::RenderWindow& window)
{
    enemymanager_.render(window);
    bulletmanager_.render(window);
}

void MidPhase::be_damage(float damage)
{
    ;
}