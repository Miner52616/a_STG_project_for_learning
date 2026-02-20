#pragma once
#include "core/application.h"
#include "entities/Player.h"
#include "entities/Bullet.h"
#include "bullets/LinearBullet.h"
#include "bullets/PlayerBullet.h"
#include "packages/BulletConfig.h"
#include "manager/BulletFactory.h"

class BulletManager
{
private:
    application &app_;
    std::vector<std::unique_ptr<Bullet>> &bulletlist_;
    BulletFactory &bulletfactory_;

public:
    BulletManager(application &app,std::vector<std::unique_ptr<Bullet>> &bulletlist,BulletFactory &bulletfactory);
    void add_process(std::unique_ptr<Bullet> bullet);
    void add_process(std::shared_ptr<BulletConfig> bulletconfig);
    void update();
    void clear();
    void render(sf::RenderWindow& window);
    void render(sf::RenderTexture& texture);

private:
    void bulletlist_update();
    void bulletlist_render(sf::RenderWindow& window);
};