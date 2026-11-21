#include "lua_packages/LuaBatch.h"
#include "batch/Batch.h"

LuaBatch::LuaBatch(Batch* batch):
    batch_(batch)
{
    ;
}

void LuaBatch::bundle_config(BulletConfig* config)
{
    batch_->bundle_config(config);
}

void LuaBatch::set_add_finished()
{
    batch_->set_add_finished();
}