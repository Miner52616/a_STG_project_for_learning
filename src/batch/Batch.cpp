#include "batch/Batch.h"
#include "packages/BulletConfig.h"

Batch::Batch(std::function<void(Batch*)> update_func):
    update_func_(update_func),
    current_batch_num_(0),
    add_finish_(false),
    clock_(0),
    phase_(1),
    trigger_(false)
{
    clock_.reset();
}

int Batch::get_current_num()
{
    return current_batch_num_;
}

void Batch::bundle_config(BulletConfig* config)
{
    config->shareconfig_.active_=true;
    config->shareconfig_.phase_=&phase_;
    config->shareconfig_.trigger_=&trigger_;
    config->shareconfig_.batch_=this;
}

void Batch::add_bullet()
{
    current_batch_num_++;
}

bool Batch::get_add_finished()
{
    return add_finish_;
}

void Batch::set_add_finished()
{
    add_finish_=true;
}

void Batch::decreace_bullet()
{
    current_batch_num_--;
}

void Batch::update()
{
    update_func_(this);
}