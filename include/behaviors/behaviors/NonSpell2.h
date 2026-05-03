#pragma once
#include "behaviors/ShootBehavior.h"
#include "packages/BulletConfig.h"
#include "core/Clock.h"

class Entity;

//与风刃一起的星星弹幕
class NonSpell2_1:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;

    int bullet_num_;
    sf::Vector2f start_position_;
    sf::Vector2f set_direction_;
    sf::Vector2f bullet_direction_;
    float gap_;

    Clock start_clock_;
    Clock shoot_clock_;
private:
    void setBulletConfig();
    //void rotate();
public:
    NonSpell2_1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

//只在开局发射一次的星星弹幕
//也被改良为单独发射星星的弹幕
class NonSpell2_2:public ShootBehavior
{
protected:
    Entity* entity_;
    BulletConfig bulletconfig_;

    int bullet_num_;//星星的一条边有几颗子弹
    int group_num_;//一共有多少颗星星
    float gap_;//星星的边的子弹的间隔
    int delaytime_;//星星整体向指定位置发射的延迟时间（开始静止的时间），时间从开始画星计时，delaytime内务必要保证把星画完
    bool get_center;//画星仅获取一次center保证画星不会受到boss移动影响
    float rotate_degree_;//每条边上相邻两个子弹的直线轨迹角度，调整可调整扇形展开大小

    sf::Vector2f center_;
    sf::Vector2f start_position_;
    sf::Vector2f set_direction_;
    sf::Vector2f bullet_direction_;
    sf::Vector2f bullet_direction2_;
    std::vector<sf::Vector2f> direction_list;

    Clock shoot_clock_;
    Clock shoot_num_;
    Clock shoot_num2_;

protected:
    void setBulletConfig();
    void reset();
public:
    NonSpell2_2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class NonSpell2_2_1:public NonSpell2_2
{
public:
    NonSpell2_2_1(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class NonSpell2_2_2:public NonSpell2_2
{
private:
    Clock start_clock_;

public:
    NonSpell2_2_2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

//单独发射星星的弹幕，继承自画星星改良型
class NonSpell2_1_2:public NonSpell2_2
{
private:
    Clock start_clock_;
    Clock son_shoot_clock_;
    bool son_left_right_;

public:
    NonSpell2_1_2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

//风刃弹幕
class NonSpell2_3:public ShootBehavior
{
private:
    Entity* entity_;
    BulletConfig bulletconfig_;
    std::vector<int> left_right_;

    int bullet_num_;
    sf::Vector2f start_position_;
    sf::Vector2f set_direction_;
    sf::Vector2f bullet_direction_;
    float gap_;

    Clock start_clock_;
    Clock shoot_clock_;
private:
    void setBulletConfig();
    //void rotate();
public:
    NonSpell2_3(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};

class NonSpell2:public Behavior
{
private:
    NonSpell2_1_2 nonspell2_1_2;
    NonSpell2_2_1 nonspell2_2_1;
    NonSpell2_2_2 nonspell2_2_2;
    NonSpell2_3 nonspell2_3;

public:
    NonSpell2(Entity* entity,Resource* resource,YellowPage* yellowpage);
    void update() override;
};