#include "entities/Boss.h"

Boss::Boss(const sf::Texture &texture,std::shared_ptr<Resource> resource):
    Entity(texture),resource_(resource),phasecontroller_(resource->app_,phaselist_),beaten_(false)
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

void Boss::render(sf::RenderTexture& texture)
{
    phasecontroller_.render(texture);
}

void Boss::add_phase(std::shared_ptr<Phase> spellphase)
{
    phasecontroller_.add_process(std::move(spellphase));
}

PhaseController* Boss::getPhaseController()
{
    return &phasecontroller_;
}

void Boss::be_damage(float damage)
{
    phasecontroller_.be_damage(damage);
}

void Boss::ProcessCollision()
{
    phasecontroller_.ProcessCollision();
}

bool Boss::isBeaten()
{
    return beaten_;
}