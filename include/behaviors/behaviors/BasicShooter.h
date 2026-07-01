#pragma once
#include "behaviors/Behavior.h"
#include "packages/BulletConfig.h"
#include "packages/EffectConfig.h"
#include "core/Clock.h"
#include <functional>

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
    int shoot_times_;//每次发射的子弹数目。每颗子弹发射前都会多执行一遍update_func_
    sf::Vector2f start_position_;
    sf::Vector2f line_direction_;
    float gap_;
    int bullet_num_;

    sf::Vector2f current_position_;
    int current_num_;

    //用于自定义修改位置属性之外的属性
    std::function<void(ShootLine*)> update_func_;

public:
    ShootLine(Entity* entity,Resource* resource,YellowPage* yellowpage,BulletConfig* bulletconfig,EffectConfig* effectconfig);
    void setDirection(sf::Vector2f direction);
    void setStartPosition(sf::Vector2f position);
    void setBulletNum(int num);
    void setDrawClock(long long int target);
    void setShootClock(long long int target);//设置两次发射之间的间隔时间
    void setShootTimes(int times);//设置每次发射子弹的数量
    void setDelay(long long int target);
    void setReady();
    void reset();
    void setGap(float gap);
    void setBulletConfig(BulletConfig* bulletconfig);
    void setUpdateFunction(std::function<void(ShootLine*)> update_func);//不要修改位置属性！
    sf::Vector2f getCurrentPosition();
    BulletConfig* getBulletConfig();
    sf::Vector2f getDirection();

    void update() override;
};

/************************************************** */

