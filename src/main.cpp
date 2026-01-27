#include "core/application.h"

int main()
{
    application app;

    while(app.IsRunning())
    {
        app.ProcessEvent();
        app.Update();
        app.Render();
    }

    return 0;
}