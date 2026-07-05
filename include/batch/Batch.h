#pragma once
#include <functional>
#include "core/Clock.h"
#include "packages/BatchConfig.h"

class BulletConfig;

//同一组弹幕的子弹的共享数据由一个batch进行维护
//子弹有哪些共享数据，batch就要管理哪些共享数据
//batch的update函数在创建batch时确定。每次创建时写好更新函数lambda，然后将其复制给batch
class Batch
{
private:
    int current_batch_num_=0;
    bool add_finish_=false;

public:
    //std::function<void(Batch*)> update_func_;
    BatchConfig batchconfig_;
    Clock clock_;

    int phase_=1;
    bool trigger_=false;

public:
    Batch(const BatchConfig* batchconfig);
    int get_current_num();
    void bundle_config(BulletConfig* config);
    void add_bullet();
    bool get_add_finished();
    void set_add_finished();
    void decreace_bullet();
    void update();
};

void copyBatchConfig(BatchConfig* copy,const BatchConfig* origin);