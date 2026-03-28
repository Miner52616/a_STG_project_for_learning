#pragma once
#include <memory>
#include <vector>
#include "packages/DropConfig.h"
#include "packages/Resource.h"
#include "packages/YellowPage.h"

class Drop;

class DropFactory
{
private:
    Resource* resource_;
    YellowPage* yellowpage_;

public:
    void set_Resourse(Resource* resource);
    void set_YellowPage(YellowPage* yellowpage);
    std::unique_ptr<Drop> create(DropConfig* dropconfig);
};