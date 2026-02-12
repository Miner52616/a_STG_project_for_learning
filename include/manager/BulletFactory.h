#pragma once
#include <memory>
#include <vector>
#include "entities/Bullet.h"
#include "bullets/LinearBullet.h"
#include "bullets/PlayerBullet.h"
#include "packages/BulletConfig.h"
#include "packages/Resource.h"

class BulletFactory
{
private:
    //std::vector<std::unique_ptr<Bullet>> bulletlist_;

public:
    //BulletFactory(std::vector<std::unique_ptr<Bullet>> bulletlist);
    std::unique_ptr<Bullet> create(std::shared_ptr<BulletConfig> bulletconfig);
};