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
    std::vector<Bullet*> &bulletlist_;
    BulletFactory &bulletfactory_;
    Resource* resource_;

public:
    BulletManager(application &app,std::vector<Bullet*> &bulletlist,BulletFactory &bulletfactory);
    //void add_process(std::unique_ptr<Bullet> bullet);
    void add_process(BulletConfig* bulletconfig,EffectConfig* effectconfig);
    void setResource(Resource* resource);
    void update();
    void clear();
    void clear_enemybullet();
    void clear_common_enemybullet();
    void render(sf::RenderWindow& window);
    void render(sf::RenderTexture& texture);

private:
    void bulletlist_update();
    void bulletlist_render(sf::RenderWindow& window);
};