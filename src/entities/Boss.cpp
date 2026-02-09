#include "entities/Boss.h"

Boss::Boss(application &app,const sf::Texture &texture,BulletManager &bulletmanager):
    Entity(app,texture),bulletmanager_(bulletmanager),phasecontroller_(app,bulletmanager_,phaselist_),beaten_(false)
{
    ;
}

void Boss::update()
{
    phasecontroller_.update();
    if(!phasecontroller_.apply_change())
    {
        beaten_=true;
    }
}

void Boss::render(sf::RenderWindow& window)
{
    phasecontroller_.render(window);
}

void Boss::add_phase(std::unique_ptr<Phase> spellphase)
{
    phasecontroller_.add_process(std::move(spellphase));
}

PhaseController* Boss::getPhaseController()
{
    return &phasecontroller_;
}

bool Boss::isBeaten()
{
    return beaten_;
}