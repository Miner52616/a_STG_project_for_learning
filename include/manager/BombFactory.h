#pragma once
#include <memory>
#include <vector>
#include "packages/Resource.h"
#include "packages/YellowPage.h"
#include "packages/BombConfig.h"

class Bomb;

class BombFactory
{
private:
    Resource* resource_;
    YellowPage* yellowpage_;
    
public:
    void set_Resourse(Resource* resource);
    void set_YellowPage(YellowPage* yellowpage);
    std::unique_ptr<Bomb> create(BombConfig* bombconfig);
};