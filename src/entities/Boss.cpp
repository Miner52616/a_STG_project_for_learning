#include "entities/Boss.h"
#include "phases/phases/SpellPhase.h"

Boss::Boss(const sf::Texture &texture,Resource* resource):
    Entity(texture),resource_(resource),phasecontroller_(resource->app_,phaselist_),beaten_(false)
{
    hitbox_r_=80;
}

void Boss::update()
{
    store_position();
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

void Boss::add_phase(std::unique_ptr<Phase> spellphase)
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

bool Boss::isDead() const
{
    //std::cout<<(((SpellPhase*)(phasecontroller_.getCurrentPhase()))->isDead())<<std::endl;
    return (((SpellPhase*)(phasecontroller_.getCurrentPhase()))->isDead());
}