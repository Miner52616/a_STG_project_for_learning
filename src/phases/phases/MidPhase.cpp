#include "phases/phases/MidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "manager/CollisionSystem.h"
#include "entities/Player.h"

MidPhase::MidPhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,int target_frame,Player &player):
    TimePhase(app,bulletmanager,collisionsystem,target_frame),enemymanager_(enemylist_),player_(player)//,enemy1_(app_,app_.enemyTexture_,bulletmanager_,player_)
{
    enemy1_=std::make_unique<Enemy1>(app_,app_.enemyTexture_,bulletmanager_,player_);
    enemy1_->setHP(200);
    enemy1_->setPosition({460,100});
    enemy1_->set_start_end(240,216000);
    enemymanager_.add_process(std::move(enemy1_));
}

void MidPhase::update()
{
    enemymanager_.clear_dead();

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

void MidPhase::ProcessCollision()
{
    for(auto it=enemylist_.begin();it!=enemylist_.end();++it)
    {
        collisionsystem_.ProcessCollision(it->get());
    }
    collisionsystem_.ProcessCollision(&player_);
}