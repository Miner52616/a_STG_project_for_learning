#pragma once
#include "phases/basicphases/TimePhase.h"
#include "core/Clock.h"
#include "behaviors/Behavior.h"
#include "overlays/overlays/TextOverlay.h"
#include "ui/NumLine1.h"

class Player;
class Boss;

class SpellPhase:public TimePhase
{
protected:
    Boss* boss_;
    Clock moveclock_;
    Clock shootclock_;
    sf::Vector2f nextposition_;
    std::vector<std::unique_ptr<Behavior>> behaviorlist_;
    sf::RectangleShape HPline_;
    float fullHP_;
    float HP_;
    bool voidspell_;
    TextOverlay spellname_;
    NumLine1 timer_;

public:
    SpellPhase(Resource* resource,YellowPage* yellowpage,int target_frame);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void render(sf::RenderTexture& texture) override;
    void addBehavior(std::unique_ptr<Behavior> behavior);
    void setHP(float HP);
    void be_damage(float damage) override;
    void ProcessCollision() override;
    void setBoss(Boss* boss);
    void setVoidSpell(bool isvoid);
    void setTextName(const std::string text);
    void setTextPosition(sf::Vector2f position);
    void setTargetFrame(int frame);
    sf::Vector2f get_targetposition_for_LeiTan(AimMove2* move) override;
    sf::Vector2f get_closest_target(sf::Vector2f position);
};