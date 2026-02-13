#include "manager/PhaseController.h"
#include "phases/basicphases/StartPhase.h"
#include <iostream>

PhaseController::PhaseController(application &app,std::vector<std::shared_ptr<Phase>> &phaselist):
    app_(app),phaselist_(phaselist),current_(1),change_(false)
{
    //phaselist_.emplace_back(std::make_unique<StartPhase>(app_,*this,bulletmanager_));
    ;
}

void PhaseController::add_process(std::shared_ptr<Phase> phase)
{
    std::cout<<"add a phase"<<std::endl;
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

void PhaseController::be_damage(float damage)
{
    phaselist_[current_-1]->be_damage(damage);
}

void PhaseController::ProcessCollision()
{
    phaselist_[current_-1]->ProcessCollision();
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
        std::cout<<"apply changing phase"<<std::endl;
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