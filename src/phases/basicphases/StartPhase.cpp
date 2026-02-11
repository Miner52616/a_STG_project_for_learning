#include "phases/basicphases/StartPhase.h"
#include "manager/PhaseController.h"

StartPhase::StartPhase(std::shared_ptr<Resource> resource):
    Phase(resource)

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