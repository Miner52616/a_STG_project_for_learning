#pragma once
#include <SFML/Graphics.hpp>
#include "core/Clock.h"
#include "packages/Resource.h"

class Behavior
{
protected:
    std::shared_ptr<Resource> resource_;
    Clock clock_;

public:
    Behavior();
    virtual void update()=0;
    void set_target(long long int target_frame);
    void set_resource(std::shared_ptr<Resource> resource);
};