#pragma once
#include "Entity.h"
#include "behaviors/Behavior.h"

class BulletManager;

//敌人
class Enemy:public Entity
{
protected:
    bool exist_;

    long long int startframe_;
    long long int endframe_;
    std::vector<std::shared_ptr<Behavior>> behaviorlist_;
    float HP_;
    bool dead_;

    BulletManager &bulletmanager_;

public:
    Enemy(application &app,const sf::Texture &texture,BulletManager &bulletmanager);  //初始化资源引用，默认敌人设置

public:
    void set_exist(bool set);  //直接设置敌人是否出现
    void set_exist(long long int frame);  //输入游戏进程此时帧，根据帧判断敌人是否出现
    void set_start_end(long long int start,long long int end);  //设置敌人会出现的帧范围
    bool isExist();
    long long int getStartFrame();
    long long int getEndFrame();
    void setHP(float HP);
    void be_damage(float damage);
    void markDead();
    bool isDead();
    void addBehavior(std::shared_ptr<Behavior> behavior);

    virtual void update(long long int frame);
    virtual void clock_count();
    void drawwindow(sf::RenderWindow& window) override;  //渲染敌人至屏幕
};