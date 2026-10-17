#pragma once
#include "entities/Entity.h"
#include "behaviors/Behavior.h"
#include "packages/Resource.h"
#include "packages/YellowPage.h"
#include "packages/DropConfig.h"
#include "packages/EffectConfig.h"
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
    Resource* resource_;
    YellowPage* yellowpage_;

    bool dead_=false;
    int getbox_r_;
    int phase_=1;
    DropType type_=DropType::Score;
    std::shared_ptr<Behavior> move1_;
    std::shared_ptr<Behavior> move2_;
    EffectConfig effectconfig_;

    float v1_=-20;
    float v2_=30;
    float v2final_=30;
    float a_=0.5;

    int score_=0;

private:
    void setEffectConfig();
public:
    Drop(const sf::Texture &texture);
    Drop(const sf::Texture &texture,Resource* resource,YellowPage* yellowpage);
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    void setType(DropType type);
    DropType getType();
    void setPhase(int phase);
    void setMove(std::shared_ptr<Behavior> move1,std::shared_ptr<Behavior> move2);
    void markDead();
    int getGetbox_r();
    bool isDead();
    bool isGot();
    void setScore(int score);

    void update();
    void drawtexture(sf::RenderTexture& texture) override;
    void score();
};