#pragma once

class Resource;
class BulletConfig;
class EffectConfig;
class BatchConfig;
class LuaBatch;

class LuaResource
{
private:
    Resource* resource_;

public:
    LuaResource(Resource* resource_);
    void addBullet(BulletConfig* bulletconfig,EffectConfig* effectconfig);
    LuaBatch addBatch(BatchConfig* batchconfig);
};