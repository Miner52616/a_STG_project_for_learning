#pragma once
#include "core/application.h"
#include "entities/Player.h"
#include "entities/Bullet.h"

class BulletManager
{
private:
    application &app_;
    Player &player_;
    std::vector<std::unique_ptr<Bullet>> playerbulletlist_;

public:
    BulletManager(application &app,Player &player);
    void update();
    void render(sf::RenderWindow& window);

private:
    void playerbulletlist_update();
    void playerbulletlist_render(sf::RenderWindow& window);

private:
    void playerbulletlist_clear();
    void playerbulletlist_move();
    void playerbulletlist_add();
};