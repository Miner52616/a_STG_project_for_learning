#pragma once
#include "batch/Batch.h"
#include "packages/BatchConfig.h"
#include "manager/BatchFactory.h"
#include <vector>
#include <memory>
#include <functional>

/*
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

    int phase_=1;
    bool trigger_=false;

    std::function<void(Batch&)> update_func_;

public:
    int get_current_num();
    virtual void update()=0;
};
*/

class BatchManager
{
private:
    BatchFactory& batchfactory_;
    std::vector<std::unique_ptr<Batch>>& batchlist_;

public:
    BatchManager(std::vector<std::unique_ptr<Batch>>& batchlist,BatchFactory& batchfactory);
    //void add_process(std::unique_ptr<Batch> batch);
    Batch* add_process(BatchConfig* batchconfig);
    void update();
    void clear_empty();
    void set_all_finished();
};