#include "behaviors/behaviors/BasicShooter.h"
#include "mathematics/mathematics.h"
#include "manager/BulletFactory.h"
#include "manager/BulletManager.h"

ShootLine::ShootLine(Entity* entity,Resource* resource,YellowPage* yellowpage,BulletConfig* bulletconfig,EffectConfig* effectconfig):
    Behavior(resource,yellowpage),entity_(entity),bulletconfig_(bulletconfig/*bulletconfig->texture_*/),effectconfig_(effectconfig),
    draw_clock_(9999),
    draw_delay_clock_(0),
    shoot_clock_(2),
    start_position_({0,0}),
    line_direction_({0,-1}),
    gap_(1),
    bullet_num_(10),
    current_position_(start_position_),
    current_num_(1)
{
    //copyconfig(&bulletconfig_,bulletconfig);
}

void ShootLine::setDirection(sf::Vector2f direction)
{
    line_direction_=normalize(direction);
}

void ShootLine::setStartPosition(sf::Vector2f position)
{
    start_position_=position;
    current_position_=start_position_;
}

void ShootLine::setBulletNum(int num)
{
    bullet_num_=num;
}

void ShootLine::setDrawClock(long long int target)
{
    draw_clock_.set_target(target);
    draw_clock_.reset();
}

void ShootLine::setShootClock(long long int target)
{
    shoot_clock_.set_target(target);
    shoot_clock_.reset();
}

void ShootLine::setDelay(long long int target)
{
    draw_delay_clock_.set_target(target);
    draw_delay_clock_.reset();
}

void ShootLine::setReady()
{
    draw_clock_.set_ready();
}

void ShootLine::reset()
{
    draw_clock_.reset();
    draw_delay_clock_.reset();
    shoot_clock_.reset();
}

void ShootLine::setGap(float gap)
{
    gap_=gap;
}

void ShootLine::setBulletConfig(BulletConfig* bulletconfig)
{
    //copyconfig(&bulletconfig_,bulletconfig);
    bulletconfig_=bulletconfig;
}

void ShootLine::update()
{
    if(draw_clock_.get_condition())
    {
        if(draw_delay_clock_.get_condition())
        {
            if(current_num_<=bullet_num_)
            {
                if(shoot_clock_.get_condition())
                {
                    shoot_clock_.reset();
                    bulletconfig_->spawn_point_=current_position_;
                    resource_->bulletmanager_.add_process(bulletconfig_,effectconfig_);
                    current_position_=current_position_+gap_*line_direction_;
                    current_num_++;
                }
            }
            else
            {
                current_num_=1;
                draw_clock_.reset();
                draw_delay_clock_.reset();
            }
        }
        draw_delay_clock_.count();
    }
    shoot_clock_.count();
    draw_clock_.count();
}