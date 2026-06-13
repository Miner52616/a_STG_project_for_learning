#include "manager/BatchManager.h"
#include <algorithm>
#include <iostream>

/********************************************* */

BatchManager::BatchManager(std::vector<std::unique_ptr<Batch>>& batchlist,BatchFactory& batchfactory):
    batchlist_(batchlist),batchfactory_(batchfactory)
{
    batchlist_.reserve(200);
}

/*
void BatchManager::add_process(std::unique_ptr<Batch> batch)
{
    batchlist_.emplace_back(std::move(batch));
}
    */

Batch* BatchManager::add_process(BatchConfig* config)
{
    std::unique_ptr<Batch> batch=batchfactory_.create(config);
    Batch* address=batch.get();
    batchlist_.emplace_back(std::move(batch));

    return address;
}

void BatchManager::update()
{
    for(auto it=batchlist_.begin();it!=batchlist_.end();++it)
    {
        (*it)->update();
    }
}

void BatchManager::clear_empty()
{
    batchlist_.erase
    (
        std::remove_if
        (
            batchlist_.begin(),batchlist_.end(),
            [this](const std::unique_ptr<Batch>& batch)
            {
                if(batch->get_add_finished())
                {
                    if((batch->get_current_num())<=0)
                    {
                        std::cout<<"Batch clear"<<std::endl;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        ),
        batchlist_.end()
    );
}

void BatchManager::set_all_finished()
{
    for(auto it=batchlist_.begin();it!=batchlist_.end();++it)
    {
        (*it)->set_add_finished();
    }
}