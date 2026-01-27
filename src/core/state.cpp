#include "core/state.h"
#include "core/application.h"
#include <iostream>

State::State(application &app):
    app_(app),font_(app.mainFont_)
{
    ;
}