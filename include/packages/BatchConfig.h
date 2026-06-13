#pragma once
#include <functional>
#include "batch/Batch.h"

class BatchConfig
{
public:
    std::function<void(Batch*)> update_func_=[](Batch*){};
    long long int target_time_=1;
};