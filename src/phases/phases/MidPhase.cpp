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

void MidPhase::add_enemy(std::unique_ptr<Enemy> enemy)
{
    enemymanager_.add_process(std::move(enemy));
}

void MidPhase::be_damage(float damage)
{
    ;
}

void MidPhase::ProcessCollision()
{
    for(auto it=enemylist_.begin();it!=enemylist_.end();++it)
    {
        resource_->collisionsystem_.ProcessCollision((*it).get());
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
        float x1=((*it)->getPosition()-position).x;
        float y1=((*it)->getPosition()-position).y;
        float x2=(targetposition-position).x;
        float y2=(targetposition-position).y;
        float length1=x1*x1+y1*y1;
        float length2=x2*x2+y2*y2;

        if((length1<length2)&&(*it)->isExist())
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

sf::Vector2f MidPhase::get_closest_target(sf::Vector2f position)
{
    //{2500,2500}是默认值，接收到这个时按无索敌对象处理
    //而且{2500,2500}足够大，可以保证最近索敌求min
    sf::Vector2f targetposition={2500,2500};
    
    for(auto it=enemylist_.begin();it!=enemylist_.end();++it)
    {
        float x1=((*it)->getPosition()-position).x;
        float y1=((*it)->getPosition()-position).y;
        float x2=(targetposition-position).x;
        float y2=(targetposition-position).y;
        float length1=x1*x1+y1*y1;
        float length2=x2*x2+y2*y2;

        if((length1<length2)&&(*it)->isExist())
        {
            targetposition=(*it)->getPosition();
        }
    }

    return targetposition;
}