#pragma once
#include <SFML/Graphics.hpp>

class application;
class PhaseController;
class BulletManager;
class CollisionSystem;

class Phase
{
protected:
    application &app_;
//    PhaseController &phasecontroller_;
    BulletManager &bulletmanager_;
    CollisionSystem &collisionsystem_;

    bool change_;

public:
    Phase(application &app,BulletManager &bulletmanager,CollisionSystem &collisionsystem);
    virtual void update()=0;
    virtual void render(sf::RenderWindow& window)=0;
    bool isFinish();
    virtual void be_damage(float damage)=0;
    virtual void ProcessCollision()=0;

protected:
//    virtual void phase_change();
};