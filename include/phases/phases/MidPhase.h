#pragma once
#include "phases/basicphases/TimePhase.h"
#include "manager/EnemyManager.h"
#include "enemies/Enemy1.h"

class Player;

class MidPhase:public TimePhase
{
protected:
    std::vector<std::unique_ptr<Enemy>> enemylist_;
    EnemyManager enemymanager_;

public:
    MidPhase(Resource* resource,YellowPage* yellowpage,int target_frame);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void render(sf::RenderTexture& texture) override;
    void add_enemy(std::unique_ptr<Enemy> enemy);
    void be_damage(float damage) override;
    void ProcessCollision() override;
    sf::Vector2f get_targetposition_for_LeiTan(AimMove2* move) override;
};