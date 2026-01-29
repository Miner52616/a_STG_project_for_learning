#include "core/application.h"

//主程序入口
int main()
{
    application app;
    
    //程序主循环，每帧由app进行相同操作
    while(app.IsRunning())
    {
        app.ProcessEvent();
        app.Update();
        app.Render();
        app.End_operation(); 
    }

    return 0;
}