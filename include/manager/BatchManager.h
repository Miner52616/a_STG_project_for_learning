#pragma once
#include <vector>
#include <memory>

//同一组弹幕的子弹的共享数据由一个batch进行维护
//子弹有哪些共享数据，batch就要管理哪些共享数据
//Batch基类留有virtual void update()=0接口，每帧将会调用每个batch的update函数
//每次使用时，派生出一个新的batch，并写好如何update
class Batch
{
private:
    int current_batch_num_=0;
    int phase_=1;
    bool trigger_=false;

public:
    int get_current_num();
    virtual void update()=0;
};

class BatchManager
{
private:
    std::vector<std::unique_ptr<Batch>>& batchlist_;

public:
    BatchManager(std::vector<std::unique_ptr<Batch>>& batchlist);
    void add_process(std::unique_ptr<Batch> batch);
    void update();
    void clear_empty();
};