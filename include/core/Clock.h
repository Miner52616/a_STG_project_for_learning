#pragma once

class Clock
{
private:
    long long int target_frame_;
    long long int current_frame_;
public:
    Clock(long long int target_frame);
    bool get_condition();
    void count();
    void reset();
};