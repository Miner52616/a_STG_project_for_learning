#pragma once
#include <SFML/Graphics.hpp>
#include "core/Clock.h"
#include "packages/Resource.h"
#include "packages/YellowPage.h"

class Behavior
{
protected:
    Resource* resource_;
    YellowPage* yellowpage_;
    Clock clock_;

public:
    Behavior();
    virtual void update()=0;
    void set_target(long long int target_frame);
    void set_resource(Resource* resource);
    void set_YellowPage(YellowPage *yellowpage);
};