#include "manager/EnemyManager.h"

EnemyManager::EnemyManager(std::vector<Enemy*> &enemylist):
    enemylist_(enemylist)
{
    ;
}

void EnemyManager::update(long long int frame)
{
    enemylist_update(frame);
    clock_count();
}

void EnemyManager::render(sf::RenderWindow& window)
{
    enemylist_render(window);
}

void EnemyManager::clock_count()
{
    for(auto it=enemylist_.begin();it!=enemylist_.end();++it)
    {
        (*it)->clock_count();
    }
}

void EnemyManager::enemylist_update(long long int frame)
{
    for(auto it=enemylist_.begin();it!=enemylist_.end();++it)
    {
        //(*it)->store_position();
        //(*it)->set_exist(frame);
        (*it)->update(frame);
    }
}

void EnemyManager::enemylist_render(sf::RenderWindow& window)
{
    for(auto it=enemylist_.begin();it!=enemylist_.end();++it)
    {
        (*it)->drawwindow(window);
    }
}