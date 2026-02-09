#include "phases/basicphases/StartPhase.h"
#include "manager/PhaseController.h"

StartPhase::StartPhase(application &app,BulletManager &bulletmanager):
    Phase(app,bulletmanager)

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