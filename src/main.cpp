#include "core/Application.h"

//主程序入口
int main()
{
    Application app;
    
    app.run();
    /*
    //程序主循环，每帧由app进行相同操作
    while(app.isRunning())
    {
        app.processEvent();
        app.update();
        app.render();
        app.end_operation(); 
    }
        */

    return 52616;
}