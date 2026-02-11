#pragma once
#include "phases/Phase.h"

class EnemyManager;

class TimePhase:public Phase
{
protected:
    int frame_;
    int target_frame_;
    
public:
    TimePhase(std::shared_ptr<Resourse> resourse,int target_frame);

protected:
    void frame_forward();
    bool isTimeup();
};