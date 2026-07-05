#pragma once
#include <functional>

class Batch;

class BatchConfig
{
public:
    std::function<void(Batch*)> update_func_=[](Batch*){};
    int target_time_=1;
    int target_time2_=1;
    int target_time3_=1;
};