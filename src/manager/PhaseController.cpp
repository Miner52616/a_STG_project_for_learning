#include "manager/PhaseController.h"
#include "phases/basicphases/StartPhase.h"
#include <iostream>

PhaseController::PhaseController(application &app,BulletManager &bulletmanager,std::vector<std::unique_ptr<Phase>> &phaselist):
    app_(app),bulletmanager_(bulletmanager),phaselist_(phaselist),current_(1),change_(false)
{
    //phaselist_.emplace_back(std::make_unique<StartPhase>(app_,*this,bulletmanager_));
    ;
}

void PhaseController::add_process(std::unique_ptr<Phase> phase)
{
    phaselist_.emplace_back(std::move(phase));
}

void PhaseController::update()
{
    if (phaselist_.empty()) return;
    if (current_ > phaselist_.size())
    {
        std::cout<<"invalid"<<std::endl;
        return;
    }

    phaselist_[current_-1]->update();
    check_phase();
}

void PhaseController::render(sf::RenderWindow& window)
{
    if (phaselist_.empty()) return;
    if (current_ > phaselist_.size()) return;

    phaselist_[current_-1]->render(window);
}

bool PhaseController::check_phase()
{
    if(phaselist_[current_-1]->isFinish())
    {
        phase_change();
        return true;
    }
    else
    {
        return false;
    }
}

void PhaseController::phase_change()
{
    change_=true;
}

bool PhaseController::apply_change()
{
    if(change_)
    {
        change_=false;
        if(current_+1<=phaselist_.size())
        {
            current_++;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}