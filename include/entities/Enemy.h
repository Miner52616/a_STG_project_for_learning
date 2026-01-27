#pragma once
#include "Entity.h"

class Enemy:public Entity
{
private:
    bool exist_;

    long long int startframe_;
    long long int endframe_;

public:
    Enemy(const sf::Texture &texture);

public:
    void set_exist(bool set);
    void set_exist(long long int frame);
    void set_start_end(long long int start,long long int end);

    void drawwindow(sf::RenderWindow& window) override;
};