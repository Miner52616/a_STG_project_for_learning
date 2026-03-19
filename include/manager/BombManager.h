#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "manager/BombFactory.h"
#include "packages/Resource.h"

class Bomb;

class BombManager
{
private:

    Resource* resource_;
    std::vector<std::unique_ptr<Bomb>> &bomblist_;
    BombFactory &bombfactory_;

    
public:
    BombManager(std::vector<std::unique_ptr<Bomb>> &bomblist_,BombFactory &bombfactory);
    void add_process(BombConfig* bombconfig);
    void update();
    void clear_dead();
    void ProcessCollision();
    void render(sf::RenderTexture& texture);
    void set_Resource(Resource* resource);
};