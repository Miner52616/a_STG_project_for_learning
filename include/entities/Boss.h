#pragma once
#include "entities/Entity.h"
#include "phases/Phase.h"
#include "manager/PhaseController.h"

class BulletManager;

class Boss:public Entity
{
protected:
    //BulletManager &bulletmanager_;//只是用于申请发射子弹
    std::shared_ptr<Resourse> resourse_;

    std::vector<std::shared_ptr<Phase>> phaselist_;//只管怎么更新boss（移动与发弹），无需维护子弹
    PhaseController phasecontroller_;

    bool beaten_;

public:
    Boss(const sf::Texture &texture,std::shared_ptr<Resourse> resourse);
    virtual void update();
    virtual void render(sf::RenderWindow& window);
    void add_phase(std::shared_ptr<Phase> spellphase);
    PhaseController* getPhaseController();
    void be_damage(float damage);
    void ProcessCollision();
    bool isBeaten();
};