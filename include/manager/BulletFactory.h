#pragma once
#include <memory>
#include <vector>
#include <queue>
#include "entities/Bullet.h"
#include "bullets/LinearBullet.h"
#include "bullets/PlayerBullet.h"
#include "packages/BulletConfig.h"
#include "packages/Resource.h"

class BulletFactory
{
    /*
private:
    std::vector<Bullet> bulletlist_;
    std::queue<int> free_list_;

    void initialize(int size);
*/

public:
    BulletFactory();
    std::unique_ptr<Bullet> create(std::shared_ptr<BulletConfig> bulletconfig);
    /*
    void destory(Bullet* bullet);
    Bullet* getBullet();
    */
};