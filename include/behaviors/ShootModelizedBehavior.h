#pragma once
#include "behaviors/ShootBehavior.h"

//模式化描述弹幕的大体框架
//派生后可以仿照这个框架，将stateUpdate和eventUpdate如这里分割update一般继续分割
class ShootModelizedBehavior:public ShootBehavior
{
protected:
    Clock delayclock_;
    Clock loopclock_;
protected:
    virtual void stateUpdate()=0;
    virtual void eventUpdate()=0;
protected:
    //以下为预留的可能可以用于将弹幕描述代码分类打包到一起的函数接口
    //可以尝试将代码分类到以下函数中，使得弹幕代码描述更加简洁和明确
    virtual void configUpdate()=0;

public:
    ShootModelizedBehavior(Resource* resource,YellowPage* yellowpage);
    void update() override;
};