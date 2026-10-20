#include "core/state.h"
#include "core/Application.h"
#include <iostream>

State::State(Application &app):
    app_(app),font_(app.assets_resource_.mainFont_)
{
    ;
}

void State::switchOnOperation()
{
    app_.window_.setFramerateLimit(60);
}

void State::switchOffOperation()
{
    ;
}