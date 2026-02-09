#pragma once
#include <SFML/Graphics.hpp>

class application;
class PhaseController;
class BulletManager;

class Phase
{
protected:
    application &app_;
//    PhaseController &phasecontroller_;
    BulletManager &bulletmanager_;

    bool change_;

public:
    Phase(application &app,BulletManager &bulletmanager);
    virtual void update()=0;
    virtual void render(sf::RenderWindow& window)=0;
    bool isFinish();

protected:
//    virtual void phase_change();
};