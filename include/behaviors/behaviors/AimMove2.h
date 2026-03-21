#pragma once
#include "behaviors/Behavior.h"
#include "core/Clock.h"

class Entity;

enum class AimState
{
    DYNAMIC,
    LOCKED    
};

class AimMove2:public Behavior
{
private:
    Entity* entity_;
    sf::Vector2f startposition_;
    sf::Vector2f targetposition_;
    sf::Vector2f v_;
    sf::Vector2f nextposition_;
    float a_;
    AimState aimstate_=AimState::DYNAMIC;
    bool done_=false;
    Clock clock_;

    float low_v_=8;
    float noise_v_=1;
    float limit_low_v=low_v_;
    float limit_noise_v=noise_v_;
    float limit_a_=a_;

public:
    AimMove2(sf::Vector2f v,float a,Entity* entity,long long int time,Resource* resource);
    void update() override;
    void set_entity(Entity* entity);
    void set_v(sf::Vector2f v);
    void set_targetposition(sf::Vector2f position);
    sf::Vector2f get_v();
    void set_aimstate(AimState aimstate);
    void set_startposition(sf::Vector2f position);
    bool isDone();
    sf::Vector2f get_position();
};