#include "lua_packages/LuaPackages.h"
#include "packages/Resource.h"
#include "manager/BulletManager.h"
#include "manager/BatchManager.h"
#include "lua_packages/LuaBatch.h"
#include "packages/AssetsResource.h"

LuaResource::LuaResource(Resource* resource):
    resource_(resource)
{
    ;
}

AssetsResource* LuaResource::getAssetsResource()
{
    return &(resource_->app_);
}

void LuaResource::addBullet(BulletConfig* bulletconfig,EffectConfig* effectconfig)
{
    resource_->bulletmanager_.add_process(bulletconfig,effectconfig);
}

LuaBatch LuaResource::addBatch(BatchConfig* batchconfig)
{
    batchconfig->update_func_=
    [](Batch* batch)
    {
        if(batch->clock_.get_condition())
        {
            switch (batch->phase_)
            {
            case 1:
                {
                    batch->clock_.reset();
                    batch->clock_.set_target(batch->batchconfig_.target_time2_);
                    break;
                }

            case 2:
                {
                    batch->clock_.reset();
                    batch->clock_.set_target(batch->batchconfig_.target_time3_);
                    break;
                }

            case 3:
                {
                    batch->clock_.reset();
                    batch->clock_.set_target(9999);
                    break;
                }
            
            default:
                break;
            }
            batch->phase_++;
        }

        if(batch->clock2_.get_condition())
        {
            batch->clock2_.reset();
            batch->trigger_=true;
        }
        else
        {
            batch->trigger_=false;
        }

        batch->clock_.count();
        batch->clock2_.count();
    };

    Batch* batch=resource_->batchmanager_.add_process(batchconfig);
    return LuaBatch(batch);
}