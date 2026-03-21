#include "phases/phases/MidPhase.h"
#include "core/application.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"
#include "manager/PhaseController.h"
#include "manager/CollisionSystem.h"
#include "entities/Player.h"
#include "behaviors/behaviors/AimMove2.h"
#include "mathematics/mathematics.h"

MidPhase::MidPhase(Resource* resource,YellowPage* yellowpage,int target_frame):
    TimePhase(resource,yellowpage,target_frame),enemymanager_(enemylist_)//,enemy1_(app_,app_.enemyTexture_,bulletmanager_,player_)
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

void MidPhase::render(sf::RenderTexture& texture)
{
    enemymanager_.render(texture);
}

void MidPhase::add_enemy(Enemy* enemy)
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
}

sf::Vector2f MidPhase::get_targetposition_for_LeiTan(AimMove2* move)
{
    sf::Vector2f position=move->get_position();
    sf::Vector2f targetposition={2500,2500};
    if(enemylist_.empty())
    {
        move->set_aimstate(AimState::LOCKED);
        return get_randomposition_for_LeiTan(move->get_v());
    }

    for(auto it=enemylist_.begin();it!=enemylist_.end();++it)
    {
        if(((*it)->getPosition()-position).length()<(targetposition-position).length()&&(*it)->isExist())
        {
            targetposition=(*it)->getPosition();
        }
    }
    if(targetposition!=sf::Vector2f{2500,2500})
    {
        return targetposition;
    }
    else
    {
        move->set_aimstate(AimState::LOCKED);
        return get_randomposition_for_LeiTan(move->get_v());
    }
    //return get_randomposition_for_LeiTan(move->get_v());
}