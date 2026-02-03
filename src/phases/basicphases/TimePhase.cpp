#include "phases/basicphases/TimePhase.h"
#include "manager/PhaseController.h"
#include "manager/EnemyManager.h"
#include "manager/BulletManager.h"

TimePhase::TimePhase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager,EnemyManager& enemymaanager,int target_frame):
    Phase(app,phasecontroller,bulletmanager),frame_(0),enemymanager_(enemymaanager),target_frame_(target_frame)
{
    ;
}

void TimePhase::frame_forward()
{
    frame_++;
}

void TimePhase::update()
{
    enemymanager_.update(frame_);
    bulletmanager_.update();
    frame_++;

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