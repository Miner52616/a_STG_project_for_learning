#pragma once
#include "behaviors/Behavior.h"

class Entity;
class Overlay;

class MarkDead:public Behavior
{
private:
    Overlay* overlay_;
    Clock delay_time_;

public:
    MarkDead(Overlay* overlay);
    void update() override;
    void setTargetTime(int time);
};