#pragma once

class Batch;
class BulletConfig;

class LuaBatch
{
private:
    Batch* batch_;

public:
    LuaBatch(Batch* batch);
    void bundle_config(BulletConfig* config);
    void set_add_finished();
};