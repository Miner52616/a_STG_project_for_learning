#pragma once
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"
#include "packages/EffectConfig.h"
#include "core/Clock.h"

class Entity;

class ShootLine:public Behavior
{
private:
    Entity* entity_;
    BulletConfig* bulletconfig_;
    EffectConfig* effectconfig_;

    //有两种使用方法，一种是设定好整体的冷却时间，固定冷却后自动重复执行
    //另一种是将整体冷却时间设定为一个非常大的数，执行时机由外部确定（因为这是一个直线放置弹幕的组件），外部执行时直接设定冷却完成（draw_clock.reset()）
    Clock draw_clock_;//控制整体操作的整个冷却时间
    Clock draw_delay_clock_;//冷却完成后执行操作的延迟时间
    Clock shoot_clock_;//每发子弹的发射间隔时间
    sf::Vector2f start_position_;
    sf::Vector2f line_direction_;
    float gap_;
    int bullet_num_;

    sf::Vector2f current_position_;
    int current_num_;

public:
    ShootLine(Entity* entity,Resource* resource,YellowPage* yellowpage,BulletConfig* bulletconfig,EffectConfig* effectconfig);
    void setDirection(sf::Vector2f direction);
    void setStartPosition(sf::Vector2f position);
    void setBulletNum(int num);
    void setDrawClock(long long int target);
    void setShootClock(long long int target);
    void setDelay(long long int target);
    void setReady();
    void reset();
    void setGap(float gap);
    void setBulletConfig(BulletConfig* bulletconfig);

    void update() override;
};

/************************************************** */

