#include "phases/basicphases/StartPhase.h"
#include "manager/PhaseController.h"

StartPhase::StartPhase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager):
    Phase(app,phasecontroller,bulletmanager)

{
    ;
}

void StartPhase::update()
{
    phasecontroller_.phase_change();
} 

void StartPhase::render(sf::RenderWindow& window)
{
    ;
}