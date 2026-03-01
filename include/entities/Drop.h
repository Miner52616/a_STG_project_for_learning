#pragma once
#include "entities/Entity.h"
#include "behaviors/Behavior.h"
#include "packages/Resource.h"
#include "packages/DropConfig.h"
/*
enum class DropType
{
    Score,
    Power
};
*/

class Drop:public Entity
{
protected:
    std::shared_ptr<Resource> resource_;

    bool dead_=false;
    int getbox_r_;
    int phase_=1;
    DropType type_=DropType::Score;
    std::shared_ptr<Behavior> move1_;
    std::shared_ptr<Behavior> move2_;

    float v1_=-20;
    float v2_=30;
    float v2final_=30;
    float a_=0.5;

public:
    Drop(const sf::Texture &texture);
    void setResource(std::shared_ptr<Resource> resource);
    void setType(DropType type);
    void setPhase(int phase);
    void setMove(std::shared_ptr<Behavior> move1,std::shared_ptr<Behavior> move2);
    void markDead();
    int getGetbox_r();
    bool isDead();

    void update();
    void drawtexture(sf::RenderTexture& texture) override;
};