#pragma once
#include "entities/Drop.h"
#include "packages/DropConfig.h"
#include "manager/DropFactory.h"

class DropManager
{
private:
    std::vector<std::unique_ptr<Drop>> &droplist_;
    DropFactory &dropfactory_;

public:
    DropManager(std::vector<std::unique_ptr<Drop>> &droplist,DropFactory &dropfactory);
    void add_process(std::shared_ptr<DropConfig> dropconfig);
    void update();
    void clear_dead();
    void render(sf::RenderTexture& texture);
};