#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "phases/Phase.h"

class application;
class BulletManager;
class AimMove2;

class PhaseController
{
private:
    application &app_;
    std::vector<std::unique_ptr<Phase>> &phaselist_; 

    int current_;
    bool change_;

public:
    PhaseController(application &app,std::vector<std::unique_ptr<Phase>> &phaselist);

    void add_process(std::unique_ptr<Phase> phase);
    void update();
    void render(sf::RenderWindow& window);
    void render(sf::RenderTexture& texture);
    void be_damage(float damage);
    void ProcessCollision();
    bool check_phase();
    void phase_change();
    bool apply_change();
    sf::Vector2f get_targetposition_for_LeiTan(AimMove2* move);
};