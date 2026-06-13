#include "behaviors/behaviors/NonSpell3.h"
#include "behaviors/behaviors/BasicShooter.h"
#include "mathematics/mathematics.h"
#include "entities/Entity.h"
#include "core/application.h"
#include "manager/BatchManager.h"

NonSpell3::NonSpell3(Entity* entity,Resource* resource,YellowPage* yellowpage):
    ShootBehavior(resource,yellowpage),entity_(entity),bulletconfig_(resource->app_.bulletsheetTexture_),
    draw_clock_(120),
    line_bullet_num_(11),
    gap_(15),
    shoot_clock_gap_(1),
    current_batch_(nullptr)
{
    setBulletConfig();
    setBatchConfig();
    //draw_clock_.reset();

    ShootLine line1=ShootLine(entity,resource,yellowpage,&bulletconfig_,&effectconfig_);
    ShootLine line2=ShootLine(entity,resource,yellowpage,&bulletconfig_,&effectconfig_);
    ShootLine line3=ShootLine(entity,resource,yellowpage,&bulletconfig_,&effectconfig_);
    ShootLine line4=ShootLine(entity,resource,yellowpage,&bulletconfig_,&effectconfig_);
    ShootLine line5=ShootLine(entity,resource,yellowpage,&bulletconfig_,&effectconfig_);

    lines_.emplace_back(line1);
    lines_.emplace_back(line2);
    lines_.emplace_back(line3);
    lines_.emplace_back(line4);
    lines_.emplace_back(line5);

    /*
    for(auto it=lines_.begin();it!=lines_.end();++it)
    {
        it->setReady();
        it->setBulletNum(11);
        it->setGap(3);
        it->setShootClock(1);
    }
        */
    sf::Vector2f direction=roundwithCenter({0,0},{0,-1},18);
    for(int i=1;i<=5;i++)
    {
        lines_[i-1].reset();
        //int bullet_num=11;
        lines_[i-1].setBulletNum(line_bullet_num_);
        lines_[i-1].setGap(gap_);
        //int shoot_clock=1;
        lines_[i-1].setDrawClock(9999);
        lines_[i-1].setShootClock(shoot_clock_gap_);
        lines_[i-1].setDelay((i-1)*line_bullet_num_);
        lines_[i-1].setDirection(direction);
        direction=roundwithCenter({0,0},direction,144);
    }
}

void NonSpell3::setBulletConfig()
{
    /*
    bulletconfig_.r_=5;
    bulletconfig_.bulletclass_=DirectBullet1;
    bulletconfig_.bulletbehavior_=Rotate;
    bulletconfig_.bulletsize_=Small;
    bulletconfig_.bullet_index_={7,11};

    //bulletconfig_.shareconfig_.active_=true;

    bulletconfig_.v_=0;
    bulletconfig_.v2_=6;
    bulletconfig_.a_=0.08;
    bulletconfig_.rotate_angle_=1;
    */
    bulletconfig_.r_=5;
    bulletconfig_.bulletclass_=PhaseCenterRotateExpandBullet1;
    bulletconfig_.bulletbehavior_=Rotate;
    bulletconfig_.bulletsize_=Small;
    bulletconfig_.bullet_index_={7,11};

    //bulletconfig_.shareconfig_.active_=true;

    bulletconfig_.v_=0;
    bulletconfig_.v2_=6;
    bulletconfig_.a_=0.08;
    bulletconfig_.rotate_angle_=1;
}

void NonSpell3::setBatchConfig()
{
    batchconfig_.target_time_=120;
    batchconfig_.update_func_=
    [](Batch* batch)
    {
        if(batch->clock_.get_condition())
        {
            batch->phase_=2;
        }
        batch->clock_.count();        
    };
}

void NonSpell3::update()
{
    for(auto it=lines_.begin();it!=lines_.end();++it)
    {
        it->update();
    }

    if(draw_clock_.get_condition())
    {
        draw_clock_.reset();
        sf::Vector2f center=entity_->getPosition();
        sf::Vector2f direction=roundwithCenter({0,0},{0,-(line_bullet_num_-1)*gap_*0.5/0.951056},-144);
        for(int i=1;i<=5;i++)
        {
            lines_[i-1].setReady();
            lines_[i-1].setStartPosition(center+direction);
            lines_[i-1].setDirection(normalize(roundwithCenter({0,0},direction,162)));
            direction=roundwithCenter({0,0},direction,144);
        }
        
        if(current_batch_!=nullptr)
        {
            current_batch_->set_add_finished();
        }
        bulletconfig_.center_point_=center;
        current_batch_=resource_->batchmanager_.add_process(&batchconfig_);
        current_batch_->bundle_config(&bulletconfig_);
    }
    draw_clock_.count();
}
