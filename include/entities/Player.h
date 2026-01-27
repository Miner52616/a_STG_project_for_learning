#pragma once
#include "Entity.h"

struct Rate
{
    int frame;
    int current;
};
class Player:public Entity
{
private:
    bool hitbox_exist_;
    int speed_;
    Rate rate_;
    bool request_shoot_;

public:
    bool Handle_shoot_request();

public:
    Player(const sf::Texture &texture);

    void Player_update();
    void drawwindow(sf::RenderWindow& window) override;
};