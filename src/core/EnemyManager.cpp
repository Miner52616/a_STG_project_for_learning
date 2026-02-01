#include "core/EnemyManager.h"

EnemyManager::EnemyManager(std::vector<Enemy*> &enemylist):
    enemylist_(enemylist)
{
    ;
}

void EnemyManager::update(long long int frame)
{
    enemylist_update(frame);
}

void EnemyManager::render(sf::RenderWindow& window)
{
    enemylist_render(window);
}

void EnemyManager::enemylist_update(long long int frame)
{
    for(auto it=enemylist_.begin();it!=enemylist_.end();++it)
    {
        (*it)->set_exist(frame);
    }
}

void EnemyManager::enemylist_render(sf::RenderWindow& window)
{
    for(auto it=enemylist_.begin();it!=enemylist_.end();++it)
    {
        (*it)->drawwindow(window);
    }
}