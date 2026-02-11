#include "phases/basicphases/StartPhase.h"
#include "manager/PhaseController.h"

StartPhase::StartPhase(std::shared_ptr<Resourse> resourse):
    Phase(resourse)

{
    ;
}
/*
void StartPhase::update()
{
    phasecontroller_.phase_change();
} 
    */

void StartPhase::render(sf::RenderWindow& window)
{
    ;
}