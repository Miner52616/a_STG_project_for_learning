#pragma once
#include "core/application.h"
#include "entities/Player.h"
#include "entities/Bullet.h"

class BulletManager
{
private:
    application &app_;
    std::vector<std::unique_ptr<Bullet>> bulletlist_;

public:
    BulletManager(application &app);
    void add_process(std::unique_ptr<Bullet> bullet);
    void update();
    void render(sf::RenderWindow& window);

private:
    void bulletlist_update();
    void bulletlist_render(sf::RenderWindow& window);
};