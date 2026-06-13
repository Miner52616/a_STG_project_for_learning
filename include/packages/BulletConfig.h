#pragma once
#include <SFML/Graphics.hpp>
#include "ui/Frame.h"
#include "core/Clock.h"
#include "packages/EffectConfig.h"

enum BulletClasses
{
    LinearBullet=0,
    PlayerBullet=1,
    DirectBullet1=2,
    DirectBullet2=3,
    PlayerAimBullet=4,
    DirectBullet3=5,
    GravityBullet=6,
    RotateBullet1=7,
    Behavior_DirectBullet1=8,
    PhaseCenterRotateBullet1=9,
    PhaseCenterRotateExpandBullet1=10
};

enum BulletBehavior
{
    Fix=0,
    Rotate=1,
    Direct=2
};

enum BulletSize
{
    Small=0,
    Big=1,
    Large=2
};

class Batch;

class ShareConfig
{
public:
    Batch* batch_=nullptr;
    bool active_=false;
    int* phase_=nullptr;
    bool* trigger_=nullptr;
};

class BulletConfig
{
public:
    float x_=9999;
    float v_=0;
    float a_=0;
    float a2_=0;
    float v2_=0;
    float v3_=0;
    float rotate_angle_=0;//用于移动轨迹会旋转的旋转型子弹的每帧的旋转角度（degree）
    float rotate_angle2_=0;
    float r_=2;
    float r2_=2;
    float damage_=0;
    float angle_=0;//子弹贴图的旋转角度（degree）。注意，0代表子弹贴图朝右
    float angle2_=0;
    float bullet_num_=0;
    bool random_son_direction_=false;
    bool not_clear_=false;
    uint8_t color_alpha_=255;
    Clock clock1_;
    Clock clock2_;
    Clock clock3_;
    sf::Vector2f direction_={0,-1};
    sf::Vector2f direction2_={0,-1};
    sf::Vector2f spawn_point_={0,0};
    sf::Vector2f center_point_={0,0};
    sf::Vector2f center_point2_={0,0};
    sf::Vector2f target_point_={0,0};
    BulletClasses bulletclass_=BulletClasses::PlayerBullet;//子弹类型。每一种子弹都有自己的更新函数
    BulletBehavior bulletbehavior_=BulletBehavior::Fix;//子弹贴图表现方式。将决定子弹贴图的朝向方向会如何更新
    BulletBehavior bulletbehavior2_=BulletBehavior::Fix;
    BulletSize bulletsize_=BulletSize::Small;//子弹大小属性，将影响贴图表的裁切方式
    std::vector<int> bullet_index_={1,1};//子弹贴图裁切的索引，填写前请务必检查不同大小属性子弹的贴图索引方式
    std::vector<int> bullet_index2_={1,1};

    ShareConfig shareconfig_;

    sf::Texture& texture_;//子弹将使用的贴图。现在一般直接给子弹一个贴图表

public:
    BulletConfig(sf::Texture& texture);
    void setClock1(int target);
};