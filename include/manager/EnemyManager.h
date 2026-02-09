#pragma once
#include "entities/Enemy.h"

class EnemyManager
{
private:
    std::vector<std::unique_ptr<Enemy>> &enemylist_;

public:
    EnemyManager(std::vector<std::unique_ptr<Enemy>> &enemylist);
    void add_process(std::unique_ptr<Enemy> enemy);
    void update(long long int frame);
    void render(sf::RenderWindow& window);
    void clear_dead();
    void clear();
    void clock_count();
private:
    void enemylist_update(long long int frame);
    void enemylist_render(sf::RenderWindow& window);
};