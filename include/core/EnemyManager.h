#pragma once
#include "entities/Enemy.h"

class EnemyManager
{
private:
    std::vector<Enemy*> &enemylist_;

public:
    EnemyManager(std::vector<Enemy*> &enemylist);
    void update(long long int frame);
    void render(sf::RenderWindow& window);
private:
    void enemylist_update(long long int frame);
    void enemylist_render(sf::RenderWindow& window);
};