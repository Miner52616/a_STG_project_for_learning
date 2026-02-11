#include "phases/phases/MidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "manager/CollisionSystem.h"
#include "entities/Player.h"

MidPhase::MidPhase(std::shared_ptr<Resource> resource,int target_frame):
    TimePhase(resource,target_frame),enemymanager_(enemylist_)//,enemy1_(app_,app_.enemyTexture_,bulletmanager_,player_)
{
//    enemy1_=std::make_shared<Enemy1>(app_,app_.enemyTexture_,bulletmanager_,player_);
//    enemy1_->setHP(200);
//    enemy1_->setPosition({460,100});
//    enemy1_->set_start_end(240,216000);
//    enemymanager_.add_process(enemy1_);
    ;
}

void MidPhase::update()
{
    enemymanager_.clear_dead();

    enemymanager_.update(frame_);
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
}

void MidPhase::add_enemy(std::shared_ptr<Enemy> enemy)
{
    enemymanager_.add_process(enemy);
}

void MidPhase::be_damage(float damage)
{
    ;
}

void MidPhase::ProcessCollision()
{
    for(auto it=enemylist_.begin();it!=enemylist_.end();++it)
    {
        resource_->collisionsystem_.ProcessCollision(*it);
    }
    resource_->collisionsystem_.ProcessCollision(resource_->player_);
}