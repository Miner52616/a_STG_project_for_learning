#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "phases/Phase.h"

//class Application;
class BulletManager;
class AimMove2;

class PhaseController
{
private:
    //Application &app_;
    std::vector<std::unique_ptr<Phase>> &phaselist_; 

    int current_;
    bool change_;

public:
    //PhaseController(Application &app,std::vector<std::unique_ptr<Phase>> &phaselist);
    PhaseController(std::vector<std::unique_ptr<Phase>> &phaselist);

    void add_process(std::unique_ptr<Phase> phase);
    void update();
    void render(sf::RenderWindow& window);
    void render(sf::RenderTexture& texture);
    void render_mid(sf::RenderTexture& texture);
    void be_damage(float damage);
    void ProcessCollision();
    Phase* getCurrentPhase() const;
    bool check_phase();
    void phase_change();
    bool apply_change();
    sf::Vector2f get_targetposition_for_LeiTan(AimMove2* move);
    sf::Vector2f get_closest_target(sf::Vector2f position);
};
