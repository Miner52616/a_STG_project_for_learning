#pragma once
#include <memory>
#include <vector>
#include <queue>
#include "entities/Bullet.h"
#include "bullets/LinearBullet.h"
#include "bullets/PlayerBullet.h"
#include "packages/BulletConfig.h"
#include "packages/Resource.h"
#include "packages/YellowPage.h"

class BulletFactory
{
    
private:
    application& app_;
    Resource* resource_;
    YellowPage* yellowpage_;

    int poolsize_=3000;
    std::vector<Bullet> bulletlist_;
    std::queue<int> free_list_;

    void initialize(int size);


public:
    BulletFactory(application& app);
    void setResource(Resource* resource);
    void setYellowPage(YellowPage* yellowpage);
    int getPoolSize();

    Bullet* create(std::shared_ptr<BulletConfig> bulletconfig);

    void destroy(Bullet* bullet);
    Bullet* getBullet();
};