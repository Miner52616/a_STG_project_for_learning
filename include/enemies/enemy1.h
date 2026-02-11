#pragma once
#include "entities/Enemy.h"
#include "core/Clock.h"

class Player;

class Enemy1:public Enemy
{
    sf::Vector2f nextposition_;
    std::shared_ptr<Player> player_;
    Clock moveclock_;
    Clock shootclock_;
public:
    Enemy1(const sf::Texture &texture,std::shared_ptr<Player> player);
public:
    void update(long long int frame) override;
    void clock_count();

private:
    void move();
};