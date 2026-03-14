#include "phases/basicphases/StartPhase.h"
#include "manager/PhaseController.h"

StartPhase::StartPhase(Resource* resource,YellowPage* yellowpage):
    Phase(resource,yellowpage)

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