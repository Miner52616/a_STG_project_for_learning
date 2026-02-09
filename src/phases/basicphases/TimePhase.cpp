#include "phases/basicphases/TimePhase.h"
#include "manager/PhaseController.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"

TimePhase::TimePhase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem,int target_frame):
    Phase(app,bulletmanager,collisionsystem),frame_(0),target_frame_(target_frame)
{
    ;
}

void TimePhase::frame_forward()
{
    frame_++;
}

bool TimePhase::isTimeup()
{
    if(frame_>=target_frame_)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*
void TimePhase::update()
{
    
    enemymanager_.update(frame_);
    bulletmanager_.update();
    frame_++;

    if(frame_>=target_frame_)
    {
        enemymanager_.clear();
        change_=true;
    }
        

    if(frame_>=target_frame_)
    {
        enemymanager_.clear();
        phasecontroller_.phase_change();
    }
}

void TimePhase::render(sf::RenderWindow& window)
{
    enemymanager_.render(window);
    bulletmanager_.render(window);
}
    */