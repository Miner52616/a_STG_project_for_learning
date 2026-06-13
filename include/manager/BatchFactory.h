#pragma once
#include "packages/BatchConfig.h"

class BatchFactory
{
public:
    std::unique_ptr<Batch> create(BatchConfig* batchconfig);
};