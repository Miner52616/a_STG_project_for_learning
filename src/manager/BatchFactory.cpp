#include "manager/BatchFactory.h"
#include "batch/Batch.h"
#include <memory>

std::unique_ptr<Batch> BatchFactory::create(BatchConfig* batchconfig)
{
    std::unique_ptr<Batch> batch;
    batch=std::make_unique<Batch>(batchconfig);
    batch->clock_.set_target(batchconfig->target_time_);

    return std::move(batch);
}