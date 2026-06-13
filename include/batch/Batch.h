#pragma once
#include <functional>
#include "core/Clock.h"

class BulletConfig;

//同一组弹幕的子弹的共享数据由一个batch进行维护
//子弹有哪些共享数据，batch就要管理哪些共享数据
//Batch基类留有virtual void update()=0接口，每帧将会调用每个batch的update函数
//每次使用时，派生出一个新的batch，并写好如何update
//也考虑和子弹类似，使用函数表进行更新。这样可以引入batch对象池。可能有奇效？
class Batch
{
private:
    int current_batch_num_=0;
    bool add_finish_=false;

    std::function<void(Batch*)> update_func_;
public:
    Clock clock_;

    int phase_=1;
    bool trigger_=false;

public:
    Batch(std::function<void(Batch*)> update_func);
    int get_current_num();
    void bundle_config(BulletConfig* config);
    void add_bullet();
    bool get_add_finished();
    void set_add_finished();
    void decreace_bullet();
    void update();
};