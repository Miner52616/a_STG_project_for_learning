#pragma once
#include <memory>
#include <vector>
#include "packages/DropConfig.h"

class Drop;

class DropFactory
{
public:
    std::unique_ptr<Drop> create(std::shared_ptr<DropConfig> dropconfig);
};