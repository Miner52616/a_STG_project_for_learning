#pragma once
#include <variant>
#include "behaviors/Behavior.h"

class Entity;
class Effect;

//这是直接速度追踪某个目标坐标点的AimMove
//越靠近目标点，速度越慢

class AimMove3:public Behavior
{
private:
    //Effect* entity_;
    std::variant<Effect*,Entity*> object_;
    sf::Vector2f targetposition_;
    float v_;

    sf::Vector2f nextposition_;

public:
    AimMove3(std::variant<Effect*,Entity*> object,float v,sf::Vector2f targetposition);
    //AimMove3(Entity* entity,float v,sf::Vector2f targetposition);
    //AimMove3(Effect* effect,float v,sf::Vector2f targetposition);
    void update() override;
    void process_update(Entity* entity);
    void process_update(Effect* effect);
};