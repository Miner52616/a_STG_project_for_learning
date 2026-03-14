#pragma once
#include "entities/Drop.h"
#include "packages/DropConfig.h"
#include "packages/Resource.h"
#include "manager/DropFactory.h"

class DropManager
{
private:
    Resource* resource_;
    YellowPage* yellowpage_;
    std::vector<std::unique_ptr<Drop>> &droplist_;
    DropFactory &dropfactory_;

public:
    DropManager(std::vector<std::unique_ptr<Drop>> &droplist,DropFactory &dropfactory);
    void add_process(std::shared_ptr<DropConfig> dropconfig);
    void set_resource(Resource* resource);
    void set_yellowpage(YellowPage* yellowpage);
    void update();
    void clear_dead();
    void render(sf::RenderTexture& texture);
};