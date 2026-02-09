#pragma once
#include "entities/Entity.h"
#include "phases/Phase.h"
#include "manager/PhaseController.h"

class BulletManager;

class Boss:public Entity
{
protected:
    BulletManager &bulletmanager_;//只是用于申请发射子弹

    std::vector<std::unique_ptr<Phase>> phaselist_;//只管怎么更新boss（移动与发弹），无需维护子弹
public:
    PhaseController phasecontroller_;
protected:
    bool beaten_;

public:
    Boss(application &app,const sf::Texture &texture,BulletManager &bulletmanager);
    virtual void update();
    virtual void render(sf::RenderWindow& window);
    void add_phase(std::unique_ptr<Phase> spellphase);
    PhaseController* getPhaseController();
    bool isBeaten();
};