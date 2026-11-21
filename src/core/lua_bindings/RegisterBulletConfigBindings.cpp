#include "core/LuaBindings.h"
#include "packages/BulletConfig.h"

void registerBulletConfigBindings(sol::state& lua)
{
    lua.new_enum<BulletClasses>
    (   
        "BulletClasses",
        {
            {"LinearBullet",BulletClasses::LinearBullet},
            {"PlayerBullet",BulletClasses::PlayerBullet},
            {"DirectBullet1",BulletClasses::DirectBullet1},
            {"DirectBullet2",BulletClasses::DirectBullet2},
            {"PlayerAimBullet",BulletClasses::PlayerAimBullet},
            {"DirectBullet3",BulletClasses::DirectBullet3},
            {"GravityBullet",BulletClasses::GravityBullet},
            {"RotateBullet1",BulletClasses::RotateBullet1},
            {"Behavior_DirectBullet1",BulletClasses::Behavior_DirectBullet1},
            {"PhaseCenterRotateBullet1",BulletClasses::PhaseCenterRotateBullet1},
            {"PhaseCenterRotateExpandBullet1",BulletClasses::PhaseCenterRotateExpandBullet1},
            {"VoidUpdate",BulletClasses::VoidUpdate}
        }
    );

    lua.new_enum<BulletBehavior>
    (
        "BulletBehavior",
        {
            {"Fix",BulletBehavior::Fix},
            {"Rotate",BulletBehavior::Rotate},
            {"Direct",BulletBehavior::Direct}
        }
    );

    lua.new_enum<BulletSize>
    (
        "BulletSize",
        {
            {"Small",BulletSize::Small},
            {"Big",BulletSize::Big},
            {"Large",BulletSize::Large}
        }
    );

    lua.new_usertype<BulletConfig>
    (
        "BulletConfig",
        sol::constructors<BulletConfig(sf::Texture& texture)>(),
        "x_",&BulletConfig::x_,
        "v_",&BulletConfig::v_,
        "a_",&BulletConfig::a_,
        "a2_",&BulletConfig::a2_,
        "v2_",&BulletConfig::v2_,
        "v3_",&BulletConfig::v3_,
        "rotate_angle_",&BulletConfig::rotate_angle_,
        "rotate_angle2_",&BulletConfig::rotate_angle2_,
        "r_",&BulletConfig::r_,
        "r2_",&BulletConfig::r2_,
        "damage_",&BulletConfig::damage_,
        "angle_",&BulletConfig::angle_,
        "angle2_",&BulletConfig::angle2_,
        "bullet_num_",&BulletConfig::bullet_num_,
        "random_son_direction_",&BulletConfig::random_son_direction_,
        "not_clear_",&BulletConfig::not_clear_,
        "self_phase_",&BulletConfig::self_phase_,
        "color_alpha_",&BulletConfig::color_alpha_,
        "clock1_",&BulletConfig::clock1_,
        "clock2_",&BulletConfig::clock2_,
        "clock3_",&BulletConfig::clock3_,
        "direction_",&BulletConfig::direction_,
        "direction2_",&BulletConfig::direction2_,
        "spawn_point_",&BulletConfig::spawn_point_,
        "center_point_",&BulletConfig::center_point_,
        "center_point2_",&BulletConfig::center_point2_,
        "target_point_",&BulletConfig::target_point_,
        "target_point2_",&BulletConfig::target_point2_,
        "target_point3_",&BulletConfig::target_point3_,
        "bulletclass_",&BulletConfig::bulletclass_,
        "bulletbehavior_",&BulletConfig::bulletbehavior_,
        "bulletbehavior2_",&BulletConfig::bulletbehavior2_,
        "bulletsize_",&BulletConfig::bulletsize_,
        "bullet_index_",&BulletConfig::bullet_index_,
        "bullet_index2_",&BulletConfig::bullet_index2_
    );
}