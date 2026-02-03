#pragma once
#include <SFML/Graphics.hpp>

class application;
class PhaseController;
class BulletManager;

class Phase
{
protected:
    application &app_;
    PhaseController &phasecontroller_;
    BulletManager &bulletmanager_;

public:
    Phase(application &app,PhaseController &phasecontroller,BulletManager &bulletmanager);
    virtual void update()=0;
    virtual void render(sf::RenderWindow& window)=0;

protected:
    virtual void phase_change();
};