#pragma once
#include <memory>
#include <vector>
#include "packages/DropConfig.h"
#include "packages/Resource.h"

class Drop;

class DropFactory
{
private:
    std::shared_ptr<Resource> resource_;

public:
    void set_Resourse(std::shared_ptr<Resource> resource);
    std::unique_ptr<Drop> create(std::shared_ptr<DropConfig> dropconfig);
};