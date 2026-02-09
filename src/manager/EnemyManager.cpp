#include "manager/EnemyManager.h"

EnemyManager::EnemyManager(std::vector<std::unique_ptr<Enemy>> &enemylist):
    enemylist_(enemylist)
{
    ;
}

void EnemyManager::add_process(std::unique_ptr<Enemy> enemy)
{
    enemylist_.emplace_back(std::move(enemy));
}

void EnemyManager::update(long long int frame)
{
    enemylist_update(frame);
    //clock_count();
}

void EnemyManager::render(sf::RenderWindow& window)
{
    enemylist_render(window);
}

void EnemyManager::clear_dead()
{
    enemylist_.erase
    (
        std::remove_if
        (
            enemylist_.begin(),enemylist_.end(),
            [this](const std::unique_ptr<Enemy> &enemy)
            {
                if(enemy->isDead())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        ),
        enemylist_.end()
    );
}

void EnemyManager::clear()
{
    enemylist_.clear();
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