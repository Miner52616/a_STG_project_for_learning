#include "manager/BatchManager.h"
#include <algorithm>

int Batch::get_current_num()
{
    return current_batch_num_;
}

/********************************************* */

BatchManager::BatchManager(std::vector<std::unique_ptr<Batch>>& batchlist):
    batchlist_(batchlist)
{
    batchlist_.reserve(200);
}

void BatchManager::add_process(std::unique_ptr<Batch> batch)
{
    batchlist_.emplace_back(std::move(batch));
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
                if((batch->get_current_num())==0)
                {
                    return true;
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