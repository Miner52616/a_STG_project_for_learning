#pragma once
#include "phases/basicphases/TimePhase.h"
#include "manager/EnemyManager.h"
#include "enemies/Enemy1.h"

class Player;

class MidPhase:public TimePhase
{
protected:
    std::vector<Enemy*> enemylist_;
    EnemyManager enemymanager_;
//    std::shared_ptr<Enemy1> enemy1_;

public:
    MidPhase(Resource* resource,YellowPage* yellowpage,int target_frame);
    void update() override;
    void render(sf::RenderWindow& window) override;
    void render(sf::RenderTexture& texture) override;
    void add_enemy(Enemy* enemy);
    void be_damage(float damage) override;
    void ProcessCollision() override;
};